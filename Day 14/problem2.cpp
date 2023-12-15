#include <bits/stdc++.h>
using namespace std;

// Map
vector<string> v;

void slideNorth(){
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
}

void slideWest(){
	// For each row, slide left
	for(int r = 0; r < v.size(); r++){
		
		// For a potential rock in each column
		for(int c = 0; c < v[0].size(); c++){
			if(v[r][c] != 'O') continue;

			int curCol = c;
			while(curCol > 0 && v[r][curCol - 1] == '.'){
				v[r][curCol - 1] = 'O';
				v[r][curCol] = '.';

				curCol--;
			}
		}
	}
}

void slideSouth(){
	// For each column, slide down
	for(int c = 0; c < v[0].size(); c++){
		
		// For a potential rock in each row
		for(int r = v.size() - 1; r >= 0; r--){
			if(v[r][c] != 'O') continue;

			int curRow = r;
			while(curRow < v.size() - 1 && v[curRow + 1][c] == '.'){
				v[curRow + 1][c] = 'O';
				v[curRow][c] = '.';

				curRow++;
			}
		}
	}
}

void slideEast(){
	// For each row, slide right
	for(int r = 0; r < v.size(); r++){
		
		// For a potential rock in each column
		for(int c = v[0].size() - 1; c >= 0; c--){
			if(v[r][c] != 'O') continue;

			int curCol = c;
			while(curCol < v[0].size() - 1 && v[r][curCol + 1] == '.'){
				v[r][curCol + 1] = 'O';
				v[r][curCol] = '.';

				curCol++;
			}
		}
	}
}

void cycle(){
	slideNorth();
	slideWest();
	slideSouth();
	slideEast();
}

void display(vector<string> vect){
	for(string s : vect)
		cout << s << "\n";
	cout << "\n";
}

bool isSame(vector<string> v1, vector<string> v2){
	if(v1.size() != v2.size()) return false;

	for(int i = 0; i < v1.size(); i++){
		if(v1[i] != v2[i])
			return false;
	}
	return true;
}

int score(){
	int ans = 0;
	for(int r = 0; r < v.size(); r++){
		int numRocks = 0;
		for(int c = 0; c < v[r].size(); c++){
			if(v[r][c] == 'O')
				numRocks++;
		}
		ans += numRocks * (v.size() - r);
	}
	return ans;
}

int main(){
	ifstream file("input.txt");
	string s;

	while(getline(file, s)){
		v.push_back(s);
	}

	vector<vector<string>> test;
	bool stop = false;
	int cycleStart = -1,
		cycleEnd = -1;

	for(int i = 0; i < 1000000000; i++){
		cycle();
		
		for(int j = 0; j < test.size(); j++){
			if(isSame(test[j], v)){
				// We found a match, cycle will repeat from now on.
				cycleStart = j;
				cycleEnd = i;
				stop = true;
				break;
			}
		}

		if(stop)
			break;

		test.push_back(v);
	}

	int numLeft = (1000000000 - cycleEnd - 1) % (cycleEnd - cycleStart);
	for(int i = 0; i < numLeft; i++){
		cycle();
	}
	cout << score() << "\n";

	return 0;
}