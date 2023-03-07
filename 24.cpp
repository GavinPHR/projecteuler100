#include <cstdio>
#include <string>
#include "utils.h"


inline int factorial(int n) {
	int ans = 1;
	for (int i = 1; i <= n; ++i) ans *= i;
	return ans;
}


int main(int argc, char const *argv[]) {
	std::uint64_t target = std::stoi(argv[1]) - 1;
	std::uint64_t ans = 0;
	std::vector<std::uint8_t> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	while (!v.empty()) {
		std::uint64_t lower = 0;
		const std::uint64_t gap = factorial(v.size() - 1);
		std::uint64_t i = 0;
		while (lower + gap <= target) {
			++i;
			lower += gap;
		}
		ans = ans * 10 + v[i];
		v.erase(v.begin() + i);
		target -= lower;
		// print_vector(std::vector<int>(v.begin(), v.end()));
	}
	// printf("%llu\n", target);
	printf("%llu\n", ans);
	return 0;
}