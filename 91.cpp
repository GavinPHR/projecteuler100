#include <cstdio>
#include <cstdint>


inline int dot(int x1, int y1, int x2, int y2) {
	return x1 * x2 + y1 * y2;
}

int main() {
	constexpr std::uint64_t n = 50;
	std::uint64_t ans = 0;
	// ans += 2 * n * n;
	// ans += n * n;
	// ans += (n / 2) * 2;
	// every thing with 2 points in the grid
	int k = n + 1;
	for (int a = 1; a < k * k - 1; ++a) {
		for (int b = a + 1; b < k * k; ++b) {
			if (a == b) continue;
			int x1 = a / k, x2 = a % k;
			int y1 = b / k, y2 = b % k;
			int z1 = x1 - y1, z2 = x2 - y2;
			// printf("!%d,%d,%d,%d\n", x1,y1,x2,y2);
			if (dot(x1, x2, z1, z2) == 0 || 
				dot(y1, y2, z1, z2) == 0 ||
				dot(x1, x2, y1, y2) == 0) {
				// printf("%d,%d,%d,%d\n", x1,y1,x2,y2);
				++ans;
			}
		}
	}
	printf("%llu\n", ans);
}
