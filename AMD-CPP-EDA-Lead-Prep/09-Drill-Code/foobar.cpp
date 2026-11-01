#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
using namespace std;

// LC 1115 FooBar: a turn flag + one condition variable.
// Kya baanta:   turn (true = foo's turn), guarded by m
// Kab ruke:     foo waits while !turn, bar waits while turn
// Kaun jagaaye: after printing, flip turn, wake the other one (only 1 other waiter -> 1 cv is enough)
// Kaise khatam: each loop runs n times; nothing to close
class FooBar {
private:
    int n;
    mutex m;
    bool turn;
    condition_variable cv;

public:
    FooBar(int n) {
        this->n = n;
        turn = true;
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lk(m);                 // 1. lock
            cv.wait(lk, [&] () {return turn;});       // 2. wait till my turn
            printFoo();                               // 3. work
            turn = false;                             // 4. change the board
            cv.notify_one();                          // 5. wake bar
        }                                             // lk unlocks here, every round
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lk(m);
            cv.wait(lk, [&] () {return !turn;});
            printBar();
            turn = true;
            cv.notify_one();
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
    string out;                                       // only touched inside print*, i.e. under fb's lock
    thread b([&]{ fb.bar([&]{ out += "bar"; }); });
    thread a([&]{ fb.foo([&]{ out += "foo"; }); });
    a.join(); b.join();
    string want;
    for (int i = 0; i < N; i++) want += "foobar";
    cout << (out == want ? "OK " : "FAIL ") << out.size() << " chars\n";
}
