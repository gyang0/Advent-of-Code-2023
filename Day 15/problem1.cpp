#include <bits/stdc++.h>
using namespace std;

int getHash(string s){
	int curVal = 0;
	for(char c : s){
		curVal += (int)(c);
		curVal *= 17;
		curVal %= 256;
	}
	return curVal;
}

int analyze(string s){
	string cur = "";
	int hashSum = 0;

	for(char c : s){
		if(c == ','){
			hashSum += getHash(cur);
			//cout << cur << ": " << getHash(cur) << "\n";
			cur = "";
		} else {
			cur += c;
		}
	}
	if(cur != "")
		hashSum += getHash(cur);
	
	return hashSum;
}

int main(){
	ifstream file("input.txt");
	string s;

	int ans = 0;
	while(getline(file, s)){
		if(s == "") continue;
		ans += analyze(s);
	}
	cout << ans << "\n";

	return 0;
}