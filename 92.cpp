#include <iostream>
#include <vector>


inline int next(int i) {
	int j = 0;
	while (i != 0) {
		j += (i % 10) * (i % 10);
		i /= 10;
	}
	return j;
}


int main() {
	constexpr int limit = 10'000'000;
	std::uint8_t *flags = new std::uint8_t[limit];
	for (int i = 0; i < limit; ++i) flags[i] = 0;
	flags[1] = 1; flags[89] = 2;
	for (int i = 1; i < limit; ++i) {
		std::vector<int> chain;
		int cur = i;
		while (flags[cur] == 0) {
			chain.push_back(cur);
			cur = next(cur);
		}
		for (auto &v : chain) flags[v] = flags[cur];
	}
	int ans = 0;
	for (int i = 1; i < limit; ++i) ans += flags[i] == 2 ? 1 : 0;
	std::cout << ans << std::endl;
	delete[] flags;
}

