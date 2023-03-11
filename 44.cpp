#include <iostream>
#include <cmath>
#include <algorithm>


inline bool is_integral(double p) {
	return std::abs(p - (std::uint64_t) p) < 0.000001;
}

// P(n) = n(3n-1)/2
// P(n) - P(n - 1) = n(3n-1)/2 - (n-1)(3(n-1)-1)/2
//                 = (3n^2-n-(3n^2-6n+3-n+1))/2
//                 = (6n-4) / 2
//                 = 3n-2
// 2P(n) = 3n^2-n
// 2P(n)/3 = n^2-n/3 = (n-1/6)^2-1/36
// 2P(n)/3+1/36 = (n-1/6)^2
// n(P) = sqrt(2P/3+1/36) + 1/6
// n(P) = (sqrt(24P+1) + 1)/6
int main() {
	auto D = UINT64_MAX;
	int k = 2;
	auto P = [](std::uint64_t n) -> std::uint64_t {return n * (3 * n - 1) / 2;};
	auto N = [](std::uint64_t p) -> double {return (std::sqrt(24 * p + 1) + 1) / 6;};
	while (3 * k - 2 < D) {
		auto pk = P(k);
		// binary search starting point
		int j = 1;
		int i = k;
		while (j < i) {
			auto mid = j + (i - j + 1) / 2;
			auto d = pk - P(mid);
			if (d < D) i = mid - 1;
			else j = mid;
		}
		for (; j < k; ++j) {
			auto pj = P(j);
			auto n_pplusj = N(pk + pj);
			if (!is_integral(n_pplusj)) continue;
			auto n_pminusj = N(pk - pj);
			if (!is_integral(n_pminusj)) continue;
			D = std::min(D, pk - pj);
		}
		++k;
	}
	std::cout << "D=" << D << std::endl;
	std::cout << "k=" << k << std::endl;
	std::cout << "P(k)=" << P(k) << std::endl;
	return 0;
}