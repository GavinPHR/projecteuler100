#include <iostream>
#include <cmath>
#include <algorithm>
#include "sieve.h"


inline bool is_integral(double p) {
	return std::abs(p - (std::uint64_t) p) < 0.000001;
}


constexpr int limit = 1000000;
const auto s = sieve(limit);


int main() {
	std::vector<std::uint64_t> primes;
	primes.push_back(2);
	for (std::uint64_t i = 3; i <= limit; i += 2) {
		if (s[i]) primes.push_back(i);
		else {
			bool possible = false;
			for (auto &p : primes) {
				if (is_integral(std::sqrt((i - p) / 2))) {
					possible = true;
					break;
				}
			}
			if (!possible) {
				std::cout << i << std::endl;
				return 0;
			}
		}
	}
	std::cout << "limit too small" << std::endl;
}