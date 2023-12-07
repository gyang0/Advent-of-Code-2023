#include <bits/stdc++.h>
using namespace std;

#define ll long long

// Just modify this a bit
ll splitInput(string s){
	string cur = "";

	for(int i = 0; i < s.size(); i++){
		if(isdigit(s[i])){
			cur += s[i];
		}
	}
	return stoll(cur);
}

ll prodAns(ll time, ll dist){
	ll ans = 0;
	for(int t = 1; t <= time; t++){
		if((time - t)*t > dist){
			ans++;
		}
	}
	return ans;
}

int main(){
	ifstream file("input.txt");

	string s;
	int index = 0;
	ll time, dist;

	while(getline(file, s)){
		if(index == 0) time = splitInput(s);
		else dist = splitInput(s);

		index++;
	}

	cout << prodAns(time, dist) << "\n";


	return 0;
}