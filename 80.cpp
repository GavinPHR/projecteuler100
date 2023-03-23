#include <iostream>
#include <cmath>
#include "big_int.h"


BigUInt init_guess(int i) {
	// i < 100
	long double sqrt = std::sqrtl(i);
	std::string s;
	int n = 0;
	while (n != 15) {
		s += std::to_string((int) sqrt);
		sqrt = std::fmod(sqrt, 1) * 10;
		++n;
	}
	while (n != 101) {
		s += '0';
		++n;
	}
	return {s};
}


BigUInt complete(BigUInt &g, int n) {
	auto below_n = [&]() {
		auto prod = g * g;
		int j = prod.xs.back();
		if (prod.xs.size() == 202) j = j * 10 + prod.xs[200];
		// std::cout << prod << "  " << n << std::endl;
		return j < n;
	};
	int i = 0;
	while (g.xs[i] == 0) ++i;
	while (!below_n()) {
		while (g.xs[i] == 0) ++i;
		--g.xs[i];
	}
	while (i >= 0) {
		while (g.xs[i] < 9) {
			++g.xs[i];
			if (!below_n()) {
				--g.xs[i];
				break;
			}
		}
		--i;
	}
	return g;
}


int main() {
	int ans = 0;
	int next = 2;
	for (int i = 2; i <= 100; ++i) {
		if (i == next * next) {
			++next;
			continue;
		}
		auto g = init_guess(i);
		complete(g, i);
		// std::cout << g << std::endl;
		// std::cout << g.xs.size() << std::endl;
		int sum = 0;
		for (int k = 1; k < 101; ++k) {
			sum += g.xs[g.xs.size() - k];
		}
		// std::cout << i << ": " << sum << std::endl;
		ans += sum;
	}
	std::cout << ans << std::endl;
}
