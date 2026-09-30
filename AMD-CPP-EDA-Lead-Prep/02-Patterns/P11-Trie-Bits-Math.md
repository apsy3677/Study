# P11: Trie, Bit Manipulation, Math

> Practice file: `06-Practice/day3.cpp` · Striver: `Trie.pdf`
> AMD reports: **bit masking / bit manipulation** (Hyderabad), swap two numbers without a temp, Roman numerals, palindrome number, `a^b % c` (Synopsys), segment tree (TechPrep).

---

## Card A: Trie = "a tree whose edges are characters; each node is a prefix"
| | |
|---|---|
| **Triggers** | prefix search, autocomplete, dictionary word search on a grid, longest common prefix, **max XOR pair** (binary trie) |
| **Node** | `array<int,26> next` (index into a node pool, cache-friendly) or `unique_ptr<Node> child[26]`, plus `bool isWord` (and a `count` if needed) |
| **Costs** | insert/search O(L). Memory 26 × nodes → use a map / sorted vector per node for big alphabets. EDA: hierarchical instance names (`top/u_core/u_alu/reg_3`) are stored in tries or **string-interned** tables. |

```cpp
struct Trie {
    struct Node { int next[26]; bool isWord = false; Node() { std::fill(std::begin(next), std::end(next), -1); } };
    vector<Node> pool{Node()};                          // node 0 = root; indices, not pointers
    void insert(const string& w) {
        int cur = 0;
        for (char ch : w) { int c = ch - 'a';
            if (pool[cur].next[c] == -1) { pool[cur].next[c] = (int)pool.size(); pool.emplace_back(); }
            cur = pool[cur].next[c]; }
        pool[cur].isWord = true;
    }
    int walk(const string& p) const { int cur = 0; for (char ch : p) { cur = pool[cur].next[ch - 'a']; if (cur == -1) return -1; } return cur; }
    bool search(const string& w) const { int n = walk(w); return n != -1 && pool[n].isWord; }
    bool startsWith(const string& p) const { return walk(p) != -1; }
};
```
> Note: take the index into `pool` *before* `emplace_back`. A reference into a vector would dangle after reallocation (a classic bug, and a good talking point).

## Card B: Bits, "the 12 lines"
```cpp
(x >> k) & 1            // test bit k
x | (1u << k)           // set
x & ~(1u << k)          // clear
x ^ (1u << k)           // toggle
x & (x - 1)             // drop the lowest set bit   (loop → popcount, Kernighan)
x & -x                  // isolate the lowest set bit (Fenwick tree!)
x && !(x & (x - 1))     // power of two
__builtin_popcount(x), __builtin_ctz(x), __builtin_clz(x)   // C++20: std::popcount, countr_zero, countl_zero
a ^= b; b ^= a; a ^= b; // swap without temp (breaks if &a == &b → both become 0!)
XOR of all = the single number when every other appears twice
for (int s = mask; s; s = (s - 1) & mask)  // enumerate the submasks of mask
```
| Trick | Why |
|---|---|
| Use `unsigned` for shifts | shifting into or out of the sign bit of a signed int is UB (pre-C++20) or implementation-defined |
| `1u << 31`, `1ULL << 40` | the literal's type sets the width |
| Endianness | little-endian (x86/AMD): the least significant byte is at the lowest address. Check with `uint32_t v=1; *(uint8_t*)&v == 1` |
| Reverse bits | swap halves: 16, 8, 4, 2, 1 with masks, or a loop of 32 |
| Gray code | `g = i ^ (i >> 1)` |
| Hardware relevance | bitfields / register masks: `(reg & MASK) >> SHIFT`; flags as `enum class` + operators |

## Card C: Math
- **gcd**: `std::gcd` / Euclid `gcd(a,b) = b ? gcd(b, a%b) : a`. lcm = a / gcd * b (divide first).
- **Fast power mod** (`a^b % c`): square-and-multiply, O(log b). Use `__int128` or mulmod if c > ~3e9.
```cpp
long long power(long long a, long long b, long long m) {
    long long r = 1 % m; a %= m;
    while (b > 0) { if (b & 1) r = r * a % m; a = a * a % m; b >>= 1; }
    return r;
}
```
- **Sieve**: O(n log log n). **Palindrome number**: reverse half the digits. **Overflow check**: `if (x > (INT_MAX - d) / 10)`.

## Card D: Range-query structures (★ stretch; name-drop in EDA context)
| Structure | Ops | When |
|---|---|---|
| Prefix sums | O(1) query, no updates | static arrays |
| **Fenwick (BIT)** | point update + prefix query, O(log n), ~10 lines | counting inversions, sweep-line counts |
| **Segment tree** | range query/update (+lazy), O(log n) | range min/max/sum with updates, rectangle union area |
| Sparse table | O(1) RMQ, static | LCA via Euler tour |
| Interval tree / R-tree | overlap queries on intervals/rectangles | EDA spatial DB, DRC |

```cpp
struct Fenwick { vector<long long> t; Fenwick(int n): t(n + 1) {}
    void add(int i, long long v) { for (++i; i < (int)t.size(); i += i & -i) t[i] += v; }
    long long sum(int i) const { long long s = 0; for (++i; i > 0; i -= i & -i) s += t[i]; return s; } // [0..i]
};
```

---

## Problems (hint ladders)
### P11-1 · Implement Trie (LC 208) ★★ · `Trie`
<details><summary>Approach check</summary>See Card A; discuss the pointer vs index-pool trade-off (allocation count, cache locality, easy serialization).</details>

### P11-2 · Number of 1 Bits / Counting Bits (LC 191/338) ★★ · `countBitsUpTo`
<details><summary>Approach check</summary>Kernighan loop; for 0..n: `bits[i] = bits[i >> 1] + (i & 1)` or `bits[i & (i-1)] + 1`.</details>

### P11-3 · Single Number (LC 136) + two singles (LC 260) ★★ · `singleNumber`
<details><summary>Hint (LC 260)</summary>XOR of all = a^b ≠ 0. Split the numbers by any set bit of a^b.</details>

### P11-4 · Reverse Bits (LC 190) ★ · `reverseBits`
<details><summary>Approach check</summary>Loop 32: `r = (r << 1) | (x & 1); x >>= 1;` using uint32_t.</details>

### P11-5 · Pow(x, n) / a^b mod c ★★ · `powMod`
<details><summary>Approach check</summary>Binary exponentiation; handle negative n for Pow(x,n) with `long long` (because −INT_MIN overflows).</details>

### P11-6 · Integer ↔ Roman (LC 12/13) ★★
<details><summary>Approach check</summary>Int→Roman: greedy over the 13 value/symbol pairs (M, CM, D, CD, C, XC, L, XL, X, IX, V, IV, I).</details>

---

## Recall check
1. Five bit tricks from memory. 2. Why does XOR-swap break when both refer to the same variable? 3. Fenwick `i & -i`: what is it?
4. Trie: pointer nodes vs an index pool: two advantages of the pool.
