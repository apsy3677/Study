// Cyclic Sort

    // only if ranges are continuous
    // CyclicSort
    vector<int> cyclicSort(vector<int> arr){
        int i = 0;

        while(i<arr.size()){
            int correctIndex = arr[i] -1; // correct index for arr[i] element
            if(arr[i] != arr[correctIndex]){
                swap(arr[i], arr[correctIndex]);
            }
            else{
                i++;
            }
        }
        return arr;
    }