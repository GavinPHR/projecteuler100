#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "utils.h"

int main() {
	std::ifstream f("22.txt");
	std::string line;
	f >> line;
	int i = 0;
	int j = 0;
	std::vector<std::string> names;
	while (i < line.size()) {
		j = i;
		while (j < line.size() && line[j] != ',') ++j;
		names.push_back(line.substr(i + 1, j - i - 2));
		i = j + 1;
	}
	std::sort(names.begin(), names.end());
	std::uint64_t ans = 0;
	for (int i = 0; i < names.size(); ++i) {
		if (names[i] == "COLIN") std::cout << "COLIN at pos " << i << std::endl;
		int val = 0;
		for (auto &c : names[i]) val += c - 'A' + 1;
		ans += (i + 1) * val;
	}
	std::cout << ans << std::endl;
	return 0;
}
