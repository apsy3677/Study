package demo;

public class UniqueElement {
    static int search(int arr[], int low, int high)
    {
        if(low>high || low<0 ){
            return -1;
        }
        if(high == low){
            return arr[low];
        }
        int mid = (low + (high-low)/2);

        if(mid %3 ==0){
            if(mid+2 <high && (arr[mid] == arr[mid+1] && arr[mid] == arr[mid+2])){
                return search(arr, mid+3, high);
            }
            else{
                return search(arr, low, mid);
            }
        }else if(mid %3 ==1){
            if(mid+1 <high && mid-1>=low && (arr[mid] == arr[mid+1] && arr[mid] == arr[mid-1])){
                return search(arr, mid+2, high);
            }
            else{
                return search(arr, low, mid);
            }
        }else{
            if( mid-2>=low && (arr[mid] == arr[mid-2] && arr[mid] == arr[mid-1])){
                return search(arr, mid+2, high);
            }
            else{
                return search(arr, low, mid);
            }
        }
    }
    // Driver Code
    public static void main(String[] args)
    {
        int arr[] = { 1, 1, 1, 3,4, 4,4, 5,5, 5, 6,6, 6,7,7,7 };
        int len = arr.length;

        System.out.println(search(arr, 0, arr.length - 1));
    }
}
