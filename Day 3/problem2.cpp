#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define f first
#define s second

// input as an array of strings
vector<string> arr;

// touching[i][j] = set of coordinates (x, y) of numbers that
// are adjacent to (i, j)
vector<vector<set<pii>>> touching;

// coordToNum[{i, j}] = number associated at that point
// (i, j) = coordinate immediately to right of the end of number
map<pii, int> coordToNum;

bool bounded(int i, int j){
	return (i >= 0 && i < arr.size() && j >= 0 && j < arr[i].size());
}

void setSurrounding(int i, int j, string cur){
	for(int x = j; x >= j - (int)cur.size() - 1; x--){
		if(bounded(i - 1, x))
			touching[i - 1][x].insert({i, j});

		if(bounded(i + 1, x))
			touching[i + 1][x].insert({i, j});

		if(bounded(i, x))
			touching[i][x].insert({i, j});
	}
}

int main(){
	ifstream file("input.txt");

	string s;
	while(getline(file, s)){
		arr.push_back(s);
	}

	touching.resize(arr.size(), vector<set<pii>>(arr[0].size()));
	
	for(int i = 0; i < arr.size(); i++){
		string cur = "";

		for(int j = 0; j < arr[i].size(); j++){
			if(isdigit(arr[i][j])){
				cur += arr[i][j];

			} else {
				if(cur != ""){
					// For the surrounding coordinates, add the number
					setSurrounding(i, j, cur);
					coordToNum[{i, j}] = stoi(cur);
				}

				cur = "";
			}
		}
		if(cur != ""){
			// For the surrounding coordinates, add the number
			setSurrounding(i, arr[i].size(), cur);
			coordToNum[{i, arr[i].size()}] = stoi(cur);
		}
	}

	long long ans = 0;
	for(int i = 0; i < arr.size(); i++){
		for(int j = 0; j < arr[i].size(); j++){
			if(arr[i][j] == '*' && touching[i][j].size() == 2){
				
				// First and last element in set
				long long n1 = coordToNum[*(touching[i][j].begin())];
				long long n2 = coordToNum[*(touching[i][j].rbegin())];
				ans += n1*n2;
			}
		}
	}
	cout << ans << "\n";


	return 0;
}