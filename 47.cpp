#include <iostream>
#include <cstdio>
#include "prime_factorization.h"


int unique_cnt(std::uint64_t n) {
	auto factors = trial_division(n);
	int ans = 0;
	int prev = 0;
	for (auto &f : factors) {
		if (f != prev) {
			++ans;
			prev = f;
		}
	}
	return ans;
}


int main(int argc, char const *argv[]) {
	constexpr int limit = 1000000;
	int n = std::stoi(argv[1]);
	int k = 0;
	for (int i = 1; i < limit; ++i) {
		auto cnt = unique_cnt(i);
		if (cnt != n) {
			k = 0;
			continue;
		}
		++k;
		if (k == n) {
			for (int j = i - n + 1; j <= i; ++j) std::cout << j << " ";
			std::cout << std::endl;
			break;
		}
	}
}




