#include <cstdio>
#include <vector>
#include "utils.h"


using Num = std::vector<std::uint8_t>;

Num add(Num &a, Num &b) {
	Num c;
	std::uint8_t carry = 0;
	for (int i = 0; i < b.size(); ++i) {
		std::uint8_t sum = b[i] + carry;
		if (i < a.size()) sum += a[i];
		c.push_back(sum % 10);
		carry = sum / 10;
	}
	if (carry) c.push_back(carry);
	return c;
}


int main() {
	constexpr int target = 1000;
	Num a(1, 1);
	Num b(1, 1);
	std::uint64_t idx = 2;
	while (b.size() < target) {
		auto c = add(a, b);
		a = b;
		b = c;
		++idx;
	}
	std::cout << idx << std::endl;
	return 0;
}

