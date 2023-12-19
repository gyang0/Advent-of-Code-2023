#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define f first
#define s second

#define ll long long int

// Heat loss map
vector<vector<int>> heatLoss;

bool isEq(pii p1, pii p2){
	return (p1.f == p2.f && p1.s == p2.s);
}

bool inRange(pii p){
	return (p.f >= 0 && p.f < heatLoss.size() && p.s >= 0 && p.s < heatLoss[0].size());
}

struct Point {
	int heat; // Heat loss so far
	pii pos;
	pii dir;

	bool operator<(const Point &other) const {
		if(heat != other.heat) return heat < other.heat;
		else if(pos != other.pos) return pos < other.pos;
		else return dir < other.dir;
	}
};


// Memoization
// <position pair, direction pair>
map<pair<pii, pii>, bool> memo;

int main(){
	ifstream file("input.txt");
	string s;

	while(getline(file, s)){
		heatLoss.push_back({});
		for(char c : s)
			heatLoss[heatLoss.size() - 1].push_back(c - '0');
	}


	// Dijkstra
	priority_queue<Point> q;
	map<pii, int> dist;

	for(int i = 0; i < heatLoss.size(); i++){
		for(int j = 0; j < heatLoss[i].size(); j++){
			dist[{i, j}] = INT_MAX;
		}
	}

	q.push({0, {0, 0}, {-10, -10}});

	while(!q.empty()){
		Point node = q.top();
		q.pop();

		
		// node.heat is initially negative because it's stored like that to ensure sorting by min
		// C++ priority_queue quirks
		node.heat *= -1;

		dist[node.pos] = min(dist[node.pos], node.heat);

		// Memoize
		if(memo.count({node.pos, node.dir}))
			continue;
		memo[{node.pos, node.dir}] = true;
		
		// Turning whenever possible after continuing for a certain distance
		for(int dx = -1; dx <= 1; dx++){
			for(int dy = -1; dy <= 1; dy++){
				if(abs(dx) + abs(dy) != 1) continue;
				
				// Can't continue straight
				if(isEq(node.dir, {dx, dy})) continue;

				// Can't reverse direction
				if(isEq(node.dir, {-dx, -dy})) continue;


				// Can either move 1, 2, or 3 times in a single direction before turning
				pii newInd = {node.pos.f, node.pos.s};
				int loss = node.heat;
				for(int d = 1; d <= 3; d++){
					newInd.f += dx;
					newInd.s += dy;

					// Out of bounds
					if(!inRange(newInd))
						break;

					loss += heatLoss[newInd.f][newInd.s];

					// Hours of debugging spent on this:
					// Can't use a typical Dijkstra to weed out solutions, since different directions give different results.
					//if(dist[node.pos] + loss < dist[newInd]){
					// Negative to make C++ priority_queue sort by min
						q.push({-loss, newInd, {dx, dy}});
					//}
				}

			}
		}
	}

	/*for(int i = 0; i < heatLoss.size(); i++){
		for(int j = 0; j < heatLoss[i].size(); j++){
			if(dist[{i, j}] == INT_MAX) cout << setw(6) << "-";
			else cout << setw(6) << dist[{i, j}];
		}
		cout << "\n";
	}
	cout << "\n";*/

	cout << dist[{heatLoss.size() - 1, heatLoss[0].size() - 1}] << "\n";
	
	return 0;
}