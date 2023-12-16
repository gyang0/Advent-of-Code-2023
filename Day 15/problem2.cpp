#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define ll long long int

// Each vectors within the array represents the contents of a box
// Vector is <string, focal length>
vector<pair<string, int>> boxes[256];

int getHash(string s){
	int curVal = 0;
	for(char c : s){
		curVal += (int)(c);
		curVal *= 17;
		curVal %= 256;
	}
	return curVal;
}

int getPos(string cur, int boxIndex){
	for(int i = 0; i < boxes[boxIndex].size(); i++){
		if(boxes[boxIndex][i].f == cur)
			return i;
	}
	return -1;
}

void analyze(string s){
	string cur = "";
	string num = "";
	bool isEq = false;

	for(char c : s){
		if(c == ','){
			// cout << "Box hash: for " << cur << "\n";
			// cout << "Is = sign? " << (isEq ? "true" : "false") << "\n";
			// cout << "Number: " << stoi(num) << "\n\n";

			int boxHash = getHash(cur);
			

			// If '-', erase occurrence
			if(!isEq){
				int posInBox = getPos(cur, boxHash);
				if(posInBox != -1)
					boxes[boxHash].erase(boxes[boxHash].begin() + posInBox);
			}

			// If '=', replace or add.
			else {
				int posInBox = getPos(cur, boxHash);
				if(posInBox != -1)
					boxes[boxHash][posInBox].s = stoi(num);
				else
					boxes[boxHash].push_back({cur, stoi(num)});
			}

			cur = "";
			isEq = false;
			num = "";

		} else {
			if(isalpha(c)) cur += c;
			else if(c == '=') isEq = true;
			else if(isdigit(c)) num += c;
		}
	}
}

int main(){
	ifstream file("input.txt");
	string s;

	while(getline(file, s)){
		if(s == "") continue;

		// Add a sentinel at the end to avoid repeating code
		s += ',';
		analyze(s);
	}

	ll ans = 0;
	for(int i = 0; i < 256; i++){
		for(int j = 0; j < boxes[i].size(); j++){
			/*
			Product of:
				(box number, 1-indexed)
				(index of the lens within the box, 1-indexed)
				(focal length of lens)
			*/

			ans += (ll)(i + 1) * (ll)(j + 1) * (ll)(boxes[i][j].s);
		}
	}
	cout << ans << "\n";

	return 0;
}