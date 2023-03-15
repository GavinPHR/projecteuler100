#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include "sieve.h"
#include "prime_factorization.h"
#include "utils.h"

using namespace std;

constexpr int limit = 10000;
const auto s = sieve(limit);
const int target = 5;


int concat(int a, int b) {
	int b_digit = (int) log10(b) + 1;
	int k = 1;
	while (b_digit--) k *= 10;
	return a * k + b;
}


bool check_prime(int x) {
	if (x <= limit) return s[x];
	return is_prime(x);
}


void recursive(const vector<int> &primes, vector<int> &cur, vector<int> &ans, int idx = 0) {
	if (cur.size() == target) {
		ans = cur;
		return;
	}
	if (idx == primes.size()) return;
	int ans_sum = accumulate(ans.begin(), ans.end(), 0);
	int cur_sum = accumulate(cur.begin(), cur.end(), 0);
	for (int i = idx; i < primes.size(); ++i) {
		auto p = primes[i];
		if (ans_sum != 0 && ans_sum + p >= ans_sum) break;
		bool possible = true;
		for (auto &n : cur) {
			int n_p = concat(n, p);
			int p_n = concat(p, n);
			if (!check_prime(n_p) || !check_prime(p_n)) {
				possible = false;
				break;
			} 
		}
		if (possible) {
			cur.push_back(p);
			recursive(primes, cur, ans, i + 1);
			cur.pop_back();
		}
	}
}


int main() {
	vector<int> primes;
	for (int i = 0; i <= limit; ++i) {
		if (s[i]) primes.push_back(i);
	}
	vector<int> cur, ans;
	recursive(primes, cur, ans);
	print_vector(ans);
	cout << accumulate(ans.begin(), ans.end(), 0) << endl;
}