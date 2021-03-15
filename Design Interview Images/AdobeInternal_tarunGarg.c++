#include <iostream>
#include <string>
using namespace std;

int check(int v1, int v2){
	if(v1<v2){
		return -1;
	}else if(v1>v2){
		return 1;
	}else {
		return 0;
	}
}

int extract(int i, int j){
	return check(stoi(a.substr(i)), stoi(b.substr(j)));
}

int compareVersions(const std::string&a, const std::string& b){
	
	int ans = 0;
	size_t s1=0, s2=0;
	int i= 0, j= 0;
	int v1=0, v2=0;
	while(1){
		s1 = a.find('.', i+1);
		s2 = b.find('.', j+1);
		
		if(s1 == string::npos && s2 == string::npos){
			ans = extract(i,j)
			break;
		}
		else if(s1 == string::npos ){
			v1 = stoi(a.substr(i));
			v2 = stoi(b.substr(j, s2 - j+1));
			ans = extract(i, j )
			break;
		}
		else if(s2 == string::npos){
			v1 = stoi(a.substr(i, s1 - i+1));
			v2 = stoi(b.substr(j));
			ans = check(v1, v2);
			break;
		}
		else{
			v1 = stoi(a.substr(i, s1 - i+1));
			v2 = stoi(b.substr(j, s2 -j+1));
			ans = check(v1, v2);

			if(ans!=0){
				return ans;
			}
		}
		i= s1 + 1;
		j= s2 + 1;
	}
	
	return ans;
}

int main() {
	// your code goes here
	return 0;
}