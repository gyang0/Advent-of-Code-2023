#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<ll> splitInput(string s){
	vector<ll> ans;
	string cur = "";

	for(char c : s){
		if(c != ' ') cur += c;
		else {
			if(cur != "")
				ans.push_back(stoll(cur));
			cur = "";
		}
	}
	if(cur != "")
		ans.push_back(stoll(cur));
	
	return ans;		
}

bool allSame(vector<ll> v){
	for(int i = 1; i < v.size(); i++){
		if(v[i] != v[0])
			return false;
	}
	return true;
}

vector<ll> diffVect(vector<ll> v){
	vector<ll> ans;
	for(int i = 1; i < v.size(); i++){
		ans.push_back(v[i] - v[i - 1]);
	}
	return ans;
}

ll getNextVal(vector<ll> v){
	if(allSame(v))
		return v[0];
	else
		return v[(int)v.size() - 1] + getNextVal(diffVect(v));
}

int main(){
	ifstream file("input.txt");

	string s;
	ll ans = 0;
	while(getline(file, s)){
		vector<ll> input = splitInput(s);
		ans += getNextVal(input);
	}
	cout << ans << "\n";

	return 0;
}