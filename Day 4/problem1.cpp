#include <bits/stdc++.h>
using namespace std;

int _find(vector<int> v, int target){
	for(int i : v){
		if(i == target)
			return true;
	}
	return false;
}

int main(){
	ifstream file("input.txt");

	string s;
	long long ans = 0;
	while(getline(file, s)){
		vector<int> has;
		vector<int> winning;

		string cur = "";
		bool hasNums = false;
		int flag = 0;
		for(int i = 4; i < s.size(); i++){
			if(s[i] == '|')
				flag++;

			if(isdigit(s[i])){
				cur += s[i];
				hasNums = true;
			} else {
				if(hasNums && s[i] != ':'){
					if(flag == 0) has.push_back(stoi(cur));
					else winning.push_back(stoi(cur));
				}

				cur = "";
				hasNums = false;
			}
		}

		// Last num
		if(hasNums){
			if(flag == 0) has.push_back(stoi(cur));
			else winning.push_back(stoi(cur));
		}

		/*for(int i : has) cout << i << " ";
			cout << "\n";
		for(int i : winning) cout << i << " ";
			cout << "\n\n";*/

		long long exp = 1;
		for(int i = 0; i < has.size(); i++){
			if(_find(winning, has[i])){
				exp *= 2;
			}
		}

		ans += exp/2;
	}

	cout << ans << "\n";

	return 0;
}