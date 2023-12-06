#include <bits/stdc++.h>
using namespace std;

#define ll long long int

vector<ll> splitInput(string s){
	string cur = "";
	vector<ll> res;

	for(int i = 0; i < s.size(); i++){
		if(isdigit(s[i])){
			cur += s[i];
		} else {
			if(cur != ""){
				res.push_back(stoll(cur, nullptr, 10));
			}
			cur = "";
		}
	}
	if(cur != ""){
		res.push_back(stoll(cur, nullptr, 10));
	}


	return res;
}

int main(){
	ifstream file("input.txt");

	string s;

	/*
	1. seed to soil
	2. soil to fertilizer
	3. fertilizer to water
	4. water to light
	5. light to temperature
	6. temperature to humidity
	7. humidity to location
	*/

	vector<ll> seeds;
	vector<bool> done;

	// C++ input is a pain sometimes
	while(getline(file, s)){
		// Initial input
		if(s.substr(0, 6) == "seeds:"){
			seeds = splitInput(s.substr(6));
			done = vector<bool>(seeds.size(), false);

		} else if(s != "" && isdigit(s[0])){
			vector<ll> res = splitInput(s);

			// Calculate
			for(int i = 0; i < seeds.size(); i++){
				if(!done[i] && res[1] <= seeds[i] && seeds[i] <= res[1] + res[2] - 1){
					seeds[i] = res[0] + (seeds[i] - res[1]);
					done[i] = true;
				}
			}
		}

		if(s == ""){
			// Reset for another run
			for(int i = 0; i < done.size(); i++){
				done[i] = false;
			}

			for(ll loc : seeds){
				cout << loc << " ";
			}
			cout << "\n";
		}
	}

	ll ans = seeds[0];
	for(ll loc : seeds){
		ans = min(ans, loc);
	}
	cout << ans << "\n";
	
	return 0;
}