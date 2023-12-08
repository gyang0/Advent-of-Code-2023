#include <bits/stdc++.h>
using namespace std;

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
	
	int steps = 0;
	string cur = "AAA";
	
	// Follow the path
	int i = 0;
	while(true){
		if(dirs[i] == 'L')
			cur = m[cur].f;
		else
			cur = m[cur].s;

		i++;
		steps++;
		i %= (int)(dirs.size());

		// Yay, found it
		if(cur == "ZZZ"){
			cout << steps << "\n";
			return 0;
		}
	}

	return 0;
}