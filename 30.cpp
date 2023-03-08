#include <iostream>
#include <cmath>
#include <vector>
#include "exponentiation.h"


int main(int argc, char const *argv[]){
	std::uint32_t p = std::stoi(argv[1]);
	std::uint32_t n = 10;
	auto max_rhs = [&]() {return exp(9, p) * (int)(1 + log10(n));};
	std::vector<std::uint32_t> ans;
	while (max_rhs() >= n) {
		auto cur = n;
		std::uint32_t sum = 0;
		while (cur != 0) {
			sum += exp((cur % 10), p);
			cur /= 10;
		}
		if (sum == n) ans.push_back(n);
		++n;
	}
	std::uint64_t sum = 0;
	for (auto &x : ans) {
		std::cout << x << " ";
		sum += x;
	}
	std::cout << sum << std::endl;
	return 0;
}