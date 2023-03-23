#include <fstream>
#include <vector>
#include "utils.h"


using Matrix = std::vector<std::vector<int>>;


Matrix read_matrix() {
	Matrix m;
	std::ifstream f("81_82_83.txt");
	std::string s;
	while (std::getline(f, s)) {
		int i = 0;
		std::vector<int> row;
		while (i < s.size()) {
			int j = i;
			while (j < s.size() && s[j] != ',') ++j;
			row.push_back(std::stoi(s.substr(i, j - i)));
			i = j + 1;
		}
		m.push_back(std::move(row));
	}
	return m;
}


void print_matrix(Matrix &m) {
	for (auto &row : m) print_vector(row);
}
