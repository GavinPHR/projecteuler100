#include <iostream>
#include <vector>
#include <unordered_map>
#include "utils.h"


int main() {
	constexpr std::uint64_t limit = 1'000'000;
	std::unordered_map<std::uint64_t, std::uint64_t> edges;
	edges.reserve(limit + 1);
	for (std::uint64_t i = 1; i <= limit; ++i) edges[i] = 1;
	for (std::uint64_t i = 2; i <= limit; ++i) {
		for (int k = 2; k <= limit / i; ++k) {
			edges[k * i] += i;
		}
	}
	int longest_size = 0;
	std::uint64_t smallest_num = INT_MAX;
	for (std::uint64_t i = 1; i <= limit; ++i) {
		std::vector<std::uint64_t> seen = {i};
		auto cur = edges[i];
		auto it = std::find(seen.begin(), seen.end(), cur);
		while (cur <= limit && it == seen.end()) {
			seen.push_back(cur);
			cur = edges[cur];
			it = std::find(seen.begin(), seen.end(), cur);
		}
		if (cur > limit) continue;
		int size = seen.end() - it;
		if (size >= longest_size) {
			if (size > longest_size) smallest_num = INT_MAX;
			longest_size = size;
			while (it != seen.end()) {
				smallest_num = std::min(smallest_num, *it);
				++it;
			}
		}
	}
	std::cout << smallest_num << std::endl;
}
