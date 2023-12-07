#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<int> splitInput(string s){
	string cur = "";
	vector<int> res;

	for(int i = 0; i < s.size(); i++){
		if(isdigit(s[i])){
			cur += s[i];
		} else {
			if(cur != ""){
				res.push_back(stoi(cur));
			}
			cur = "";
		}
	}
	if(cur != "")
		res.push_back(stoll(cur));

	return res;
}


vector<int> times;
vector<int> distances;

ll prodAns(int i){
	ll ans = 0;
	for(int time = 1; time <= times[i]; time++){
		if((times[i] - time)*time > distances[i]){
			ans++;
		}
	}
	return ans;
}

int main(){
	ifstream file("input.txt");


	string s;
	int index = 0;
	while(getline(file, s)){
		if(index == 0) times = splitInput(s);
		else distances = splitInput(s);

		index++;
	}

	ll ans = 1;
	for(int i = 0; i < times.size(); i++){
		ans *= prodAns(i);
	}
	cout << ans << "\n";


	return 0;
}