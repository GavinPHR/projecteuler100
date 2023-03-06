#include <iostream>
#include <vector>
#include "utils.h"

using Num = std::vector<std::uint8_t>;

Num mult_(Num &n, std::uint8_t k) {
	Num ans(n.size() + 1, 0);
	std::uint8_t carry = 0;
	for (int i = 0; i < n.size(); ++i) {
		std::uint8_t tmp = n[i] * k + carry;
		ans[i] = tmp % 10;
		carry = tmp / 10;
	}
	ans[n.size()] = carry;
	return ans;
}


void add(Num &ans, Num &&tmp, int offset) {
	for (int i = 0; i < tmp.size(); ++i) {
		ans[i + offset] += tmp[i];
	}
}


Num mult(Num &n, std::uint8_t k) {
	Num x;
	while (k != 0) {
		x.push_back(k % 10);
		k /= 10;
	}
	Num ans(n.size() + x.size());
	for (int i = 0; i < x.size(); ++i) {
		add(ans, mult_(n, x[i]), i);
	}
	size_t last = ans.size() - 1;
	while (ans[last--] == 0) ans.pop_back();
	return ans;
}


int main() {
	Num n;
	n.push_back(1);
	for (std::uint8_t k = 1; k <= 100; ++k) {
		n = mult(n, k);
		// print_vector(std::vector<int>(n.begin(), n.end()));
	}
	std::uint64_t sum = 0;
	for (auto &d : n) sum += d;
	std::cout << sum << std::endl;
}
