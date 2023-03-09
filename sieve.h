#include <vector>


inline std::vector<bool> sieve(size_t max) {
	std::vector<bool> s(max + 1, true);
	s[0] = false;
	s[1] = false;
	for (size_t i = 2; i <= max; ++i) {
		if (!s[i]) continue;
		size_t k = 2;
		while (k * i <= max) s[k++ * i] = false;
	}
	return s;
}
