#include <cstdint>
#include <iostream>

inline std::uint64_t factorial(int n, int r = 0) {
	std::uint64_t ans = 1;
	while (n != r) ans *= n--;
	return ans;
}


inline std::uint64_t nCr(int n, int r) {
	return factorial(n, n - r) / factorial(r);
}


inline std::uint64_t nPr(int n, int r) {
	return factorial(n, n - r);
}
