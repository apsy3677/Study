/*
You are running a classroom and suspect that some of your students are passing around the answer to a multiple-choice question in 2D grids of letters. The word may start anywhere in the grid, and consecutive letters can be either immediately below or immediately to the right of the previous letter.

Given a grid and a word, write a function that returns the location of the word in the grid as a list of coordinates. If there are multiple matches, return any one.

grid1 = [
    ['b', 'b', 'b', 'a', 'l', 'l', 'o', 'o'],
    ['b', 'a', 'c', 'c', 'e', 's', 'c', 'n'],
    ['a', 'l', 't', 'e', 'w', 'c', 'e', 'w'],
    ['a', 'l', 'o', 's', 's', 'e', 'c', 'c'],
    ['w', 'o', 'o', 'w', 'a', 'c', 'a', 'w'],
    ['i', 'b', 'w', 'o', 'w', 'w', 'o', 'w']
]
word1_1 = "access"      # [(1, 1), (1, 2), (1, 3), (2, 3), (3, 3), (3, 4)]
word1_2 = "balloon"     # [(0, 2), (0, 3), (0, 4), (0, 5), (0, 6), (0, 7), (1, 7)]

word1_3 = "wow"         # [(4, 3), (5, 3), (5, 4)] OR 
                        # [(5, 2), (5, 3), (5, 4)] OR 
                        # [(5, 5), (5, 6), (5, 7)]
                          
word1_4 = "sec"         # [(3, 4), (3, 5), (3, 6)] OR 
                        # [(3, 4), (3, 5), (4, 5)]    

word1_5 = "bbaal"       # [(0, 0), (1, 0), (2, 0), (3, 0), (3, 1)]


grid2 = [
  ['a'],
]
word2_1 = "a"

grid3 = [
    ['c', 'a'],
    ['t', 't'],
    ['h', 'a'],
    ['a', 'c'],
    ['t', 'g']
]
word3_1 = "cat"
word3_2 = "hat"

grid4 = [
    ['c', 'c', 'x', 't', 'i', 'b'],
    ['c', 'a', 't', 'n', 'i', 'i'],
    ['a', 'x', 'n', 'x', 'p', 't'],
    ['t', 'x', 'i', 'x', 't', 't']
]
word4_1 = "catnip"      # [(1, 0), (1, 1), (1, 2), (1, 3), (1, 4), (2, 4)] OR
                        # [(0, 1), (1, 1), (1, 2), (1, 3), (1, 4), (2, 4)]


All test cases:

search(grid1, word1_1) => [(1, 1), (1, 2), (1, 3), (2, 3), (3, 3), (3, 4)]
search(grid1, word1_2) => [(0, 2), (0, 3), (0, 4), (0, 5), (0, 6), (0, 7), (1, 7)]
search(grid1, word1_3) => [(4, 3), (5, 3), (5, 4)] OR 
                          [(5, 2), (5, 3), (5, 4)] OR 
                          [(5, 5), (5, 6), (5, 7)]
search(grid1, word1_4) => [(3, 4), (3, 5), (3, 6)] OR
                          [(3, 4), (3, 5), (4, 5)]                           
search(grid1, word1_5) => [(0, 0), (1, 0), (2, 0), (3, 0), (3, 1)]

search(grid2, word2_1) => [(0, 0)]

search(grid3, word3_1) => [(0, 0), (0, 1), (1, 1)]
search(grid3, word3_2) => [(2, 0), (3, 0), (4, 0)]

search(grid4, word4_1) => [(1, 0), (1, 1), (1, 2), (1, 3), (1, 4), (2, 4)] OR
                          [(0, 1), (1, 1), (1, 2), (1, 3), (1, 4), (2, 4)]

Complexity analysis variables:

r = number of rows
c = number of columns
w = length of the word

*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


string find(vector<string> &words, string &note) {
  
  unordered_map<char, int> noteCount;
  
  for(char c: note) {
    noteCount[c]++;
  }
  
  for (auto &w : words) {
    unordered_map<char, int> wordCount;
    for (char c: w) {
      wordCount[c]++;
    }
    
    bool ok = true;
    for(auto &p : wordCount) {
      if (noteCount[p.first] < p.second) {
        ok = false;
        break;
      }
    }
    
    if(ok) {
      return w;
    }
  }
  
  return "-";
  
}


// pair<int,int>
int R, C;
vector < pair<int,int>> path;

bool dfs(vector<vector<char>> &grid, string &word, int i, int j, int idx) {
  if (idx == word.size()){
    return true;
  }
  if (i>=R || j>=C || grid[i][j] != word[idx]) {
    return false;
  }
  
  path.push_back({i,j});
  // right
  if (dfs(grid, word, i, j+1, idx+1)) {
    return true;
  }
  if (dfs(grid, word, i+1, j, idx+1)) {
    return true;
  }
  path.pop_back();
  return false;
}

vector <pair<int,int>> searchWord (vector<vector<char>> &grid, string &word) {
  R = grid.size();
  C = grid[0].size();
  
  for(int i=0;i<R;i++) {
    for (int j= 0;j<C; j++) {
      path.clear();
      if (dfs(grid, word, i,j, 0)) {
        return path;
      }
    }
  }
  return {};
}


int main() {
  vector<vector<char>> grid1 = {
    {'b', 'b', 'b', 'a', 'l', 'l', 'o', 'o'},
    {'b', 'a', 'c', 'c', 'e', 's', 'c', 'n'},
    {'a', 'l', 't', 'e', 'w', 'c', 'e', 'w'},
    {'a', 'l', 'o', 's', 's', 'e', 'c', 'c'},
    {'w', 'o', 'o', 'w', 'a', 'c', 'a', 'w'},
    {'i', 'b', 'w', 'o', 'w', 'w', 'o', 'w'},
  };
  string word1_1 = "access";
  string word1_2 = "balloon";
  string word1_3 = "wow";
  string word1_4 = "sec";
  string word1_5 = "bbaal";

  vector<vector<char>> grid2 = {
    {'a'},
  };
  string word2_1 = "a";

  vector<vector<char>> grid3 = {
    {'c', 'a'},
    {'t', 't'},
    {'h', 'a'},
    {'a', 'c'},
    {'t', 'g'},
  };
  string word3_1 = "cat";
  string word3_2 = "hat";

  vector<vector<char>> grid4 = {
    {'c', 'c', 'x', 't', 'i', 'b'},
    {'c', 'a', 't', 'n', 'i', 'i'},
    {'a', 'x', 'n', 'x', 'p', 't'},
    {'t', 'x', 'i', 'x', 't', 't'},
  };
  string word4_1 = "catnip";

  vector<pair<int,int>> path = searchWord(grid1, word2_1);
  
  // 
//   search(grid1, word1_1) => [(1, 1), (1, 2), (1, 3), (2, 3), (3, 3), (3, 4)]
// search(grid1, word1_2) => [(0, 2), (0, 3), (0, 4), (0, 5), (0, 6), (0, 7), (1, 7)]
// search(grid1, word1_3) => [(4, 3), (5, 3), (5, 4)] OR 
//                           [(5, 2), (5, 3), (5, 4)] OR 
//                           [(5, 5), (5, 6), (5, 7)]
// search(grid1, word1_4) => [(3, 4), (3, 5), (3, 6)] OR
//                           [(3, 4), (3, 5), (4, 5)]                           
// search(grid1, word1_5) => [(0, 0), (1, 0), (2, 0), (3, 0), (3, 1)]

// search(grid2, word2_1) => [(0, 0)]

// search(grid3, word3_1) => [(0, 0), (0, 1), (1, 1)]
// search(grid3, word3_2) => [(2, 0), (3, 0), (4, 0)]

// search(grid4, word4_1) => [(1, 0), (1, 1), (1, 2), (1, 3), (1, 4), (2, 4)] OR
//                           [(0, 1), (1, 1), (1, 2), (1, 3), (1, 4), (2, 4)]
  
  path = searchWord(grid1, word1_1);
  
  for (auto p : path) {
    cout << p.first <<"," <<p.second <<endl;;
  } 
  path = searchWord(grid1, word1_2);
  
  for (auto p : path) {
    cout << p.first <<"," <<p.second <<endl;;
  } 
  path = searchWord(grid1, word1_3);
  
  for (auto p : path) {
    cout << p.first <<"," <<p.second <<endl;;
  } 
  path = searchWord(grid1, word1_4);
  
  for (auto p : path) {
    cout << p.first <<"," <<p.second <<endl;;
  } 
  path = searchWord(grid1, word1_5);
  
  for (auto p : path) {
    cout << p.first <<"," <<p.second <<endl;;
  } 
  path = searchWord(grid1, word1_1);
  
  for (auto p : path) {
    cout << p.first <<"," <<p.second <<endl;;
  } 
  path = searchWord(grid1, word1_1);
  
  for (auto p : path) {
    cout << p.first <<"," <<p.second <<endl;;
  } 
  // cout<< find(words, note1) <<endl;
  // cout<< find(words, note2) <<endl;
  // cout<< find(words, note3) <<endl;
  // cout<< find(words, note4) <<endl;
  // cout<< find(words, note5) <<endl;
  // cout<< find(words, note6) <<endl;
  // cout<< find(words, note7) <<endl;
  
  return 0;
}
