#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "prime_factorization.h"
#include "utils.h"


int phi(int n, std::unordered_set<int> &ps) {
	if (ps.empty()) return n - 1;  // n is prime
	std::uint64_t partial = n;
	for (auto &p : ps) {
		partial = (partial * (p - 1)) / p;
	}
	return partial;
}

bool is_permutation(int n, int phi_n) {
	auto to_string = [](int k) {
		auto s = std::to_string(k);
		std::sort(s.begin(), s.end());
		return s;
	};
	return to_string(n) == to_string(phi_n);
}

int brute_force() {  // 17s runtime
	constexpr int limit = 10'000'000;
	std::vector<std::unordered_set<int>> sieve(limit + 1);
	std::vector<bool> permutation(limit + 1, false);
	float min_ratio = 100;
	int ans;
	for (int n = 2; n <= limit; ++n) {
		int phi_n = phi(n, sieve[n]);
		float ratio = n / (float) phi_n;
		if (ratio < min_ratio) {
			if (is_permutation(n, phi_n)) {
				min_ratio = ratio;
				ans = n;
			}
		}
		if (!sieve[n].empty()) continue;
		int k = 2;
		while (k * n <= limit) {
			sieve[k * n].insert(n);
			++k;
		}
	}
	std::cout << ans << std::endl;
}


// phi(prime) = prime - 1
// if gcd(m, n) = 1, phi(mn) = phi(m)phi(n)
// intuition to find two primes (m, n) as close to sqrt(10^7) as possible
// so that mn <= 10^7 and phi(mn) = (m - 1)(n - 1)
int main() {
	// sqrt(10^7) = 10^3.5 = 10^3*sqrt(10) ~ 3000
	constexpr int limit = 10'000'000;
	int lower = 2000, upper = 5000;
	std::vector<int> primes;
	for (int i = lower; i <= upper; ++i) {
		if (trial_division(i).size() == 1) primes.push_back(i);
	}
	float min_ratio = 1000;
	int ans;
	for (int i = 0; i < primes.size(); ++i) {
		int m = primes[i];
		for (int j = i; j < primes.size(); ++j) {
			int n = primes[j];
			int mn = m * n;
			if (mn > limit) break;
			int phi = (m - 1) * (n - 1);
			float ratio = mn / (float) phi;
			if (ratio > min_ratio) continue;
			if (!is_permutation(mn, phi)) continue;
			min_ratio = ratio;
			ans = mn;
		}
	}
	std::cout << ans << std::endl;
}

