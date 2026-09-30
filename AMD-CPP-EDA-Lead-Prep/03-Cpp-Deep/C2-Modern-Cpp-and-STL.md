# C2: Modern C++ (11→20) & STL Internals

> AMD ★★★: smart pointers (and their internals), move semantics, Rule of 3/5, RAII, lambdas. ★★: STL container internals, templates vs virtual.

---

## 1. Value categories & move semantics ★★★
**30-sec:** "An lvalue has identity (a name, an address); an rvalue is a temporary. Move semantics let a type **steal** resources from an rvalue instead of deep-copying: a move ctor `T(T&&)` takes the pointer and nulls the source. `std::move` doesn't move anything. It's just a `static_cast<T&&>` that *permits* moving. After a move the source is in a *valid but unspecified* state (it can be destroyed or reassigned)."

- `T&&` in a **non-template** context = an rvalue reference. In `template<class T> f(T&& x)` or `auto&&` = a **forwarding (universal) reference**. It binds to anything and preserves the category via **reference collapsing** (`& &&` → `&`, `&& &&` → `&&`).
- `std::forward<T>(x)` = conditional move: moves only if the caller passed an rvalue. Use it for perfect forwarding (`emplace_back`, `make_unique`).
- **Named rvalue references are lvalues:** inside `f(T&& x)`, `x` is an lvalue → you need `std::move(x)` to move it on.
- `std::move` on a **const** object → selects the copy ctor (a silent copy).
- **Don't** `return std::move(local);`. It blocks NRVO. Plain `return local;` is either elided or implicitly moved.

