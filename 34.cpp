#include <iostream>
#include <cmath>
#include <vector>

int factorial[10];

int main(int argc, char const *argv[]){
	factorial[0] = 1;
	for (int i = 1; i < 10; ++i) factorial[i] = i * factorial[i - 1];
	std::uint32_t n = 10;
	auto max_rhs = [&]() {return factorial[9] * (int)(1 + log10(n));};
	std::vector<std::uint32_t> ans;
	while (max_rhs() >= n) {
		auto cur = n;
		std::uint32_t sum = 0;
		while (cur != 0) {
			sum += factorial[cur % 10];
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