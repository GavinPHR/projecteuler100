#include <iostream>



int main() {
	constexpr int n = 21;
	auto index = [] (int i, int j) {return n * i + j;};
	std::uint64_t grid[n * n];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == 0 || j == 0) {
				grid[index(i, j)] = 1;
			} else {
				grid[index(i, j)] = grid[index(i - 1, j)] + grid[index(i, j - 1)];
			}
		}
	}
	std::cout << grid[index(n - 1, n - 1)];
	return 0;
}