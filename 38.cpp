#include <iostream>
#include <algorithm>


constexpr std::uint64_t max = 987654321;


bool is_pandigital(std::uint64_t n) {
	bool taken[10];
	taken[0] = true;
	for (int i = 1; i < 10; ++i) taken[i] = false;
	while (n != 0) {
		if (taken[n % 10]) return false;
		taken[n % 10] = true;
		n /= 10;
	}
	for (int i = 1; i < 10; ++i) {
		if (!taken[i]) return false;
	}
	return true;
}


std::uint64_t get_num(int i, int n) {
	std::string s;
	for (int j = 1; j <= n; ++j) {
		s += std::to_string(i * j);
	}
	return std::stoull(s);
}


int main() {
	std::uint64_t best = 0;
	for (int n = 2; n < 10; ++n) {
		int i = 1;
		auto res = get_num(i, n);
		while (res <= max) {
			if (is_pandigital(res)) {
				best = std::max(best, res);
				// std::cout << best << std::endl;
			}
			++i;
			res = get_num(i, n);
		}
	}
	std::cout << best << std::endl;
	return 0;
}
