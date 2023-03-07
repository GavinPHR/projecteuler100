#include <cstdio>
#include <unordered_set>
#include "prime_factorization.h"
#include "utils.h"


int main() {
	constexpr size_t n = 28123 + 1;
	std::vector<std::uint64_t> abundant;
	bool possible[n];
	for (bool &b : possible) b = false;
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
		if (sum > i) {
			abundant.push_back(i);
			for (auto &x : abundant) {
				if (i + x < n) possible[i + x] = true;
				else break;
			}
		}
	}
	// print_vector(abundant);
	std::uint64_t ans = 0;
	for (std::uint64_t i = 1; i < n; ++i) {
		if (!possible[i]) ans += i;
	}
	std::cout << ans << std::endl; 
	return 0;
}
