// Tests for day4. Included at the end of day4.cpp (and solutions/day4_sol.cpp).
#pragma once
#include "../test.h"
using tst::Counted;

static void t_RingBuffer() {
    RingBuffer<int> rb(3);
    CHECK(rb.empty());
    CHECK_EQ(rb.capacity(), (size_t)3);
    CHECK(rb.push(1)); CHECK(rb.push(2)); CHECK(rb.push(3));
    CHECK(rb.full());
    CHECK(!rb.push(4));                                  // full
    int x = -1;
    CHECK(rb.pop(x) && x == 1);
    CHECK(rb.push(4));                                   // wraps around
    CHECK(rb.pop(x) && x == 2);
    CHECK(rb.pop(x) && x == 3);
    CHECK(rb.pop(x) && x == 4);
    CHECK(!rb.pop(x));                                   // empty
    CHECK_EQ(rb.size(), (size_t)0);
    bool ok = true;                                      // many wrap-arounds keep FIFO order
    for (int i = 0; i < 1000 && ok; ++i) { ok = rb.push(i) && rb.pop(x) && x == i; }
    CHECK(ok);
}

static void t_UniquePtr() {
    CHECK(!is_copy_constructible_v<UniquePtr<int>>);
    CHECK(!is_copy_assignable_v<UniquePtr<int>>);
    CHECK(is_nothrow_move_constructible_v<UniquePtr<int>>);
    CHECK_EQ(sizeof(UniquePtr<int>), sizeof(int*));
    Counted::reset();
    {
        UniquePtr<Counted> a(new Counted(5));
        CHECK(a.get() != nullptr && (*a).v == 5 && a->v == 5);
        UniquePtr<Counted> b = std::move(a);             // move ctor
        CHECK(a.get() == nullptr && !a);
        CHECK(b.get() != nullptr && b->v == 5);
        UniquePtr<Counted> c(new Counted(6));
        c = std::move(b);                                // move assign: Counted(6) must be destroyed
        CHECK_EQ(Counted::alive, 1);
        CHECK(c.get() != nullptr && c->v == 5);
        c.reset(new Counted(7));
        CHECK_EQ(Counted::alive, 1);
        Counted* raw = c.release();
        CHECK(!c && raw && raw->v == 7);
        delete raw;
        c.reset(new Counted(8));
    }
    CHECK_EQ(Counted::alive, 0);                         // destructor freed Counted(8)
}

static void t_SharedPtr() {
    Counted::reset();
    {
        SharedPtr<Counted> a(new Counted(5));
        CHECK_EQ(a.use_count(), 1L);
        {
            SharedPtr<Counted> b = a;                    // copy
            CHECK_EQ(a.use_count(), 2L);
            CHECK(b.get() == a.get() && b.get() != nullptr && b->v == 5);
        }
        CHECK_EQ(a.use_count(), 1L);
        SharedPtr<Counted> c = std::move(a);             // move: no count change
        CHECK(a.get() == nullptr);
        CHECK_EQ(c.use_count(), 1L);
        CHECK_EQ(Counted::alive, 1);

        SharedPtr<Counted> d(new Counted(1)), e(new Counted(2));
        d = e;                                           // Counted(1) must die
        CHECK_EQ(Counted::alive, 2);
        CHECK_EQ(e.use_count(), 2L);
        d = d;                                           // self-assignment is safe
        CHECK_EQ(d.use_count(), 2L);
        CHECK(d.get() != nullptr && d->v == 2);
        d.reset();
        CHECK_EQ(e.use_count(), 1L);
        CHECK(!d);
    }
    CHECK_EQ(Counted::alive, 0);

    // concurrent copies of the same (const) SharedPtr: the refcount must be atomic
    {
        SharedPtr<Counted> root(new Counted(9));
        vector<thread> ts;
        for (int t = 0; t < 8; ++t)
            ts.emplace_back([&root] { for (int i = 0; i < 20000; ++i) { SharedPtr<Counted> local = root; (void)local; } });
        for (auto& t : ts) t.join();
        CHECK_EQ(root.use_count(), 1L);
        CHECK_EQ(Counted::alive, 1);
    }
    CHECK_EQ(Counted::alive, 0);
}

