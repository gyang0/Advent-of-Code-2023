#include <bits/stdc++.h>
using namespace std;

string trim(string s){
	if(s[0] == ' ' || s[0] == ',' || s[0] == ':' || s[0] == ';')
		s.erase(s.begin() + 0);

	if(s[s.length() - 1] == ' ' || s[s.length() - 1] == ',' || s[s.length() - 1] == ':' || s[s.length() - 1] == ';')
		s.erase(s.begin() + s.length() - 1);

	return s;
}

vector<int> rgbs(string s){
	vector<string> v;

	string cur = "";

	// Get words
	for(char c : s){
		if(c == ' '){
			v.push_back(trim(cur));
			cur = "";
		} else {
			cur += c;
		}
	}
	if(cur != "") v.push_back(trim(cur));

	int red = 0,
		green = 0,
		blue = 0;

	for(int i = 0; i < v.size() - 1; i++){
		if(v[i + 1] == "red") red += stoi(v[i]);
		if(v[i + 1] == "green") green += stoi(v[i]);
		if(v[i + 1] == "blue") blue += stoi(v[i]);
	}

	return {red, green, blue};
}

int main(){
	ifstream file;
	file.open("input.txt");

	string s;
	
	long long int ans = 0;
	int prevNum = -1;

	while(getline(file, s)){
		vector<int> minRGBs = {0, 0, 0};

		string cur = "";

		for(char c : s){
			if(c == ':'){
				cur = "";
			} else if(c == ';'){
				vector<int> res = rgbs(cur);
				
				minRGBs[0] = max(minRGBs[0], res[0]);
				minRGBs[1] = max(minRGBs[1], res[1]);
				minRGBs[2] = max(minRGBs[2], res[2]);
				
				cur = "";
			} else {
				cur += c;
			}
		}
		if(cur != ""){
			vector<int> res = rgbs(cur);
			
			minRGBs[0] = max(minRGBs[0], res[0]);
			minRGBs[1] = max(minRGBs[1], res[1]);
			minRGBs[2] = max(minRGBs[2], res[2]);
		}

		ans += (minRGBs[0] * minRGBs[1] * minRGBs[2]);
	}

	cout << ans << "\n";

	return 0;
}