Reverse a linked list
Reverse a singly linked list. See the example below.

    int firstMissingPositive(vector<int>& arr) {
        // check if 1 is present, valid numbers
        int N = arr.size();
        int validNums = 0;
        bool onePresent = false;
        for(int &num : arr){
            if(num == 1) onePresent = true;
            if(num <= 0 || num >N){
                // update them to 1
                num = 1;
            }
            else{
                validNums++;
            }
        }
        if(!onePresent) return 1;
        if(validNums == N) return N+1;

        // Do Hashing as all nums are positive 

        for(int &num : arr){
            if(num > 0){
                arr[num-1] = -arr[num-1];
            }
        }
        int ans = 0;
        for(int &num : arr){
            ans++;
            if(num > 0){
                return ans;
            }
        }
        return ans;
    }
