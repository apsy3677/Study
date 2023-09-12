// You have been given information regarding K time series data.

// A Discrete time series is an array of (timei,valuei)
//  .

// Let T1 = [ (0,1) , (3,5) , (7,2) ]

// Let T2 = [ (2,2) , (3,3) , (6,1) ]

// The time series denotes the spike at time timei
//  with a magnitude of valuei
// . The magnitude remains same until a new spike occurs with an updated magnitude.

// For T1 , value = 1 for [0,3) , 5 for [3,7) , 2 for [7,inf)

// for T2 , value = 2 for [0,2) , 3 for [3,6) , 1 for [6,inf)

// Adding T1 and T2 results in a new time series = [ (0,1) , (2,3) , (3,8) , (6,6) , (7,3) ]

// Given K such time series, Print the resultant time series after adding all K time series.

// First add 2 time series data.
// 5
// 0 2 3 6 7 
// 0 1 8 5 1

#include <bits/stdc++.h>
  using namespace std;
typedef pair<int, int> pii;

vector<vector<pii>> T; // K Time series data 
vector<pii> mergeSeriesData(vector<pii> &t1, vector<pii>&t2 ){
    vector<pii> ans;
    int n = t1.size(), m = t2.size();

    int l = 0, r = 0;

    while(l<n && r<m){
        if(t1[l].first == t2[r].first){
            int val = t1[l].second + t2[r].second;
            ans.push_back({t1[l].first, val});
            l++, r++;
        }
        else if(t1[l].first < t2[r].first){
            int val = t1[l].second + (r>0 ? t2[r-1].second : 0);
            ans.push_back({t1[l].first, val});
            l++;
        }
        else{   
            int val = t2[r].second + (l>0 ? t1[l-1].second : 0);
            ans.push_back({t2[r].first, val});
            r++;
        }
    }
    while(l < n){
        int val = t1[l].second + (r>0 ? t2[r-1].second : 0);
        ans.push_back({t1[l].first, val});
        l++;
    }
    while(r < m){
        int val = t2[r].second + (l>0 ? t1[l-1].second : 0);
        ans.push_back({t2[r].first, val});
        r++;
    }
    return ans;
}

vector<pii> merge(int i, int j){
    if(i==j) return T[i];

    int mid = (i+j)/2;
	vector<pii> left = merge(i, mid),
		right = merge(mid+1, j);
    return mergeSeriesData(left, right);
}
  int main() {
    // cout << "Hello World";
    vector<vector<pii>> input;
    int k, n;
    cin>>k;
    int low = 0, high = k-1;
    while(k--){
      cin>>n;
      vector<pii> time(n);
      for(int i=0;i<n;i++) 
        cin>> time[i].first;
      for(int i=0;i<n;i++) 
        cin>> time[i].second;
      T.push_back(time);
    }
    
    vector<pii> ans = merge(low, high);
    cout<<ans.size()<<endl;
    for(auto &[time, _] : ans){
      cout<<time<<" ";
    } cout<<endl;
    for(auto &[_, val] : ans){
      cout<<val<<" ";
    } cout<<endl;
    return 0;

  }

int main(){
    
}

