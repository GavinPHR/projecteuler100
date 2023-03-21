#include <iostream>
#include <vector>
#include "utils.h"
// #include <algorithm>


//dp is too slow
// int dp() {
// 	constexpr int size = 50'000;
// 	constexpr int target = 1'000'000;
// 	std::vector<std::vector<int>> p(size, std::vector<int>(size, 0));
// 	p[0][0] = 1;
// 	for (int n = 1; n < size; ++n) {
// 		for (int max_chunk = 1; max_chunk <= n; ++max_chunk) {
// 			p[n][max_chunk] += p[n][max_chunk - 1];
// 			int remainder = n - max_chunk;
// 			p[n][max_chunk] += p[remainder][std::min(remainder, max_chunk)];
// 			p[n][max_chunk] %= target;
// 		}
// 		if (p[n][n] == 0) {
// 			std::cout << n << std::endl;
// 			break;
// 		}
// 	}
// 	// for (auto &row : p) print_vector(row);
// 	return 0;
// }


//https://en.wikipedia.org/wiki/Partition_function_(number_theory)#Recurrence_relations


constexpr int MOD = 1'000'000;


int main() {
	constexpr int preserve = 1'000'000;
	constexpr int kreserve = 1'000;
	std::vector<int> P;
	P.reserve(preserve);
	P.push_back(1);
	std::vector<int> Kplus(kreserve);
	std::vector<int> Kminus(kreserve);
	for (int k = 0; k < kreserve; ++k) Kplus[k] = k * (3 * k - 1) / 2;
	for (int k = 0; k < kreserve; ++k) Kminus[k] = -k * (3 * -k - 1) / 2;
	auto p = [&](int n) {
		int ans = 0;
		int k = 1;
		while (true) {
			int sign = k % 2 ? 1 : -1;
			int kplus = Kplus[k];
			int kminus = Kminus[k];
			if (n - kplus < 0 && n - kminus < 0) break;
			if (n - kplus >= 0) ans += sign * P[n - kplus];
			if (n - kminus >= 0) ans += sign * P[n - kminus];
			ans %= MOD;
			++k;
		}
		return ans;
	};
	int n = 1;
	while (true) {
		int pn = p(n);
		if (pn == 0) {
			std::cout << n << std::endl;
			break;
		}
		P.push_back(pn);
		++n;
		if (n >= preserve) break;
	}
}
