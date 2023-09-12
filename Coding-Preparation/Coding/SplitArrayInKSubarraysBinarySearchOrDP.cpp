// Split Array into Largest Sum subarray
// Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.

// Return the minimized largest sum of the split.

// A subarray is a contiguous part of the array.

    bool split(vector<int>& arr, int k, int threshold){
        int curr = 0;
        int count = 0;
        for(auto x: arr){
            if(x > threshold) return false;
            if(x + curr > threshold){
                count++;
                curr = x;
            }
            else{
                curr += x;
            }
        }
        // cout<<count<<" :: ";
        if(curr != 0) count++;
        return count <= k;
    }
    int splitArray(vector<int>& arr, int k) {
        int low = 0, high = 0;
        for(auto x : arr ){
            high += x;
            low = max(low, x);
        }
        int ans = INT_MAX;
        while(low <= high){
            int mid = low + ((high-low)>>1);

            bool canSplit = split(arr,k, mid); // threshold is mid
            if(canSplit){
                ans = mid;
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return ans;
    }