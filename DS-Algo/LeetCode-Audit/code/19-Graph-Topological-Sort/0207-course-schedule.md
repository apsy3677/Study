# 207. Course Schedule

[Problem](https://leetcode.com/problems/course-schedule/) · Medium · Graph: Topological Sort → Cycle detection

LeetCode tags: depth-first-search, breadth-first-search, graph, topological-sort, directed-acyclic-graph

Attempts since Mar 2023: 11 · accepted: 7 · failed before first AC: 0

## Attempt 1 · 2023-03-15 14:43 IST · Accepted · C++

[submission 915544402](https://leetcode.com/submissions/detail/915544402/) · tests 52/52 · runtime 24 ms (beats 6.7%)

```cpp
class Solution {
public:

    bool detectCycle(int u, vector<bool> &vis, vector<bool> &curVis, vector<vector<int>> &gr){

        vis[u] = true;
        curVis[u] = true;

        for(auto x: gr[u]){
            if(!vis[x]){
                if(detectCycle(x, vis, curVis, gr)){
                    return true;
                }
            }
            else if(vis[x] && curVis[x]){
                return true;
            }
        }

        // removing this node from dfs path
        curVis[u] = false;
        return false;
    }

    bool canFinish(int n, vector<vector<int>>& pre) {
        vector<vector<int>> gr(n, vector<int>());

        for(int i=0;i<pre.size();i++){
            gr[pre[i][0]].push_back(pre[i][1]);
        }
        vector<bool> vis(n, false), curVis(n, false);

        for(int i=0;i<n;i++){
            if(!vis[i]){
                if(detectCycle(i, vis, curVis, gr)){
                    return false;
                }
            }
        }
        return true;
    }
};
```

## Attempt 2 · 2023-04-29 14:30 IST · Accepted · C++

[submission 941464543](https://leetcode.com/submissions/detail/941464543/) · tests 52/52 · runtime 25 ms (beats 6.7%)

```cpp
class Solution {
public:

    bool detectCycle(int u, vector<bool> &vis, vector<bool> &curVis, vector<vector<int>> &gr){

        vis[u] = true;
        curVis[u] = true;

        for(auto x: gr[u]){
            if(!vis[x]){
                if(detectCycle(x, vis, curVis, gr)){
                    return true;
                }
            }
            else if(vis[x] && curVis[x]){
                return true;
            }
        }

        // removing this node from dfs path
        curVis[u] = false;
        return false;
    }

    bool canFinish(int n, vector<vector<int>>& pre) {
        vector<vector<int>> gr(n, vector<int>());
        vector<int> inDegree(n,0);
        for(int i=0;i<pre.size();i++){
            gr[pre[i][0]].push_back(pre[i][1]);
            inDegree[pre[i][1]]++;
        }
        vector<bool> vis(n, false), curVis(n, false);
        queue<int> qu;
        for(int i=0;i<n;i++){
            if(inDegree[i]==0) qu.push(i);
        }
        int taken =0;
        while(!qu.empty()){
            int sz = qu.size();
            while(sz--){
                int node = qu.front(); qu.pop();
                taken++;
                for(auto it: gr[node]){
                    inDegree[it]--;
                    if(inDegree[it]==0) qu.push(it);
                }
            }
        }
        return taken == n ? true : false;
        // for(int i=0;i<n;i++){
        //     if(!vis[i]){
        //         if(detectCycle(i, vis, curVis, gr)){
        //             return false;
        //         }
        //     }
        // }
        // return true;
    }
};
```

## Attempt 3 · 2023-11-19 08:07 IST · Wrong Answer · Python3

[submission 1101773559](https://leetcode.com/submissions/detail/1101773559/) · tests 23/52

Failing input:

```text
1
[]
```

Expected:

```text
true
```

Your output:

```text
false
```

```python
class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create adj list
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
        
        # print(adjList)
        visited = {}
        
        def dfs(node):
            # 1. check if visited
            if node in visited:
                return visited[node] # False for cycle and True for seen before
            
            #2. set to visiting
            visited[node] = False

            #3. process neigh
            for next_node in adjList[node]:
                if not dfs(next_node): return True

            visited[node]= True

            return False

        for course in range(numCourses):
            if dfs(course):
                return True
            
        return False
```

## Attempt 4 · 2023-11-19 08:14 IST · Output Limit Exceeded · Python3

[submission 1101782525](https://leetcode.com/submissions/detail/1101782525/) · tests 44/52

Failing input:

```text
1000
[[785,230],[843,838],[725,91],[236,135],[804,544],[779,204],[599,306],[685,651],[716,562],[419,381],[575,549],[895,348],[872,16],[938,344],[565,340],[794,21],[867,557],[857,486],[256,131],[959,439],[756,728],[873,330],[320,99],[825,657],[620,63],[534,404],[795,385],[171,159],[982,854],[458,203],[243,107],[403,289],[868,400],[313,214],[851,368],[773,767],[276,0],[948,672],[439,100],[437,255],[ ... [19094 more chars]
```

Expected:

```text
true
```

```python
class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create adj list
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
        
        # print(adjList)
        visited = {}
        
        def dfs(node):
            # 1. check if visited
            if node in visited:
                print(node, visited)
                return visited[node] # False for cycle and True for seen before
            
            #2. set to visiting
            visited[node] = False

            #3. process neigh
            for next_node in adjList[node]:
                if not dfs(next_node): return False

            visited[node]= True

            return True

        for course in range(numCourses):
            print('checking for course', course)
            if not dfs(course):
                return False
            
        return True
```

## Attempt 5 · 2023-11-19 08:14 IST · Accepted · Python3

[submission 1101782848](https://leetcode.com/submissions/detail/1101782848/) · tests 52/52 · runtime 98 ms (beats 5.1%)

```python
class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create adj list
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
        
        # print(adjList)
        visited = {}
        
        def dfs(node):
            # 1. check if visited
            if node in visited:
                # print(node, visited)
                return visited[node] # False for cycle and True for seen before
            
            #2. set to visiting
            visited[node] = False

            #3. process neigh
            for next_node in adjList[node]:
                if not dfs(next_node): return False

            visited[node]= True

            return True

        for course in range(numCourses):
            # print('checking for course', course)
            if not dfs(course):
                return False
            
        return True
```

## Attempt 6 · 2023-12-20 05:19 IST · Accepted · Python3

[submission 1123781267](https://leetcode.com/submissions/detail/1123781267/) · tests 52/52 · runtime 112 ms (beats 5.1%)

```python
class Solution:
    
    def canFinish1(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create adj list
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
        
        # print(adjList)
        visited = {}
        
        # if no cycle return True else False
        def dfs(node):
            # 1. check if visited
            if node in visited:
                # print(node, visited)
                return visited[node] # False for cycle and True for seen before
            
            #2. set to visiting
            visited[node] = False

            #3. process neigh
            for next_node in adjList[node]:
                if not dfs(next_node): return False

            visited[node]= True

            return True

        for course in range(numCourses):
            # print('checking for course', course)
            if not dfs(course):
                return False
            
        return True
            
    def canFinish2(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        indegree = Counter({course:0 for course in range(numCourses)})
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
            indegree[a] +=1

        # start with indegree 0
        queue = deque([course for course in range(numCourses) if indegree[course] == 0])

        nodesVisited = 0
        while queue:
            node = queue.popleft()
            nodesVisited +=1
            for nei in adjList[node]:
                indegree[nei] -=1
                if indegree[nei] ==0:
                    queue.append(nei)
        
        return numCourses == nodesVisited


    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create a adjlist 
        adjList = defaultdict(set)

        # indegree for all the nodes
        # important to keep all nodes
        indegree = Counter({course:0 for course in range(numCourses)})
        
        # create ajlist for node with outgoing connection
        for a,b in prerequisites:
            if a not in adjList[b]:
                adjList[b].add(a)
                indegree[a] +=1

        # process nodes with indegree 0
        # these courses have no prerequisites for them
        queue = deque([course for course in indegree if indegree[course]==0])

        visited = 0
        while queue:
            c = queue.popleft()
            visited +=1
            for d in adjList[c]:
                indegree[d]-=1
                if indegree[d]==0:
                    queue.append(d)

        return visited == numCourses
```

## Attempt 7 · 2023-12-20 05:53 IST · Accepted · Python3

[submission 1123795027](https://leetcode.com/submissions/detail/1123795027/) · tests 52/52 · runtime 94 ms (beats 5.1%)

```python
class Solution:
    
    def canFinish1(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create adj list
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
        
        # print(adjList)
        visited = {}
        
        # if no cycle return True else False
        def dfs(node):
            # 1. check if visited
            if node in visited:
                # print(node, visited)
                return visited[node] # False for cycle and True for seen before
            
            #2. set to visiting
            visited[node] = False

            #3. process neigh
            for next_node in adjList[node]:
                if not dfs(next_node): return False

            visited[node]= True

            return True

        for course in range(numCourses):
            # print('checking for course', course)
            if not dfs(course):
                return False
            
        return True
            
    def canFinish2(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        indegree = Counter({course:0 for course in range(numCourses)})
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
            indegree[a] +=1

        # start with indegree 0
        queue = deque([course for course in range(numCourses) if indegree[course] == 0])

        nodesVisited = 0
        while queue:
            node = queue.popleft()
            nodesVisited +=1
            for nei in adjList[node]:
                indegree[nei] -=1
                if indegree[nei] ==0:
                    queue.append(nei)
        
        return numCourses == nodesVisited


    def canFinish4(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create a adjlist 
        adjList = defaultdict(set)

        # indegree for all the nodes
        # important to keep all nodes
        indegree = Counter({course:0 for course in range(numCourses)})
        
        # create ajlist for node with outgoing connection
        for a,b in prerequisites:
            if a not in adjList[b]:
                adjList[b].add(a)
                indegree[a] +=1

        # process nodes with indegree 0
        # these courses have no prerequisites for them
        queue = deque([course for course in indegree if indegree[course]==0])

        visited = 0
        while queue:
            c = queue.popleft()
            visited +=1
            for d in adjList[c]:
                indegree[d]-=1
                if indegree[d]==0:
                    queue.append(d)

        return visited == numCourses


    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # detect cycle using dfs

        adjList = defaultdict(set)
        #1. creat adjlist
        for a,b in prerequisites:
            adjList[b].add(a)

        #2. dfs

        visited = {} # 1. true - finsihed 2. inprogress
        def dfs(node):
            if node in visited:
                # return True if finsihed processing
                # false if there is a loop
                return visited[node]

            #2. set current node to visiting
            visited[node] = False

            for c in adjList[node]:
                if not dfs(c):
                    return False

            visited[node] = True

            return True

        # process all connected components
        for course in range(numCourses):
            if not dfs(course):
                return False
        
        return True
```

## Attempt 8 · 2023-12-20 05:53 IST · Wrong Answer · Python3

[submission 1123795365](https://leetcode.com/submissions/detail/1123795365/) · tests 30/52

Failing input:

```text
1
[]
```

Expected:

```text
true
```

Your output:

```text
false
```

```python
class Solution:
    
    def canFinish1(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create adj list
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
        
        # print(adjList)
        visited = {}
        
        # if no cycle return True else False
        def dfs(node):
            # 1. check if visited
            if node in visited:
                # print(node, visited)
                return visited[node] # False for cycle and True for seen before
            
            #2. set to visiting
            visited[node] = False

            #3. process neigh
            for next_node in adjList[node]:
                if not dfs(next_node): return False

            visited[node]= True

            return True

        for course in range(numCourses):
            # print('checking for course', course)
            if not dfs(course):
                return False
            
        return True
            
    def canFinish2(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        indegree = Counter({course:0 for course in range(numCourses)})
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
            indegree[a] +=1

        # start with indegree 0
        queue = deque([course for course in range(numCourses) if indegree[course] == 0])

        nodesVisited = 0
        while queue:
            node = queue.popleft()
            nodesVisited +=1
            for nei in adjList[node]:
                indegree[nei] -=1
                if indegree[nei] ==0:
                    queue.append(nei)
        
        return numCourses == nodesVisited


    def canFinish4(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create a adjlist 
        adjList = defaultdict(set)

        # indegree for all the nodes
        # important to keep all nodes
        indegree = Counter({course:0 for course in range(numCourses)})
        
        # create ajlist for node with outgoing connection
        for a,b in prerequisites:
            if a not in adjList[b]:
                adjList[b].add(a)
                indegree[a] +=1

        # process nodes with indegree 0
        # these courses have no prerequisites for them
        queue = deque([course for course in indegree if indegree[course]==0])

        visited = 0
        while queue:
            c = queue.popleft()
            visited +=1
            for d in adjList[c]:
                indegree[d]-=1
                if indegree[d]==0:
                    queue.append(d)

        return visited == numCourses


    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # detect cycle using dfs

        adjList = defaultdict(set)
        #1. creat adjlist
        for a,b in prerequisites:
            adjList[b].add(a)

        #2. dfs

        visited = {} # 1. true - finsihed 2. inprogress
        def dfs(node):
            if node in visited:
                # return True if finsihed processing
                # false if there is a loop
                return visited[node]

            #2. set current node to visiting
            visited[node] = False

            for c in adjList[node]:
                if not dfs(c):
                    return True

            visited[node] = True

            return False

        # process all connected components
        for course in range(numCourses):
            if not dfs(course):
                return False
        
        return True
```

## Attempt 9 · 2023-12-20 05:54 IST · Accepted · Python3

[submission 1123795445](https://leetcode.com/submissions/detail/1123795445/) · tests 52/52 · runtime 98 ms (beats 5.1%)

```python
class Solution:
    
    def canFinish1(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create adj list
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
        
        # print(adjList)
        visited = {}
        
        # if no cycle return True else False
        def dfs(node):
            # 1. check if visited
            if node in visited:
                # print(node, visited)
                return visited[node] # False for cycle and True for seen before
            
            #2. set to visiting
            visited[node] = False

            #3. process neigh
            for next_node in adjList[node]:
                if not dfs(next_node): return False

            visited[node]= True

            return True

        for course in range(numCourses):
            # print('checking for course', course)
            if not dfs(course):
                return False
            
        return True
            
    def canFinish2(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        indegree = Counter({course:0 for course in range(numCourses)})
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
            indegree[a] +=1

        # start with indegree 0
        queue = deque([course for course in range(numCourses) if indegree[course] == 0])

        nodesVisited = 0
        while queue:
            node = queue.popleft()
            nodesVisited +=1
            for nei in adjList[node]:
                indegree[nei] -=1
                if indegree[nei] ==0:
                    queue.append(nei)
        
        return numCourses == nodesVisited


    def canFinish4(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create a adjlist 
        adjList = defaultdict(set)

        # indegree for all the nodes
        # important to keep all nodes
        indegree = Counter({course:0 for course in range(numCourses)})
        
        # create ajlist for node with outgoing connection
        for a,b in prerequisites:
            if a not in adjList[b]:
                adjList[b].add(a)
                indegree[a] +=1

        # process nodes with indegree 0
        # these courses have no prerequisites for them
        queue = deque([course for course in indegree if indegree[course]==0])

        visited = 0
        while queue:
            c = queue.popleft()
            visited +=1
            for d in adjList[c]:
                indegree[d]-=1
                if indegree[d]==0:
                    queue.append(d)

        return visited == numCourses


    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # detect cycle using dfs

        adjList = defaultdict(set)
        #1. creat adjlist
        for a,b in prerequisites:
            adjList[b].add(a)

        #2. dfs

        visited = {} # 1. true - finsihed 2. inprogress
        def dfs(node):
            if node in visited:
                # return True if finsihed processing
                # false if there is a loop
                return visited[node]

            #2. set current nodeto visiting
            visited[node] = False

            for c in adjList[node]:
                if not dfs(c):
                    return False

            visited[node] = True

            return True

        # process all connected components
        for course in range(numCourses):
            if not dfs(course):
                return False
        
        return True
```

## Attempt 10 · 2024-01-06 01:05 IST · Runtime Error · Python3

[submission 1137908034](https://leetcode.com/submissions/detail/1137908034/) · tests 0/52

Failing input:

```text
2
[[1,0]]
```

Expected:

```text
true
```

Runtime error:

```text
AttributeError: 'set' object has no attribute 'append'
    ^^^^^^^^^^^^^^^^^^^^^^^^
    adj_list[course2].append(course1)
Line 135 in canFinish (Solution.py)
          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ret = Solution().canFinish(param_1, param_2)
Line 199 in _driver (Solution.py)
    _driver()
Line 210 in <module> (Solution.py)
```

```python
class Solution:
    
    def canFinish1(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create adj list
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
        
        # print(adjList)
        visited = {}
        
        # if no cycle return True else False
        def dfs(node):
            # 1. check if visited
            if node in visited:
                # print(node, visited)
                return visited[node] # False for cycle and True for seen before
            
            #2. set to visiting
            visited[node] = False

            #3. process neigh
            for next_node in adjList[node]:
                if not dfs(next_node): return False

            visited[node]= True

            return True

        for course in range(numCourses):
            # print('checking for course', course)
            if not dfs(course):
                return False
            
        return True
            
    def canFinish2(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        indegree = Counter({course:0 for course in range(numCourses)})
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
            indegree[a] +=1

        # start with indegree 0
        queue = deque([course for course in range(numCourses) if indegree[course] == 0])

        nodesVisited = 0
        while queue:
            node = queue.popleft()
            nodesVisited +=1
            for nei in adjList[node]:
                indegree[nei] -=1
                if indegree[nei] ==0:
                    queue.append(nei)
        
        return numCourses == nodesVisited


    def canFinish4(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create a adjlist 
        adjList = defaultdict(set)

        # indegree for all the nodes
        # important to keep all nodes
        indegree = Counter({course:0 for course in range(numCourses)})
        
        # create ajlist for node with outgoing connection
        for a,b in prerequisites:
            if a not in adjList[b]:
                adjList[b].add(a)
                indegree[a] +=1

        # process nodes with indegree 0
        # these courses have no prerequisites for them
        queue = deque([course for course in indegree if indegree[course]==0])

        visited = 0
        while queue:
            c = queue.popleft()
            visited +=1
            for d in adjList[c]:
                indegree[d]-=1
                if indegree[d]==0:
                    queue.append(d)

        return visited == numCourses


    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # detect cycle using dfs

        adjList = defaultdict(set)
        #1. creat adjlist
        for a,b in prerequisites:
            adjList[b].add(a)

        #2. dfs

        visited = {} # 1. true - finsihed 2. inprogress
        def dfs(node):
            if node in visited:
                # return True if finsihed processing
                # false if there is a loop
                return visited[node]

            #2. set current nodeto visiting
            visited[node] = False

            for c in adjList[node]:
                if not dfs(c):
                    return False

            visited[node] = True

            return True

        # process all connected components
        for course in range(numCourses):
            if not dfs(course):
                return False
        
        return True

    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create graph adjlist
        adj_list = defaultdict(set)
        # indegree
        indegree = Counter({i:0 for i in range(numCourses)})

        for course1, course2 in prerequisites:
            # if b should come before a 
            # create b: [a,] nodes that follow b
            # because when you remove a node, you want to find and decrase indegree
            # for all nodes that were dependent on this node
            adj_list[course2].append(course1)
            indegree[a] +=1

        # find all 0 indegree
        queue = dequeue([i for i in indegree.keys() if indegree[i]==0])

        visited_courses = 0
        while queue:
            course = queue.popleft()

            # update visited
            visited_courses +=1 

            for next_course in adj_list[course]:
                indegree[next_course]-=1

                if indegree[next_course] ==0:
                    queue.append(next_course)

        #if there are no cycles, we would have visited all courses
        return visited_courses == numCourses
```

## Attempt 11 · 2024-01-06 01:05 IST · Accepted · Python3

[submission 1137908453](https://leetcode.com/submissions/detail/1137908453/) · tests 52/52 · runtime 92 ms (beats 5.1%)

```python
class Solution:
    
    def canFinish1(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create adj list
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
        
        # print(adjList)
        visited = {}
        
        # if no cycle return True else False
        def dfs(node):
            # 1. check if visited
            if node in visited:
                # print(node, visited)
                return visited[node] # False for cycle and True for seen before
            
            #2. set to visiting
            visited[node] = False

            #3. process neigh
            for next_node in adjList[node]:
                if not dfs(next_node): return False

            visited[node]= True

            return True

        for course in range(numCourses):
            # print('checking for course', course)
            if not dfs(course):
                return False
            
        return True
            
    def canFinish2(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        indegree = Counter({course:0 for course in range(numCourses)})
        adjList = defaultdict(list)
        for a,b in prerequisites:
            adjList[b].append(a)
            indegree[a] +=1

        # start with indegree 0
        queue = deque([course for course in range(numCourses) if indegree[course] == 0])

        nodesVisited = 0
        while queue:
            node = queue.popleft()
            nodesVisited +=1
            for nei in adjList[node]:
                indegree[nei] -=1
                if indegree[nei] ==0:
                    queue.append(nei)
        
        return numCourses == nodesVisited


    def canFinish4(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create a adjlist 
        adjList = defaultdict(set)

        # indegree for all the nodes
        # important to keep all nodes
        indegree = Counter({course:0 for course in range(numCourses)})
        
        # create ajlist for node with outgoing connection
        for a,b in prerequisites:
            if a not in adjList[b]:
                adjList[b].add(a)
                indegree[a] +=1

        # process nodes with indegree 0
        # these courses have no prerequisites for them
        queue = deque([course for course in indegree if indegree[course]==0])

        visited = 0
        while queue:
            c = queue.popleft()
            visited +=1
            for d in adjList[c]:
                indegree[d]-=1
                if indegree[d]==0:
                    queue.append(d)

        return visited == numCourses


    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # detect cycle using dfs

        adjList = defaultdict(set)
        #1. creat adjlist
        for a,b in prerequisites:
            adjList[b].add(a)

        #2. dfs

        visited = {} # 1. true - finsihed 2. inprogress
        def dfs(node):
            if node in visited:
                # return True if finsihed processing
                # false if there is a loop
                return visited[node]

            #2. set current nodeto visiting
            visited[node] = False

            for c in adjList[node]:
                if not dfs(c):
                    return False

            visited[node] = True

            return True

        # process all connected components
        for course in range(numCourses):
            if not dfs(course):
                return False
        
        return True

    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # create graph adjlist
        adj_list = defaultdict(list)
        # indegree
        indegree = Counter({i:0 for i in range(numCourses)})

        for course1, course2 in prerequisites:
            # if b should come before a 
            # create b: [a,] nodes that follow b
            # because when you remove a node, you want to find and decrase indegree
            # for all nodes that were dependent on this node
            adj_list[course2].append(course1)
            indegree[course1] +=1

        # find all 0 indegree
        queue = deque([i for i in indegree.keys() if indegree[i]==0])

        visited_courses = 0
        while queue:
            course = queue.popleft()

            # update visited
            visited_courses +=1 

            for next_course in adj_list[course]:
                indegree[next_course]-=1

                if indegree[next_course] ==0:
                    queue.append(next_course)

        #if there are no cycles, we would have visited all courses
        return visited_courses == numCourses
```
