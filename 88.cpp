#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>
#include <unordered_set>
#include <numeric>
#include "utils.h"

using F = std::vector<int>;
using Fs = std::vector<F>;
using Fss = std::vector<Fs>;


Fss compute_factorizations(int n) {
	Fss fss(n + 1);
	for (int i = 2; i <= n; ++i) {
		int ceil = std::sqrt(i);
		Fs fs;
		fs.push_back({i});
		for (int j = 2; j <= ceil; ++j) {
			if (i % j != 0) continue;
			int k = i / j;  // i = j * k, j <= k
			for (auto f : fss[k]) {
				f.push_back(j);
				std::sort(f.begin(), f.end());
				if (std::find(fs.begin(), fs.end(), f) != fs.end()) continue;
				fs.push_back(std::move(f));
			}
		}
		fss[i] = std::move(fs);
	}
	return fss;
}



// for a number n, let one of its factorization be f1*f2*...
// if f1*f2*... > f1+f2+..., we can add 1s to both sides to make them equal
// for a set with size k, the a trivial solution is 1^(k-2)*2*k = (k-2)*1+2+k = 2k
int main() {
	constexpr int limit = 12'000;
	auto fss = compute_factorizations(2 * limit);
	// for (int i = 0; i <= limit; ++i) {
	// 	auto &fs = fss[i];
	// 	std::cout << i << std::endl;
	// 	for (auto &f : fs) print_vector(f);
	// }
	std::vector<int> res(limit + 1, 0);
	for (int i = 2; i <= 2 * limit; ++i) {
		for (auto &f : fss[i]) {
			if (f.size() == 1) continue;
			auto sum = std::accumulate(f.begin(), f.end(), 0);
			auto prod = std::accumulate(f.begin(), f.end(), 1, std::multiplies());
			if (prod < sum) continue;
			int k = prod - sum + f.size();
			if (k > limit) continue;
			if (res[k] == 0) res[k] = i;
		}
	}
	std::unordered_set<int> set(res.begin(), res.end());
	std::cout << std::accumulate(set.begin(), set.end(), 0) << std::endl;
}
