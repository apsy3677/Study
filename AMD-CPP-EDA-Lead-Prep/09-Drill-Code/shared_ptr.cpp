#include <atomic>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>
using namespace std;

// SharedPtr<T> from scratch (interview L1 + L2). weak_ptr: explain only.
// The 4 verbs: copy = share (+1) · move = steal, null the source (no count change)
//              assign = release what the TARGET held, then share/steal · destroy = release (last one deletes)
// L1 = long* cnt. L2 (thread-safe count) = atomic<long>*: the "--, was it the last?" check must be ONE atomic step.
template<class T>
class SharedPtr {
    T* p = nullptr;
    atomic<long>* cnt = nullptr;                                  // shared by every copy, lives on the heap
    void release() {                                              // drop my share; the last one out deletes both
        if (cnt && cnt->fetch_sub(1, memory_order_acq_rel) == 1) { delete p; delete cnt; }
        p = nullptr; cnt = nullptr;
    }
public:
    SharedPtr() = default;
    explicit SharedPtr(T* raw) : p(raw), cnt(raw ? new atomic<long>(1) : nullptr) {}   // explicit: no silent T* -> owner
    ~SharedPtr() { release(); }

    SharedPtr(const SharedPtr& o) : p(o.p), cnt(o.cnt) {          // copy = share, +1
        if (cnt) cnt->fetch_add(1, memory_order_relaxed);
    }
    SharedPtr(SharedPtr&& o) noexcept : p(o.p), cnt(o.cnt) {      // move = steal; source becomes empty, no -1
        o.p = nullptr; o.cnt = nullptr;
    }
    SharedPtr& operator=(const SharedPtr& o) {                    // only the TARGET (this) releases
        if (this != &o) {                                         // self-assign: a = a must not delete
            release();
            p = o.p; cnt = o.cnt;
            if (cnt) cnt->fetch_add(1, memory_order_relaxed);
        }
        return *this;                                             // safer variant: SharedPtr tmp(o); swap with tmp
    }
    SharedPtr& operator=(SharedPtr&& o) noexcept {
        if (this != &o) {
            release();
            p = o.p; cnt = o.cnt;
            o.p = nullptr; o.cnt = nullptr;
        }
        return *this;
    }

    T& operator*() const { return *p; }                           // no arguments: dereference the owned object
    T* operator->() const { return p; }
    T* get() const { return p; }
    long use_count() const { return cnt ? cnt->load(memory_order_relaxed) : 0; }
    explicit operator bool() const { return p != nullptr; }
};

struct Widget {
    int id;
    Widget(int i) : id(i) { cout << "  Widget " << id << " created\n"; }
    ~Widget() { cout << "  Widget " << id << " destroyed\n"; }
};

int main() {
    cout << "1. copy / move / assign\n";
    {
        SharedPtr<Widget> a(new Widget(1));                       // Widget 1 created          a:1
        SharedPtr<Widget> b = a;                                  // copy                      count 2
        SharedPtr<Widget> c(std::move(b));                        // move: b empty, still 2
        cout << "  a=" << a.use_count() << " b=" << b.use_count() << " c=" << c.use_count() << '\n';   // a=2 b=0 c=2
        a = a;                                                    // self-assign: nothing changes
        SharedPtr<Widget> d(new Widget(2));                       // Widget 2 created
        d = c;                                                    // d releases Widget 2 -> destroyed; Widget 1 count 3
        cout << "  a=" << a.use_count() << " d=" << d.use_count() << " d->id=" << d->id << '\n';      // a=3 d=3 id=1
        a = SharedPtr<Widget>();                                  // a lets go: count 2
        cout << "  c=" << c.use_count() << '\n';                  // c=2
    }                                                             // c, d go: Widget 1 destroyed exactly once

    cout << "2. 8 threads x 100000 copies of one pointer\n";
    SharedPtr<Widget> sp(new Widget(3));
    vector<thread> ts;
    for (int t = 0; t < 8; t++)
        ts.emplace_back([&sp]{
            for (int i = 0; i < 100000; i++) { SharedPtr<Widget> local(sp); }   // +1 then -1, concurrently
        });
    for (auto& th : ts) th.join();
    cout << "  use_count after all threads: " << sp.use_count() << " (want 1)\n";
}                                                                 // Widget 3 destroyed
