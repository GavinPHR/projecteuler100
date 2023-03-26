#include <iostream>
#include <cmath>
#include <algorithm>


std::uint64_t gcd(std::uint64_t a, std::uint64_t b) {
	return b ? gcd(b, a % b) : a;
}


// two things that are confusing are
// 1. can base be odd and base/2 = integer + 1/2
//    => height = sqrt(int^2-(int+1/2)^2) = sqrt(int+0.75) = irrational
//    => NO
// 2. can height be fractionnal i.e. 2 (base) * 3.5 (height) = 7
//    => NO because if base it integer, height = sqrt(int)
//    => sqrt(int) is either an integer or is irrational 
// Conclusion: base must be even and height must be integral
// base/2, height, side must form a primitive triple, with multiplier k=1
// Can also brute-force, similar complexity
int main() {
	constexpr std::uint64_t limit = 1'000'000'000;
	// sides be c, c, c+-1
	// 3c - 1 <= limit
	constexpr std::uint64_t max_c = (limit + 1) / 3; 
	// c = m^2+n^2, m > n > 0
	std::uint64_t max_m = std::sqrt(max_c - 1);  // 18257
	// c+-1 = 2*min((m^2-n^2), 2mn) ==> condition holds
	std::uint64_t sum = 0;
	for (std::uint64_t m = 2; m <= max_m; ++m) {
		for (std::uint64_t n = 1; n < m; ++n) {
			if ((m + n) % 2 == 0) continue;  // must have one odd, one even
			if (gcd(m, n) != 1) continue;  // must be co prime
			const auto m2 = m * m;
			const auto n2 = n * n;
			const auto c = m2 + n2;
			const auto base = 2 * std::min(m2 - n2, 2 * m * n);
			if ((c > base && (c - base) == 1) || (c < base && (base - c) == 1)) {
				const auto perimeter = 2 * c + base;
				if (perimeter > limit) continue;
				sum += perimeter;
				// std::cout << c << " " << base << std::endl;
			}
		}
	}
	std::cout << sum << std::endl;
}
