#include <iostream>
#include <cstdio>
#include <cmath>


// a^2 + b^2 = c^2
// a + b + c = p
// a <= b < c
// a + b > c
// p <= 1000
int main() {
	constexpr int limit = 1000;
	int ps[limit + 1];
	for (auto &cnt : ps) cnt = 0;
	for (int a = 1; a <= 500; ++a) {
		for (int b = a; b <= 500; ++b) {
			double c_ = std::sqrt(a * a + b * b);
			int c = c_;
			if (std::abs(c - c_) > 0.00001) continue;
			int p = a + b + c;
			if (p <= limit) ++ps[p];
		 	else break;
			// if (p <= limit) {
			// 	printf("%d=%d+%d+%d  ", p, a, b, (int) c);
			// 	printf("%d %d\n", a * a + b * b, c * c);
			// }
		}
	}
	int bestp = 0;
	int best_cnt = 0;
	for (int p = 0; p <= limit; ++p) {
		if (ps[p] > best_cnt) {
			best_cnt = ps[p];
			bestp = p;
		}
	}
	std::cout << bestp << std::endl;
}