#include <cstdio>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include "sieve.h"


constexpr int limit = 10000;
const auto s = sieve(limit);


int smallest(int n) {
	std::vector<int> xs;
	while (n != 0) {
		xs.push_back(n % 10);
		n /= 10;
	}
	std::sort(xs.begin(), xs.end());
	int ans = 0;
	for (auto &x : xs) ans = ans * 10 + x;
	return ans;
}


int main() {
	std::unordered_map<int, std::unordered_set<int>> map;
	for (int i = 1001; i < limit; ++i) {
		if (!s[i]) continue;
		map[smallest(i)].insert(i);
	}
	for (auto it = map.begin(); it != map.end(); ++it) {
		auto &s = it->second;
		if (s.size() < 3) continue;
		for (auto &x : s) {
			for (auto &y : s) {
				if (x <= y) continue;
				if (s.find(x + x - y) != s.end()) {
					printf("%d %d %d\n", y, x, x + x - y);
				}
			}
		}
	}
}
