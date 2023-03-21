#include <iostream>
#include <vector>
#include "prime_factorization.h"
#include "utils.h"

//  0  1  2  3  4  5  6
//2       1  0  1  0  1
//3          1  1  1  2
//5                2  2
// dp[i][j] -> to construct j using primes <= primes[i]
int main() {
	constexpr int n = 100;
	constexpr int target = 5'000;
	std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
	std::vector<int> primes;
	primes.push_back(2);
	for (int j = 2; j < n; j += 2) dp[0][j] = 1;
	for (int i = 0; i < n; ++i) dp[i][2] = 1;
	for (int j = 3; j < n; ++j) {
		if (is_prime(j)) primes.push_back(j);
		for (int i = 1; i < primes.size(); ++i) {
			int p = primes[i];
			int k = 0;
			while (j - k * p >= 0) {
				if (j - k * p == 0) {
					dp[i][j] += 1;
				} else {
					dp[i][j] += dp[i - 1][j - k * p];
				}
				++k;
			}
		}
		if (dp[primes.size() - 1][j] > target) {
			std::cout << j << std::endl;
			break;
		}
		for (int i = primes.size(); i < n; ++i) dp[i][j] = dp[primes.size() - 1][j];
	}
	// for (auto &row : dp) print_vector(row);
}
