#include <bits/stdc++.h>
using namespace std;

int _find(vector<int> v, int target){
	for(int i : v){
		if(i == target)
			return true;
	}
	return false;
}

// numCards[i] = number of cards you have whose ID is i
map<int, int> numCards;

void display(){
	for(const auto &[key, val] : numCards){
		cout << key << ": " << val << "\n";
	}
	cout << "\n";
}

int main(){
	ifstream file("input.txt");

	
	string s;
	int lineIndex = 1;

	numCards[1] = 0;


	while(getline(file, s)){
		vector<int> has;
		vector<int> winning;

		string cur = "";
		bool hasNums = false;
		int flag = 0;
		for(int i = 4; i < s.size(); i++){
			if(s[i] == '|')
				flag++;

			if(isdigit(s[i])){
				cur += s[i];
				hasNums = true;
			} else {
				if(hasNums && s[i] != ':'){
					if(flag == 0) has.push_back(stoi(cur));
					else winning.push_back(stoi(cur));
				}

				cur = "";
				hasNums = false;
			}
		}

		// Last num
		if(hasNums){
			if(flag == 0) has.push_back(stoi(cur));
			else winning.push_back(stoi(cur));
		}

		int matching = 0;
		for(int i = 0; i < has.size(); i++){
			if(_find(winning, has[i])){
				matching++;
			}
		}


		// Account for card we already have
		numCards[lineIndex]++;

		for(int dx = 1; dx <= matching; dx++){
			numCards[lineIndex + dx] += numCards[lineIndex];
		}

		//cout << "Line " << lineIndex << ": " << matching << "\n";
		//display();

		lineIndex++;
	}

	int ans = 0;
	for(const auto &[key, val] : numCards){
		ans += val;
	}
	cout << ans << "\n";

	return 0;
}