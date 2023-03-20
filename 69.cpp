#include <iostream>
#include <vector>
#include <unordered_set>
#include "utils.h"


int phi(int n, std::unordered_set<int> &ps) {
	if (ps.empty()) return n - 1;  // n is prime
	// std::cout << n << ": ";
	std::uint64_t partial = n;
	for (auto &p : ps) {
		partial = (partial * (p - 1)) / p;
		// std::cout << p << ",";
	}
	// std::cout << partial << std::endl;
	return partial;
}

// https://en.wikipedia.org/wiki/Euler%27s_totient_function#Computing_Euler's_totient_function
int main() {
	constexpr int limit = 1'000'000;
	std::vector<std::unordered_set<int>> sieve(limit + 1);
	std::vector<float> ratio(limit + 1);
	for (int n = 2; n <= limit; ++n) {
		ratio[n] = n / (double) phi(n, sieve[n]);
		if (!sieve[n].empty()) continue;
		int k = 2;
		while (k * n <= limit) {
			sieve[k * n].insert(n);
			++k;
		}
	}
	// print_vector(ratio);
	float max_ratio = 0;
	int ans;
	for (int n = 2; n <= limit; ++n) {
		if (ratio[n] > max_ratio) {
			max_ratio = ratio[n];
			ans = n;
		}
	}
	std::cout << ans << std::endl;
}
