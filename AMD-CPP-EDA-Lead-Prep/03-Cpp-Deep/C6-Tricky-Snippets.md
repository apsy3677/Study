# C6: Predict the Output / Find the Bug (without running it)

> AMD 2025–26 reports: "debug code snippets **without executing** them", "debugging buggy code / race conditions".
> Method: for each snippet, **say** (1) the output or behaviour, (2) *why*, (3) the fix. Only then open the answer.
> Day 1: #1–13 · Day 2: #14–26.

---

### 1. Virtual call in constructor
```cpp
struct B { B() { hello(); } virtual void hello() { cout << "B"; } };
struct D : B { void hello() override { cout << "D"; } };
int main() { D d; d.hello(); }
```
<details><summary>Answer</summary>`BD`. During B's constructor the object is a B (vptr → B's vtable), so there's no dispatch to D. Then `d.hello()` dispatches normally.</details>

### 2. Default arguments on virtuals
```cpp
struct B { virtual void f(int x = 1) { cout << "B" << x; } };
struct D : B { void f(int x = 2) override { cout << "D" << x; } };
int main() { B* p = new D; p->f(); delete p; }
```
<details><summary>Answer</summary>`D1`. The body is chosen dynamically (D) but the default argument statically (from B's declaration, the static type). Also a leak/UB hazard: no virtual dtor (harmless here since D has no extra state, but still UB by the standard).</details>

### 3. Slicing
```cpp
struct B { virtual string name() const { return "B"; } };
struct D : B { string name() const override { return "D"; } };
void byVal(B b) { cout << b.name(); }
void byRef(const B& b) { cout << b.name(); }
int main() { D d; byVal(d); byRef(d); }
```
<details><summary>Answer</summary>`BD`. Pass-by-value copies only the B subobject (sliced; its vptr is B's).</details>

### 4. Non-virtual destructor
```cpp
struct B { ~B() { cout << "~B "; } };
struct D : B { vector<int> v = vector<int>(1000); ~D() { cout << "~D "; } };
int main() { B* p = new D; delete p; }
```
<details><summary>Answer</summary>**UB**. Typically prints `~B ` only and leaks v's buffer. Fix: `virtual ~B() = default;`. Note that `shared_ptr<B> p(new D)` or `make_shared<D>()` would print `~D ~B ` even without a virtual dtor, while `unique_ptr<B>` would not.</details>

### 5. Name hiding
```cpp
struct B { void f(int) { cout << "B::f(int)"; } };
struct D : B { void f(double) { cout << "D::f(double)"; } };
int main() { D d; d.f(1); }
```
<details><summary>Answer</summary>`D::f(double)`. D::f hides every B::f, and 1 converts to double. Fix: `using B::f;` inside D → `B::f(int)` becomes the exact match.</details>

### 6. Modifying a vector during range-for
```cpp
vector<int> v = {1, 2, 3};
for (int& x : v) if (x == 2) v.push_back(4);
```
<details><summary>Answer</summary>**UB**: push_back reallocates (capacity 3 → 6), so the loop's hidden iterators and `x` dangle. Fix: an index loop that re-reads `v.size()`, or collect the additions and append after the loop.</details>

### 7. Erase inside an iterator loop
```cpp
vector<int> v = {1, 2, 2, 3};
for (auto it = v.begin(); it != v.end(); ++it) if (*it == 2) v.erase(it);
```
<details><summary>Answer</summary>**UB**: `it` is invalidated by erase, then incremented. Even with a fix that ignores that, it would skip the second 2. Fix: `it = v.erase(it)` in an if/else, or `std::erase(v, 2)` (C++20) / the erase-remove idiom (O(n) overall instead of O(n²)).</details>

### 8. Unsigned underflow
```cpp
vector<int> v;
for (size_t i = 0; i < v.size() - 1; ++i) cout << v[i];
```
<details><summary>Answer</summary>`v.size() - 1` wraps to `SIZE_MAX` → out-of-bounds reads → UB/crash. Fix: `i + 1 < v.size()` or cast to a signed int.</details>

### 9. Returning a reference to a temporary
```cpp
const string& longer(const string& a, const string& b) { return a.size() > b.size() ? a : b; }
int main() { const string& r = longer("hello", "hi"); cout << r; }
```
<details><summary>Answer</summary>**UB (dangling)**. The two temporary strings die at the end of the full expression. Lifetime extension applies only when a temporary binds *directly* to a local reference, not through a function's return. Fix: return by value.</details>

### 10. `string_view` to a temporary
```cpp
string_view sv = string("temporary") + "!";
cout << sv;
```
<details><summary>Answer</summary>**UB**: the string temporary dies at the `;`. `string_view` never owns. Fix: `string s = …; string_view sv = s;`.</details>

### 11. `map::operator[]` on read
```cpp
map<string, int> m;
if (m["x"] == 0) cout << m.size();
```
<details><summary>Answer</summary>Prints `1`: operator[] inserted `{"x", 0}`. Use `find`/`count`/`contains`. (Also: operator[] can't be used on a const map.)</details>

### 12. Bit-operator precedence
```cpp
int x = 4;
if (x & 1 == 0) cout << "even"; else cout << "odd";
```
<details><summary>Answer</summary>Prints `odd`. `==` binds tighter than `&` → `x & (1 == 0)` → `x & 0` → 0 → false. Fix: `(x & 1) == 0`. Compile with `-Wall` (it warns: -Wparentheses).</details>

### 13. `sizeof` and array decay
```cpp
void f(int a[10]) { cout << sizeof(a); }
int main() { int arr[10]; cout << sizeof(arr) << " "; f(arr); }
```
<details><summary>Answer</summary>`40 8` (x86-64). A parameter `int a[10]` is really `int*`. Use `std::array`/`std::span` or a template `template<size_t N> void f(int (&a)[N])`.</details>

---

### 14. The classic data race
```cpp
int counter = 0;
auto work = [&] { for (int i = 0; i < 1'000'000; ++i) ++counter; };
thread t1(work), t2(work); t1.join(); t2.join();
cout << counter;
```
<details><summary>Answer</summary>**UB (data race)**. In practice it's usually < 2,000,000 (lost updates: load, add, store interleave). Fix: `atomic<int>` (fetch_add), a mutex, or best: per-thread local counts summed after join (no contention).</details>

### 15. Double-checked locking
```cpp
Singleton* Singleton::get() {
    if (!inst_) { lock_guard<mutex> g(m_); if (!inst_) inst_ = new Singleton(); }
    return inst_;
}
```
<details><summary>Answer</summary>Data race on the non-atomic `inst_`: another thread can see a non-null pointer before the object's construction is visible (reordering). Fix: `static Singleton& get() { static Singleton s; return s; }` (thread-safe since C++11), `call_once`, or `atomic<Singleton*>` with acquire/release.</details>

### 16. Condition variable without a predicate
```cpp
// consumer
unique_lock<mutex> lk(m);
cv.wait(lk);
process(q.front()); q.pop();
```
<details><summary>Answer</summary>Two bugs: a **spurious wakeup** → the queue may be empty → UB on `front()`. A **lost wakeup**: if the producer notified before the consumer waited, it blocks forever. Fix: `cv.wait(lk, [&]{ return !q.empty(); });`.</details>

### 17. Detached thread with a reference capture
```cpp
void start() { int local = 5; thread t([&] { use(local); }); t.detach(); }
```
<details><summary>Answer</summary>Dangling reference after `start` returns → UB. Capture by value (`[local]`), or join, or give the thread ownership of its data. Rule: detached threads must own everything they touch.</details>

### 18. `shared_ptr` cycle
```cpp
struct Node { shared_ptr<Node> next; ~Node() { cout << "bye "; } };
int main() { auto a = make_shared<Node>(); auto b = make_shared<Node>(); a->next = b; b->next = a; }
```
<details><summary>Answer</summary>Prints nothing: a leak. Each refcount stays at 1 after the locals die. Fix: make one direction `weak_ptr<Node>`.</details>

### 19. Lambda returning a dangling capture
```cpp
function<int()> make() { int x = 42; return [&] { return x; }; }
int main() { cout << make()(); }
```
<details><summary>Answer</summary>**UB**: x died when `make` returned. Use `[x]` or `[=]`.</details>

### 20. `std::move` on a const object
```cpp
const vector<int> a(1'000'000, 1);
vector<int> b = std::move(a);
cout << a.size();
```
<details><summary>Answer</summary>Prints `1000000`. `std::move(a)` gives a `const vector&&`, which can't bind to `vector&&`, so the **copy** constructor is chosen. A silent performance bug.</details>

### 21. Copies vs moves in `vector` growth
```cpp
struct X { X() {} X(const X&) { cout << "C"; } X(X&&) noexcept { cout << "M"; } };
int main() { vector<X> v; v.push_back(X()); v.push_back(X()); }
```
<details><summary>Answer</summary>`MMM` (libstdc++): the 1st push moves the temporary. The 2nd push reallocates (cap 1 → 2): it moves the new temporary into place, then relocates the old element **by move because the move ctor is noexcept**. Remove `noexcept` → `MMC` (the old element gets **copied** to keep the strong exception guarantee). A `reserve(2)` up front → `MM`.</details>

### 22. Signed overflow check
```cpp
bool willOverflow(int a) { return a + 1 < a; }
```
<details><summary>Answer</summary>Signed overflow is UB, so the optimizer may fold this to `return false;` at -O2. Correct check: `a == INT_MAX`, or in general `b > 0 && a > INT_MAX - b`. Also `__builtin_add_overflow`.</details>

### 23. `new[]` with `delete`
```cpp
string* p = new string[3];
delete p;
```
<details><summary>Answer</summary>**UB**: it must be `delete[] p` (to run 3 destructors and use the array cookie). Better: `vector<string>` or `unique_ptr<string[]>`.</details>

### 24. Throwing from a destructor
```cpp
struct Bad { ~Bad() { throw 1; } };
int main() { try { Bad b; } catch (...) { cout << "caught"; } }
```
<details><summary>Answer</summary>`std::terminate` is called, and "caught" is **not** printed. Destructors are implicitly `noexcept`. Never throw from destructors; log or store the error instead.</details>

### 25. `vector<bool>` proxy surprise
```cpp
vector<bool> v(2);
auto x = v[0];
x = true;
cout << v[0];
```
<details><summary>Answer</summary>Prints `1`. `auto` deduces `vector<bool>::reference` (a proxy to the bit), so assigning through it modifies `v`. With `vector<int>` it would print 0. Use `bool x = v[0];`.</details>

### 26. Inserting into an `unordered_map` while iterating
```cpp
unordered_map<int, int> m{{1, 1}};
for (auto& [k, v] : m) m[k + 1] = v;
```
<details><summary>Answer</summary>**UB**: an insertion may trigger a rehash that invalidates the loop's iterators, and even without a rehash, whether new elements are visited is unspecified (a potential infinite loop). Fix: collect the updates into a separate container and apply them after the loop.</details>

### 27 (bonus). Evaluation order
```cpp
int next() { static int n = 0; return ++n; }
int main() { cout << next() << next() << next(); }
```
<details><summary>Answer</summary>C++17 and later: `123` (the operands of `<<` are sequenced left to right). Before C++17 the order was unspecified. Say both, since it shows you know the standard changed.</details>

### 28 (bonus). Struct padding
```cpp
struct A { char c; double d; int i; };
struct B { double d; int i; char c; };
cout << sizeof(A) << " " << sizeof(B);
```
<details><summary>Answer</summary>`24 16`. Reorder the fields largest → smallest. At 100M objects that's 800 MB saved.</details>
