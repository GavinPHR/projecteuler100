#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "prime_factorization.h"
#include "utils.h"

constexpr int SHIFT = 10;


std::pair<int, int> decompose(int a) {
	auto a_factors_ = trial_division(a);
	std::vector<int> a_base;
	std::vector<int> a_exp;
	int prev = 0;
	for (auto &f : a_factors_) {
		if (f != prev) {
			a_base.push_back(f);
			a_exp.push_back(1);
			prev = f;
		} else {
			++a_exp[a_exp.size() - 1];
		}
	}
	int base = 0;
	int exp = 0;
	for (auto &ab : a_base) {
		base <<= SHIFT;
		base |= ab;
	}
	for (auto &ae : a_exp) {
		exp <<= SHIFT;
		exp |= ae;
	}
	// printf("%d %d\n", base, exp);
	// print_vector(a_base);
	// print_vector(a_exp);
	return {base, exp};
}

int main() {
	// with base a <= 100, a can have at most
	// 3 distinct prime factors since 2*3*5*7 > 100
	// each factor (and exponents) can be represented using 7 bits
	// 32 bit is enough to store 3 numbers
	// uniquely represent each a with [prime_bases] + [exponents]
	// each exponent for a must be <= 6 since 2^7 > 100
	// largest exponent in the representation of a^b is <= 600 (10 bits)
	constexpr int k = 100;
	std::unordered_map<int, std::unordered_set<int>> ans;
	constexpr int mask = 1023;  // 2^SHIFT - 1
	for (int a = 2; a <= k; ++a) {
		auto [base, exp] = decompose(a);
		for (int b = 2; b <= k; ++b) {
			int a_exp = exp;
			int ab_exp = 0;
			for (int i = 0; i < 3; ++i) {
				ab_exp <<= SHIFT;
				ab_exp |= (a_exp & mask) * b;
				// printf("%d ", (a_exp & mask) * b);
				a_exp >>= SHIFT;
			}
			ans[base].insert(ab_exp);
			// printf("\n");
		}
	}
	int sum = 0;
	for (auto it = ans.begin(); it != ans.end(); ++it) {
		sum += (it->second).size();
	}
	std::cout << sum << std::endl;
	return 0;
}
