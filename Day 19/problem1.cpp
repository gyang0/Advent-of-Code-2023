#include <bits/stdc++.h>
using namespace std;


struct Gear {
	int x;
	int m;
	int a;
	int s;
};

map<string, vector<string>> conditions;

bool includes(string s, char c){
	for(char cc : s){
		if(cc == c) return true;
	}
	return false;
}

bool test(string workflow, int x, int m, int a, int s){
	for(string str : conditions[workflow]){
		if(str == "A") return true;
		else if(str == "R") return false;
		else if(!includes(str, ':')) return test(str, x, m, a, s);
		else {
			char c = str[0];
			char ineq = str[1];
			int comp = stoi(str.substr(2, str.find(':')));
			string then = str.substr(str.find(':') + 1);

			if(ineq == '<'){
				if(c == 'x' && x < comp){
					if(then == "A") return true;
					if(then == "R") return false;
					else return test(then, x, m, a, s);

				} else if(c == 'm' && m < comp){
					if(then == "A") return true;
					if(then == "R") return false;
					else return test(then, x, m, a, s);

				} else if(c == 'a' && a < comp){
					if(then == "A") return true;
					if(then == "R") return false;
					else return test(then, x, m, a, s);

				} else if(c == 's' && s < comp){
					if(then == "A") return true;
					if(then == "R") return false;
					else return test(then, x, m, a, s);
				}

			} else {
				if(c == 'x' && x > comp){
					if(then == "A") return true;
					if(then == "R") return false;
					else return test(then, x, m, a, s);

				} else if(c == 'm' && m > comp){
					if(then == "A") return true;
					if(then == "R") return false;
					else return test(then, x, m, a, s);

				} else if(c == 'a' && a > comp){
					if(then == "A") return true;
					if(then == "R") return false;
					else return test(then, x, m, a, s);

				} else if(c == 's' && s > comp){
					if(then == "A") return true;
					if(then == "R") return false;
					else return test(then, x, m, a, s);
				}
			}

		}
	}
}

void workflowInput(string s){
	string name = "";
	while(s[0] != '{'){
		name += s[0];
		s.erase(s.begin());
	}

	// Get rid of curly braces
	s.erase(s.begin());
	s.erase(s.begin() + s.size() - 1);

	string cur = "";
	for(int i = 0; i < s.size(); i++){
		if(s[i] == ','){
			conditions[name].push_back(cur);
			cur = "";
		} else {
			cur += s[i];
		}
	}
	conditions[name].push_back(cur);
}

int ans = 0;

void gearInput(string s){
	// Get rid of curly braces
	s.erase(s.begin());
	s.erase(s.begin() + s.size() - 1);

	int index = 0;
	int xmas[] = {0, 0, 0, 0};

	string cur = "";
	for(int i = 0; i < s.size(); i++){
		if(s[i] == ','){
			// Format: C=12345 where C={x,m,a,s} and any number
			int comp = stoi(cur.substr(2));
			xmas[index] = comp;

			cur = "";
			index++;
		} else {
			cur += s[i];
		}
	}

	int comp = stoi(cur.substr(2));
	xmas[index] = comp;
	
	if(test("in", xmas[0], xmas[1], xmas[2], xmas[3]))
		ans += (xmas[0] + xmas[1] + xmas[2] + xmas[3]);
}

int main(){
	ifstream file("input.txt");
	string s;

	int mode = 0;
	while(getline(file, s)){
		if(s == ""){
			mode++;
			continue;
		}

		if(mode == 0){
			workflowInput(s);
		} else {
			gearInput(s);
		}
	}

	/*for(const auto &[key, val] : conditions){
		cout << key << ":\n";
		for(string s : val)
			cout << "	" << s << "\n";
	}*/

	cout << ans << "\n";

	return 0;
}