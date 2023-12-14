#include <bits/stdc++.h>

using namespace std;

#define ll long long int
#define f first
#define s second

pair<string, vector<int>> splitInput(string str){
	string s1 = "";
	string s2 = "";
	vector<int> v;

	int mode = 0;
	for(char c : str){
		if(c == ' '){
			mode++;
			continue;
		}

		if(mode == 0) s1 += c;
		else {
			if(isdigit(c)) s2 += c;
			else {
				v.push_back(stoi(s2));
				s2 = "";
			}
		}
	}
	v.push_back(stoi(s2));

	return {s1, v};
}

string customTrim(string s){
	string ans = s;

	// Condense all multiple occurrences of '.' into one '.'
	for(int i = 1; i < ans.size(); i++){
		if(ans[i - 1] == ans[i] && ans[i] == '.'){
			ans.erase(ans.begin() + i);
			i--;
		}
	}

	// Now remove the '.' before any occurrences of '?' or '#'
	// and after the last occurrences of '?' or '#'
	// basically trimming from the beginning and end of the string
	while(ans[0] == '.'){
		ans.erase(ans.begin());
	}
	while(ans[ans.size() - 1] == '.'){
		ans.erase(ans.begin() + ans.size() - 1);
	}

	// One final '.' at the end, to serve as a delimiter/sentinel
	ans += '.';
	return ans;
}


// To store data for DP
// Is it DP or just brute force + memoization?
struct Helper {
	string s;
	vector<int> pattern;
	char lastElement;

	// Required for map sorting
	bool operator<(const Helper &other) const {
		if(s != other.s) return s < other.s;
		else if(pattern != other.pattern) return pattern < other.pattern;
		else return lastElement < other.lastElement;
	}
};

map<Helper, bool> exists;
map<Helper, ll> memo;

/**
 * Note on what the absolute heck is going on here.
 * Basically a faster, more efficient, and more complex version of "calc" in my code for part 1.
 * 
 * I used customTrim() on the string before starting this recursion, so:
 * 		1. No appearances of '.' before a '#' or '?'
 * 		2. No repeat occurrences of '.'
 * 		3. Only one final '.' at the end of the string
 * 
 * These conditions are necessary for what follows.
 * 
 * "pattern" stores the current pattern to fulfill.
 * We decrease pattern[0] by 1 if current char is '#' - simulates continuing the pattern.
 * 		If pattern[0] becomes less than 0 after this decrease, pattern is not fulfilled. Return 0.
 * 
 * Delete pattern[0] if current char is '.' - simulates starting over for a new pattern.
 * 		If pattern[0] is not 0, then pattern wasn't fulfilled. Return 0.
 * 		Because of the '.' at the end, if we reach curStr == "", we know that the configuration successfully passed.
 * 
 * For a '?' - combine both cases. (ans for '?') = (ans for '.') + (ans for '#')
 * 		Special condition: if we assume '?' to be a '.' - problem occurs if next element is a '.'
 * 		Because then we delete extra stuff.
 * 		To avoid that, the extra "lastElement" contains the last character encountered, to be used to check these things.
 * 
 * 		Yet another special case: if a string begins with a '?' - then problem occurs if we assume that to be a '.'
 * 		So we use the initial value '.' to get around that.
 * 
 * That probably doesn't make sense. But why are you even looking at this monstrosity? These are just notes for future me.
 * Go look at better solutions by other people.
 */
ll calc(string curStr, vector<int> pattern, char lastElement){
	//cout << curStr << "  | ";
	//for(int a : pattern) cout << " " << a;
	//cout << "  |  " << lastElement << "\n";

	if(exists[{curStr, pattern, lastElement}])
		return memo[{curStr, pattern, lastElement}];

	
	// Special case for when we accidentally make a repeating '.' sequence
	if(curStr[0] == '.' && lastElement == '.'){
		return calc(curStr.substr(1, curStr.size()), pattern, '.');
	}

	// Passed all tests, valid configuration found
	if(curStr.size() == 0 && pattern.size() == 0) return 1;

	// Invalid configuration (premature stop)
	if(curStr.size() == 0 && pattern.size() != 0) return 0;
	

	ll ans = -1;
	if(curStr[0] == '#'){
		if(pattern.size() == 0)
			ans = 0;
		else {
			pattern[0]--;

			if(pattern[0] < 0) ans = 0;
			else ans = calc(curStr.substr(1, curStr.size()), pattern, '#');

			pattern[0]++;
		}

	} else if(curStr[0] == '.'){
		if(pattern[0] != 0) ans = 0;
		else {
			int deleted = pattern[0];
			pattern.erase(pattern.begin());
			ans = calc(curStr.substr(1, curStr.size()), pattern, '.');
			pattern.insert(pattern.begin(), deleted);
		}

	} else if(curStr[0] == '?'){
		if(pattern.size() == 0)
			ans = calc("." + curStr.substr(1, curStr.size()), pattern, lastElement);
		else
			ans = calc("#" + curStr.substr(1, curStr.size()), pattern, lastElement) +
				  calc("." + curStr.substr(1, curStr.size()), pattern, lastElement);
	}

	exists[{curStr, pattern, lastElement}] = true;
	memo[{curStr, pattern, lastElement}] = ans;
	return ans;
}


int main(){
	ifstream file("input.txt");
	string s;

	ll ans = 0;
	int ind = 0;
	while(getline(file, s)){
		pair<string, vector<int>> p = splitInput(s);

		//cout << "------------  " << customTrim(p.f) << "\n";

		string s = "";
		vector<int> v;
		for(int i = 0; i < 5; i++){
			s += (p.f + "?");
			for(int a : p.s)
				v.push_back(a);
		}
		s.pop_back();

		ans += calc(customTrim(s), v, '.');
		
		ind++;
		if(ind % 10 == 0) cout << ind/10 << "%" << " done\n";
	}
	cout << ans << "\n";
	
	return 0;
}