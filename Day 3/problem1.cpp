#include <bits/stdc++.h>
using namespace std;

vector<string> arr;

bool bounded(int i, int j){
	return (i >= 0 && i < arr.size() && j >= 0 && j < arr[i].size());
}

bool check(int i, int j){
	return bounded(i, j) && !isdigit(arr[i][j]) && arr[i][j] != '.';
}

bool surrounding(int i, int j){
	return check(i - 1, j) || check(i + 1, j) ||
		   check(i, j - 1) || check(i, j + 1) ||
		   check(i - 1, j - 1) || check(i - 1, j + 1) ||
		   check(i + 1, j - 1) || check(i + 1, j + 1);
}

int main(){
	ifstream file;
	file.open("input.txt");

	string s;
	while(getline(file, s)){
		arr.push_back(s);
	}

	int ans = 0;

	for(int i = 0; i < arr.size(); i++){
		string cur = "";
		bool ok = false;

		for(int j = 0; j < arr[i].size(); j++){
			if(isdigit(arr[i][j])){
				cur += arr[i][j];

				if(surrounding(i, j)){
					ok = true;
				}

			} else {
				if(cur != ""){
					if(ok){
						ans += stoi(cur);
						ok = false;
					}
				}

				cur = "";
			}
		}
		if(cur != ""){
			if(ok){
				ans += stoi(cur);
				ok = false;
			}
		}
	}

	cout << ans << "\n";

	return 0;
}