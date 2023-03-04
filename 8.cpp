#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "utils.h"


std::uint64_t prod(std::vector<int> &buffer) {
	std::uint64_t ans = 1;
	for (auto &i : buffer) ans *= i;
	return ans;
}


int main(int argc, char const *argv[]) {
	int n = std::stoi(argv[1]);
	std::ifstream f("8.txt");
	std::string line;
	std::string s;
	while (f >> line) s += line;
	f.close();
	std::vector<int> buffer(n);
	for (int i = 0; i < n - 1; ++i) buffer[i] = s[i] - '0';
	int idx = n - 1;
	int size = s.size();
	std::uint64_t ans = 0;
	for (int i = n - 1; i < size; ++i) {
		buffer[idx] = s[i] - '0';
		ans = std::max(ans, prod(buffer));
		idx = (idx + 1) % n;
	}
	std::cout << ans << std::endl;
	return 0;
}