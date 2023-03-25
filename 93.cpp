#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <numeric>


constexpr double EPS = 0.0001;


int to_int(double x) {
	int lower = std::ceil(x - EPS);
	int upper = std::floor(x + EPS);
	if (lower == upper) return lower;
	return -1;
}


void dfs(std::unordered_set<double> unused, std::vector<bool> &flags, double x = 0) {
	if (unused.size() == 0) {
		// std::cout << x << " ";
		int idx = to_int(x);
		if (idx > 0) flags[idx] = true;
		return;
	}
	if (unused.size() == 4) {
		auto tmp = unused;
		for (auto &y : unused) {
			tmp.erase(y);
			dfs(tmp, flags, y); 
			tmp.insert(y);
		}
	} else {
		auto tmp = unused; 
		for (auto &y : unused) {
			tmp.erase(y); 
			dfs(tmp, flags, x + y);
			dfs(tmp, flags, x - y);
			dfs(tmp, flags, y - x);
			dfs(tmp, flags, x * y);
			if (y != 0) dfs(tmp, flags, x / y);
			if (x != 0) dfs(tmp, flags, y / x);
			tmp.insert(y);
		}
	}
}


int main() {
	int max_len = 0;
	int ans;
	for (int a = 0; a <= 6; ++a) {
		for (int b = a + 1; b <= 7; ++b) {
			for (int c = b + 1; c <= 8; ++c) {
				for (int d = c + 1; d <= 9; ++d) {
					std::vector<bool> flags(10'000, false);
					dfs({(double)a, (double)b, (double)c, (double)d}, flags);
					int i = 1;
					for (; i < flags.size(); ++i) {
						if (!flags[i]) break;
					}
					if (i - 1 > max_len) {
						max_len = i - 1;
						ans = a * 1000 + b * 100 + c * 10 + d;
					}
				}
			}
		}
	}
	std::cout << ans << std::endl;
}
