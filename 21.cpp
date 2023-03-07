#include <cstdio>
#include <unordered_set>
#include "prime_factorization.h"

int main() {
	constexpr size_t n = 10000;
	std::uint64_t map[n];
	map[0] = 0;
	map[1] = 1;
	std::uint64_t ans = 0;
	for (std::uint64_t i = 2; i < n; ++i) {
		auto fs = trial_division(i);
		std::unordered_set<std::uint64_t> divisors;
		divisors.insert(1);
		for (auto &f : fs) {
			auto tmp = divisors;
			for (auto &d : tmp) {
				divisors.insert(f * d);
			}
		}
		std::uint64_t sum = 0;
		for (auto &d : divisors) sum += d;
		sum -= i;
		// printf("%llu - ", i);
		// for (auto &d : divisors) printf("%llu ", d);
		// printf("\n");
		map[i] = sum;
		if (sum < i && map[sum] == i) ans += sum + i;
	}
	printf("%llu", ans);
	return 0;
}
