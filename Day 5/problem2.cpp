#include <bits/stdc++.h>
using namespace std;

#define ll long long int

struct Range {
	ll start;
	ll end;
	bool done;
};

vector<ll> splitInput(string s){
	string cur = "";
	vector<ll> res;

	for(char c : s){
		if(isdigit(c)){
			cur += c;
		} else {
			if(cur != "")
				res.push_back(stoll(cur));
			
			cur = "";
		}
	}
	if(cur != "")
		res.push_back(stoll(cur));

	return res;
}

vector<Range> testRanges(ll mapTo, ll mapFrom, ll len, vector<Range> ranges){
	vector<Range> ans;
	
	for(Range r : ranges){
		if(r.done){
			ans.push_back({ r.start, r.end, true });
			continue;
		}
		
		// Casework time
		if(r.end < mapFrom || r.start > mapFrom + len - 1){
			ans.push_back({r.start, r.end, false });

		} else if(r.start < mapFrom && r.end > mapFrom + len - 1){
			ans.push_back({ r.start, mapFrom - 1, false });
			ans.push_back({ mapTo, mapTo + len - 1, true });
			ans.push_back({ mapFrom + len, r.end, false });

		} else if(r.start < mapFrom && r.end <= mapFrom + len - 1){
			ans.push_back({ r.start, mapFrom - 1, false });
			ans.push_back({ mapTo, mapTo + (r.end - mapFrom), true });

		} else if(r.start >= mapFrom && r.end > mapFrom + len - 1){
			ans.push_back({ mapTo + (r.start - mapFrom), mapTo + len - 1, true });
			ans.push_back({ mapFrom + len, r.end, false });

		} else if(r.start >= mapFrom && r.end <= mapFrom + len - 1){
			ans.push_back({ mapTo + (r.start - mapFrom), mapTo + (r.end - mapFrom), true });
		}
	}

	return ans;
}

int main(){
	ifstream file("input.txt");
	
	bool getSeeds = false;
	string s;
	
	// Ranges to consider (all ranges are inclusive at both ends)
	vector<Range> ranges;

	while(getline(file, s)){
		// Input
		vector<ll> input = splitInput(s);

		// Initial input
		if(!getSeeds){
			for(int i = 0; i < input.size(); i += 2)
				ranges.push_back({input[i], input[i] + input[i + 1] - 1, false});

			getSeeds = true;

		} else if(s != "" && isdigit(s[0])){
			// Calculate
			ranges = testRanges(input[0], input[1], input[2], ranges);

		} else {
			// Reset for another run
			for(int i = 0; i < ranges.size(); i++)
				ranges[i].done = false;
		}
	}

	ll ans = ranges[0].start;
	for(Range r : ranges){
		ans = min(ans, r.start);
	}
	cout << ans << "\n";
	
	return 0;
}