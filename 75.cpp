#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>


int gcd(int a, int b) {
	return a ? gcd(b % a, a) : b;
}

//https://en.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple
// m > n > 0
//a=m^2-n^2, b=2mn, c=m^2+n^2
//a+b+c=2m^2+2mn
//2m^2+2m<=limit (n=1)
//m(m+1)<=limit/2
//m<sqrt(limit)/2
int main() {
	constexpr std::uint64_t limit = 1'500'000;
	std::uint8_t cnt[limit + 1];
	for (int i = 0; i <= limit; ++i) cnt[i] = 0;
	int m = 2;
	while (m * (m + 1) <= limit / 2) {
		int start = 1 + m % 2;  //m is odd, n must be even, and vice versa
		for (int n = start; n < m; n += 2) {
			if (gcd(m, n) != 1) continue; //not coprime
			int len = 2 * m * m + 2 * m * n;
			int k = 1;
			while (k * len <= limit) {
				++cnt[k * len];
				++k;
			}
		}
		++m;
	}
	int ans = 0;
	for (int i = 0; i <= limit; ++i) {
		if (cnt[i] == 1) ++ans;
	}
	std::cout << ans << std::endl;
}
