#include <iostream>
#include <list>
using namespace std;

// splice = cut a node out and re-link it elsewhere. Same node, same address, no copy, no new/delete.
// Read it as: dst.splice(WHERE in dst, FROM which list, WHICH node)   -> "kahan, kisse, kaun"
void show(const char* tag, list<pair<int,int>>& l) {
    cout << tag;
    for (auto& p : l) cout << " [" << p.first << ':' << p.second << " @" << &p << ']';
    cout << '\n';
}

int main() {
    list<pair<int,int>> dll = {{4, 4}, {3, 3}, {1, 1}};
    auto it = next(dll.begin(), 2);                          // the 1:1 node (what pos[1] holds)
    show("before            :", dll);

    dll.splice(dll.begin(), dll, it);                        // move 1:1 to the front
    show("after splice      :", dll);
    cout << "it still points to: " << it->first << " @" << &*it << "  (same address, map needs no update)\n";

    auto kv = *it;                                           // the erase + insert way, for comparison
    dll.erase(it);                                           // node freed -> 'it' (and pos[1]) now dangle
    dll.push_front(kv);                                      // a NEW node; same address here only by luck (allocator
                                                             // reused the freed block) -> 'it' is still officially dead
    show("after erase+insert:", dll);
}
