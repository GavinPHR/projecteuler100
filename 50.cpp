#include <iostream>
#include "sieve.h"


int main(int argc, char const *argv[]) {
	const int limit = std::stoi(argv[1]);
	const auto s = sieve(limit);
	int longest = 0;
	int ans = 0;
	std::vector<std::uint64_t> prefix;
	prefix.push_back(0);
	for (int i = 2; i < limit; ++i) {
		if (!s[i]) continue;
		prefix.push_back(i + prefix.back());
		int r = prefix.size() - 1;
		int l = r - longest - 1;
		int cand = 0;
		for (; l >= 0; --l) {
			cand = prefix[r] - prefix[l];
			if (cand >= limit) break;
			if (s[cand] && (r - l) > longest) {
				longest = r - l;
				ans = cand;
			}
		}
	}
	std::cout << ans << std::endl;
	std::cout << longest << std::endl;
}