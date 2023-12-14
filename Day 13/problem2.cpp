#include <bits/stdc++.h>
using namespace std;

int rowDiffs(vector<string> v, int row1, int row2){
	int diffs = 0;
	for(int i = 0; i < v[0].size(); i++){
		if(v[row1][i] != v[row2][i])
			diffs++;
	}
	return diffs;
}

int columnDiffs(vector<string> v, int col1, int col2){
	int diffs = 0;
	for(int r = 0; r < v.size(); r++){
		if(v[r][col1] != v[r][col2])
			diffs++;
	}
	return diffs;
}

int calc(vector<string> v){
	int ans = 0;

	// Horizontal
	for(int i = 1; i < v.size(); i++){
		// Horizontal reflection starting at the gap between
		// row (i - 1) and i
		
		// # of different positions
		int diffs = 0;
		for(int j = 0; j < i; j++){
			if(i + j >= v.size()) break;
			diffs += rowDiffs(v, i - 1 - j, i + j);
		}

		if(diffs == 1){
			ans += 100*i;
			break;
		}
	}

	// Vertical
	for(int i = 1; i < v[0].size(); i++){
		// Vertical reflection starting at the gap between
		// column (i - 1) and i
		
		// # of different positions
		int diffs = 0;
		for(int j = 0; j < i; j++){
			if(i + j >= v[0].size()) break;
			diffs += columnDiffs(v, i - 1 - j, i + j);
		}

		if(diffs == 1){
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
			v.resize(0);
		} else {
			v.push_back(s);
		}
	}
	if(v.size() != 0){
		ans += calc(v);
	}

	cout << ans << "\n";

	return 0;
}