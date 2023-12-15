#include <bits/stdc++.h>
using namespace std;

int main(){
	ifstream file("input.txt");
	string s;

	vector<string> v;
	while(getline(file, s)){
		v.push_back(s);
	}

	// For each column, slide up
	for(int c = 0; c < v[0].size(); c++){
		
		// For a potential rock in each row
		for(int r = 0; r < v.size(); r++){
			if(v[r][c] != 'O') continue;

			int curRow = r;
			while(curRow > 0 && v[curRow - 1][c] == '.'){
				v[curRow - 1][c] = 'O';
				v[curRow][c] = '.';

				curRow--;
			}
		}
	}

	int ans = 0;
	for(int r = 0; r < v.size(); r++){
		int numRocks = 0;
		for(int c = 0; c < v[r].size(); c++){
			if(v[r][c] == 'O')
				numRocks++;
		}
		ans += numRocks * (v.size() - r);
	}
	cout << ans << "\n";
	
	return 0;
}