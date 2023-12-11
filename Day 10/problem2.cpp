#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define pii pair<int, int>
#define f first
#define s second

vector<string> arr;
map<pii, bool> visited;

struct Point {
	int x;
	int y;
	vector<pii> steps; // What points were taken to reach this point
};

// Can move to certain direction if it's one of these chars
string goingRight = "-J7";
string goingLeft = "-LF";
string goingDown = "|LJ";
string goingUp = "|F7";

bool inRange(int i, int j){
	return !(i < 0 || i >= arr.size() || j < 0 || j >= arr[0].size());
}

bool check(int i, int j, string dir){
	if(dir == "up")
		return (
			inRange(i - 1, j) &&
		  	!visited[{i - 1, j}] &&
		   	goingUp.find(arr[i - 1][j]) < goingUp.size()
		);

	if(dir == "down")
		return (
			inRange(i + 1, j) &&
			!visited[{i + 1, j}] &&
			goingDown.find(arr[i + 1][j]) < goingDown.size()
		);

	if(dir == "left")
		return (
			inRange(i, j - 1) &&
			!visited[{i, j - 1}] &&
			goingLeft.find(arr[i][j - 1]) < goingLeft.size()
		);

	if(dir == "right")
		return (
			inRange(i, j + 1) &&
			!visited[{i, j + 1}] &&
			goingRight.find(arr[i][j + 1]) < goingRight.size()
		);

	// To keep the compiler happy
	return false;
}

vector<pii> addTo(vector<pii> v, pii p){
	vector<pii> ans;
	for(pii pp : v)
		ans.push_back(pp);
	
	ans.push_back(p);
	return ans;
}


int main(){
	ifstream file("input.txt");

	string s;
	while(getline(file, s)){
		arr.push_back(s);
	}

	int xStart = 0;
	int yStart = 0;
	for(int i = 0; i < arr.size(); i++){
		for(int j = 0; j < arr[i].size(); j++){
			if(arr[i][j] == 'S'){
				xStart = i;
				yStart = j;
				break;
			}
		}
	}


	
	// Since it's a loop, there'll be 2 different places where we can start the BFS
	// But only choose one, so that the entire loop will be iterated.
	int jumpOffX, jumpOffY;
	while(true){
		if(check(xStart, yStart, "up")){
			jumpOffX = xStart - 1;
			jumpOffY = yStart;
			break;
		}
		if(check(xStart, yStart, "down")){
			jumpOffX = xStart + 1;
			jumpOffY = yStart;
			break;
		}
		if(check(xStart, yStart, "left")){
			jumpOffX = xStart;
			jumpOffY = yStart - 1;
			break;
		}
		if(check(xStart, yStart, "right")){
			jumpOffX = xStart;
			jumpOffY = yStart + 1;
			break;
		}
	}
	
	// BFS init
	queue<Point> q;
	int maxSteps = 0;

	// S = 1st point, (jumpOffX, jumpOffY) = 2nd point
	// When we round back to S at the end, it isn't counted.
	vector<pii> v;
	v.push_back({xStart, yStart});
	v.push_back({jumpOffX, jumpOffY});

	q.push({jumpOffX, jumpOffY, v});
	visited[{xStart, yStart}] = true;

	vector<pii> stepsForLoop;

	while(!q.empty()){
		Point cur = q.front();
		q.pop();

		visited[{cur.x, cur.y}] = true;
		if(cur.steps.size() > maxSteps){
			maxSteps = cur.steps.size();
			stepsForLoop = cur.steps;
		}

		if(check(cur.x, cur.y, "up")){
			vector<pii> v = addTo(cur.steps, {cur.x - 1, cur.y});
			q.push({cur.x - 1, cur.y, v});
		}

		if(check(cur.x, cur.y, "down")){
			vector<pii> v = addTo(cur.steps, {cur.x + 1, cur.y});
			q.push({cur.x + 1, cur.y, v});
		}
		
		if(check(cur.x, cur.y, "left")){
			vector<pii> v = addTo(cur.steps, {cur.x, cur.y - 1});
			q.push({cur.x, cur.y - 1, v});
		}

		if(check(cur.x, cur.y, "right")){
			vector<pii> v = addTo(cur.steps, {cur.x, cur.y + 1});
			q.push({cur.x, cur.y + 1, v});
		}
	}

	// Shoelace formula
	ll area = 0;
	for(int i = 1; i < stepsForLoop.size(); i++){
		area += stepsForLoop[i - 1].f * stepsForLoop[i].s - 
		    	stepsForLoop[i - 1].s * stepsForLoop[i].f;
	}
	area += stepsForLoop[stepsForLoop.size() - 1].f * stepsForLoop[0].s - 
			stepsForLoop[stepsForLoop.size() - 1].s * stepsForLoop[0].f;

	if(area < 0) area *= -1;
	area /= 2;

	// Pick's Theorem
	cout << area - stepsForLoop.size()/2 + 1 << "\n";

	return 0;
}