#include <iostream>


int main() {
	constexpr std::uint32_t limit = 1000000;
	std::uint32_t cache[limit];
	for (int i = 0; i < limit; ++i) cache[i] = 0;
	std::uint32_t longest = 0;
	std::uint32_t ans = 0;
	for (std::uint32_t i = 1; i < limit; ++i) {
		std::uint32_t n = i;
		std::uint32_t length = 0;
		while (n != 1) {
			if (n < limit && cache[n]) {
				length += cache[n];
				break;
			}
			if (n % 2) {
				n = 3 * n + 1;
			} else {
				n /= 2;
			}
			++length;
		}
		cache[i] = length;
		if (length > longest) {
			longest = length;
			ans = i;
		}
	}
	std::cout << "Number: " << ans << " Length: " << longest << std::endl;
	return 0;
}
