#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.h"

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

constexpr int M_max = 2'000;  // guess max M
constexpr int target = 1'000'000;  // guess max M


void add_possibilities(std::vector<int> &cnt, std::int64_t a, std::int64_t b) {
	if (a > M_max || b > 2 * a) return;
	// std::cout << a << " " << b << std::endl;
	int k = 1;
	std::int64_t D_max, H_min;
	while (k * a <= M_max) {
		D_max = std::min(k * a, k * b - 1);
		H_min = k * b - D_max;
		cnt[k * a] += (D_max - H_min) / 2 + 1;
		// std::cout << k << " -- " << (D_max - H_min) / 2 + 1 << std::endl;
		++k;
	}
}


int main() {
	std::vector<int> cnt(M_max + 1, 0);
	// let a cuboid have dimension WxDxH where W>=D>=H  (M=W)
	// dist=sqrt(W^2+(D+H)^2)
	// generate primitive pythagorean triples a<b<c => W=a, b=D+H
	// multiples are also possibilities
	auto both_odd = [](int m, int n) {return (m % 2) && (n % 2);};
	for (int m = 2; m <= M_max; ++m) {
		for (int n = 1; n < m; ++n) {
			if (!both_odd(m, n) || gcd(m, n) != 1) continue;
			std::int64_t a = m * n;
			std::int64_t b = (m * m - n * n) / 2;
			add_possibilities(cnt, a, b);
			add_possibilities(cnt, b, a);
		}
	}
	for (int i = 1; i <= M_max; ++i) {
		cnt[i] += cnt[i - 1];
		if (cnt[i] > target) {
			std::cout << i << std::endl;
			return 0;
		}
	}
}
