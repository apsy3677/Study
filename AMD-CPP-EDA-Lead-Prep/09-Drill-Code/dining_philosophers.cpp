#include <atomic>
#include <chrono>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
using namespace std;

// LC 1226 The Dining Philosophers.
// Kya baanta:   5 forks; fork i is shared by 2 neighbours -> one mutex per fork
// Kab ruke:     a fork my neighbour holds -> lock() blocks (mutex line, no cv needed)
// Kaun jagaaye: the neighbour's unlock hands the fork over
// Kaise khatam: each call eats once; the danger is never finishing = deadlock (circular wait)
// Fix: one global lock order -> always take the LOWER-numbered fork first. Breaks the circle.
class DiningPhilosophers {
    mutex fork[5];
public:
    void wantsToEat(int p,
                    function<void()> pickLeftFork, function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork, function<void()> putRightFork) {
        int left = p, right = (p + 1) % 5;
        lock_guard<mutex> a(fork[min(left, right)]);    // lower number first: P4 takes fork 0 before fork 4
        lock_guard<mutex> b(fork[max(left, right)]);
        pickLeftFork(); pickRightFork();
        eat();
        putLeftFork(); putRightFork();
    }                                                   // b, then a unlock
};

// Naive version, for the demo only: everyone takes LEFT first -> deadlock.
class NaivePhilosophers {
    mutex fork[5];
public:
    void wantsToEat(int p, function<void()> eat) {
        lock_guard<mutex> a(fork[p]);                         // left
        this_thread::sleep_for(chrono::milliseconds(10));     // widen the window so all 5 grab their left
        lock_guard<mutex> b(fork[(p + 1) % 5]);               // right = my neighbour's left -> held
        eat();
    }
};

int main(int argc, char** argv) {
    atomic<int> meals{0}, clashes{0};
    atomic<bool> eating[5] = {};
    auto eat = [&](int p) {
        eating[p] = true;
        if (eating[(p + 1) % 5] || eating[(p + 4) % 5]) clashes++;   // neighbour eating too = a fork shared = bug
        meals++;
        eating[p] = false;
    };

    if (argc > 1 && string(argv[1]) == "naive") {             // ./dining naive
        NaivePhilosophers dp;
        vector<thread> ts;
        for (int p = 0; p < 5; p++)
            ts.emplace_back([&, p]{ dp.wantsToEat(p, [&]{ eat(p); }); });   // 1 meal each
        this_thread::sleep_for(chrono::seconds(2));
        if (meals < 5) {
            cout << "DEADLOCK: " << meals << " of 5 ate; each holds its left fork, waits for the right" << endl;
            _Exit(0);                                         // threads are stuck forever, can't join them (endl: _Exit skips the flush)
        }
        for (auto& t : ts) t.join();
        cout << "naive got lucky this time: " << meals << " meals\n";
        return 0;
    }

    const int N = 2000;                                       // meals per philosopher
    DiningPhilosophers dp;
    vector<thread> ts;
    for (int p = 0; p < 5; p++)
        ts.emplace_back([&, p]{
            for (int i = 0; i < N; i++)
                dp.wantsToEat(p, []{}, []{}, [&]{ eat(p); }, []{}, []{});
        });
    for (auto& t : ts) t.join();
    cout << "ordered: " << meals << " meals (want " << 5 * N << "), neighbour clashes " << clashes << '\n';
}
