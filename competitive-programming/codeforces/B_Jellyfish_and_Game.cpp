#include <bits/stdc++.h>

using namespace std;

/* PRINTS */
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>

#define ar array
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

#define pb push_back
#define eb emplace_back


const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

/* PRINTS */
template <class T>
void print_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}"; }


void solve() {
    ll n,m,k;
    cin>>n>>m>>k;

    vector<ll> arr(n), brr(m);
    ll sum1=0, sum2=0;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        sum1 += arr[i];
    }
    sort(all(arr));
    for(int i=0;i<m;i++){
        cin>>brr[i];
        sum2 += brr[i];

    }
    sort(all(brr));
    // cout<<sum1<< " " <<sum2 <<":: ";
    if(k & 1){
        // 1 will win
        if(arr[0] <= brr[m-1]) {
            cout << sum1 + brr[m-1] - arr[0] << endl;
        }
        else{
            cout<<sum1 <<endl;
        }
    } else {
        if(arr[0] >= brr[m-1]) {
            cout << sum1 + brr[0] - arr[n-1] << endl;
        }
        else {
            cout<<sum1 - arr[0] + brr[m-1] - arr[n-1] + brr[0]<<endl;
        }
    }
}

int main() {
    
	#ifndef ONLINE_JUDGE
	// freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	#endif

    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}