static void t_FixedPool() {
    Counted::reset();
    FixedPool pool(sizeof(Counted), 4);
    vector<void*> ps;
    for (int i = 0; i < 10; ++i) {
        void* p = pool.allocate();
        CHECK(p != nullptr);
        if (!p) return;
        CHECK(reinterpret_cast<uintptr_t>(p) % alignof(std::max_align_t) == 0);
        ps.push_back(p);
    }
    CHECK_EQ(pool.blockCount(), (size_t)3);              // 10 slots / 4 per block
    set<void*> distinct(ps.begin(), ps.end());
    CHECK_EQ(distinct.size(), (size_t)10);
    for (int i = 0; i < 10; ++i) new (ps[i]) Counted(i);  // placement new
    bool vals = true;
    for (int i = 0; i < 10; ++i) vals = vals && static_cast<Counted*>(ps[i])->v == i;
    CHECK(vals);
    for (void* p : ps) { static_cast<Counted*>(p)->~Counted(); }
    CHECK_EQ(Counted::alive, 0);
    pool.deallocate(ps[3]);
    CHECK(pool.allocate() == ps[3]);                     // LIFO reuse from the free list
    for (void* p : ps) pool.deallocate(p);
    for (int i = 0; i < 10; ++i) pool.allocate();        // reuse: no new blocks
    CHECK_EQ(pool.blockCount(), (size_t)3);
}

static void t_MyVector() {
    Counted::reset();
    {
        MyVector<Counted> v;
        for (int i = 0; i < 100; ++i) v.push_back(Counted(i));
        CHECK_EQ(v.size(), (size_t)100);
        CHECK(v.capacity() >= 100);
        bool vals = v.size() == 100;
        for (size_t i = 0; vals && i < 100; ++i) vals = v[i].v == (int)i;
        CHECK(vals);
        CHECK_EQ(Counted::copies, 0);                    // noexcept move → no copies on growth
        CHECK_EQ(Counted::alive, 100);
        v.pop_back();
        CHECK_EQ(v.size(), (size_t)99);
        CHECK_EQ(Counted::alive, 99);
        Counted lv(42);
        v.push_back(lv);                                 // lvalue → exactly one copy
        CHECK_EQ(Counted::copies, 1);
    }
    CHECK_EQ(Counted::alive, 0);                         // destructor destroyed everything
    {
        MyVector<Counted> r;
        r.reserve(50);
        CHECK(r.capacity() >= 50);
        CHECK_EQ(r.size(), (size_t)0);
        CHECK_EQ(Counted::alive, 0);                     // reserve constructs nothing
    }
    {
        MyVector<int> g; set<size_t> caps;
        for (int i = 0; i < 1000; ++i) { g.push_back(i); caps.insert(g.capacity()); }
        CHECK(caps.size() <= 20);                        // geometric growth
    }
    {
        const string big = "a long string that is definitely not in the SSO buffer";
        MyVector<string> s;
        s.push_back(string(big));
        while (s.size() > 0 && s.size() < s.capacity()) s.push_back(string(big));  // fill to capacity
        size_t before = s.size();
        if (before > 0) s.push_back(s[0]);               // forces reallocation; s[0] lives in the OLD buffer
        CHECK(before > 0 && s.size() == before + 1 && s[before] == big);
    }
}

