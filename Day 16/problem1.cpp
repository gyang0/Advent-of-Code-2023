#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define f first
#define s second

// The map
vector<string> v;

struct Helper {
	int i;
	int j;
	pii dir;

	bool operator<(const Helper &other) const{
		if(i != other.i) return i < other.i;
		else if(j != other.j) return j < other.j;
		else if(dir.f != other.dir.f) return dir.f < other.dir.f;
		return dir.s < other.dir.s;
	}
};
map<Helper, bool> visited;

bool pairEq(pii p1, pii p2){
	return (p1.f == p2.f && p1.s == p2.s);
}


void traverse(int i, int j, pii dir){
	if(i < 0 || i >= v.size() || j < 0 || j >= v[i].size()) return;
	if(visited[{i, j, dir}]) return;
	
	visited[{i, j, dir}] = true;

	switch(v[i][j]){
	case '.':
		traverse(i + dir.f, j + dir.s, dir);
		break;
	case '/':
		if(pairEq(dir, {0, 1})) traverse(i - 1, j, {-1, 0});
		if(pairEq(dir, {0, -1})) traverse(i + 1, j, {1, 0});
		if(pairEq(dir, {1, 0})) traverse(i, j - 1, {0, -1});
		if(pairEq(dir, {-1, 0})) traverse(i, j + 1, {0, 1});
		break;
	case '\\':
		if(pairEq(dir, {0, 1})) traverse(i + 1, j, {1, 0});
		if(pairEq(dir, {0, -1})) traverse(i - 1, j, {-1, 0});
		if(pairEq(dir, {1, 0})) traverse(i, j + 1, {0, 1});
		if(pairEq(dir, {-1, 0})) traverse(i, j - 1, {0, -1});
		break;
	case '-':
		if(pairEq(dir, {0, 1}) || pairEq(dir, {0, -1}))
			traverse(i + dir.f, j + dir.s, dir);
		else {
			traverse(i, j - 1, {0, -1});
			traverse(i, j + 1, {0, 1});
		}
		break;
	case '|':
		if(pairEq(dir, {1, 0}) || pairEq(dir, {-1, 0}))
			traverse(i + dir.f, j + dir.s, dir);
		else {
			traverse(i - 1, j, {-1, 0});
			traverse(i + 1, j, {1, 0});
		}
		break;
	}
}

int main(){
	ifstream file("input.txt");
	string s;

	while(getline(file, s)){
		v.push_back(s);
	}

	traverse(0, 0, {0, 1});

	int ans = 0;
	for(int i = 0; i < v.size(); i++){
		for(int j = 0; j < v[i].size(); j++){
			//if(visited[{i, j}]) cout << "#";
			//else cout << ".";

			if(visited[{i, j, {-1, 0}}] || visited[{i, j, {1, 0}}] || visited[{i, j, {0, -1}}] || visited[{i, j, {0, 1}}])
				ans++;
		}
		//cout << "\n";
	}
	cout << ans << "\n";

	return 0;
}