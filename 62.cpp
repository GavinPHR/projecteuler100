#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "utils.h"


std::string to_lowest_string(std::uint64_t n) {
	std::vector<int> v;
	while (n != 0) {
		v.push_back(n % 10);
		n /= 10;
	}
	std::sort(v.begin(), v.end());
	std::string s;
	for (auto &x : v) s += (char) (x + '0');
	return s;
}


int main() {
	constexpr int target = 5;
	constexpr int limit = 1'000'000;  //10^6^3 = 10^18 < LLU
	std::unordered_map<std::string, std::vector<int>> cnt;
	for (int i = 100; i < limit; ++i) {
		auto cube = ((std::uint64_t) i) * i * i;
		auto s = to_lowest_string(cube);
		cnt[s].push_back(i);
	}
	int smallest = INT_MAX;
	for (auto &[a, bs] : cnt) {
		if (bs.size() == target) {
			for (auto b : bs) smallest = std::min(smallest, b);
		}
	}
	std::cout << smallest << std::endl;
	auto cube = ((std::uint64_t) smallest) * smallest * smallest;
	std::cout << cube << std::endl;
	print_vector(cnt[to_lowest_string(cube)]);
}
