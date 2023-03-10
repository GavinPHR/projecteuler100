#include <iostream>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "prime_factorization.h"
#include "exponentiation.h"
#include "utils.h"


constexpr std::uint64_t limit = 1000000;


std::unordered_set<std::uint64_t> left() {
	// last digit must be prime
	std::unordered_set<std::uint64_t> ans;
	std::vector<std::uint64_t> stack =  {2, 3, 5, 7};
	while (!stack.empty()) {
		auto n = stack.back();
		stack.pop_back();
		ans.insert(n);
		for (int i = 1; i < 10; ++i) {
			int cand = i * exp(10, 1 + (int) log10(n)) + n;
			if (cand > limit) continue;
			if (trial_division(cand).size() == 1) stack.push_back(cand);
		}
	}
	return ans;
}


std::unordered_set<std::uint64_t> right() {
	// first digit must be prime
	std::unordered_set<std::uint64_t> ans;
	std::vector<std::uint64_t> stack =  {2, 3, 5, 7};
	while (!stack.empty()) {
		auto n = stack.back();
		stack.pop_back();
		ans.insert(n);
		for (int i = 1; i < 10; ++i) {
			int cand = n * 10 + i;
			if (cand > limit) continue;
			if (trial_division(cand).size() == 1) stack.push_back(cand);
		}
	}
	return ans;
}


int main(int argc, char const *argv[]) {
	auto l = left();
	auto r = right();
	auto intersect_sum = [&]() {
		std::vector<std::uint64_t> ans;
		for (auto &x : l) {
			if (r.find(x) != r.end()) ans.push_back(x);
		}
		if (ans.size() != 15) return (std::uint64_t) 0;
		std::uint64_t sum = 0;
		for (auto &x : ans) sum += x;
		sum -= 2 + 3 + 5 + 7;
		return sum;
	};
	std::cout << l.size() << std::endl;
	std::cout << r.size() << std::endl;
	std::cout << intersect_sum() << std::endl;
	return 0;
}
