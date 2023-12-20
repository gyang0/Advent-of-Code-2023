#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define pii pair<long long int, long long int>
#define f first
#define s second

struct Gear {
	int x;
	int m;
	int a;
	int s;
};

map<string, vector<string>> conditions;

bool includes(string s, char c){
	for(char cc : s){
		if(cc == c) return true;
	}
	return false;
}

// How many combinations are accepted?
ll test(string workflow, pii xRng, pii mRng, pii aRng, pii sRng){
	// Checks
	if(workflow == "A") return (xRng.s - xRng.f)*(mRng.s - mRng.f)*(aRng.s - aRng.f)*(sRng.s - sRng.f);
	else if(workflow == "R") return 0;
	
	//if(xRng.s <= xRng.f) return 0;
	//if(mRng.s <= mRng.f) return 0;
	//if(aRng.s <= aRng.f) return 0;
	//if(sRng.s <= sRng.f) return 0;

	ll ans = 0;

	for(string str : conditions[workflow]){
		if(str == "A"){
			ans += (xRng.s - xRng.f)*(mRng.s - mRng.f)*(aRng.s - aRng.f)*(sRng.s - sRng.f);
			break;
		}
		else if(str == "R"){
			ans += 0;
			break;
		}
		else if(!includes(str, ':')){
			ans += test(str, xRng, mRng, aRng, sRng);
			break;
		}
		else {
			char c = str[0];
			char ineq = str[1];
			int comp = stoi(str.substr(2, str.find(':')));
			string then = str.substr(str.find(':') + 1);

			if(c == 'x'){
				if(ineq == '<'){
					ans += test(then, {xRng.f, comp}, mRng, aRng, sRng);
					xRng.f = comp;
				} else {
					ans += test(then, {comp + 1, xRng.s}, mRng, aRng, sRng);
					xRng.s = comp + 1;
				}
			} else if(c == 'm'){
				if(ineq == '<'){
					ans += test(then, xRng, {mRng.f, comp}, aRng, sRng);
					mRng.f = comp;
				} else {
					ans += test(then, xRng, {comp + 1, mRng.s}, aRng, sRng);
					mRng.s = comp + 1;
				}
			} else if(c == 'a'){
				if(ineq == '<'){
					ans += test(then, xRng, mRng, {aRng.f, comp}, sRng);
					aRng.f = comp;
				} else {
					ans += test(then, xRng, mRng, {comp + 1, aRng.s}, sRng);
					aRng.s = comp + 1;
				}
			} else {
				if(ineq == '<'){
					ans += test(then, xRng, mRng, aRng, {sRng.f, comp});
					sRng.f = comp;
				} else {
					ans += test(then, xRng, mRng, aRng, {comp + 1, sRng.s});
					sRng.s = comp + 1;
				}
			}
		}
	}

	return ans;
}

void workflowInput(string s){
	string name = "";
	while(s[0] != '{'){
		name += s[0];
		s.erase(s.begin());
	}

	// Get rid of curly braces
	s.erase(s.begin());
	s.erase(s.begin() + s.size() - 1);

	string cur = "";
	for(int i = 0; i < s.size(); i++){
		if(s[i] == ','){
			conditions[name].push_back(cur);
			cur = "";
		} else {
			cur += s[i];
		}
	}
	conditions[name].push_back(cur);
}


int main(){
	ifstream file("input.txt");
	string s;

	int mode = 0;
	while(getline(file, s)){
		if(s == ""){
			mode++;
			continue;
		}

		if(mode == 0){
			workflowInput(s);
		} else {
			// gearInput(s);
		}
	}

	// Now testing ranges
	// All ranges should be [inclusive, exclusive)
	cout << test("in", {1, 4001}, {1, 4001}, {1, 4001}, {1, 4001}) << "\n";

	return 0;
}