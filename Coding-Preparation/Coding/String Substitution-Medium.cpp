Given two strings str1 and str2 of the same length, determine whether you can transform str1 into str2 by doing zero or more conversions.

In one conversion you can convert all occurrences of one character in str1 to any other lowercase English character.

Return true if and only if you can transform str1 into str2.


Input: str1 = "aabcc", str2 = "ccdee"
Output: true
Explanation: Convert 'c' to 'e' then 'b' to 'd' then 'a' to 'c'. Note that the order of conversions matter.

str1 = "aabcc"

a -> 0,1
b -> 2
c -> 3,4

str1 = "ccdee"

c -> 0,1
d -> 2
e -> 3,4

    bool canConvert(string str1, string str2) {
        set<vector<int>> set1, set2;

        for(auto ch = 'a'; ch<='z'; ch++){
            vector<int> occurences;
            for(int i=0;i<str1.size();i++){
                if( str1[i] == ch){
                    occurences.push_back(i);
                }
            }
            set1.insert(occurences);
        }

        for(auto ch = 'a'; ch<='z'; ch++){
            vector<int> occurences;
            for(int i=0;i<str2.size();i++){
                if( str2[i] == ch){
                    occurences.push_back(i);
                }
            }
            set2.insert(occurences);
        }

        if(set1 == set2 ) return true;
        
    }