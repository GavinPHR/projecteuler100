#include <cstdio>
#include <cmath>
#include <algorithm>


inline bool is_integral(double p) {
	return std::abs(p - (std::uint64_t) p) < 0.000001;
}

// i = sqrt(3j^2-j+1/4) - 1/2
// j = (sqrt(24(2k^2 - k)+1)+1)/6
int main() {
	auto ij = [](std::uint64_t j) -> double {
		return std::sqrt(3 * j * j - j + 1.0 / 4) - 1.0 / 2;};
	auto jk = [](std::uint64_t k) -> double {
		return (std::sqrt(24 * (2 * k * k - k) + 1) + 1) / 6;};
	std::uint64_t k = 1;
	int target = 3;
	while (target != 0) {
		auto j = jk(k);
		if (is_integral(j)) {
			auto i = ij(j);
			if (is_integral(i)) {
				printf("%llu %llu %llu\n", (std::uint64_t) i, (std::uint64_t) j, k);
				printf("%llu\n", k * (2 * k - 1));
				--target;
			}
		}
		++k;
	}
	return 0;
}