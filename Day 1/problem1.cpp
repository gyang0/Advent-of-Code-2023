#include <bits/stdc++.h>
using namespace std;

int main(){
	ifstream file;
	file.open("input.txt");

	string s;
	long long ans = 0;
	while(getline(file, s)){
		int first = -1,
			last;

		for(char c : s){
			if('0' <= c && c <= '9'){
				if(first == -1)
					first = c - '0';
				
				last = c - '0';
			}
		}
		
		ans += (10 * first) + last;
	}

	cout << ans << "\n";

	return 0;
}