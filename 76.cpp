#include <iostream>


std::uint64_t recurse(int n, int hi) {
	if (hi == 1) return 1;
	std::uint64_t ans = 0;
	int k = 0;
	while (n - k * hi >= 0) {
		if (n - k * hi == 0) {
			++ans;
			break;
		}
		ans += recurse(n - k * hi, hi - 1);
		++k;
	}
	return ans;
}


int main() {
	constexpr int target = 100;
	std::cout << recurse(target, target - 1) << std::endl; 
}
