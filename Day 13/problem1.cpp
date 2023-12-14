#include <bits/stdc++.h>
using namespace std;

bool columnEqual(vector<string> v, int col1, int col2){
	for(int r = 0; r < v.size(); r++){
		if(v[r][col1] != v[r][col2])
			return false;
	}
	return true;
}

int calc(vector<string> v){
	int ans = 0;

	// Horizontal
	for(int i = 1; i < v.size(); i++){
		// Horizontal reflection starting at the gap between
		// row (i - 1) and i
		bool isRef = true;

		for(int j = 0; j < i; j++){
			if(i + j >= v.size()) break;

			if(v[i - 1 - j] != v[i + j]){
				isRef = false;
				break;
			}
		}

		if(isRef){
			ans += 100*i;
			break;
		}
	}

	// Vertical
	for(int i = 1; i < v[0].size(); i++){
		// Vertical reflection starting at the gap between
		// column (i - 1) and i
		bool isRef = true;
		for(int j = 0; j < i; j++){
			if(i + j >= v[0].size()) break;

			if(!columnEqual(v, i - 1 - j, i + j)){
				isRef = false;
				break;
			}
		}

		if(isRef){
			ans += i;
			break;
		}
	}

	return ans;
}

int main(){
	ifstream file("input.txt");
	string s;

	vector<string> v;
	int ans = 0;

	while(getline(file, s)){
		if(s == ""){
			ans += calc(v);
			//cout << calc(v) << "\n";
			v.resize(0);
		} else {
			v.push_back(s);
		}
	}
	if(v.size() != 0){
		ans += calc(v);
		//cout << calc(v) << "\n";
	}

	cout << ans << "\n";

	return 0;
}