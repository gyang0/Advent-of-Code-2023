#include <bits/stdc++.h>
using namespace std;

string words[] = {
	"",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};

int main(){
	ifstream file;
	file.open("input.txt");

	string s;
	long long ans = 0;
	while(getline(file, s)){
		int first = -1,
			last;

		for(int i = 0; i < s.length(); i++){
			// Numbers
			if('0' <= s[i] && s[i] <= '9'){
				if(first == -1)
					first = s[i] - '0';
				
				last = s[i] - '0';
			}

			// Words (check words[1] to words[9])
			for(int j = 1; j <= 9; j++){

				// If the potential string is within bounds
				if(i + words[j].length() <= s.length()){
					if(s.substr(i, words[j].length()) == words[j]){
						if(first == -1)
							first = j;

						last = j;
					}
				}
			}
		}

		ans += (10 * first) + last;
	}

	cout << ans << "\n";

	return 0;
}