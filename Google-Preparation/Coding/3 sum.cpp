3 sum

Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]

    void twoSum(vector<int>& arr, int sum, int index, set<vector<int>> &st){
        int left =0, right = arr.size() -1;

        while(left < right){
            if(left == index) left++;
            else if(right == index) right--;

            if(arr[left] + arr[right] == sum){
                st.insert({arr[left], arr[index], arr[right]});
                left++;
            }
            else if(arr[left] + arr[right] < sum) left++;
            else right--;
        }
    }
    vector<vector<int>> threeSum(vector<int>& arr) {
        set<vector<int>> st;
        sort(arr.begin(), arr.end());
        int totalSum = 0;
        for(int i=0;i<arr.size();i++){
            int sum = totalSum - arr[i];
            twoSum(arr, sum, i, st);
        }
        return {st.begin(), st.end()};
    }