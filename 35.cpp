#include <iostream>
#include <unordered_set>
#include <vector>
#include "sieve.h"


int main(int argc, char const *argv[]) {
	size_t max = std::stoi(argv[1]);
	auto s = sieve(max);
	std::unordered_set<std::uint64_t> ans;
	auto mod = [](int a, int b) {return (b + (a % b)) % b;};
	for (size_t i = 0; i < s.size(); ++i) {
		if (!s[i]) continue;
		if (ans.find(i) != ans.end()) continue;
		std::vector<std::uint64_t> buffer;
		auto n = i;
		bool all_prime = true;
		while (n != 0) {
			int tmp = n % 10;
			if (tmp == 0) {
				all_prime = false;
				break;
			}
			buffer.push_back(tmp);
			n /= 10;
		}
		if (!all_prime) continue;
		int len = buffer.size();
		std::vector<std::uint64_t> history;
		for (int start = 0; start < len; ++start) {
			std::uint64_t val = buffer[start];
			int next = mod(start - 1, len);
			while (next != start) {
				val = val * 10 + buffer[next];
				next = mod(next - 1, len);
			}
			if (!s[val]) {
				all_prime = false;
				break;
			}
			history.push_back(val);
		}
		if (!all_prime) continue;
		for (auto &val : history) {
			ans.insert(val);
			// std::cout << val << " ";
		}
		// std::cout << std::endl;
	}
	std::cout << ans.size() << std::endl;
	return 0;
}