#include <iostream>
#include <algorithm>
#include "81_82_83.h"


int main() {
	Matrix m = read_matrix();
	int s = m.size();
	for (int i = 1; i < s; ++i) {
		m[0][i] += m[0][i - 1];
		m[i][0] += m[i - 1][0];
	}
	for (int i = 1; i < s; ++i) {
		for (int j = 1; j < s; ++j) {
			m[i][j] += std::min(m[i - 1][j], m[i][j - 1]);
		}
	}
	std::cout << m[s - 1][s - 1] << std::endl;
}
