Merge overlapping intervals
Given a collection of intervals, merge all overlapping intervals. See the example below.
Example 1:

Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

Example 2:
Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

vector<vector<int>> merge(vector<vector<int>>& intervals){
    vector<vector<int>> merged;
    if(intervals.empty()) return merged;
    sort(intervals.begin(), intervals.end(), [](const vector<int> a, const vector<int> b){
        return a[0] < b[0];
    });

    merged.push_back( { intervals[0][0], intervals[0][1] } );

    for(int i=1;i<intervals.size();i++){
        if(intervals[i][0] > merged.back()[1]){
            merged.push_back( { intervals[i][0], intervals[i][1]});
        }
        else{
            merged.back()[1] = intervals[i][1];
        }
    }
    return merged;
}