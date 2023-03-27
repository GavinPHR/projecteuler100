#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "utils.h"


using Grid = std::vector<std::vector<int>>;
using Grids = std::vector<Grid>;
constexpr int N = 9;

Grids read_grids() {
	std::ifstream f("96.txt");
	std::vector<std::string> lines;
	std::string line;
	Grids Gs;
	while (std::getline(f, line)) lines.push_back(std::move(line));
	for (int i = 0; i < lines.size() / 10; ++i) {
		int next = (i + 1) * 10;
		Grid G;
		for (int j = i * 10 + 1; j < next; ++j) {
			std::vector<int> row;
			for (auto &c : lines[j]) row.push_back(c - '0');
			G.push_back(std::move(row));
		}
		Gs.push_back(std::move(G));
	}
	return Gs;
}


inline int get_k(int i, int j) {
	return (i / 3) * 3 + j / 3;
}


bool solve(
	Grid &G, 
	std::unordered_map<int, std::unordered_set<int>> &rows,
	std::unordered_map<int, std::unordered_set<int>> &cols,
	std::unordered_map<int, std::unordered_set<int>> &subs,
	int idx = 0) 
{
	if (idx == N * N) return true;
	int i = idx / N, j = idx % N;
	int x = G[i][j];
	if (x != 0) return solve(G, rows, cols, subs, idx + 1);
	for (x = 1; x <= N; ++x) {
		if (rows[i].find(x) != rows[i].end()) continue;
		if (cols[j].find(x) != cols[j].end()) continue;
		int k = get_k(i, j);
		if (subs[k].find(x) != subs[k].end()) continue;
		G[i][j] = x;
		rows[i].insert(x);
		cols[j].insert(x);
		subs[k].insert(x);
		if (solve(G, rows, cols, subs, idx + 1)) return true;
		G[i][j] = 0;
		rows[i].erase(x);
		cols[j].erase(x);
		subs[k].erase(x);
	}
	return false;
}


int main() {
	auto Gs = read_grids();
	int ans = 0;
	for (auto &G : Gs) {
		// for (auto &row : G) print_vector(row);
		// std::cout << std::endl;
		std::unordered_map<int, std::unordered_set<int>> rows, cols, subs;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				int x = G[i][j];
				if (x == 0) continue;
				rows[i].insert(x);
				cols[j].insert(x);
				subs[get_k(i, j)].insert(x);
			}
		}
		if (!solve(G, rows, cols, subs)) throw;
		ans += G[0][0] * 100 + G[0][1] * 10 + G[0][2];
	}
	std::cout << ans << std::endl;
}


