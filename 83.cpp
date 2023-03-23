#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>
#include "81_82_83.h"


const std::vector<std::pair<int, int>> D = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};


void dfs() {
	Matrix m = read_matrix();
	int s = m.size();
	Matrix dp(s, std::vector<int>(s, INT_MAX));
	dp[0][0] = m[0][0];
	std::vector<std::tuple<int, int, int>> stack;
	stack.push_back({dp[0][0], 0, 0});
	while (!stack.empty()) {
		auto [sum, i, j] = stack.back();
		stack.pop_back();
		for (auto &[di, dj] : D) {
			int ii = i + di, jj = j + dj;
			if (ii < 0 || ii >= s || jj < 0 || jj >= s) continue;
			int new_sum = sum + m[ii][jj];
			if (new_sum >= dp[ii][jj]) continue;
			dp[ii][jj] = new_sum;
			stack.push_back({new_sum, ii, jj});
		}
	}
	std::cout << dp[s - 1][s - 1] << std::endl;
}


std::pair<int, int> get_min_dist(Matrix &dist, std::vector<std::pair<int, int>> &Q) {
	int min_idx = 0;
	int min_dist = INT_MAX;
	for (int k = 0; k < Q.size(); ++k) {
		auto &[i, j] = Q[k];
		if (dist[i][j] < min_dist) {
			min_dist = dist[i][j];
			min_idx = k;
		}
	}
	std::swap(Q[min_idx], Q.back());
	auto ans = Q.back();
	Q.pop_back();
	return ans;
}


bool in_Q(std::pair<int, int> lhs, std::vector<std::pair<int, int>> &Q) {
	for (auto &rhs : Q) {
		if (lhs == rhs) return true;
	}
	return false;
}


void dijkstra() {
	Matrix m = read_matrix();
	int s = m.size();
	Matrix dist(s, std::vector<int>(s, INT_MAX));
	dist[0][0] = m[0][0];
	std::vector<std::pair<int, int>> Q;
	for (int i = 0; i < s; ++i) {
		for (int j = 0; j < s; ++j) Q.push_back({i, j});
	}
	while (!Q.empty()) {
		auto [i, j] = get_min_dist(dist, Q);
		for (auto &[di, dj] : D) {
			int ii = i + di, jj = j + dj;
			if (ii < 0 || ii >= s || jj < 0 || jj >= s) continue;
			if (!in_Q({ii, jj}, Q)) continue;
			int alt = dist[i][j] + m[ii][jj];
			if (alt >= dist[ii][jj]) continue;
			dist[ii][jj] = alt;
		}
	}
	std::cout << dist[s - 1][s - 1] << std::endl;
}


int main() {
	dijkstra();
}