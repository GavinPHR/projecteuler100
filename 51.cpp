#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include "utils.h"
#include "sieve.h"

using namespace std;

constexpr int limit = 1000000;
const auto s = sieve(limit);


void generate_(vector<char> &cs, char c, unordered_set<string> &ans, int i = 0) {
	if (i == cs.size()) {
		string tmp = "";
		for (auto &c : cs) tmp += c;
		ans.insert(tmp);
		return;
	}
	if (cs[i] == c) {
		cs[i] = '*';
		generate_(cs, c, ans, i + 1);
		cs[i] = c;
	}
	generate_(cs, c, ans, i + 1);
}


unordered_set<string> generate(int n) {
	vector<char> cs;
	while (n != 0) {
		cs.push_back((char) ('0' + n % 10));
		n /= 10;
	}
	reverse(cs.begin(), cs.end());
	int len = cs.size();
	unordered_set<string> ans;
	for (auto &c : cs) generate_(cs, c, ans);
	return ans;
}


int main() {
	vector<int> primes;
	for (int i = 2; i <= limit; ++i) {
		if (s[i]) primes.push_back(i);
	}
	unordered_map<string, vector<int>> cnt;
	int num_primes = 2;
	for (auto &p : primes) {
		for (auto &s : generate(p)) {
			cnt[s].push_back(p);
			if (cnt[s].size() == num_primes) {
				print_vector(cnt[s]);
				++num_primes;
			}
		}
	}
}
