#include <iostream>
#include <cmath>


inline int gcd(int a, int b) {
	return a ? gcd(b % a, a) : b;
}


int main() {
	constexpr int limit = 12'000;
	int ans = 0;
	for (int b = 2; b <= limit; ++b) {
		for (int a = std::floor(b / 3.0 + 1); a < b / 2.0; ++a) {
			ans += gcd(a, b) == 1;
		}
	}
	std::cout << ans << std::endl;
}
