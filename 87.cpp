#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include "utils.h"
#include "sieve.h"


constexpr int limit = 50'000'000;
int limit_sq = std::sqrt(limit);
const auto s = sieve(limit_sq);


int main() {
	std::vector<int> sq, qu, fo;
	for (int i = 2; i < s.size(); ++i) {
		if (!s[i]) continue;
		sq.push_back(i * i);
	}
	for (int i = 2; i < s.size(); ++i) {
		if (!s[i]) continue;
		auto res = i * i * i;
		if (res >= limit) break;
		qu.push_back(res);
	}
	for (int i = 2; i < s.size(); ++i) {
		if (!s[i]) continue;
		auto res = i * i * i * i;
		if (res >= limit) break;
		fo.push_back(res);
	}
	// std::cout << sq.size() << " " << qu.size() << " " << fo.size() << std::endl;
	// print_vector(fo);
	std::unordered_set<int> set;
	for (auto &x : sq) {
		// std::cout << x << std::endl;
		for (auto &y : qu) {
			const auto xy = x + y;
			if (xy >= limit) break;
			for (auto &z : fo) {
				auto xyz = xy + z;
				if (xyz >= limit) break;
				// std::cout << res << std::endl;
				set.insert(xyz);
			}
		}
	}
	std::cout << set.size() << std::endl;
}
