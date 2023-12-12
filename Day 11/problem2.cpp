#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define pii pair<int, int>
#define f first
#define s second

// Map (with galaxy expansion taken into account)
vector<string> arr;

// Coordinates of stars
vector<pii> stars;

bool allRows(string s, char target){
	for(char c : s){
		if(c != target)
			return false;
	}
	return true;
}

bool allColumns(int c, char target){
	for(string s : arr){
		if(s[c] != target)
			return false;
	}
	return true;
}

map<int, bool> emptyRow;
map<int, bool> emptyCol;

const int GALAXY_INC_BY = 1000000;

ll manhattan(pii p1, pii p2){
	ll rowDist = 0;
	for(int i = min(p1.f, p2.f); i < max(p1.f, p2.f); i++){
		if(emptyRow[i]) rowDist += GALAXY_INC_BY;
		else rowDist++;
	}

	ll colDist = 0;
	for(int i = min(p1.s, p2.s); i < max(p1.s, p2.s); i++){
		if(emptyCol[i]) colDist += GALAXY_INC_BY;
		else colDist++;
	}

	return rowDist + colDist;
}

int main(){
	ifstream file("input.txt");

	// 1. Get input
	string s;
	while(getline(file, s)){
		arr.push_back(s);
	}

	// Expansions
	for(int r = 0; r < arr.size(); r++){
		if(allRows(arr[r], '.')) emptyRow[r] = true;
	}
	for(int c = 0; c < arr[0].size(); c++){
		if(allColumns(c, '.')) emptyCol[c] = true;
	}

	
	// 2. Assign numbers to each galaxy
	for(int i = 0; i < arr.size(); i++){
		for(int j = 0; j < arr[i].size(); j++){
			if(arr[i][j] == '#')
				stars.push_back({i, j});
		}
	}

	// 3. For each of the stars, find distance to the rest
	//    of the stars using a variation of manhattan distance
	ll sum = 0;
	for(int i = 0; i < stars.size(); i++){
		for(int j = i + 1; j < stars.size(); j++){
			sum += manhattan(stars[i], stars[j]);
		}
	}

	cout << sum << "\n";

	
	return 0;
}