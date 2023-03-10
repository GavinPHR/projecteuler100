#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "prime_factorization.h"

 
bool is_prime(int n) {
	return trial_division(n).size() == 1;
}


void
generate(std::unordered_set<int> available, 
		 std::vector<int> &res,
		 int cur = 0) {
	if (available.empty()) {
		res.push_back(cur);
		return;
	}
	auto tmp = available;
	for (auto &x : available) {
		tmp.erase(x);
		generate(tmp, res, cur * 10 + x);
		tmp.insert(x);
	}
} 


int main() {
	int ans = 0;
	for (int n = 9; n > 1; --n) {
		std::vector<int> res;
		std::unordered_set<int> available;
		for (int i = 1; i <= n; ++i) available.insert(i);
		generate(available, res);
		for (auto &x : res) {
			if (is_prime(x) && x > ans) ans = x;
		}
		if (ans) break;
	}
	std::cout << ans << std::endl;
	return 0;
}
