#include <iostream>
#include <vector>
#include "utils.h"
#include "big_int.h"

// a + b / c
void iterate(BigUInt &a, BigUInt &b, BigUInt &c) {
	b = std::move(a * c + b);
	std::swap(b, c);
}


// e's continued fraction is
// 2; 1,2,1,1,4,1,1,6,1,1,8,...,1,1,2k,...
int main() {
	constexpr int target = 100;
	std::vector<int> cf;
	cf.push_back(2);
	while (true) {
		int s = cf.size();
		if (s == target) break;
		if (s % 3 == 2) cf.push_back(2 * (s + 1) / 3);
		else cf.push_back(1);
	}
	BigUInt b(1);
	BigUInt c(cf.back());
	cf.pop_back();
	while (!cf.empty()) {
		auto a = BigUInt(cf.back());
		iterate(a, b, c);
		cf.pop_back();
	}
	std::cout << b << " " << c << std::endl;
	int ans = 0;
	for (auto &x : c.xs) ans += x;
	std::cout << ans << std::endl;
}
