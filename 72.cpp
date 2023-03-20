#include <iostream>
#include <vector>
#include <unordered_set>
#include "utils.h"


int phi(int n, std::unordered_set<int> &ps) {
	if (ps.empty()) return n - 1;  // n is prime
	std::uint64_t partial = n;
	for (auto &p : ps) {
		partial = (partial * (p - 1)) / p;
	}
	return partial;
}

int main() {
	constexpr int limit = 1'000'000;
	std::uint64_t ans = 0;
	std::vector<std::unordered_set<int>> sieve(limit + 1);
	for (int n = 2; n <= limit; ++n) {
		ans += phi(n, sieve[n]);
		if (!sieve[n].empty()) continue;
		int k = 2;
		while (k * n <= limit) {
			sieve[k * n].insert(n);
			++k;
		}
	}
	std::cout << ans << std::endl;
}
