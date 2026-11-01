#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
using namespace std;

template<typename T>
class BlockingQueue {
    deque<T> queue;                           // shared state, guarded by m
    size_t capacity;
    mutex m;
    condition_variable not_full, not_empty;   // two waiting rooms
public:
    BlockingQueue(size_t cap) : capacity(cap) {}

    bool put(T v) {
        unique_lock<mutex> lk(m);                                    // locks m right here
        not_full.wait(lk, [&]{ return queue.size() < capacity; });  // go ahead only when there's room
        queue.push_back(v);
        not_empty.notify_one();                                      // wake one consumer
        return true;
    }                                                                // lk unlocks m here

    T take() {
        unique_lock<mutex> lk(m);
        not_empty.wait(lk, [&]{ return !queue.empty(); });          // go ahead only when there's an item
        T v = queue.front();
        queue.pop_front();
        not_full.notify_one();                                       // wake one producer
        return v;
    }
};

int main() {
    BlockingQueue<string> bq(4);              // capacity 4
    const int W = 10, N = 5;                  // 10 workers x 5 lines each

    thread writer([&]{                        // 1 consumer
        for (int i = 0; i < W * N; i++)       // knows how many lines are coming -> no close needed
            cout << bq.take() << '\n';        // cout stands in for the disk
    });

    vector<thread> workers;
    for (int w = 0; w < W; w++)
        workers.emplace_back([&, w]{          // w by value: each thread keeps its own id
            for (int i = 0; i < N; i++)
                bq.put("worker " + to_string(w) + " line " + to_string(i));
        });

    for (auto& t : workers) t.join();         // all producers done
    writer.join();                            // writer has drained all 50 lines
}
