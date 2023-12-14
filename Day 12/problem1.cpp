#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define f first
#define s second

pair<string, vector<int>> splitInput(string str){
	string s1 = "";
	string s2 = "";
	vector<int> v;

	int mode = 0;
	for(char c : str){
		if(c == ' '){
			mode++;
			continue;
		}

		if(mode == 0) s1 += c;
		else {
			if(isdigit(c)) s2 += c;
			else {
				v.push_back(stoi(s2));
				s2 = "";
			}
		}
	}
	v.push_back(stoi(s2));

	return {s1, v};
}

bool matchesPattern(string cur, vector<int> pattern){
	vector<int> test;

	int streak = 0;
	for(char c : cur){
		if(c == '#') streak++;
		else {
			if(streak != 0)
				test.push_back(streak);
			streak = 0;
		}
	}
	if(streak != 0)
		test.push_back(streak);

	if(test.size() != pattern.size()) return false;

	for(int i = 0; i < test.size(); i++){
		if(test[i] != pattern[i])
			return false;
	}

	return true;
}

ll calc(string cur, string model, vector<int> pattern, int index){
	if(index >= model.size()){
		if(matchesPattern(cur, pattern)) return (ll)1;
		else return (ll)0;
	}

	if(model[index] != '?')
		return calc(cur + model[index], model, pattern, index + 1);
	else
		return calc(cur + '#', model, pattern, index + 1) + 
			   calc(cur + '.', model, pattern, index + 1);
}

int main(){
	ifstream file("input.txt");
	string s;

	ll ans = 0;
	int ind = 0;
	while(getline(file, s)){
		//if(s == "") continue;

		pair<string, vector<int>> p = splitInput(s);

		ans += calc("", p.f, p.s, 0);

		ind++;
		if(ind % 10 == 0) cout << ind/10 << "%" << " done\n";
	}
	cout << ans << "\n";
	
	return 0;
}