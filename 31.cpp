#include <iostream>
#include <vector>
#include <utility>
#include "utils.h"


int main() {
	std::vector<std::uint64_t> denoms = {1, 2, 5, 10, 20, 50, 100, 200};
	std::uint64_t ans = 0;
	std::vector<std::uint64_t> stack1;
	std::vector<std::uint64_t> stack2;
	stack1.push_back(200);
	while (!stack1.empty()) {
		// std::cout << "vec: ";
		// for (auto &x : stack1) std::cout << x << " ";
		// std::cout << std::endl;
		auto d = denoms.back();
		if (d == 1) {
			ans += stack1.size();
			break;
		}
		denoms.pop_back();
		// std::cout << d << std::endl;
		for (auto &remain : stack1) {
			std::uint64_t mult = 0;
			while (mult * d < remain) {
				stack2.push_back(remain - mult * d);
				++mult;
			}
			if (mult * d == remain) ++ans;
		}
		swap(stack1, stack2);
		stack2.clear();
	}
	std::cout << ans << std::endl;
	return 0;
}
