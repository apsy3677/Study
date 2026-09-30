# C1: The C++ Object Model (what the compiler really builds)

> AMD ★★★: "What is a virtual function and how does it work internally (vtable/vptr)?" This is asked in almost every AMD C++ report.
> Format per topic: **30-second answer** (say this first) → **depth** (for follow-ups) → **trap**.

---

## 1. Virtual functions, vtable, vptr ★★★
**30-sec answer:** "For each polymorphic class the compiler emits one **vtable**: a static array of function pointers, one per virtual function, plus RTTI info. Each *object* gets a hidden **vptr** (usually at offset 0) that the constructor sets to its class's vtable. A virtual call `p->f()` compiles to: load the vptr, load the slot for `f`, indirect-call it. Cost: one extra pointer per object, two dependent loads + an indirect branch per call, and **no inlining** unless the compiler can devirtualize."

**Depth**
- The vtable layout (Itanium ABI, used by GCC/Clang on Linux): `[offset-to-top][RTTI ptr][f1][f2]…`; the vptr points at `f1`'s slot.
- The derived vtable copies the base's slots, **overrides** the replaced ones and **appends** new virtuals.
- **Construction order:** base ctor runs with vptr = **Base** vtable → then members → then the derived ctor body with vptr = Derived vtable. Hence:
- **Calling a virtual from a constructor/destructor** dispatches to the *current* class's version, not the most-derived one. Calling a **pure** virtual there → UB (usually "pure virtual method called" + abort).
- **Devirtualization:** `final` classes/methods, calls on objects (not pointers), LTO/whole-program analysis, speculative devirtualization with a guard.
- **Performance talking point (lead):** the vcall itself is cheap (~1–3 ns when predicted). The real costs are the lost inlining and the pointer-chasing, heterogeneous object layout. In hot EDA loops over millions of objects, prefer **data-oriented** designs (homogeneous arrays, switch on a type tag, or CRTP / templates).

```cpp
struct Base { virtual void f(); virtual ~Base() = default; int x; };   // sizeof = 16 on x86-64 (vptr 8 + int 4 + pad 4)
struct Der : Base { void f() override; virtual void g(); };            // same vptr, a longer vtable
```

## 2. Virtual destructor ★★★
**30-sec:** "If you `delete` a derived object through a base pointer and the base destructor isn't virtual, the behaviour is **undefined**. In practice only the base part is destroyed, so derived resources leak. Rule: a class meant for polymorphic deletion has a **public virtual** destructor, *or* a **protected non-virtual** one so that deleting through the base isn't allowed."
**Trap:** `shared_ptr<Base> p = make_shared<Derived>()` **does** call `~Derived` even without a virtual dtor (the control block captures the right deleter), but `unique_ptr<Base>` does not. A great follow-up answer.

## 3. Static vs dynamic binding · overloading vs overriding · hiding ★★
- Overload: same scope, different signature, resolved at **compile time**.
- Override: derived redefines a **virtual** with the same signature, resolved at **run time**. Always write `override` (the compiler catches signature typos).
- **Name hiding:** declaring `f(double)` in Derived **hides** all Base `f` overloads → bring them back with `using Base::f;`.
- **Default arguments are bound statically:** `Base* p = new Der; p->f();` uses **Base's** default argument with **Der's** body. Never change defaults in overrides.
- `final` on a class or method prevents further derivation or overriding (and enables devirtualization).

## 4. Object slicing ★★
Copying a `Derived` into a `Base` **by value** copies only the Base subobject; the vptr is the Base's. `void f(Base b)` → slicing. Pass `const Base&` or a pointer. Polymorphic types should usually **delete copy** or provide a `virtual clone()`.

## 5. Multiple & virtual inheritance ★★
- Multiple inheritance: an object has **multiple vptrs** (one per polymorphic base subobject). Casting `Der*`→`Base2*` **adjusts the pointer** by an offset. Calls through `Base2*` go via **thunks** that adjust `this`.
- **Diamond** (`B : A`, `C : A`, `D : B, C`): two copies of A → ambiguity. **Virtual inheritance** (`B : virtual A`) shares one A. The cost is a virtual base offset lookup through the vtable, and **the most-derived class constructs the virtual base**.
- Interview line: "I prefer composition + interfaces (pure abstract classes, no data) over diamonds. Multiple interface inheritance is cheap and clean."

## 6. `sizeof` puzzles ★★
| Type | sizeof (x86-64) | Why |
|---|---|---|
| `struct E {};` | 1 | distinct objects need distinct addresses |
| `struct D : E { int x; };` | 4 | **Empty Base Optimization** |
| `struct V { virtual void f(); };` | 8 | vptr |
| `struct S { char c; int i; char d; };` | 12 | padding: c(1)+3, i(4), d(1)+3 |
| `struct S2 { int i; char c; char d; };` | 8 | reorder members largest → smallest to cut padding |
| `int a[10]` passed to `f(int a[])` | 8 | array decays to a pointer |
| `[[no_unique_address]] Empty e;` (C++20) | can be 0 | EBO for members |

