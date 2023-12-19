#include <bits/stdc++.h>
using namespace std;

#define pii pair<long long int, long long int>
#define f first
#define s second

#define ll long long int

vector<string> splitInput(string &s){
	vector<string> v;

	string cur = "";
	for(char c : s){
		if(c != ' ') cur += c;
		else {
			v.push_back(cur);
			cur = "";
		}
	}
	if(cur != "") v.push_back(cur);

	return v;
}

int main(){
	ifstream file("input.txt");
	string s;

	pii curPos = {0, 0};
	vector<pii> points = {curPos};

	ll boundary = 0;

	while(getline(file, s)){
		vector<string> v = splitInput(s);

		if(v[0] == "R") curPos.s += stoi(v[1]);
		else if(v[0] == "L") curPos.s -= stoi(v[1]);
		else if(v[0] == "U") curPos.f -= stoi(v[1]);
		else curPos.f += stoi(v[1]);

		boundary += stoi(v[1]);

		points.push_back(curPos);
	}

	// Shoelace theorem again
	ll area = 0;
	for(int i = 1; i < points.size(); i++){
		// (x1, y1) = (points[i - 1].f, points[i - 1].s)
		// (x2, y2) = (points[i].f, points[i].s)
		area += (points[i - 1].f * points[i].s) - (points[i - 1].s * points[i].f);
	}
	area += (points[points.size() - 1].f * points[0].s) - (points[points.size() - 1].s * points[0].f);

	area /= 2;
	area = abs(area);

	// Pick's Theorem
	// A = i + b/2 - 1
	// We want i + b
	// i = A - b/2 + 1
	// i + b = A + b/2 + 1
	cout << area + boundary/2 + 1 << "\n";

	return 0;
}