#include <iostream>
#include <unordered_set>
#include <vector>


const int divivsors[7] = {2, 3, 5, 7, 11, 13, 17};


void dfs(std::unordered_set<int> xs, 
	     std::vector<int> &cur, 
	     std::vector<std::uint64_t> &ans) {
	if (xs.empty()) {
		std::uint64_t tmp = 0;
		for (auto &x : cur) tmp = tmp * 10 + x;
		ans.push_back(tmp);
		return;
	}
	int n = cur.size();
	auto d = n < 3 ? 1 : divivsors[n - 3];
	int k = 0;
	if (n > 2) k = cur[n - 2] * 100 + cur[n - 1] * 10;
	auto tmp = xs;
	for (auto &x : xs) {
		if ((k + x) % d != 0) continue;
		cur.push_back(x);
		tmp.erase(x);
		dfs(tmp, cur, ans);
		tmp.insert(x);
		cur.pop_back();
	}
}


int main() {
	std::unordered_set<int> xs;
	for (int i = 0; i < 10; ++i) xs.insert(i);
	std::vector<int> cur;
	std::vector<std::uint64_t> ans;
	for (int i = 1; i < 10; ++i) {
		xs.erase(i);
		cur.push_back(i);
		dfs(xs, cur, ans);
		cur.pop_back();
		xs.insert(i);
	}
	std::uint64_t sum = 0;
	for (auto &x : ans) {
		sum += x;
		std::cout << x << std::endl;
	}
	std::cout << sum << std::endl;
}