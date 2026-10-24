# 301. Remove Invalid Parentheses

[Problem](https://leetcode.com/problems/remove-invalid-parentheses/) · Hard · Backtracking → BFS/backtrack with pruning

LeetCode tags: string, backtracking, breadth-first-search

Attempts since Mar 2023: 21 · accepted: 15 · failed before first AC: 3

## Attempt 1 · 2023-03-22 23:40 IST · Time Limit Exceeded · C++

[submission 920285535](https://leetcode.com/submissions/detail/920285535/) · tests 117/127

Failing input:

```text
"((s(())()(()))(((((("
```

Expected:

```text
["(s(())()(()))","((s())()(()))","((s(()))(()))","((s(())()()))"]
```

```cpp
class Solution {
    vector<string> ans;
    set<string> valid;
    int minRemoved;
public:
    void recur(string s,string exp, int index, int left, int right, int removed){
        if(index == s.size()){
            if(left == right){
                if(removed <= minRemoved){
                    if(removed < minRemoved){
                        valid.clear();
                        minRemoved = removed;
                    }
                    valid.insert(exp);
                }
            }
            return;
        }
        char ch= s[index];
        int l = exp.size();

        if(ch!='(' && ch != ')'){
            exp += ch;
            recur(s,exp, index+1,left, right, removed);
            exp.erase(l,1);
        }
        else{
            // not taking or deleting
            recur(s,exp,index+1,left,right,removed+1);
            
            exp += ch;

            if(ch == '('){
                recur(s,exp,index+1, left+1,right,removed);
            }
            else if(right <left){
                recur(s,exp,index+1,left, right+1,removed);
            }
            // undo the append
            exp.erase(l,1);

        }
    }
    vector<string> removeInvalidParentheses(string s) {
        minRemoved = INT_MAX;
        string validPara ="";
        recur(s,validPara,0,0,0,0);
        return vector<string>(valid.begin(), valid.end());
    }
};
```

## Attempt 2 · 2023-03-23 00:06 IST · Time Limit Exceeded · C++

[submission 920301430](https://leetcode.com/submissions/detail/920301430/) · tests 123/127

Failing input:

```text
"((((((((((((((((((((aaaaa"
```

Expected:

```text
["aaaaa"]
```

```cpp
class Solution {
    vector<string> ans;
    set<string> valid;
    int minRemoved;
public:
    void recur(string s,string exp, int index, int left, int right, int removed){
        if(index == s.size()){
            if(left == right){
                if(removed <= minRemoved){
                    if(removed < minRemoved){
                        valid.clear();
                        minRemoved = removed;
                    }
                    valid.insert(exp);
                }
            }
            return;
        }
        char ch= s[index];
        int l = exp.size();

        if(ch!='(' && ch != ')'){
            exp += ch;
            recur(s,exp, index+1,left, right, removed);
            exp.erase(l,1);
        }
        else{
            // not taking or deleting
            recur(s,exp,index+1,left,right,removed+1);
            
            exp += ch;

            if(ch == '('){
                recur(s,exp,index+1, left+1,right,removed);
            }
            else if(right <left){
                recur(s,exp,index+1,left, right+1,removed);
            }
            // undo the append
            exp.erase(l,1);

        }
    }

    void recur1(string s,string exp, int index, int left, int right, int left_rem, int right_rem){
        if(index == s.size()){
            if(left_rem == 0 && right_rem == 0){
                valid.insert(exp);
            }
            return;
        }
        char ch= s[index];
        int l = exp.size();

        if(ch!='(' && ch != ')'){
            exp += ch;
            recur1(s,exp, index+1,left, right, left_rem, right_rem);
            exp.erase(l,1);
        }
        else{
            // not taking or deleting
            if((ch == '(' && left_rem > 0) || (ch ==')' && right_rem>0))
                recur1(s,exp,index+1,left,right,
                    left_rem - (ch == '('? 1:0),
                    right_rem - (ch == ')'?1:0));
            
            exp += ch;

            if(ch == '('){
                recur1(s,exp,index+1, left+1,right,left_rem, right_rem);
            }
            else if(right <left){
                recur1(s,exp,index+1,left, right+1,left_rem, right_rem);
            }
            // undo the append
            exp.erase(l,1);

        }
    }

    vector<string> removeInvalidParentheses(string s) {
        minRemoved = INT_MAX;
        string validPara ="";

        int left=0, right=0;

        for(int i=0;i<s.size();i++){
            if(s[i]=='('){
                left++;
            }
            else if(s[i] == ')'){
                left > 0 ? left-- : right++;
            }
        }

        // recur(s,validPara,0,0,0,0);
        recur1(s,validPara,0,0,0,left,right);
        return vector<string>(valid.begin(), valid.end());
    }
};
```

## Attempt 3 · 2023-03-23 00:08 IST · Time Limit Exceeded · C++

[submission 920302443](https://leetcode.com/submissions/detail/920302443/) · tests 123/127

Failing input:

```text
"((((((((((((((((((((aaaaa"
```

Expected:

```text
["aaaaa"]
```

```cpp
class Solution {
    vector<string> ans;
    set<string> valid;
    int minRemoved;
public:
    void recur(string s,string exp, int index, int left, int right, int removed){
        if(index == s.size()){
            if(left == right){
                if(removed <= minRemoved){
                    if(removed < minRemoved){
                        valid.clear();
                        minRemoved = removed;
                    }
                    valid.insert(exp);
                }
            }
            return;
        }
        char ch= s[index];
        int l = exp.size();

        if(ch!='(' && ch != ')'){
            exp += ch;
            recur(s,exp, index+1,left, right, removed);
            exp.erase(l,1);
        }
        else{
            // not taking or deleting
            recur(s,exp,index+1,left,right,removed+1);
            
            exp += ch;

            if(ch == '('){
                recur(s,exp,index+1, left+1,right,removed);
            }
            else if(right <left){
                recur(s,exp,index+1,left, right+1,removed);
            }
            // undo the append
            exp.erase(l,1);

        }
    }

    void recur1(string s,string exp, int index, int left, int right, int left_rem, int right_rem){
        if(index == s.size()){
            if(left_rem == 0 && right_rem == 0){
                valid.insert(exp);
            }
            return;
        }
        char ch= s[index];
        int l = exp.size();

        // not taking or deleting
        if((ch == '(' && left_rem > 0) || (ch ==')' && right_rem>0))
            recur1(s,exp,index+1,left,right,
                left_rem - (ch == '('? 1:0),
                right_rem - (ch == ')'?1:0));

        if(ch!='(' && ch != ')'){
            exp += ch;
            recur1(s,exp, index+1,left, right, left_rem, right_rem);
            exp.erase(l,1);
        }
        else{
            
            exp += ch;

            if(ch == '('){
                recur1(s,exp,index+1, left+1,right,left_rem, right_rem);
            }
            else if(right <left){
                recur1(s,exp,index+1,left, right+1,left_rem, right_rem);
            }
            // undo the append
            exp.erase(l,1);

        }
    }

    vector<string> removeInvalidParentheses(string s) {
        minRemoved = INT_MAX;
        string validPara ="";

        int left=0, right=0;

        for(int i=0;i<s.size();i++){
            if(s[i]=='('){
                left++;
            }
            else if(s[i] == ')'){
                left > 0 ? left-- : right++;
            }
        }

        // recur(s,validPara,0,0,0,0);
        recur1(s,validPara,0,0,0,left,right);
        return vector<string>(valid.begin(), valid.end());
    }
};
```

## Attempt 4 · 2023-03-23 00:12 IST · Accepted · C++

[submission 920304652](https://leetcode.com/submissions/detail/920304652/) · tests 127/127 · runtime 96 ms (beats 42.3%)

```cpp
class Solution {
    vector<string> ans;
    set<string> valid;
    int minRemoved;
public:
    void recur(string s,string exp, int index, int left, int right, int removed){
        if(index == s.size()){
            if(left == right){
                if(removed <= minRemoved){
                    if(removed < minRemoved){
                        valid.clear();
                        minRemoved = removed;
                    }
                    valid.insert(exp);
                }
            }
            return;
        }
        char ch= s[index];
        int l = exp.size();

        if(ch!='(' && ch != ')'){
            exp += ch;
            recur(s,exp, index+1,left, right, removed);
            exp.erase(l,1);
        }
        else{
            // not taking or deleting
            recur(s,exp,index+1,left,right,removed+1);
            
            exp += ch;

            if(ch == '('){
                recur(s,exp,index+1, left+1,right,removed);
            }
            else if(right <left){
                recur(s,exp,index+1,left, right+1,removed);
            }
            // undo the append
            exp.erase(l,1);

        }
    }

    void recur1(string &s,string &exp, int index, int left, int right, int left_rem, int right_rem){
        if(index == s.size()){
            if(left_rem == 0 && right_rem == 0){
                valid.insert(exp);
            }
            return;
        }
        char ch= s[index];
        int l = exp.size();

        // not taking or deleting
        if((ch == '(' && left_rem > 0) || (ch ==')' && right_rem>0))
            recur1(s,exp,index+1,left,right,
                left_rem - (ch == '('? 1:0),
                right_rem - (ch == ')'?1:0));

        if(ch!='(' && ch != ')'){
            exp += ch;
            recur1(s,exp, index+1,left, right, left_rem, right_rem);
            exp.erase(l,1);
        }
        else{
            
            exp += ch;

            if(ch == '('){
                recur1(s,exp,index+1, left+1,right,left_rem, right_rem);
            }
            else if(right <left){
                recur1(s,exp,index+1,left, right+1,left_rem, right_rem);
            }
            // undo the append
            exp.erase(l,1);

        }
    }

    vector<string> removeInvalidParentheses(string s) {
        minRemoved = INT_MAX;
        string validPara ="";

        int left=0, right=0;

        for(int i=0;i<s.size();i++){
            if(s[i]=='('){
                left++;
            }
            else if(s[i] == ')'){
                left > 0 ? left-- : right++;
            }
        }

        // recur(s,validPara,0,0,0,0);
        recur1(s,validPara,0,0,0,left,right);
        return vector<string>(valid.begin(), valid.end());
    }

    void removeInvalid(string& s, int pos, string t, unordered_set<string>& v, int lCount, int rCount, int openCount){
        if(s[pos] == '\0') { if(!openCount) v.insert(t); return ; }
        if(s[pos] == '('){
            if(lCount) removeInvalid(s, pos+1, t, v, lCount-1, rCount, openCount);
            removeInvalid(s, pos+1, t+"(", v, lCount, rCount, openCount+1);
        }
        else if(s[pos] == ')'){
            if(rCount) removeInvalid(s, pos+1, t, v, lCount, rCount-1, openCount);
            if(openCount) removeInvalid(s, pos+1, t+")", v, lCount, rCount, openCount-1);
        }
        else removeInvalid(s, pos+1, t+s[pos], v, lCount, rCount, openCount);
    }
};
```

## Attempt 5 · 2023-03-23 00:17 IST · Accepted · C++

[submission 920307494](https://leetcode.com/submissions/detail/920307494/) · tests 127/127 · runtime 99 ms (beats 42.2%)

```cpp
class Solution {
    vector<string> ans;
    set<string> valid;
    int minRemoved;
public:
    void recur(string s,string exp, int index, int left, int right, int removed){
        if(index == s.size()){
            if(left == right){
                if(removed <= minRemoved){
                    if(removed < minRemoved){
                        valid.clear();
                        minRemoved = removed;
                    }
                    valid.insert(exp);
                }
            }
            return;
        }
        char ch= s[index];
        int l = exp.size();

        if(ch!='(' && ch != ')'){
            exp += ch;
            recur(s,exp, index+1,left, right, removed);
            exp.erase(l,1);
        }
        else{
            // not taking or deleting
            recur(s,exp,index+1,left,right,removed+1);
            
            exp += ch;

            if(ch == '('){
                recur(s,exp,index+1, left+1,right,removed);
            }
            else if(right <left){
                recur(s,exp,index+1,left, right+1,removed);
            }
            // undo the append
            exp.erase(l,1);

        }
    }

    void recur1(string &s,string &exp, int index, int left, int right, int left_rem, int right_rem){
        if(index == s.size()){
            if(left_rem == 0 && right_rem == 0){
                valid.insert(exp);
            }
            return;
        }
        char ch= s[index];
        int l = exp.size();

        // not taking or deleting
        if((ch == '(' && left_rem > 0) || (ch ==')' && right_rem>0))
            recur1(s,exp,index+1,left,right,
                left_rem - (ch == '('? 1:0),
                right_rem - (ch == ')'?1:0));

        if(ch!='(' && ch != ')'){
            exp += ch;
            recur1(s,exp, index+1,left, right, left_rem, right_rem);
            exp.erase(l,1);
        }
        else{
            
            exp += ch;

            if(ch == '('){
                recur1(s,exp,index+1, left+1,right,left_rem, right_rem);
            }
            else if(right <left){
                recur1(s,exp,index+1,left, right+1,left_rem, right_rem);
            }
            // undo the append
            exp.erase(l,1);

        }
    }

    vector<string> removeInvalidParentheses(string s) {
        minRemoved = INT_MAX;
        string validPara ="";

        int left=0, right=0;

        for(int i=0;i<s.size();i++){
            if(s[i]=='('){
                left++;
            }
            else if(s[i] == ')'){
                left > 0 ? left-- : right++;
            }
        }

        // recur(s,validPara,0,0,0,0);
        recur1(s,validPara,0,0,0,left,right);
        return vector<string>(valid.begin(), valid.end());
    }

    void removeInvalid(string& s, int pos, string t, unordered_set<string>& v, int lCount, int rCount, int openCount){
        if(s[pos] == '\0') { if(!openCount) v.insert(t); return ; }
        if(s[pos] == '('){
            if(lCount) removeInvalid(s, pos+1, t, v, lCount-1, rCount, openCount);
            removeInvalid(s, pos+1, t+"(", v, lCount, rCount, openCount+1);
        }
        else if(s[pos] == ')'){
            if(rCount) removeInvalid(s, pos+1, t, v, lCount, rCount-1, openCount);
            if(openCount) removeInvalid(s, pos+1, t+")", v, lCount, rCount, openCount-1);
        }
        else removeInvalid(s, pos+1, t+s[pos], v, lCount, rCount, openCount);
    }
};
```

## Attempt 6 · 2023-12-04 07:03 IST · Accepted · Python3

[submission 1111829707](https://leetcode.com/submissions/detail/1111829707/) · tests 127/127 · runtime 303 ms (beats 42.2%)

```python
class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        def isValid(s):
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        queue =deque([s])
        validStrings = []
        found = False
        while queue:
            current_level = set()
            size = len(queue)
            for _ in range(size):
                s = queue.popleft()
                
                if isValid(s):
                    validStrings.append(s)
                    found = True

                for i in range(len(s)):
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings
```

## Attempt 7 · 2023-12-04 07:04 IST · Accepted · Python3

[submission 1111829774](https://leetcode.com/submissions/detail/1111829774/) · tests 127/127 · runtime 299 ms (beats 42.3%)

```python
class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        def isValid(s):
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        queue =deque([s])
        validStrings = []
        found = False
        current_level = set()
        while queue:
            
            size = len(queue)
            for _ in range(size):
                s = queue.popleft()
                
                if isValid(s):
                    validStrings.append(s)
                    found = True

                for i in range(len(s)):
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings
```

## Attempt 8 · 2023-12-22 07:48 IST · Accepted · Python3

[submission 1125507833](https://leetcode.com/submissions/detail/1125507833/) · tests 127/127 · runtime 244 ms (beats 42.7%)

```python
class Solution:
    def removeInvalidParentheses2(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        '''
        def isValid(s):
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        queue =deque([s])
        validStrings = []
        found = False
        
        while queue:
            current_level = set()
            size = len(queue)
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level
        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings
```

## Attempt 9 · 2023-12-27 08:35 IST · Output Limit Exceeded · Python3

[submission 1129326954](https://leetcode.com/submissions/detail/1129326954/) · tests 86/127

Failing input:

```text
"))(((((()())(()"
```

Expected:

```text
["(()())()","((()))()","((()()))","(((())))"]
```

```python
class Solution:
    def removeInvalidParentheses2(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        '''
        def isValid(s):
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        queue =deque([s])
        validStrings = []
        found = False
        
        while queue:
            current_level = set()
            size = len(queue)
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level
        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings

 

    def removeInvalidParentheses(self, s: str) -> List[str]:
        def isValid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                if count < 0:
                    return False
            return count == 0

        def dfs(s, start, lremove, rremove):
            print(lremove, rremove)
            if lremove == 0 and rremove == 0:
                if isValid(s):
                    ans.add(s)
                return


            print(start)
            for i in range(0, len(s)):
                print(i, s[i:])
                if i > start and s[i] == s[i - 1]:  # Skip duplicates
                    continue
                if s[i] == '(' and lremove > 0:
                    dfs(s[:i] + s[i + 1:], i, lremove - 1, rremove)
                elif s[i] == ')' and rremove > 0:
                    print(s[:i], s[i+1:], i)
                    dfs(s[:i] + s[i + 1:], i, lremove, rremove - 1)

        # Count the number of misplaced left and right parentheses
        lremove = rremove = 0
        for char in s:
            if char == '(':
                lremove += 1
            elif char == ')':
                if lremove > 0:
                    lremove -= 1
                else:
                    rremove += 1

        ans = set()
        dfs(s, 0, lremove, rremove)
        return list(ans)
```

## Attempt 10 · 2023-12-27 08:36 IST · Time Limit Exceeded · Python3

[submission 1129327075](https://leetcode.com/submissions/detail/1129327075/) · tests 98/127

Failing input:

```text
")()(e()))))))(((("
```

Expected:

```text
["((e()))","()(e())"]
```

```python
class Solution:
    def removeInvalidParentheses2(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        '''
        def isValid(s):
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        queue =deque([s])
        validStrings = []
        found = False
        
        while queue:
            current_level = set()
            size = len(queue)
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level
        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings

 

    def removeInvalidParentheses(self, s: str) -> List[str]:
        def isValid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                if count < 0:
                    return False
            return count == 0

        def dfs(s, start, lremove, rremove):
            # print(lremove, rremove)
            if lremove == 0 and rremove == 0:
                if isValid(s):
                    ans.add(s)
                return


            # print(start)
            for i in range(0, len(s)):
                # print(i, s[i:])
                if i > start and s[i] == s[i - 1]:  # Skip duplicates
                    continue
                if s[i] == '(' and lremove > 0:
                    dfs(s[:i] + s[i + 1:], i, lremove - 1, rremove)
                elif s[i] == ')' and rremove > 0:
                    # print(s[:i], s[i+1:], i)
                    dfs(s[:i] + s[i + 1:], i, lremove, rremove - 1)

        # Count the number of misplaced left and right parentheses
        lremove = rremove = 0
        for char in s:
            if char == '(':
                lremove += 1
            elif char == ')':
                if lremove > 0:
                    lremove -= 1
                else:
                    rremove += 1

        ans = set()
        dfs(s, 0, lremove, rremove)
        return list(ans)
```

## Attempt 11 · 2023-12-27 08:36 IST · Accepted · Python3

[submission 1129327268](https://leetcode.com/submissions/detail/1129327268/) · tests 127/127 · runtime 53 ms (beats 70.9%)

```python
class Solution:
    def removeInvalidParentheses2(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        '''
        def isValid(s):
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        queue =deque([s])
        validStrings = []
        found = False
        
        while queue:
            current_level = set()
            size = len(queue)
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level
        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings

 

    def removeInvalidParentheses(self, s: str) -> List[str]:
        def isValid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                if count < 0:
                    return False
            return count == 0

        def dfs(s, start, lremove, rremove):
            # print(lremove, rremove)
            if lremove == 0 and rremove == 0:
                if isValid(s):
                    ans.add(s)
                return


            # print(start)
            for i in range(start, len(s)):
                # print(i, s[i:])
                if i > start and s[i] == s[i - 1]:  # Skip duplicates
                    continue
                if s[i] == '(' and lremove > 0:
                    dfs(s[:i] + s[i + 1:], i, lremove - 1, rremove)
                elif s[i] == ')' and rremove > 0:
                    # print(s[:i], s[i+1:], i)
                    dfs(s[:i] + s[i + 1:], i, lremove, rremove - 1)

        # Count the number of misplaced left and right parentheses
        lremove = rremove = 0
        for char in s:
            if char == '(':
                lremove += 1
            elif char == ')':
                if lremove > 0:
                    lremove -= 1
                else:
                    rremove += 1

        ans = set()
        dfs(s, 0, lremove, rremove)
        return list(ans)
```

## Attempt 12 · 2023-12-31 03:09 IST · Accepted · Python3

[submission 1132507586](https://leetcode.com/submissions/detail/1132507586/) · tests 127/127 · runtime 95 ms (beats 48.8%)

```python
class Solution:
    def removeInvalidParentheses2(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        n* 2^n

        '''
        def isValid(s):
            '''
            to check for valid string - right and left balance 
            if extra right - invalid
            if after balancing, extra left - invalid
            '''
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        # queue to keep track of all states from single removal, two removal ...
        # remove first char from every position to get new states
        # then for each state, remove one more from every position and so on
        queue =deque([s])
        validStrings = []
        found = False
        
        # while still some string to process
        while queue:

            # visited set to avoid duplicates
            current_level = set()

            # current level size
            size = len(queue)

            # process one level at a time
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):

                    # if not already processed
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level
        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings

 

    def removeInvalidParentheses(self, s: str) -> List[str]:
        def isValid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                if count < 0:
                    return False
            return count == 0

        def dfs(s, start, lremove, rremove, level):
            # print(lremove, rremove)

            # base condition 
            # if you use len(s) == start as base condition - you might get valid strings with more than minimum removal like () because it would traverse deep and delete most of chars to get a  valid string with few chars
            
            if lremove == 0 and rremove == 0:
                if isValid(s):
                    ans.add(s)
                return


            # print(start)
            # for each index starting from start in the new string
            for i in range(start, len(s)):
                
                # skip duplicates - if two are some dont' process - would lead to same result
                if i > start and s[i] == s[i - 1]:  # Skip duplicates
                    continue

                # decide wheter to delete left or right or both and decremenet lremove or rremove
                if s[i] == '(' and lremove > 0:
                    dfs(s[:i] + s[i + 1:], i, lremove - 1, rremove, level+1)
                elif s[i] == ')' and rremove > 0:
                    # print(s[:i], s[i+1:], i)
                    print('removing right')
                    dfs(s[:i] + s[i + 1:], i, lremove, rremove - 1, level+1)

        # Count the number of misplaced left and right parentheses
        lremove = rremove = 0
        for char in s:
            if char == '(':
                lremove += 1
            elif char == ')':
                if lremove > 0:
                    lremove -= 1
                else:
                    rremove += 1

        ans = set()
        print(lremove, rremove)
        dfs(s, 0, lremove, rremove,0)
        return list(ans)
```

## Attempt 13 · 2023-12-31 09:02 IST · Accepted · Python3

[submission 1132694948](https://leetcode.com/submissions/detail/1132694948/) · tests 127/127 · runtime 389 ms (beats 41.5%)

```python
class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        
        queue = deque([s])
        visited = set({s})
        result = []
        found= False
        
        def isValid(s):
            bal = 0
            for l in s:
                if l == '(': bal +=1
                if l == ')':
                    if bal <=0:
                        return False
                    else:
                        bal -=1
            return bal == 0

        
        while queue:
            size = len(queue)
            
            for i in range(size):
            
                s = queue.popleft()

                if isValid(s):
                    result.append(s)
                    found = True
                    
                for i in range(len(s)):
                    new_s = s[:i]+s[i+1:]
                    if new_s not in visited:
                        queue.append(new_s)
                        visited.add(new_s)

            if found:
                break
                
        return result
```

## Attempt 14 · 2024-01-14 00:50 IST · Accepted · Python3

[submission 1145309080](https://leetcode.com/submissions/detail/1145309080/) · tests 127/127 · runtime 38 ms (beats 72.8%)

```python
class Solution:
    def removeInvalidParentheses2(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        n* 2^n

        '''
        def isValid(s):
            '''
            to check for valid string - right and left balance 
            if extra right - invalid
            if after balancing, extra left - invalid
            '''
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        # queue to keep track of all states from single removal, two removal ...
        # remove first char from every position to get new states
        # then for each state, remove one more from every position and so on
        queue =deque([s])
        validStrings = []
        found = False
        
        # visited set to avoid duplicates
        current_level = set()

        # while still some string to process
        while queue:



            # current level size
            size = len(queue)

            # process one level at a time
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):

                    # if not already processed
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level

        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings

 

    def removeInvalidParentheses(self, s: str) -> List[str]:
        def isValid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                if count < 0:
                    return False
            return count == 0

        def dfs(s, start, lremove, rremove, level):
            # print(lremove, rremove)

            # base condition 
            # if you use len(s) == start as base condition - you might get valid strings with more than minimum removal like () because it would traverse deep and delete most of chars to get a  valid string with few chars
            
            if lremove == 0 and rremove == 0:
                if isValid(s):
                    ans.add(s)
                return


            # print(start)
            # for each index starting from start in the new string
            for i in range(start, len(s)):
                
                # skip duplicates - if two are some dont' process - would lead to same result
                if i > start and s[i] == s[i - 1]:  # Skip duplicates
                    continue

                # decide wheter to delete left or right or both and decremenet lremove or rremove
                if s[i] == '(' and lremove > 0:
                    dfs(s[:i] + s[i + 1:], i, lremove - 1, rremove, level+1)
                elif s[i] == ')' and rremove > 0:
                    # print(s[:i], s[i+1:], i)
                    print('removing right')
                    dfs(s[:i] + s[i + 1:], i, lremove, rremove - 1, level+1)

        # Count the number of misplaced left and right parentheses
        lremove = rremove = 0
        for char in s:
            if char == '(':
                lremove += 1
            elif char == ')':
                if lremove > 0:
                    lremove -= 1
                else:
                    rremove += 1

        ans = set()
        print(lremove, rremove)
        dfs(s, 0, lremove, rremove,0)
        return list(ans)

    def removeInvalidParentheses(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []

        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        def remove(s, start, open_bal, close_bal):
            if open_bal ==0 and close_bal ==0:
                if is_valid(s):
                    result.append(s[:])
                return

            # for each index, remove the index
            for indx in range(start, len(s)):
                # remove indx
                if indx>0 and s[indx-1] == s[indx]:
                    continue
                if s[indx]=='(' and open_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal-1, close_bal)
                elif s[indx]==')' and close_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal, close_bal-1)

        remove(s, 0, open_bal, close_bal)
        return result
```

## Attempt 15 · 2024-01-14 00:58 IST · Wrong Answer · Python3

[submission 1145314605](https://leetcode.com/submissions/detail/1145314605/) · tests 29/127

Failing input:

```text
")(f"
```

Expected:

```text
["f"]
```

Your output:

```text
[""]
```

```python
class Solution:
    def removeInvalidParentheses2(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        n* 2^n

        '''
        def isValid(s):
            '''
            to check for valid string - right and left balance 
            if extra right - invalid
            if after balancing, extra left - invalid
            '''
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        # queue to keep track of all states from single removal, two removal ...
        # remove first char from every position to get new states
        # then for each state, remove one more from every position and so on
        queue =deque([s])
        validStrings = []
        found = False
        
        # visited set to avoid duplicates
        current_level = set()

        # while still some string to process
        while queue:



            # current level size
            size = len(queue)

            # process one level at a time
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):

                    # if not already processed
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level

        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings

 

    def removeInvalidParentheses(self, s: str) -> List[str]:
        def isValid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                if count < 0:
                    return False
            return count == 0

        def dfs(s, start, lremove, rremove, level):
            # print(lremove, rremove)

            # base condition 
            # if you use len(s) == start as base condition - you might get valid strings with more than minimum removal like () because it would traverse deep and delete most of chars to get a  valid string with few chars
            
            if lremove == 0 and rremove == 0:
                if isValid(s):
                    ans.add(s)
                return


            # print(start)
            # for each index starting from start in the new string
            for i in range(start, len(s)):
                
                # skip duplicates - if two are some dont' process - would lead to same result
                if i > start and s[i] == s[i - 1]:  # Skip duplicates
                    continue

                # decide wheter to delete left or right or both and decremenet lremove or rremove
                if s[i] == '(' and lremove > 0:
                    dfs(s[:i] + s[i + 1:], i, lremove - 1, rremove, level+1)
                elif s[i] == ')' and rremove > 0:
                    # print(s[:i], s[i+1:], i)
                    print('removing right')
                    dfs(s[:i] + s[i + 1:], i, lremove, rremove - 1, level+1)

        # Count the number of misplaced left and right parentheses
        lremove = rremove = 0
        for char in s:
            if char == '(':
                lremove += 1
            elif char == ')':
                if lremove > 0:
                    lremove -= 1
                else:
                    rremove += 1

        ans = set()
        print(lremove, rremove)
        dfs(s, 0, lremove, rremove,0)
        return list(ans)

    def removeInvalidParentheses(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []

        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        def remove(s, start, open_bal, close_bal):
            if open_bal ==0 and close_bal ==0:
                if is_valid(s):
                    result.append(s[:])
                return

            # for each index, remove the index
            for indx in range(start, len(s)):
                # remove indx
                if indx>0 and s[indx-1] == s[indx]:
                    continue
                if s[indx]=='(' and open_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal-1, close_bal)
                elif s[indx]==')' and close_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal, close_bal-1)

        remove(s, 0, open_bal, close_bal)
        return result

    def removeInvalidParentheses(self, s: str) -> List[str]:
        queue = deque([s])
        visited= set({s})
        result = []
        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0
        found = False
        while queue:
            
            for _ in range(len(queue)):
                new_s = queue.popleft()

                if is_valid(new_s):
                    result.append(new_s)
                    found = True

                for indx in range(len(new_s)):
                    if s[:indx] + s[indx+1:]  not in visited:
                        queue.append(s[:indx] + s[indx+1:])
                        visited.add(s[:indx] + s[indx+1:])

            if found:
                break
        return result if len(result) else [""]
```

## Attempt 16 · 2024-01-14 01:04 IST · Accepted · Python3

[submission 1145318187](https://leetcode.com/submissions/detail/1145318187/) · tests 127/127 · runtime 154 ms (beats 46.3%)

```python
class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        n* 2^n

        '''
        def isValid(s):
            '''
            to check for valid string - right and left balance 
            if extra right - invalid
            if after balancing, extra left - invalid
            '''
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        # queue to keep track of all states from single removal, two removal ...
        # remove first char from every position to get new states
        # then for each state, remove one more from every position and so on
        queue =deque([s])
        validStrings = []
        found = False
        
        # visited set to avoid duplicates
        current_level = set()

        # while still some string to process
        while queue:



            # current level size
            size = len(queue)

            # process one level at a time
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):
                    if s[i] not in '()':
                        continue
                    # if not already processed
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses8(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level

        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings

 

    def removeInvalidParentheses9(self, s: str) -> List[str]:
        def isValid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                if count < 0:
                    return False
            return count == 0

        def dfs(s, start, lremove, rremove, level):
            # print(lremove, rremove)

            # base condition 
            # if you use len(s) == start as base condition - you might get valid strings with more than minimum removal like () because it would traverse deep and delete most of chars to get a  valid string with few chars
            
            if lremove == 0 and rremove == 0:
                if isValid(s):
                    ans.add(s)
                return


            # print(start)
            # for each index starting from start in the new string
            for i in range(start, len(s)):
                
                # skip duplicates - if two are some dont' process - would lead to same result
                if i > start and s[i] == s[i - 1]:  # Skip duplicates
                    continue

                # decide wheter to delete left or right or both and decremenet lremove or rremove
                if s[i] == '(' and lremove > 0:
                    dfs(s[:i] + s[i + 1:], i, lremove - 1, rremove, level+1)
                elif s[i] == ')' and rremove > 0:
                    # print(s[:i], s[i+1:], i)
                    print('removing right')
                    dfs(s[:i] + s[i + 1:], i, lremove, rremove - 1, level+1)

        # Count the number of misplaced left and right parentheses
        lremove = rremove = 0
        for char in s:
            if char == '(':
                lremove += 1
            elif char == ')':
                if lremove > 0:
                    lremove -= 1
                else:
                    rremove += 1

        ans = set()
        print(lremove, rremove)
        dfs(s, 0, lremove, rremove,0)
        return list(ans)

    def removeInvalidParentheses4(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []

        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        def remove(s, start, open_bal, close_bal):
            if open_bal ==0 and close_bal ==0:
                if is_valid(s):
                    result.append(s[:])
                return

            # for each index, remove the index
            for indx in range(start, len(s)):
                # remove indx
                if indx>0 and s[indx-1] == s[indx]:
                    continue
                if s[indx]=='(' and open_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal-1, close_bal)
                elif s[indx]==')' and close_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal, close_bal-1)

        remove(s, 0, open_bal, close_bal)
        return result

    def removeInvalidParentheses5(self, s: str) -> List[str]:
        queue = deque([s])
        visited= set()
        result = []
        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0
        
        found = False
        while queue:
            
            for _ in range(len(queue)):
                new_s = queue.popleft()

                if is_valid(new_s):
                    result.append(new_s)
                    found = True

                for indx in range(len(new_s)):
                    if new_s[indx] not in '()':
                        continue
                    if s[:indx] + s[indx+1:]  not in visited:
                        queue.append(s[:indx] + s[indx+1:])
                        visited.add(s[:indx] + s[indx+1:])

            if found:
                break
        return result
```

## Attempt 17 · 2024-01-22 08:21 IST · Accepted · Python3

[submission 1153143209](https://leetcode.com/submissions/detail/1153143209/) · tests 127/127 · runtime 146 ms (beats 46.8%)

```python
class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        n* 2^n

        '''
        def isValid(s):
            '''
            to check for valid string - right and left balance 
            if extra right - invalid
            if after balancing, extra left - invalid
            '''
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        # queue to keep track of all states from single removal, two removal ...
        # remove first char from every position to get new states
        # then for each state, remove one more from every position and so on
        queue =deque([s])
        validStrings = []
        found = False
        
        # visited set to avoid duplicates
        current_level = set()

        # while still some string to process
        while queue:



            # current level size
            size = len(queue)

            # process one level at a time
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):
                    if s[i] not in '()':
                        continue
                    # if not already processed
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses8(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level

        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings

 

    def removeInvalidParentheses9(self, s: str) -> List[str]:
        def isValid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                if count < 0:
                    return False
            return count == 0

        def dfs(s, start, lremove, rremove, level):
            # print(lremove, rremove)

            # base condition 
            # if you use len(s) == start as base condition - you might get valid strings with more than minimum removal like () because it would traverse deep and delete most of chars to get a  valid string with few chars
            
            if lremove == 0 and rremove == 0:
                if isValid(s):
                    ans.add(s)
                return


            # print(start)
            # for each index starting from start in the new string
            for i in range(start, len(s)):
                
                # skip duplicates - if two are some dont' process - would lead to same result
                if i > start and s[i] == s[i - 1]:  # Skip duplicates
                    continue

                # decide wheter to delete left or right or both and decremenet lremove or rremove
                if s[i] == '(' and lremove > 0:
                    dfs(s[:i] + s[i + 1:], i, lremove - 1, rremove, level+1)
                elif s[i] == ')' and rremove > 0:
                    # print(s[:i], s[i+1:], i)
                    print('removing right')
                    dfs(s[:i] + s[i + 1:], i, lremove, rremove - 1, level+1)

        # Count the number of misplaced left and right parentheses
        lremove = rremove = 0
        for char in s:
            if char == '(':
                lremove += 1
            elif char == ')':
                if lremove > 0:
                    lremove -= 1
                else:
                    rremove += 1

        ans = set()
        print(lremove, rremove)
        dfs(s, 0, lremove, rremove,0)
        return list(ans)

    def removeInvalidParentheses4(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []

        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        def remove(s, start, open_bal, close_bal):
            if open_bal ==0 and close_bal ==0:
                if is_valid(s):
                    result.append(s[:])
                return

            # for each index, remove the index
            for indx in range(start, len(s)):
                # remove indx
                if indx>0 and s[indx-1] == s[indx]:
                    continue
                if s[indx]=='(' and open_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal-1, close_bal)
                elif s[indx]==')' and close_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal, close_bal-1)

        remove(s, 0, open_bal, close_bal)
        return result

    def removeInvalidParentheses(self, s: str) -> List[str]:
        queue = deque([s])
        visited= set()
        result = []
        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0
        
        found = False
        while queue:
            
            for _ in range(len(queue)):
                new_s = queue.popleft()

                if is_valid(new_s):
                    result.append(new_s)
                    found = True

                for indx in range(len(new_s)):
                    if new_s[indx] not in '()':
                        continue
                    if new_s[:indx] + new_s[indx+1:]  not in visited:
                        queue.append(new_s[:indx] + new_s[indx+1:])
                        visited.add(new_s[:indx] + new_s[indx+1:])

            if found:
                break
        return result

    def removeInvalidParentheses4(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []
        memo = {}
        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        def remove(s, start, open_bal, close_bal):
            if open_bal ==0 and close_bal ==0:
                if is_valid(s):
                    result.append(s[:])
                    memo[(s, open_bal, close_bal)] = result
                return

            tmp_result = []

            # for each index, remove the index
            for indx in range(start, len(s)):
                # remove indx
                if indx>0 and s[indx-1] == s[indx]:
                    continue
                if s[indx]=='(' and open_bal>0:
                    tmp_result += remove(s[:indx]+s[indx+1:], indx, open_bal-1, close_bal)
                elif s[indx]==')' and close_bal>0:
                    tmp_result += remove(s[:indx]+s[indx+1:], indx, open_bal, close_bal-1)
            
            memo[(s, open_bal, close_bal)] = tmp_result 

            return  memo[(s, open_bal, close_bal)]
        
        remove(s, 0, open_bal, close_bal)
        return result
```

## Attempt 18 · 2024-01-22 08:21 IST · Accepted · Python3

[submission 1153143273](https://leetcode.com/submissions/detail/1153143273/) · tests 127/127 · runtime 147 ms (beats 46.7%)

```python
class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        n* 2^n

        '''
        def isValid(s):
            '''
            to check for valid string - right and left balance 
            if extra right - invalid
            if after balancing, extra left - invalid
            '''
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        # queue to keep track of all states from single removal, two removal ...
        # remove first char from every position to get new states
        # then for each state, remove one more from every position and so on
        queue =deque([s])
        validStrings = []
        found = False
        
        # visited set to avoid duplicates
        current_level = set()

        # while still some string to process
        while queue:



            # current level size
            size = len(queue)

            # process one level at a time
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):
                    if s[i] not in '()':
                        continue
                    # if not already processed
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses8(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level

        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings

 

    def removeInvalidParentheses9(self, s: str) -> List[str]:
        def isValid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                if count < 0:
                    return False
            return count == 0

        def dfs(s, start, lremove, rremove, level):
            # print(lremove, rremove)

            # base condition 
            # if you use len(s) == start as base condition - you might get valid strings with more than minimum removal like () because it would traverse deep and delete most of chars to get a  valid string with few chars
            
            if lremove == 0 and rremove == 0:
                if isValid(s):
                    ans.add(s)
                return


            # print(start)
            # for each index starting from start in the new string
            for i in range(start, len(s)):
                
                # skip duplicates - if two are some dont' process - would lead to same result
                if i > start and s[i] == s[i - 1]:  # Skip duplicates
                    continue

                # decide wheter to delete left or right or both and decremenet lremove or rremove
                if s[i] == '(' and lremove > 0:
                    dfs(s[:i] + s[i + 1:], i, lremove - 1, rremove, level+1)
                elif s[i] == ')' and rremove > 0:
                    # print(s[:i], s[i+1:], i)
                    print('removing right')
                    dfs(s[:i] + s[i + 1:], i, lremove, rremove - 1, level+1)

        # Count the number of misplaced left and right parentheses
        lremove = rremove = 0
        for char in s:
            if char == '(':
                lremove += 1
            elif char == ')':
                if lremove > 0:
                    lremove -= 1
                else:
                    rremove += 1

        ans = set()
        print(lremove, rremove)
        dfs(s, 0, lremove, rremove,0)
        return list(ans)

    def removeInvalidParentheses4(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []

        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        def remove(s, start, open_bal, close_bal):
            if open_bal ==0 and close_bal ==0:
                if is_valid(s):
                    result.append(s[:])
                return

            # for each index, remove the index
            for indx in range(start, len(s)):
                # remove indx
                if indx>0 and s[indx-1] == s[indx]:
                    continue
                if s[indx]=='(' and open_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal-1, close_bal)
                elif s[indx]==')' and close_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal, close_bal-1)

        remove(s, 0, open_bal, close_bal)
        return result

    def removeInvalidParentheses(self, s: str) -> List[str]:
        queue = deque([s])
        visited= set()
        result = []
        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0
        
        found = False
        while queue:
            
            for _ in range(len(queue)):
                new_s = queue.popleft()

                if is_valid(new_s):
                    result.append(new_s)
                    found = True

                for indx in range(len(new_s)):
                    if new_s[indx] not in '()':
                        continue
                    if new_s[:indx] + new_s[indx+1:]  not in visited:
                        queue.append(new_s[:indx] + new_s[indx+1:])
                        visited.add(new_s[:indx] + new_s[indx+1:])

            if found:
                break
        return result

    def removeInvalidParentheses4(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []
        memo = {}
        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        def remove(s, start, open_bal, close_bal):
            if open_bal ==0 and close_bal ==0:
                if is_valid(s):
                    result.append(s[:])
                    memo[(s, open_bal, close_bal)] = result
                return

            tmp_result = []

            # for each index, remove the index
            for indx in range(start, len(s)):
                # remove indx
                if indx>0 and s[indx-1] == s[indx]:
                    continue
                if s[indx]=='(' and open_bal>0:
                    tmp_result += remove(s[:indx]+s[indx+1:], indx, open_bal-1, close_bal)
                elif s[indx]==')' and close_bal>0:
                    tmp_result += remove(s[:indx]+s[indx+1:], indx, open_bal, close_bal-1)
            
            memo[(s, open_bal, close_bal)] = tmp_result 

            return  memo[(s, open_bal, close_bal)]
        
        remove(s, 0, open_bal, close_bal)
        return result
```

## Attempt 19 · 2024-01-22 08:30 IST · Accepted · Python3

[submission 1153148447](https://leetcode.com/submissions/detail/1153148447/) · tests 127/127 · runtime 58 ms (beats 70.5%)

```python
class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        n* 2^n

        '''
        def isValid(s):
            '''
            to check for valid string - right and left balance 
            if extra right - invalid
            if after balancing, extra left - invalid
            '''
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        # queue to keep track of all states from single removal, two removal ...
        # remove first char from every position to get new states
        # then for each state, remove one more from every position and so on
        queue =deque([s])
        validStrings = []
        found = False
        
        # visited set to avoid duplicates
        current_level = set()

        # while still some string to process
        while queue:



            # current level size
            size = len(queue)

            # process one level at a time
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):
                    if s[i] not in '()':
                        continue
                    # if not already processed
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses8(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level

        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings

 

    def removeInvalidParentheses9(self, s: str) -> List[str]:
        def isValid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                if count < 0:
                    return False
            return count == 0

        def dfs(s, start, lremove, rremove, level):
            # print(lremove, rremove)

            # base condition 
            # if you use len(s) == start as base condition - you might get valid strings with more than minimum removal like () because it would traverse deep and delete most of chars to get a  valid string with few chars
            
            if lremove == 0 and rremove == 0:
                if isValid(s):
                    ans.add(s)
                return


            # print(start)
            # for each index starting from start in the new string
            for i in range(start, len(s)):
                
                # skip duplicates - if two are some dont' process - would lead to same result
                if i > start and s[i] == s[i - 1]:  # Skip duplicates
                    continue

                # decide wheter to delete left or right or both and decremenet lremove or rremove
                if s[i] == '(' and lremove > 0:
                    dfs(s[:i] + s[i + 1:], i, lremove - 1, rremove, level+1)
                elif s[i] == ')' and rremove > 0:
                    # print(s[:i], s[i+1:], i)
                    print('removing right')
                    dfs(s[:i] + s[i + 1:], i, lremove, rremove - 1, level+1)

        # Count the number of misplaced left and right parentheses
        lremove = rremove = 0
        for char in s:
            if char == '(':
                lremove += 1
            elif char == ')':
                if lremove > 0:
                    lremove -= 1
                else:
                    rremove += 1

        ans = set()
        print(lremove, rremove)
        dfs(s, 0, lremove, rremove,0)
        return list(ans)

    def removeInvalidParentheses4(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []

        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        def remove(s, start, open_bal, close_bal):
            if open_bal ==0 and close_bal ==0:
                if is_valid(s):
                    result.append(s[:])
                return

            # for each index, remove the index
            for indx in range(start, len(s)):
                # remove indx
                if indx>0 and s[indx-1] == s[indx]:
                    continue
                if s[indx]=='(' and open_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal-1, close_bal)
                elif s[indx]==')' and close_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal, close_bal-1)

        remove(s, 0, open_bal, close_bal)
        return result

    def removeInvalidParentheses(self, s: str) -> List[str]:
        queue = deque([s])
        visited= set()
        result = []
        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0
        
        found = False
        while queue:
            
            for _ in range(len(queue)):
                new_s = queue.popleft()

                if is_valid(new_s):
                    result.append(new_s)
                    found = True

                for indx in range(len(new_s)):
                    if new_s[indx] not in '()':
                        continue
                    if new_s[:indx] + new_s[indx+1:]  not in visited:
                        queue.append(new_s[:indx] + new_s[indx+1:])
                        visited.add(new_s[:indx] + new_s[indx+1:])

            if found:
                break
        return result

    def removeInvalidParentheses(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []
        memo = {}
        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        memo = {}

        def remove(s, start, open_bal, close_bal):
            if (s, open_bal, close_bal) in memo:
                return memo[(s, open_bal, close_bal)]

            if open_bal == 0 and close_bal == 0:
                if is_valid(s):
                    result.append(s[:])
                memo[(s, open_bal, close_bal)] = result
                return result

            temp_result = []
            for indx in range(start, len(s)):
                if indx > 0 and s[indx-1] == s[indx]:
                    continue
                if s[indx] == '(' and open_bal > 0:
                    temp_result += remove(s[:indx] + s[indx+1:], indx, open_bal - 1, close_bal)
                elif s[indx] == ')' and close_bal > 0:
                    temp_result += remove(s[:indx] + s[indx+1:], indx, open_bal, close_bal - 1)

            memo[(s, open_bal, close_bal)] = temp_result
            return temp_result

        remove(s, 0, open_bal, close_bal)
        return result
```

## Attempt 20 · 2024-02-10 01:54 IST · Accepted · Python3

[submission 1170928533](https://leetcode.com/submissions/detail/1170928533/) · tests 127/127 · runtime 52 ms (beats 71.0%)

```python
class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        n* 2^n

        '''
        def isValid(s):
            '''
            to check for valid string - right and left balance 
            if extra right - invalid
            if after balancing, extra left - invalid
            '''
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        # queue to keep track of all states from single removal, two removal ...
        # remove first char from every position to get new states
        # then for each state, remove one more from every position and so on
        queue =deque([s])
        validStrings = []
        found = False
        
        # visited set to avoid duplicates
        current_level = set()

        # while still some string to process
        while queue:



            # current level size
            size = len(queue)

            # process one level at a time
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):
                    if s[i] not in '()':
                        continue
                    # if not already processed
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses8(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level

        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings

 

    def removeInvalidParentheses9(self, s: str) -> List[str]:
        def isValid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                if count < 0:
                    return False
            return count == 0

        def dfs(s, start, lremove, rremove, level):
            # print(lremove, rremove)

            # base condition 
            # if you use len(s) == start as base condition - you might get valid strings with more than minimum removal like () because it would traverse deep and delete most of chars to get a  valid string with few chars
            
            if lremove == 0 and rremove == 0:
                if isValid(s):
                    ans.add(s)
                return


            # print(start)
            # for each index starting from start in the new string
            for i in range(start, len(s)):
                
                # skip duplicates - if two are some dont' process - would lead to same result
                if i > start and s[i] == s[i - 1]:  # Skip duplicates
                    continue

                # decide wheter to delete left or right or both and decremenet lremove or rremove
                if s[i] == '(' and lremove > 0:
                    dfs(s[:i] + s[i + 1:], i, lremove - 1, rremove, level+1)
                elif s[i] == ')' and rremove > 0:
                    # print(s[:i], s[i+1:], i)
                    print('removing right')
                    dfs(s[:i] + s[i + 1:], i, lremove, rremove - 1, level+1)

        # Count the number of misplaced left and right parentheses
        lremove = rremove = 0
        for char in s:
            if char == '(':
                lremove += 1
            elif char == ')':
                if lremove > 0:
                    lremove -= 1
                else:
                    rremove += 1

        ans = set()
        print(lremove, rremove)
        dfs(s, 0, lremove, rremove,0)
        return list(ans)

    def removeInvalidParentheses4(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []

        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        def remove(s, start, open_bal, close_bal):
            if open_bal ==0 and close_bal ==0:
                if is_valid(s):
                    result.append(s[:])
                return

            # for each index, remove the index
            for indx in range(start, len(s)):
                # remove indx
                if indx>0 and s[indx-1] == s[indx]:
                    continue
                if s[indx]=='(' and open_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal-1, close_bal)
                elif s[indx]==')' and close_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal, close_bal-1)

        remove(s, 0, open_bal, close_bal)
        return result

    def removeInvalidParentheses(self, s: str) -> List[str]:
        queue = deque([s])
        visited= set()
        result = []
        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0
        
        found = False
        while queue:
            
            for _ in range(len(queue)):
                new_s = queue.popleft()

                if is_valid(new_s):
                    result.append(new_s)
                    found = True

                for indx in range(len(new_s)):
                    if new_s[indx] not in '()':
                        continue
                    if new_s[:indx] + new_s[indx+1:]  not in visited:
                        queue.append(new_s[:indx] + new_s[indx+1:])
                        visited.add(new_s[:indx] + new_s[indx+1:])

            if found:
                break
        return result

    def removeInvalidParentheses(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []
        memo = {}
        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        memo = {}

        def remove(s, start, open_bal, close_bal):
            if (s, open_bal, close_bal) in memo:
                return memo[(s, open_bal, close_bal)]

            if open_bal == 0 and close_bal == 0:
                print(s,result)
                if is_valid(s):
                    result.append(s[:])
                else:
                    print('invalid but saving')
                    print(result)
                memo[(s, open_bal, close_bal)] = result
                return result

            temp_result = []
            for indx in range(start, len(s)):
                if indx > 0 and s[indx-1] == s[indx]:
                    continue
                if s[indx] == '(' and open_bal > 0:
                    temp_result += remove(s[:indx] + s[indx+1:], indx, open_bal - 1, close_bal)
                elif s[indx] == ')' and close_bal > 0:
                    temp_result += remove(s[:indx] + s[indx+1:], indx, open_bal, close_bal - 1)

            memo[(s, open_bal, close_bal)] = temp_result
            return temp_result

        remove(s, 0, open_bal, close_bal)
        print(memo)
        return result
        

    def removeInvalidParentheses(self, s: str) -> List[str]:
        def isValid(s):
            lopen = 0
            for l in s:
                if l =='(': lopen+=1
                if l==')': 
                    if lopen >0:
                        lopen -=1
                    else:
                        return False
            return lopen ==0

        lopen = lclose = 0
        for l in s:
            if l =='(': lopen+=1
            if l==')': 
                if lopen >0:
                    lopen -=1
                else:
                    lclose +=1
        result = []
        def remove(s, start, lopen, lclose):
            if lopen ==0 and lclose==0:
                if isValid(s):
                    result.append(s[:])
                return 

            for indx in range(start, len(s)):
                if indx > 0 and s[indx-1] == s[indx]:
                    continue
                new_s = s[:indx]+ s[indx+1:]
                  
                if s[indx] =='(' and lopen >0:
                    remove(new_s, indx, lopen-1, lclose)
                if s[indx] ==')' and lclose >0:
                    remove(new_s, indx,  lopen, lclose-1)

        remove(s, 0, lopen, lclose)
        return result 
                
    def removeInvalidParentheses2(self, s: str) -> List[str]:
        def is_valid(s):
            lopen = 0
            for l in s:
                if l =='(': lopen+=1
                if l==')': 
                    if lopen >0:
                        lopen -=1
                    else:
                        return False
            return lopen ==0

        queue = deque([s])
        visited = set({s})
        found = False
        result = []
        while queue:
            for _ in range(len(queue)):
                new_s = queue.popleft()
                
                if is_valid(new_s):
                    result.append(new_s[:])
                    found = True

                for idx in range(len(new_s)):
                    if new_s[idx] not in '()':
                        continue

                    if new_s[:idx] + new_s[idx+1:] not in visited:
                        visited.add( new_s[:idx] + new_s[idx+1:])
                        queue.append( new_s[:idx] + new_s[idx+1:])
            if found:
                break

        return result
```

## Attempt 21 · 2024-02-10 02:04 IST · Accepted · Python3

[submission 1170933737](https://leetcode.com/submissions/detail/1170933737/) · tests 127/127 · runtime 136 ms (beats 47.3%)

```python
class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        '''
        queue maintains new state after removing 0 char at 0 level
        1 at level 1 , 2 at level 2 and so on
        it maintains new state after removal of one more character 

        n* 2^n

        '''
        def isValid(s):
            '''
            to check for valid string - right and left balance 
            if extra right - invalid
            if after balancing, extra left - invalid
            '''
            balance = 0
            for l in s:
                if l =='(': balance +=1
                elif l ==')':
                    if balance <=0:
                        return False
                    balance -=1
            return balance == 0

        # queue to keep track of all states from single removal, two removal ...
        # remove first char from every position to get new states
        # then for each state, remove one more from every position and so on
        queue =deque([s])
        validStrings = []
        found = False
        
        # visited set to avoid duplicates
        current_level = set()

        # while still some string to process
        while queue:



            # current level size
            size = len(queue)

            # process one level at a time
            for _ in range(size):
                s = queue.popleft()
                
                ## check if valid string
                ## process all strings at this level 
                ## after this it won't be minimum removals
                if isValid(s):
                    validStrings.append(s)
                    found = True

                # remove each chracter and add it to queue
                for i in range(len(s)):
                    if s[i] not in '()':
                        continue
                    # if not already processed
                    if s[:i] + s[i+1:] not in current_level:
                        queue.append(s[:i] + s[i+1:])
                        current_level.add(s[:i] + s[i+1:])

            if found:
                break
        
        return validStrings

    def removeInvalidParentheses8(self, s: str) -> List[str]:
        '''
        for each string remove from all the positions
        since we have to find all the valid string with minimal removal -> traverse level by level using len(size) and once you find a valid string don't process next level just process all strings at this level

        '''

        queue = deque([s]) # number of deletions
        found = False
        validStrings = []


        # check if the current parenthesis string is balanced
        def isBalanced(s):
            bal = 0
            for l in s:
                if l =='(': bal+=1
                elif l ==')':
                    if bal <=0:
                        return False
                    bal -=1
            return bal==0

       
        #
        while queue:
            visited = set()
            size = len(queue)
            for i in range(size):
                current = queue.popleft()

                # print('checking', current)
                if isBalanced(current):
                    # print('found the string')
                    found = True
                    validStrings.append(current)
                    
                for i in range(len(current)):
                    new_s = current[:i] + current[i+1:]
                    if new_s not in visited:
                        queue.append((new_s))
                        visited.add(new_s)

            if found:
                break

        return validStrings

 

    def removeInvalidParentheses9(self, s: str) -> List[str]:
        def isValid(s):
            count = 0
            for char in s:
                if char == '(':
                    count += 1
                elif char == ')':
                    count -= 1
                if count < 0:
                    return False
            return count == 0

        def dfs(s, start, lremove, rremove, level):
            # print(lremove, rremove)

            # base condition 
            # if you use len(s) == start as base condition - you might get valid strings with more than minimum removal like () because it would traverse deep and delete most of chars to get a  valid string with few chars
            
            if lremove == 0 and rremove == 0:
                if isValid(s):
                    ans.add(s)
                return


            # print(start)
            # for each index starting from start in the new string
            for i in range(start, len(s)):
                
                # skip duplicates - if two are some dont' process - would lead to same result
                if i > start and s[i] == s[i - 1]:  # Skip duplicates
                    continue

                # decide wheter to delete left or right or both and decremenet lremove or rremove
                if s[i] == '(' and lremove > 0:
                    dfs(s[:i] + s[i + 1:], i, lremove - 1, rremove, level+1)
                elif s[i] == ')' and rremove > 0:
                    # print(s[:i], s[i+1:], i)
                    print('removing right')
                    dfs(s[:i] + s[i + 1:], i, lremove, rremove - 1, level+1)

        # Count the number of misplaced left and right parentheses
        lremove = rremove = 0
        for char in s:
            if char == '(':
                lremove += 1
            elif char == ')':
                if lremove > 0:
                    lremove -= 1
                else:
                    rremove += 1

        ans = set()
        print(lremove, rremove)
        dfs(s, 0, lremove, rremove,0)
        return list(ans)

    def removeInvalidParentheses4(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []

        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        def remove(s, start, open_bal, close_bal):
            if open_bal ==0 and close_bal ==0:
                if is_valid(s):
                    result.append(s[:])
                return

            # for each index, remove the index
            for indx in range(start, len(s)):
                # remove indx
                if indx>0 and s[indx-1] == s[indx]:
                    continue
                if s[indx]=='(' and open_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal-1, close_bal)
                elif s[indx]==')' and close_bal>0:
                    remove(s[:indx]+s[indx+1:], indx, open_bal, close_bal-1)

        remove(s, 0, open_bal, close_bal)
        return result

    def removeInvalidParentheses(self, s: str) -> List[str]:
        queue = deque([s])
        visited= set()
        result = []
        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0
        
        found = False
        while queue:
            
            for _ in range(len(queue)):
                new_s = queue.popleft()

                if is_valid(new_s):
                    result.append(new_s)
                    found = True

                for indx in range(len(new_s)):
                    if new_s[indx] not in '()':
                        continue
                    if new_s[:indx] + new_s[indx+1:]  not in visited:
                        queue.append(new_s[:indx] + new_s[indx+1:])
                        visited.add(new_s[:indx] + new_s[indx+1:])

            if found:
                break
        return result

    def removeInvalidParentheses(self, s: str) -> List[str]:
        open_bal = 0
        close_bal = 0
        for l in s:
            if l =='(': open_bal +=1
            elif l ==')':
                if open_bal >0:
                    open_bal -=1
                else:
                    close_bal +=1
        result = []
        memo = {}
        def is_valid(s):
            open_bal = 0
            for l in s:
                if l =='(': open_bal +=1
                if l==')':
                    if open_bal <=0:
                        return False
                    open_bal -=1
            return open_bal ==0

        memo = {}

        def remove(s, start, open_bal, close_bal):
            if (s, open_bal, close_bal) in memo:
                return memo[(s, open_bal, close_bal)]

            if open_bal == 0 and close_bal == 0:
                print(s,result)
                if is_valid(s):
                    result.append(s[:])
                else:
                    print('invalid but saving')
                    print(result)
                memo[(s, open_bal, close_bal)] = result
                return result

            temp_result = []
            for indx in range(start, len(s)):
                if indx > 0 and s[indx-1] == s[indx]:
                    continue
                if s[indx] == '(' and open_bal > 0:
                    temp_result += remove(s[:indx] + s[indx+1:], indx, open_bal - 1, close_bal)
                elif s[indx] == ')' and close_bal > 0:
                    temp_result += remove(s[:indx] + s[indx+1:], indx, open_bal, close_bal - 1)

            memo[(s, open_bal, close_bal)] = temp_result
            return temp_result

        remove(s, 0, open_bal, close_bal)
        print(memo)
        return result
        

    def removeInvalidParentheses(self, s: str) -> List[str]:
        def isValid(s):
            lopen = 0
            for l in s:
                if l =='(': lopen+=1
                if l==')': 
                    if lopen >0:
                        lopen -=1
                    else:
                        return False
            return lopen ==0

        lopen = lclose = 0
        for l in s:
            if l =='(': lopen+=1
            if l==')': 
                if lopen >0:
                    lopen -=1
                else:
                    lclose +=1
        result = []
        def remove(s, start, lopen, lclose):
            if lopen ==0 and lclose==0:
                if isValid(s):
                    result.append(s[:])
                return 

            for indx in range(start, len(s)):
                if indx > 0 and s[indx-1] == s[indx]:
                    continue
                new_s = s[:indx]+ s[indx+1:]
                  
                if s[indx] =='(' and lopen >0:
                    remove(new_s, indx, lopen-1, lclose)
                if s[indx] ==')' and lclose >0:
                    remove(new_s, indx,  lopen, lclose-1)

        remove(s, 0, lopen, lclose)
        return result 
                
    def removeInvalidParentheses(self, s: str) -> List[str]:
        def is_valid(s):
            lopen = 0
            for l in s:
                if l =='(': lopen+=1
                if l==')': 
                    if lopen >0:
                        lopen -=1
                    else:
                        return False
            return lopen ==0

        queue = deque([s])
        
        found = False
        result = []
        while queue:
            visited = set({s})
            for _ in range(len(queue)):
                new_s = queue.popleft()
                
                if is_valid(new_s):
                    result.append(new_s[:])
                    found = True

                for idx in range(len(new_s)):
                    if new_s[idx] not in '()':
                        continue

                    if new_s[:idx] + new_s[idx+1:] not in visited:
                        visited.add( new_s[:idx] + new_s[idx+1:])
                        queue.append( new_s[:idx] + new_s[idx+1:])
            if found:
                break

        return result
```
