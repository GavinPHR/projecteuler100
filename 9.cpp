#include <cstdio>


int main() {
	// a < b < c, a + b + c = 1000
	// 335 <= c <= 998
	// a + b = 1000 - c
	// 1 <= a <= (1000 - c - 1) / 2
	for (int c = 335; c <= 998; ++c) {
		for (int a = 1; a <= (1000 - c - 1) / 2; ++a) {
			int b = 1000 - a - c;
			if (a * a + b * b == c * c) {
				printf("%d*%d*%d=%d\n", a, b, c, a * b * c);
				return 0;
			}
		}
	}
	return 0;
}