static void t_BlockingQueue() {
    {
        BlockingQueue<int> q(4);
        CHECK(q.push(1)); CHECK(q.push(2));
        CHECK_EQ(q.pop(), optional<int>(1));
        CHECK_EQ(q.pop(), optional<int>(2));
        q.push(3);
        q.close();
        CHECK(!q.push(4));                               // closed
        CHECK_EQ(q.pop(), optional<int>(3));             // drain
        CHECK_EQ(q.pop(), optional<int>());              // then nullopt
    }
    {
        BlockingQueue<int> q(16);                        // small capacity → producers block
        const int P = 4, C = 4, N = 10000;
        atomic<ll> consumed{0}; atomic<int> count{0};
        vector<thread> prod, cons;
        for (int c = 0; c < C; ++c)
            cons.emplace_back([&] { while (auto v = q.pop()) { consumed += *v; ++count; } });
        for (int p = 0; p < P; ++p)
            prod.emplace_back([&, p] { for (int i = 1; i <= N; ++i) q.push(p * N + i); });
        for (auto& t : prod) t.join();
        q.close();
        for (auto& t : cons) t.join();
        ll total = (ll)P * N * (P * N + 1) / 2;
        CHECK_EQ(count.load(), P * N);
        CHECK_EQ(consumed.load(), total);
    }
}

static void t_printAlternately() {
    CHECK_EQ(printAlternately(10), string("1 2 3 4 5 6 7 8 9 10"));
    CHECK_EQ(printAlternately(1), string("1"));
    CHECK_EQ(printAlternately(0), string(""));
    string big = printAlternately(500);
    CHECK(big.size() > 3 && big.substr(big.size() - 3) == "500");
}

static void t_parallelSum() {
    VI a(1'000'003);
    for (size_t i = 0; i < a.size(); ++i) a[i] = (int)(i % 1000) - 400;
    ll expect = accumulate(a.begin(), a.end(), 0LL);
    CHECK_EQ(parallelSum(a, 1), expect);
    CHECK_EQ(parallelSum(a, 4), expect);
    CHECK_EQ(parallelSum(a, 7), expect);
    CHECK_EQ(parallelSum(VI{}, 3), 0LL);
    CHECK_EQ(parallelSum(VI{5, 6}, 8), 11LL);           // more threads than elements
}

static void t_ThreadPool() {
    {
        ThreadPool pool(4);
        vector<future<int>> fs;
        for (int i = 0; i < 100; ++i) fs.push_back(pool.submit([i] { return i * i; }));
        ll sum = 0; bool valid = true;
        for (auto& f : fs) { if (!f.valid()) { valid = false; break; } sum += f.get(); }
        CHECK(valid);
        CHECK_EQ(sum, 328350LL);                         // Σ i² for i < 100
    }
    atomic<int> ran{0};
    {
        ThreadPool pool(2);
        for (int i = 0; i < 50; ++i)
            pool.submit([&ran] { this_thread::sleep_for(chrono::microseconds(200)); return ++ran; });
    }                                                    // destructor must finish queued tasks
    CHECK_EQ(ran.load(), 50);
}

static void t_allocMatrix() {
    int** m = allocMatrix(3, 4);
    CHECK(m != nullptr);
    if (!m) return;
    bool zero = true;
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 4; ++j) zero = zero && m[i][j] == 0;
    CHECK(zero);
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 4; ++j) m[i][j] = i * 10 + j;
    CHECK(m[2][3] == 23 && m[1][0] == 10);
    CHECK(m[1] == m[0] + 4 && m[2] == m[0] + 8);       // one contiguous block
    freeMatrix(m);
}

int main(int argc, char** argv) {
    if (argc > 1) tst::filter = argv[1];
    SECTION(t_RingBuffer);
    SECTION(t_UniquePtr);
    SECTION(t_SharedPtr);
    SECTION(t_FixedPool);
    SECTION(t_MyVector);
    SECTION(t_BlockingQueue);
    SECTION(t_printAlternately);
    SECTION(t_parallelSum);
    SECTION(t_ThreadPool);
    SECTION(t_allocMatrix);
    return tst::summary("day4");
}
