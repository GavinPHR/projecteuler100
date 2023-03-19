#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>


// not sure why 6549438327211015 is incorrect
// brute force search

std::string concat(std::vector<int> &v) {
	int min = INT_MAX;
	int offset = 0;
	for (int i = 0; i < 5; ++i) {
		if (v[i] < min) {
			min = v[i];
			offset = i;
		}
	}
	std::string ans;
	int sum = 0;
	for (int i = 0; i < 5; ++i) {
		int idx1 = (i + offset) % 5;
		int idx2 = idx1 + 5;
		int idx3 = (idx1 + 6) % 5 + 5;
		int local_sum = v[idx1] + v[idx2] + v[idx3];
		if (sum == 0) sum = local_sum;
		else if (local_sum != sum) return "0";
		ans += std::to_string(v[idx1]);
		ans += std::to_string(v[idx2]);
		ans += std::to_string(v[idx3]);
	}
	return ans;
}


void dfs(std::vector<int> &v, std::unordered_set<int> unused, std::string &best_ans) {
	if (unused.empty()) {
		best_ans = std::max(best_ans, concat(v));
		return;
	}
	if (unused.size() == 5 && (unused.find(10) != unused.end())) {
		return;
	}
	auto copy = unused;
	for (auto &x : copy) {
		v.push_back(x);
		unused.erase(x);
		dfs(v, unused, best_ans);
		unused.insert(x);
		v.pop_back();
	}
}


int main() {
	std::vector<int> v;
	std::unordered_set<int> unused;
	for (int i = 1; i <= 10; ++i) unused.insert(i);
	std::string ans = "0";
	dfs(v, unused, ans);
	std::cout << ans << std::endl;
}
