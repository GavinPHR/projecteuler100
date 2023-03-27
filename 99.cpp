#include <iostream>
#include <fstream>
#include <cmath>


int main() {
	std::ifstream f("99.txt");
	int i = 1;
	double largest = 0;
	int ans;
	std::string line;
	while (std::getline(f, line)) {
		int j = 0;
		while (line[j] != ',') ++j;
		int base = std::stoi(line.substr(0, j));
		int exp = std::stoi(line.substr(j + 1, line.size() - j - 1));
		double n = exp * std::log10(base);
		if (n > largest) {
			largest = n;
			ans = i;
		}
		++i;
	}
	std::cout << ans << std::endl;
}
