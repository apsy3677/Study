# 721. Accounts Merge

[Problem](https://leetcode.com/problems/accounts-merge/) · Medium · Graph: Union-Find → Union by email

LeetCode tags: array, hash-table, string, depth-first-search, breadth-first-search, union-find, sorting

Attempts since Mar 2023: 5 · accepted: 3 · failed before first AC: 1

## Attempt 1 · 2023-04-30 18:13 IST · Wrong Answer · C++

[submission 942101259](https://leetcode.com/submissions/detail/942101259/) · tests 49/50

Failing input:

```text
[["David","Avid0@m.co","David0@m.co","David1@m.co"],["David","Gvid3@m.co","David3@m.co","David4@m.co"],["David","David4@m.co","David5@m.co"],["David","David2@m.co","David3@m.co"],["David","David1@m.co","David2@m.co"]]
```

Expected:

```text
[["David","Avid0@m.co","David0@m.co","David1@m.co","David2@m.co","David3@m.co","David4@m.co","David5@m.co","Gvid3@m.co"]]
```

Your output:

```text
[["Avid0@m.co","David","David0@m.co","David1@m.co","David2@m.co","David3@m.co","David4@m.co","David5@m.co","Gvid3@m.co"]]
```

```cpp
//User function Template for C++
class DisjointSet {
public:
    vector<int> rank, parent, size;
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DisjointSet ds(n);
        unordered_map<string, int> userId;
        int user=0;
        for(auto account : accounts){
            string name = account[0];

            for(int i=1;i<account.size();i++){
                string email = account[i];
                if(userId.count(email) == 0){
                    userId[email] = user;
                }
                else{
                    ds.unionBySize(user, userId[email]);
                }
            }
            user++;
        }
        vector<string> merged[n];
        for(auto &mail : userId){
            int id = mail.second;
            string email = mail.first;

            int parent = ds.findUPar(id);
            merged[parent].push_back(email);
        }
        vector<vector<string>> ans;

        cout<<"Merged ";
        for(int i=0;i<n;i++){
            vector<string> res;
            cout<<merged[i].size()<<"|";
            if(merged[i].size() > 0){
                res.push_back(accounts[i][0]);
                for(auto mail : merged[i])
                    res.push_back(mail);
                sort(res.begin(), res.end());
                ans.push_back(res);
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-04-30 18:15 IST · Accepted · C++

[submission 942101745](https://leetcode.com/submissions/detail/942101745/) · tests 50/50 · runtime 99 ms (beats 8.4%)

```cpp
//User function Template for C++
class DisjointSet {
public:
    vector<int> rank, parent, size;
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DisjointSet ds(n);
        unordered_map<string, int> userId;
        int user=0;
        for(auto account : accounts){
            string name = account[0];

            for(int i=1;i<account.size();i++){
                string email = account[i];
                if(userId.count(email) == 0){
                    userId[email] = user;
                }
                else{
                    ds.unionBySize(user, userId[email]);
                }
            }
            user++;
        }
        vector<string> merged[n];
        for(auto &mail : userId){
            int id = mail.second;
            string email = mail.first;

            int parent = ds.findUPar(id);
            merged[parent].push_back(email);
        }
        vector<vector<string>> ans;

        cout<<"Merged ";
        for(int i=0;i<n;i++){
            vector<string> res;
            sort(merged[i].begin(), merged[i].end());
            cout<<merged[i].size()<<"|";
            if(merged[i].size() > 0){
                res.push_back(accounts[i][0]);
                for(auto mail : merged[i])
                    res.push_back(mail);
                ans.push_back(res);
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-11-28 03:13 IST · Wrong Answer · Python3

[submission 1107725257](https://leetcode.com/submissions/detail/1107725257/) · tests 49/50

Failing input:

```text
[["David","Avid0@m.co","David0@m.co","David1@m.co"],["David","Gvid3@m.co","David3@m.co","David4@m.co"],["David","David4@m.co","David5@m.co"],["David","David2@m.co","David3@m.co"],["David","David1@m.co","David2@m.co"]]
```

Expected:

```text
[["David","Avid0@m.co","David0@m.co","David1@m.co","David2@m.co","David3@m.co","David4@m.co","David5@m.co","Gvid3@m.co"]]
```

Your output:

```text
[["Avid0@m.co","David","David0@m.co","David1@m.co","David2@m.co","David3@m.co","David4@m.co","David5@m.co","Gvid3@m.co"]]
```

```python
class Solution:
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:
        # 1. create graph
        graph = defaultdict(set)
        email_to_name ={}
        for account in accounts:
            name = account[0]
            first_email = account[1]
            email_to_name[first_email] = name
            for email in account[1:]:
                graph[first_email].add(email)
                graph[email].add(first_email)
                email_to_name[email] = name
        print(graph)


        def dfs(email, emails):
            if email in visited:
                return

            visited.add(email)
            emails.append(email)

            for e in graph[email]:
                dfs(e, emails)

        visited = set()
        merged_accounts = []
        print(graph.keys())
        for email in graph:
            print(email)
            if email in visited:
                continue
            emails = [email_to_name[email]]
            dfs(email, emails)
            merged_accounts.append(sorted(emails))

        return merged_accounts
```

## Attempt 4 · 2023-11-28 03:19 IST · Accepted · Python3

[submission 1107727740](https://leetcode.com/submissions/detail/1107727740/) · tests 50/50 · runtime 209 ms (beats 6.5%)

```python
class Solution:
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:
        # 1. create graph
        graph = defaultdict(list)
        email_to_name ={}
        for account in accounts:
            name = account[0]
            first_email = account[1]
            email_to_name[first_email] = name
            for email in account[1:]:
                graph[first_email].append(email)
                graph[email].append(first_email)
                email_to_name[email] = name
        # print(graph)


        def dfs(email, emails):
            if email in visited:
                return

            visited.add(email)
            emails.append(email)

            for e in graph[email]:
                dfs(e, emails)

        visited = set()
        merged_accounts = []
        #print(graph.keys())
        for email in graph:
            #print(email)
            if email in visited:
                continue
            emails = []
            dfs(email, emails)
            merged_accounts.append([email_to_name[email]] + sorted(emails))

        return merged_accounts
```

## Attempt 5 · 2023-11-28 03:19 IST · Accepted · Python3

[submission 1107727897](https://leetcode.com/submissions/detail/1107727897/) · tests 50/50 · runtime 205 ms (beats 6.6%)

```python
class Solution:
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:
        # 1. create graph
        graph = defaultdict(set)
        email_to_name ={}
        for account in accounts:
            name = account[0]
            first_email = account[1]
            email_to_name[first_email] = name
            for email in account[1:]:
                graph[first_email].add(email)
                graph[email].add(first_email)
                email_to_name[email] = name
        # print(graph)


        def dfs(email, emails):
            if email in visited:
                return

            visited.add(email)
            emails.append(email)

            for e in graph[email]:
                dfs(e, emails)

        visited = set()
        merged_accounts = []
        #print(graph.keys())
        for email in graph:
            #print(email)
            if email in visited:
                continue
            emails = []
            dfs(email, emails)
            merged_accounts.append([email_to_name[email]] + sorted(emails))

        return merged_accounts
```
