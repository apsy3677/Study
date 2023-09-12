#include <bits/stdc++.h>

using namespace std;

int main(){
    // cout<<" Hello VS code "<<endl;
    // For getting input from input.txt file
    // freopen("input.txt", "r", stdin);
 
    // // Printing the Output to output.txt file
    // freopen("output.txt", "w", stdout);
    int n,t;
    cin>>t;
    // cout<<t<<endl;
    while(t--){
        cin>>n;
        // cout<<n<<endl;;

        int arr[n];
        int ans[n+1] ={0};
        map<int, vector<int> > mp;
        for(int i=0;i<n;i++){
            cin>>arr[i];
            // cout<<arr[i]<<" ";
            mp[arr[i]].push_back(i);
        }
        // cout<<endl;
        int c = 1;
        for(auto it = mp.rbegin(); it !=mp.rend();it++){
            vector<int> & v = it->second;
            int val = it->first;
            // cout<< val <<": ";
            for(int i=0;i<v.size();i++){
                // cout<<c<<" ";
                ans[v[i]] = c++; 
                
            }
            // cout<<endl;
            
        }
        // cout<< "ans" <<":: ";
        for(int i=0;i<n;i++){
            cout<< ans[i] << " ";
        }
        cout<<endl;
    }
    return 0;
}