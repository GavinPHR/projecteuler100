#include <iostream>
#include <vector>
#include <algorithm>


std::uint64_t smallest(std::uint64_t n) {
	std::vector<std::uint64_t> v;
	while (n != 0) {
		v.push_back(n % 10);
		n /= 10;
	}
	std::sort(v.begin(), v.end());
	std::uint64_t ans = 0;
	for (auto &x : v) ans = ans * 10 + x;
	return ans;
}


int main() {
	std::uint64_t base = 1;
	std::uint64_t i = base;
	while (true) {
		base *= 10;
		for (; 6 * i < base; ++i) {
			std::uint64_t k = smallest(i);
			bool found = true;
			for (int mult = 2; mult <= 6; ++mult) {
				if (smallest(mult * i) != k) {
					found = false;
					break;
				}
			}
			if (found) {
				std::cout << i << std::endl;
				return 0;
			}
		}
		i = base;
	}

}
