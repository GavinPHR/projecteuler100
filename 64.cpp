#include <iostream>
#include <cmath>


void iter(int &n, int &x, int &y, int &z) {
	int ry = n - z * z;
	if (ry % y == 0) {
		y = ry / y;
	} else {
		std::cout << "!";
	}
	x = (int) ((std::sqrt(n) + z) / y);
	z = std::abs(z - x * y);
}


int main() {
	constexpr int limit = 10'000;
	int next = 2;
	int ans = 0;
	for (int n = 2; n <= limit; ++n) {
		if (n == next * next) {
			++next;
			continue;
		}
		// a_i = x, y / (sqrt(n) - z)
		int x1 = next - 1;
		int y1 = 1;
		int z1 = x1;
		iter(n, x1, y1, z1);
		int x = x1, y = y1, z = z1;
		int i = 0;
		while (true) {
			iter(n, x, y, z);
			++i;
			if (x == x1 && y == y1 && z == z1) {
				break;
			}
		}
		if (i % 2) ++ans;
	}
	std::cout << ans << std::endl;
}