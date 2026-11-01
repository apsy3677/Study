#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

// LC 347 Top K Frequent. Count first, then pick the k biggest counts.

// Way 1: MIN-heap of size k, O(n + u log k). Root = weakest of the current top k = the one to kick out.
vector<int> topKHeap(vector<int>& nums, int k) {
    unordered_map<int,int> cnt;
    for (int x : nums) cnt[x]++;                                          // 1. count
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;   // 2. min-heap of {count, value}
    for (auto& [v, c] : cnt) {
        pq.push({c, v});
        if ((int)pq.size() > k) pq.pop();                                 // 3. over k -> drop the weakest
    }
    vector<int> out;
    while (!pq.empty()) { out.push_back(pq.top().second); pq.pop(); }
    return out;
}

// Way 2: bucket by count, O(n). A count is between 1 and n, so bucket[c] = values seen exactly c times.
vector<int> topKBucket(vector<int>& nums, int k) {
    unordered_map<int,int> cnt;
    for (int x : nums) cnt[x]++;
    vector<vector<int>> bucket(nums.size() + 1);
    for (auto& [v, c] : cnt) bucket[c].push_back(v);
    vector<int> out;
    for (int c = nums.size(); c > 0 && (int)out.size() < k; c--)          // walk from the highest count down
        for (int v : bucket[c])
            if ((int)out.size() < k) out.push_back(v);
    return out;
}

int main() {
    vector<int> nums = {1, 1, 1, 2, 2, 3, 3, 3, 3, 4};
    for (int x : topKHeap(nums, 2)) cout << x << ' ';                     // 1 3 (heap pops weakest first)
    cout << "| ";
    for (int x : topKBucket(nums, 2)) cout << x << ' ';                   // 3 1
    cout << '\n';
}
