#include <iostream>
#include <vector>
#include <unordered_map>
#include "combinatorics.h"


int next(int i, std::vector<int> &f) {
	int ans = 0;
	while (i != 0) {
		ans += f[i % 10];
		i /= 10;
	}
	return ans;
}

int main() {
	constexpr int limit = 1'000'000;
	std::vector<int> f(10);
	for (int i = 0; i < 10; ++i) f[i] = factorial(i);
	std::unordered_map<int, int> cache;
	//169 → 363601 → 1454 → 169
	//871 → 45361 → 871
	//872 → 45362 → 872
	cache[169] = 3;
	cache[363601] = 3;
	cache[1454] = 3;
	cache[871] = 2;
	cache[45361] = 2;
	cache[872] = 2;
	cache[45362] = 2;
	for (int start = 1; start < limit; ++start) {
		if (cache.find(start) != cache.end()) continue;
		int len = 1;
		int cur = start;
		while (true) {
			auto tmp = next(cur, f);
			if (tmp == cur) {
				cache[start] = len;
				break;
			} else if (cache.find(tmp) != cache.end()) {
				len += cache[tmp];
				cache[start] = len;
				break;
			}
			cur = tmp;
			++len;
		}
	}
	int ans = 0;
	for (auto &[a, b] : cache) {
		if (b == 60) ++ans;
	}
	std::cout << ans << std::endl;
}
