# 1105. Filling Bookcase Shelves

[Problem](https://leetcode.com/problems/filling-bookcase-shelves/) · Medium · DP: Partition / Interval (MCM) → Front partition DP

LeetCode tags: array, dynamic-programming

Attempts since Mar 2023: 4 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-03-25 00:38 IST · Time Limit Exceeded · C++

[submission 921475765](https://leetcode.com/submissions/detail/921475765/) · tests 7/20

Failing input:

```text
[[11,83],[170,4],[93,80],[155,163],[134,118],[75,14],[122,192],[123,154],[187,29],[160,64],[170,152],[113,179],[60,102],[28,187],[59,95],[187,97],[49,193],[67,126],[75,45],[130,160],[4,102],[116,171],[43,170],[96,188],[54,15],[167,183],[58,158],[59,55],[148,183],[89,95],[90,113],[51,49],[91,28],[172,103],[173,3],[131,78],[11,199],[77,200],[58,65],[77,30],[157,58],[18,194],[101,148],[22,197],[76,18 ... [1404 more chars]
```

Expected:

```text
15672
```

```cpp
class Solution {
public:
    int DP(vector<vector<int>>& books, int shelfWidth, int currWidth, int i, int ht){
        if(i == books.size()){
            return ht;
        }
        int wid = books[i][0];
        int height = books[i][1];
        int ans = INT_MAX, ans1 = INT_MAX;
        // place on next shelf
        if(wid <= currWidth)
            ans = DP(books, shelfWidth, currWidth-wid, i+1, max(ht, height));
        // place on current shelf
        // ShelfHeight so Far and after placing it on new shelf
        ans1 = ht + DP(books, shelfWidth, shelfWidth - wid, i+1, height);
        return min(ans, ans1);
    }
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        return DP(books, shelfWidth, shelfWidth, 0, 0);
    }
};
```

## Attempt 2 · 2023-03-25 00:45 IST · Accepted · C++

[submission 921478900](https://leetcode.com/submissions/detail/921478900/) · tests 20/20 · runtime 12 ms (beats 5.0%)

```cpp
// class Solution {
// public:
//     int DP(vector<vector<int>>& books, int shelfWidth, int currWidth, int i, int ht, vector<vector<int>> &dp){
//         if(i == books.size()){
//             return ht;
//         }
//         if(dp[i][shelfWidth] != -1){
//             return dp[i][currWidth];
//         }
//         int wid = books[i][0];
//         int height = books[i][1];
//         int ans = INT_MAX, ans1 = INT_MAX;
//         // place on next shelf
//         if(wid <= currWidth)
//             ans = DP(books, shelfWidth, currWidth-wid, i+1, max(ht, height), dp);
//         // place on current shelf
//         // ShelfHeight so Far and after placing it on new shelf
//         ans1 = ht + DP(books, shelfWidth, shelfWidth - wid, i+1, height, dp);
//         return dp[i][currWidth] = min(ans, ans1);
//     }
//     int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
//         int n = books.size();
//         vector<vector<int>> dp(n, vector<int>(shelfWidth, -1));
//         return DP(books, shelfWidth, shelfWidth, 0, 0, dp);
//     }
// };

class Solution {
private:
	int solve(vector<vector<int>> &books, int i, int remShelfWidth, int maxShelfHeight, 
			 int shelfWidth, vector<vector<int>> &dp) {

		if(i == books.size()) {
			return maxShelfHeight;
		}

		if(dp[i][remShelfWidth] != -1)
			return dp[i][remShelfWidth];

		int currShelf = INT_MAX, nextShelf = INT_MAX;

		int bookWidth = books[i][0];
		int bookHeight = books[i][1];

		if(bookWidth <= remShelfWidth) {
			currShelf = solve(books, i + 1, remShelfWidth - bookWidth, 
							  max(maxShelfHeight, bookHeight), shelfWidth, dp);
		}

		nextShelf = maxShelfHeight + solve(books, i + 1, shelfWidth - bookWidth, 
										   bookHeight, shelfWidth, dp);

		return dp[i][remShelfWidth] = min(currShelf, nextShelf);
	}
public:
	int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
		vector<vector<int>> dp(1001, vector<int> (shelfWidth + 1, -1));
		return solve(books, 0, shelfWidth, 0, shelfWidth, dp);
	}
};
```

## Attempt 3 · 2023-03-25 00:48 IST · Time Limit Exceeded · C++

[submission 921480328](https://leetcode.com/submissions/detail/921480328/) · tests 7/20

Failing input:

```text
[[11,83],[170,4],[93,80],[155,163],[134,118],[75,14],[122,192],[123,154],[187,29],[160,64],[170,152],[113,179],[60,102],[28,187],[59,95],[187,97],[49,193],[67,126],[75,45],[130,160],[4,102],[116,171],[43,170],[96,188],[54,15],[167,183],[58,158],[59,55],[148,183],[89,95],[90,113],[51,49],[91,28],[172,103],[173,3],[131,78],[11,199],[77,200],[58,65],[77,30],[157,58],[18,194],[101,148],[22,197],[76,18 ... [1404 more chars]
```

Expected:

```text
15672
```

```cpp
class Solution {
public:
    int DP(vector<vector<int>>& books, int shelfWidth, int currWidth, int i, int ht, vector<vector<int>> &dp){
        if(i == books.size()){
            return ht;
        }
        if(dp[i][shelfWidth] != -1){
            return dp[i][currWidth];
        }
        int wid = books[i][0];
        int height = books[i][1];
        int ans = INT_MAX, ans1 = INT_MAX;
        // place on next shelf
        if(wid <= currWidth)
            ans = DP(books, shelfWidth, currWidth-wid, i+1, max(ht, height), dp);
        // place on current shelf
        // ShelfHeight so Far and after placing it on new shelf
        ans1 = ht + DP(books, shelfWidth, shelfWidth - wid, i+1, height, dp);
        return dp[i][currWidth] = min(ans, ans1);
    }
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        vector<vector<int>> dp(n+2, vector<int>(shelfWidth+2, -1));
        return DP(books, shelfWidth, shelfWidth, 0, 0, dp);
    }
};

// class Solution {
// private:
// 	int solve(vector<vector<int>> &books, int i, int remShelfWidth, int maxShelfHeight, 
// 			 int shelfWidth, vector<vector<int>> &dp) {

// 		if(i == books.size()) {
// 			return maxShelfHeight;
// 		}

// 		if(dp[i][remShelfWidth] != -1)
// 			return dp[i][remShelfWidth];

// 		int currShelf = INT_MAX, nextShelf = INT_MAX;

// 		int bookWidth = books[i][0];
// 		int bookHeight = books[i][1];

// 		if(bookWidth <= remShelfWidth) {
// 			currShelf = solve(books, i + 1, remShelfWidth - bookWidth, 
// 							  max(maxShelfHeight, bookHeight), shelfWidth, dp);
// 		}

// 		nextShelf = maxShelfHeight + solve(books, i + 1, shelfWidth - bookWidth, 
// 										   bookHeight, shelfWidth, dp);

// 		return dp[i][remShelfWidth] = min(currShelf, nextShelf);
// 	}
// public:
// 	int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
// 		vector<vector<int>> dp(1001, vector<int> (shelfWidth + 1, -1));
// 		return solve(books, 0, shelfWidth, 0, shelfWidth, dp);
// 	}
// };
```

## Attempt 4 · 2023-03-25 00:57 IST · Time Limit Exceeded · C++

[submission 921484449](https://leetcode.com/submissions/detail/921484449/) · tests 7/20

Failing input:

```text
[[11,83],[170,4],[93,80],[155,163],[134,118],[75,14],[122,192],[123,154],[187,29],[160,64],[170,152],[113,179],[60,102],[28,187],[59,95],[187,97],[49,193],[67,126],[75,45],[130,160],[4,102],[116,171],[43,170],[96,188],[54,15],[167,183],[58,158],[59,55],[148,183],[89,95],[90,113],[51,49],[91,28],[172,103],[173,3],[131,78],[11,199],[77,200],[58,65],[77,30],[157,58],[18,194],[101,148],[22,197],[76,18 ... [1404 more chars]
```

Expected:

```text
15672
```

```cpp
class Solution {
public:
    int DP(vector<vector<int>>& books, int &shelfWidth, int currWidth, int i, int ht, vector<vector<int>> &dp){
        if(i == books.size()){
            return ht;
        }
        if(dp[i][shelfWidth] != -1){
            return dp[i][currWidth];
        }
        int wid = books[i][0];
        int height = books[i][1];
        int ans = INT_MAX, ans1 = INT_MAX;
        // place on next shelf
        if(wid <= currWidth)
            ans = DP(books, shelfWidth, currWidth-wid, i+1, max(ht, height), dp);
        // place on current shelf
        // ShelfHeight so Far and after placing it on new shelf
        ans1 = ht + DP(books, shelfWidth, shelfWidth - wid, i+1, height, dp);
        return dp[i][currWidth] = min(ans, ans1);
    }
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        // int n = books.size();
        vector<vector<int>> dp(1001, vector<int>(shelfWidth+1, -1));
        return DP(books, shelfWidth, shelfWidth, 0, 0, dp);
    }
};

// class Solution {
// private:
// 	int solve(vector<vector<int>> &books, int i, int remShelfWidth, int maxShelfHeight, 
// 			 int shelfWidth, vector<vector<int>> &dp) {

// 		if(i == books.size()) {
// 			return maxShelfHeight;
// 		}

// 		if(dp[i][remShelfWidth] != -1)
// 			return dp[i][remShelfWidth];

// 		int currShelf = INT_MAX, nextShelf = INT_MAX;

// 		int bookWidth = books[i][0];
// 		int bookHeight = books[i][1];

// 		if(bookWidth <= remShelfWidth) {
// 			currShelf = solve(books, i + 1, remShelfWidth - bookWidth, 
// 							  max(maxShelfHeight, bookHeight), shelfWidth, dp);
// 		}

// 		nextShelf = maxShelfHeight + solve(books, i + 1, shelfWidth - bookWidth, 
// 										   bookHeight, shelfWidth, dp);

// 		return dp[i][remShelfWidth] = min(currShelf, nextShelf);
// 	}
// public:
// 	int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
// 		vector<vector<int>> dp(1001, vector<int> (shelfWidth + 1, -1));
// 		return solve(books, 0, shelfWidth, 0, shelfWidth, dp);
// 	}
// };
```