## 2. Copy elision / RVO ★★
- C++17: **guaranteed** elision for prvalues: `T f() { return T(args); }` and `T x = T(...)` construct directly in place (T needn't even be movable).
- NRVO (named local): permitted, not guaranteed; common in practice. If not elided → implicit move.
- The practical rule: **return by value**, pass by `const&` (or by value + move for "sink" parameters you'll store).

## 3. Rule of 0 / 3 / 5 ★★★
| Rule | Statement |
|---|---|
| **0** | Classes that don't manage resources directly declare **none** of the special members. Use RAII members (`vector`, `string`, `unique_ptr`). *The goal.* |
| **3** | If you need a custom dtor, copy ctor or copy assign, you probably need all three (C++98). |
| **5** | Add the move ctor + move assign (C++11). Declaring any of dtor/copy suppresses the implicit moves → the class silently copies. |

```cpp
class Buffer {                                           // Rule of 5, done right
    size_t n_ = 0; int* p_ = nullptr;
public:
    explicit Buffer(size_t n) : n_(n), p_(new int[n]{}) {}
    ~Buffer() { delete[] p_; }
    Buffer(const Buffer& o) : n_(o.n_), p_(new int[o.n_]) { std::copy(o.p_, o.p_ + n_, p_); }
    Buffer(Buffer&& o) noexcept : n_(std::exchange(o.n_, 0)), p_(std::exchange(o.p_, nullptr)) {}
    Buffer& operator=(Buffer o) noexcept { swap(o); return *this; }   // copy-and-swap: handles copy AND move, strong guarantee
    void swap(Buffer& o) noexcept { std::swap(n_, o.n_); std::swap(p_, o.p_); }
};
```
- **Mark move ops `noexcept`**, or `vector` will **copy** during reallocation (`move_if_noexcept` for the strong guarantee).
- Self-assignment safety: copy-and-swap handles it for free.

## 4. RAII ★★★
**30-sec:** "Resource Acquisition Is Initialization: tie a resource's lifetime to an object's scope. The constructor acquires and the destructor releases. Because destructors run during stack unwinding, you get exception safety and no leaks on early returns. Examples: `unique_ptr`, `lock_guard`, `fstream`, `vector`, and scope guards for Tcl interpreter state or temp files."
Lead angle: "I enforce it in reviews: no naked `new`/`delete`, and no manual `lock()`/`unlock()`."

## 5. Smart pointers ★★★ (implementation in P12-D3)
| | `unique_ptr<T>` | `shared_ptr<T>` | `weak_ptr<T>` |
|---|---|---|---|
| Ownership | exclusive, move-only | shared, ref-counted | non-owning observer |
| Size | 1 pointer (with a stateless deleter) | 2 pointers (object + control block) | 2 pointers |
| Cost | zero overhead vs a raw pointer | atomic inc/dec on copy/destroy; control-block allocation | lock() = atomic CAS |
| Use | the **default** for ownership: factories, pimpl, containers of polymorphic objects | genuinely shared lifetime (caches, async callbacks, graph nodes w/o cycles) | break cycles, caches that shouldn't extend lifetime, observers |

Key facts to say:
- `make_unique` / `make_shared`: exception-safe (no leak if another argument throws, pre-C++17) and `make_shared` does **one allocation**.
- `make_shared` downside: the object's memory lives until the last **weak_ptr** is gone.
- `shared_ptr` refcount updates are atomic, so **passing `shared_ptr` by value in hot paths is costly**. Pass `const shared_ptr&` or a raw `T*`/`T&` when not transferring ownership.
- Aliasing constructor: `shared_ptr<Member>(owner, &owner->member)` shares ownership of the whole object.
- Custom deleters: `unique_ptr<FILE, decltype(&fclose)> f(fopen(...), &fclose);` (the deleter is part of unique_ptr's type, but not shared_ptr's).
- `unique_ptr<T[]>` for arrays; prefer `vector`.
- **Never** create two `shared_ptr`s from the same raw pointer (double delete) → use `enable_shared_from_this`.

## 6. Lambdas ★★
- A lambda is an unnamed **closure class** with `operator()`; the captures become data members.
- `[=]` copy, `[&]` reference, `[x, &y]`, `[this]` (captures the pointer!), `[*this]` (C++17 copy of the object), init-capture `[p = std::move(ptr)]` (move-only captures).
- `mutable` lets you modify the by-value captures. Captureless lambdas convert to function pointers.
- Generic lambda `[](auto x)` = a templated `operator()`.
- **Dangling:** returning a lambda that captured locals by reference; storing a `[this]` lambda in a callback that outlives the object (a classic async bug → capture a `weak_ptr`).
- `std::function` = type-erased: may heap-allocate, has indirect-call overhead. Prefer templates / `auto` params for hot callbacks.

## 7. Templates & static polymorphism ★★
- Templates are instantiated per type at compile time → zero-cost abstraction, inlinable; the downside is code bloat and compile time (your 2M-line decoupling story fits here: explicit instantiation, `extern template`, pimpl).
- **CRTP:** `template<class D> struct Base { void run() { static_cast<D*>(this)->impl(); } };` gives compile-time dispatch without a vtable.
- **Virtual vs templates:** runtime flexibility (plugins, heterogeneous containers) vs speed and inlining (hot loops). A mix is common: a type-erased interface outside, templates inside.
- SFINAE → C++20 **concepts** (`template<std::integral T>`, `requires` clauses) for readable constraints and errors.
- Variadic templates + fold expressions: `(std::cout << ... << args);`.
- `if constexpr` for compile-time branching.

## 8. Other modern features to name-drop correctly
`auto` (drops ref/const: use `auto&`/`const auto&`) · `decltype(auto)` · structured bindings · `std::optional` (a maybe-value, no heap) · `std::variant` + `std::visit` (a type-safe union, an alternative to inheritance for closed sets) · `std::string_view` (non-owning, **dangling risk**, not null-terminated) · `std::span` · ranges/views (lazy pipelines) · `constexpr` everything · `std::jthread` (auto-join + stop_token) · coroutines (C++20) · modules (C++20; mention compile-time wins) · `std::format` (C++20) · `std::expected` (C++23).

---

## 9. STL internals ★★ (what "which container and why" really means)

### `std::vector`
- Contiguous; `size`/`capacity`; growth ×2 (libstdc++) or ×1.5 (MSVC) → amortized O(1) `push_back`.
- **Invalidation:** reallocation invalidates everything; `insert`/`erase` invalidate at or after the point.
- `reserve` when the size is known; `shrink_to_fit` is non-binding; `clear` keeps the capacity.
- `emplace_back` constructs in place (useful for non-movable types or avoiding temporaries); for already-constructed objects, `push_back(std::move(x))` is the same.
- `vector<bool>`: bit-packed proxy, not a real container.

### `std::deque`
A map of fixed-size blocks → O(1) push/pop at both ends, random access with double indirection. **References stay valid on push at the ends** (iterators don't). The default underlying container for `stack`/`queue`.

### `std::list` / `forward_list`
Node-based; O(1) insert/erase/splice with an iterator; **iterators stay valid** except for the erased element. Terrible cache behaviour. Use it for LRU and splicing.

### `std::map` / `set` (ordered)
**Red-black tree**: O(log n); ordered iteration; `lower_bound`/`upper_bound`; iterators stable on insert/erase of other elements. Each node is a separate allocation (~32–48 B overhead). C++17 `extract`/`merge` move nodes without reallocation.

### `std::unordered_map` / `set`
**Hash table with separate chaining** (buckets of linked nodes in libstdc++). Avg O(1); `load_factor` > `max_load_factor` (default 1.0) → **rehash** → **invalidates iterators** (not references/pointers to elements). `reserve(n)` avoids rehashes. The worst case O(n) comes from bad hashes. Custom key → specialize `std::hash` or pass a hasher + equality.
Faster alternatives (a lead talking point): open addressing (`absl::flat_hash_map`, `robin_hood`), sorted `vector` + binary search for read-mostly data.

### `std::priority_queue`
A binary heap on a `vector` (`push_heap`/`pop_heap`). No decrease-key or iteration.

### Algorithms
`sort` = **introsort** (quicksort + heapsort fallback + insertion sort for small ranges), O(n log n) worst, **not stable** · `stable_sort` = merge sort (uses a buffer) · `nth_element` = introselect O(n) avg · `partial_sort` = heap · `lower_bound` needs random access for O(log n) · `remove`/`remove_if` don't erase (erase-remove idiom; C++20 `std::erase_if`).

### Complexity table (say these without thinking)
| | vector | deque | list | map | unordered_map |
|---|---|---|---|---|---|
| random access | O(1) | O(1) | – | – | – |
| push back | O(1)* | O(1) | O(1) | – | – |
| push front | O(n) | O(1) | O(1) | – | – |
| insert middle | O(n) | O(n) | O(1)† | O(log n) | O(1) avg |
| find | O(n) / O(log n) sorted | O(n) | O(n) | O(log n) | O(1) avg |
\* amortized · † given an iterator

---

## Self-test
1. What does `std::move` compile to? What's the moved-from state?
2. `template<class T> void f(T&& x)`: what is `x` when called with an lvalue `int`? What does `std::forward` do?
3. Why must a move ctor be `noexcept` for vector growth to use it?
4. Write the Rule-of-5 `Buffer` from memory in 5 minutes.
5. `make_shared` vs `shared_ptr<T>(new T)`: two differences.
6. When does `unordered_map` invalidate iterators? References?
7. `std::sort` algorithm and stability. What do you use for a stable sort?
8. Virtual functions vs CRTP: when do you choose which?
9. A lambda capturing `this` is stored in a callback queue. What can go wrong and how do you fix it?
