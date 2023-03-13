#include <iostream>
#include "combinatorics.h"


int main() {
	constexpr int limit = 1000000;
	int ans = 0;
	for (int n = 1; n <= 100; ++n) {
		for (int r = 1; r <= n / 2; ++r) {
			if (nCr(n, r) > limit) {
				ans += n - r - r + 1;
				break;
			}
		}
	}
	std::cout << ans << std::endl;
}
