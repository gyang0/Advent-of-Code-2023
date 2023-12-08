#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define pss pair<string, string>
#define f first
#define s second

vector<string> splitInput(string s){
	vector<string> ans;
	string cur = "";

	for(char c : s){
		if('A' <= c && c <= 'Z')
			cur += c;
		else {
			if(cur != "") ans.push_back(cur);
			cur = "";
		}
	}
	if(cur != "") ans.push_back(cur);
	return ans;
}

int main(){
	ifstream file("input.txt");

	string s;
	string dirs;
	bool firstLine = false;

	map<string, pss> m;

	while(getline(file, s)){
		if(s == "") continue;

		if(!firstLine){
			dirs = s;
			firstLine = true;
		} else {
			vector<string> hmm = splitInput(s);
			m[hmm[0]] = {hmm[1], hmm[2]};
		}
	}
	

	vector<int> times;

	for(const auto &[key, val] : m){
		if(key[2] != 'A') continue;

		string cur = key;
		int steps = 0;
		int i = 0;
		
		// Follow the path
		while(true){
			if(dirs[i] == 'L')
				cur = m[cur].f;
			else
				cur = m[cur].s;

			i++;
			steps++;
			i %= (int)(dirs.size());

			// Found an endpoint
			if(cur[2] == 'Z'){
				times.push_back(steps);
				break;
			}
		}
	}

	// Find LCM of all times it takes to reach a destination
	ll ans = times[0];
	for(int i = 1; i < times.size(); i++){
		ans = lcm(ans, (ll)times[i]);
	}

	cout << ans << "\n";

	return 0;
}