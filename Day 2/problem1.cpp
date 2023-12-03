#include <bits/stdc++.h>
using namespace std;

const int RED = 12;
const int GREEN = 13;
const int BLUE = 14;

bool isNum(string s){
	if(s.length() == 0)
		return false;

	for(char c : s){
		if(!isdigit(c))
			return false;
	}
	return true;
}

string trim(string s){
	if(s[0] == ' ' || s[0] == ',' || s[0] == ':' || s[0] == ';')
		s.erase(s.begin() + 0);

	if(s[s.length() - 1] == ' ' || s[s.length() - 1] == ',' || s[s.length() - 1] == ':' || s[s.length() - 1] == ';')
		s.erase(s.begin() + s.length() - 1);

	return s;
}

int main(){
	ifstream file;
	file.open("input.txt");

	string s;
	
	int ans = 0;
	int prevNum = -1;

	while(getline(file, s)){
		string cur = "";
		vector<string> v;

		// Get words
		for(char c : s){
			if(c == ' '){
				v.push_back(trim(cur));
				cur = "";
			} else {
				cur += c;
			}
		}

		int red = INT_MIN,
			green = INT_MIN,
			blue = INT_MIN;

		for(int i = 0; i < v.size() - 1; i++){
			if(v[i + 1] == "red") red = max(red, stoi(v[i]));
			if(v[i + 1] == "green") green = max(green, stoi(v[i]));
			if(v[i + 1] == "blue") blue = max(blue, stoi(v[i]));
		}

		if(red <= RED && green <= GREEN && blue <= BLUE){
			ans += stoi(v[1]);
		}
	}

	cout << ans << "\n";

	return 0;
}