#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "utils.h"


std::unordered_set<int> read_logs() {
	std::unordered_set<int> logs;
	std::ifstream f("79.txt");
	std::string line;
	while (f >> line) logs.insert(std::stoi(line));
	return logs;
}


int main() {
	auto logs = read_logs();
	std::vector<int> v(logs.begin(), logs.end());
	std::sort(v.begin(), v.end());
	print_vector(v);
	// 73162890, solved by hand
	// seems everyone in the thread also did the same procedure
	// deduplication -> sort -> by hand
}
