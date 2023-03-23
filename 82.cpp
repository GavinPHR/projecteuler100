#include <iostream>
#include <algorithm>
#include "81_82_83.h"


void transpose(Matrix &m) {
	// easier to work with, going to bottom
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			std::swap(m[i][j], m[j][i]);
		}
	}
}


int path_sum(Matrix &m, int i, int j, int k) {
	int sum = m[i - 1][j];
	if (k >= j) {
		while (j <= k) {
			sum += m[i][j];
			++j;
		}
	} else {
		while (j >= k) {
			sum += m[i][j];
			--j;
		}
	}
	return sum;
}


int main() {
	Matrix m = read_matrix();
	transpose(m);
	int s = m.size();
	for (int i = 1; i < s; ++i) {
		std::vector<int> res(s, INT_MAX);
		// go from row[i - 1][j] to row[i][k]
		for (int j = 0; j < s; ++j) {
			for (int k = 0; k < s; ++k) {
				res[k] = std::min(res[k], path_sum(m, i, j, k));
			}
		}
		m[i] = std::move(res);
	}
	int ans = INT_MAX;
	for (auto &x : m.back()) ans = std::min(ans, x);
	std::cout << ans << std::endl;
}