Alignment rule: each member is aligned to its `alignof`; the struct size is rounded up to the max alignment. `#pragma pack` / `alignas(64)` (for cache-line separation).

## 7. Special member functions: what the compiler generates ★★★ (details in C2)
Default ctor, copy ctor, copy assign, move ctor, move assign, destructor.
- Declaring **any** of copy/move/dtor **suppresses the implicit move ops** (they fall back to copy!).
- Declaring a move op **deletes** the implicit copy ops.
- Rule of 0: let members (RAII types) handle everything. Rule of 5: if you write one, consider all five.

## 8. Const, references, pointers ★★
- `const T* p` (pointee const) vs `T* const p` (pointer const). Read right-to-left.
- `const` member function: `this` is `const T*`. `mutable` members for caches and mutexes.
- **Reference vs pointer:** a reference must be bound at init, can't be reseated, is never null (in valid code). Implemented as a pointer under the hood.
- `const T&` binds to temporaries and extends their lifetime (only for a local reference bound directly, **not** through a function return).
- `constexpr` (compile-time evaluable) vs `const` (read-only). `consteval` = must be compile-time.

## 9. Storage, linkage, `static`, `inline` ★★
| Keyword | Meaning |
|---|---|
| `static` local variable | initialized once, on first pass; **thread-safe initialization since C++11** ("magic statics", the Meyers singleton) |
| `static` at namespace scope | internal linkage (prefer an unnamed namespace) |
| `static` member | one per class; define it in one TU, or use `inline static` (C++17) |
| `inline` function/variable | may be defined in multiple TUs (ODR-safe); inlining itself is the optimizer's decision |
| `extern "C"` | C linkage, no name mangling (for C APIs / dlsym) |
| `volatile` | the compiler must not optimize the accesses away (MMIO registers). **Not** atomic, **not** a memory fence, **not for threads** |

**Static initialization order fiasco:** globals in different TUs have an unspecified init order. Fix: function-local static (construct on first use).

## 10. `new`/`delete` vs `malloc`/`free` ★★
- `new` = allocate (`operator new`) **+ construct**; throws `std::bad_alloc`. `malloc` = raw bytes, returns NULL, no constructor.
- `delete[]` for arrays (it calls N destructors; the element count is stored in a hidden cookie for non-trivial types). Mismatching `new[]`/`delete` → UB.
- **Placement new:** `new (buf) T(args)` constructs in existing memory; destroy with an explicit `p->~T()`.
- You can overload `operator new/delete` per class (pools) or globally (tracking).
- Never mix: `free()` on `new`'d memory → UB.

## 11. Exceptions ★
- Stack unwinding runs the destructors of fully constructed objects → **this is why RAII works**.
- Throwing from a destructor during unwinding → `std::terminate`. Destructors are `noexcept` by default.
- The guarantees: **no-throw**, **strong** (commit-or-rollback: copy-and-swap), **basic** (no leaks, valid state).
- Cost: zero-cost model (table-based) → no cost on the happy path, expensive throw. Many EDA / perf codebases compile with `-fno-exceptions` or use error codes / `std::expected` (C++23) in hot paths.

## 12. RTTI & casts ★★
| Cast | Use |
|---|---|
| `static_cast` | known-safe conversions, upcasts, numeric, `void*`→`T*` |
| `dynamic_cast` | a checked downcast on polymorphic types (returns null or throws for references); costs a string/type-info walk. Frequent use suggests a design smell → use a virtual or visitor |
| `const_cast` | remove const; writing to a truly-const object = UB |
| `reinterpret_cast` | bit reinterpretation (pointer ↔ integer); type punning via it is UB. Use `memcpy`/`std::bit_cast` |

## 13. Undefined behaviour you must name on sight ★★
Signed overflow · out-of-bounds · null/dangling deref · use-after-free · double free · data race · uninitialized read · strict-aliasing violation · shifting ≥ width or negative · modifying a string literal · missing `return` in a non-void function · `delete` on a non-virtual-dtor base pointer · unsequenced modifications (`i = i++ + 1` pre-C++17 rules, still bad style).
**Why it matters (lead):** optimizers *assume* no UB → "impossible" branches get deleted → bugs that appear only at `-O2` (see C4, "crash only in release").

---

## Self-test (close the file, answer aloud, then check)
1. Draw the memory of `Der` from §1: where's the vptr, what does the vtable contain?
2. What does a virtual call in a base constructor dispatch to, and why?
3. `unique_ptr<Base>(new Der)` with a non-virtual `~Base`: what happens? With `shared_ptr` + `make_shared<Der>`?
4. Why can overriding a function with a different default argument surprise you?
5. `sizeof` of `{char; double; char;}` vs `{double; char; char;}`?
6. Explain the name hiding fix.
7. Two differences between `new` and `malloc`; what's placement new for?
8. Why is `volatile` not for multithreading?
