# 2390. Removing Stars From a String

[Problem](https://leetcode.com/problems/removing-stars-from-a-string/) · Medium · Stack → Stack

LeetCode tags: string, stack, simulation

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-09-12 20:05 IST · Memory Limit Exceeded · C++

[submission 1047528661](https://leetcode.com/submissions/detail/1047528661/) · tests 32/65

Failing input:

```text
"rcroimdplvbjlolnvsuyfuiosziuzeyciffwkpmtboiojjmbciuvybfcpheembrrgofkdluszemgclmxuexxzobkrvluwfrqccaijbecpbypxkmhpnhosnamebvvfcypihrqludospxkshesixyusfnlayckvuqhxnzihvvsytpdllzucuplyoozvhdspbdssmtnxnmnydswmnyodbnudthjvvbvdhdwexjcfcxxppnpmrctyvlykkhnxhvppbutfkextstklstggqstpdzcpstrdyzbttoorkkkceakgwmuztfmbzfctsjwqghxjnrtmcbrzbhdcgtubagfvspcrrhziylesfymavaguwxrlfwlcofvzrqwtauhjsekmidttkwzrvynqklfzka ... [99602 more chars]
```

Expected:

```text
"rcroimdplvbjlolnvsuyfuiosziuzeyciffwkpmtboiojjmbciuvybfcpheembrrgofkdluszemgclmxuexxzobkrvluwfrqccaijbecpbypxkmhpnhosnamebvvfcypihrqludospxkshesixyusfnlayckvuqhxnzihvvsytpdllzucuplyoozvhdspbdssmtnxnmnydswmnyodbnudthjvvbvdhdwexjcfcxxppnpmrctyvlykkhnxhvppbutfkextstklstggqstpdzcpstrdyzbttoorkkkceakgwmuztfmbzfctsjwqghxjnrtmcbrzbhdcgtubagfvspcrrhziylesfymavaguwxrlfwlcofvzrqwtauhjsekmidttkwzrvynqklfzka ... [99602 more chars]
```

```cpp
class Solution {
public:
    string removeStars(string s) {
        stack<char> result;
        for(auto i:s) {
            if(i == '*') {
                while(result.size()>0) {
                    if(result.top() != '*') {
                        result.pop();
                        break;
                    }
                }
            } else {
                result.push(i);
            }
        }
        string str = "";
        while(result.size()>0) {
            str = result.top() + str;
            result.pop();
        }
        return str;
    }
};
```

## Attempt 2 · 2023-09-12 20:15 IST · Accepted · C++

[submission 1047537156](https://leetcode.com/submissions/detail/1047537156/) · runtime 84 ms

_Code not returned by LeetCode._
