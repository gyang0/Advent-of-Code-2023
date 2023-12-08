#include <bits/stdc++.h>
using namespace std;

#define psi pair<string, int>
#define f first
#define s second

psi splitInput(string str){
	psi res;

	string cur = "";
	for(char c : str){
		if(c == ' '){
			res.f = cur;
			cur = "";
		} else {
			cur += c;
		}
	}
	res.s = stoi(cur);
	return res;
}

int getRank(char c){
	switch(c){
	case 'A': return 13;
	case 'K': return 12;
	case 'Q': return 11;
	case 'T': return 10;
	case '9': return 9;
	case '8': return 8;
	case '7': return 7;
	case '6': return 6;
	case '5': return 5;
	case '4': return 4;
	case '3': return 3;
	case '2': return 2;
	case 'J': return 1;
	}
	return 0;
}

bool matches(vector<int> v1, vector<int> v2){
	if(v1.size() != v2.size())
		return false;
	
	for(int i = 0; i < v1.size(); i++){
		if(v1[i] != v2[i])
			return false;
	}
	return true;
}

int getCardScore(string s){
	map<char, int> m;

	for(char c : s){
		m[c]++;
	}

	vector<int> v;
	for(const auto &[key, val] : m)
		v.push_back(val);
	sort(v.begin(), v.end());

	if(matches(v, {5})) return 7; // Five of a kind
	if(matches(v, {1, 4})) return 6; // Four of a kind
	if(matches(v, {2, 3})) return 5; // Full house
	if(matches(v, {1, 1, 3})) return 4; // Three of a kind
	if(matches(v, {1, 2, 2})) return 3; // Two pair
	if(matches(v, {1, 1, 1, 2})) return 2; // One pair
	if(matches(v, {1, 1, 1, 1, 1})) return 1; // High card

	return 0;
}

char possible[] = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};

int getType(string str){
	map<char, int> m;
	for(char c : str)
		m[c]++;

	char toReplaceWith = 'A';
	int curMaxVal = 0;
	for(const auto &[key, val] : m){
		if(key != 'J'){
			if(val > curMaxVal){
				toReplaceWith = key;
				curMaxVal = val;
			}
		}
	}

	string s = "";
	for(char c : str){
		if(c == 'J') s += toReplaceWith;
		else s += c;
	}

	return getCardScore(s);
}

int main(){
	ifstream file("input.txt");

	string str;
	vector<psi> cards;
	while(getline(file, str)){
		psi p = splitInput(str);
		cards.push_back(p);
	}

	sort(cards.begin(), cards.end(), [](const psi &c1, const psi &c2){
		if(getType(c1.f) == getType(c2.f)){
			for(int i = 0; i < c1.f.size(); i++){
				if(c1.f[i] != c2.f[i])
					return getRank(c1.f[i]) < getRank(c2.f[i]);
			}
		} else {
			return getType(c1.f) < getType(c2.f);
		}
	});

	long long int ans = 0;
	for(int i = 0; i < cards.size(); i++)
		ans += cards[i].s * (i + 1);

	cout << ans << "\n";


	return 0;
}