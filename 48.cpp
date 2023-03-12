#include <iostream>


int main(int argc, char const *argv[]) {
	constexpr std::uint64_t mod = 10000000000;
	std::uint64_t ans = 0;
	int n = std::stoi(argv[1]);
	for (int i = 1; i <= n; ++i) {
		std::uint64_t tmp = 1;
		for (int j = 1; j <= i; ++j) {
			tmp = (tmp * i) % mod;
		}
		ans = (ans + tmp) % mod;
	}
	std::cout << ans << std::endl;
}
