arr[] n 

vector< pair<int, int> > pairList( vector<int> arr, int sum){
	
	vector< pair<int,int> > ans;

	map<int, bool> mp;
	// set<int> for better data structure

	for(int i=0;i<arr.size();i++){
		if(mp.contains(sum - arr[i])){
			ans.push_back(make_pair(sum - arr[i], arr[i]));
		}
		mp[arr[i]]= true;
	}

	return ans;
}

vector<tuple> getPairList(){
	vector< tuple > ans;
	//map<int, bool> mp;
	set<int> mp; //for better data structure

	for(int i=0;i<arr.size();i++){
		if(mp.contains(sum - arr[i])){
			ans.push_back(make_pair(sum - arr[i], arr[i]));
		}
		mp.insert(arr[i]);
	}

	return ans;
}

vector<tuple> getTripletList(vector<int> arr, int sum){
	// a+b+c =sum

	b , a,c


}

vector< tuple > clientAPI (vector<int> arr, int sum){
		vector<tuple> ans;
		ans.append(getPairList(arr, sum));
		ans.append(getTripletList(arr,sum));

		return ans;

}

/*
interface tuple {
	 
}

class Pair implements tuple{
	
}

class Triplet implements tuple{
	
}
*/

vector< tuple *> 

Inputs and outputs
[1 2 3 4 5] 3 
[{1,2}]

[1 2 3 4 5] 5 
[{1,4}, {2,3}] or [{}]

[] 5


void testPairList(){
	
	vector<int> arr1 = 
}