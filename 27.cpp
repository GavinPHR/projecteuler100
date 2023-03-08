#include <iostream>
#include <unordered_set>



int main() {
	// f = n * n + a * n + b, abs(a) < 1000, abs(b) <= 1000
	// assume n is at most 200
	// max f = 200 * 200 + 999 * 200 + 1000
	//       = 40000 + 199800 + 1000 = 240800
	constexpr int maxn = 200;
	int a = 999;
	int b = 1000;
	auto f = [&](int n) {return n * n + a * n + b;};
	int maxf = f(maxn);
	int sieve[maxf + 1];
	for (auto &x : sieve) x = true;
	sieve[0] = false;
	sieve[1] = false;
	for (int i = 2; i * i <= maxf; ++i) {
		if (!sieve[i]) continue;
		int mult = 2;
		while (mult * i <= maxf) sieve[i * mult++] = false;
	}
	int besta = 0;
	int bestb = 0;
	int bestn = 0;
	for (b = 2; b <= 1000; ++b) {  // b must be prime when n = 0
		if (!sieve[b]) continue;
		for (a = -999; a <= 999; ++a) {
			int n = 0;
			int fn = f(n);
			while (fn >= 2 && sieve[fn]) {
				fn = f(++n);
				if (n > maxn) {
					std::cout << "maxn is too small" << std::endl;
					return 0;
				}
			}
			if (n > bestn) {
				bestn = n;
				besta = a;
				bestb = b;
			}
		}
	}
	std::cout << besta * bestb << " " << bestn << std::endl;
	return 0;
}
