#include <functional>
#include <iostream>
#include <semaphore>
#include <string>
#include <thread>
using namespace std;

// LC 1115 FooBar with 2 semaphores ("token jars"). No mutex, no turn, no cv: the jar counts ARE the board.
// Kya baanta:   the two jars (each holds 0 or 1 token)
// Kab ruke:     acquire() on an empty jar sleeps
// Kaun jagaaye: foo puts a token in barJar, bar puts one in fooJar
// Kaise khatam: each loop runs n times
// LeetCode fallback if <semaphore> doesn't compile there: POSIX <semaphore.h>
//   sem_t s; sem_init(&s, 0, 1);  sem_wait(&s) = acquire;  sem_post(&s) = release
class FooBar {
    int n;
    binary_semaphore fooJar{1};       // foo goes first: its jar starts with 1 token
    binary_semaphore barJar{0};       // bar must wait: empty jar
public:
    FooBar(int n) : n(n) {}

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            fooJar.acquire();         // take my token (sleep if the jar is empty)
            printFoo();
            barJar.release();         // put a token in bar's jar -> wakes bar
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            barJar.acquire();
            printBar();
            fooJar.release();
        }
    }
};

int main() {
    {   // 1. small visible run, bar's thread started first on purpose
        FooBar fb(3);
        thread b([&]{ fb.bar([]{ cout << "bar"; }); });
        thread a([&]{ fb.foo([]{ cout << "foo"; }); });
        a.join(); b.join();
        cout << '\n';
    }
    // 2. stress: 100000 rounds, compare with the exact expected string
    const int N = 100000;
    FooBar fb(N);
    string out;                       // safe without a mutex: release -> acquire orders memory between the threads
    thread b([&]{ fb.bar([&]{ out += "bar"; }); });
    thread a([&]{ fb.foo([&]{ out += "foo"; }); });
    a.join(); b.join();
    string want;
    for (int i = 0; i < N; i++) want += "foobar";
    cout << (out == want ? "OK " : "FAIL ") << out.size() << " chars\n";
}
