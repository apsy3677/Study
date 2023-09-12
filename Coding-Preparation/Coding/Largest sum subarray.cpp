// Largest sum subarray
// In the array below, the largest sum subarray starts at index 3 and ends at 6, and with the largest sum being 12.
// Input: [-2,1,-3,4,-1,2,1,-5,4],
// Output: 6
// Explanation: [4,-1,2,1] has the largest sum = 6.

    int maxSubArray(vector<int>& arr) {
        if(arr.size() ==0) return 0;
        int currSum = arr[0];
        int sum = arr[0];

        for(int i=1;i<arr.size();i++){
            currSum = max(arr[i], currSum+arr[i]);
            sum = max(currSum , sum);
        }
        return sum;
    }