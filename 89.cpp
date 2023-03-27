#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "utils.h"


using Roman = std::string;

const std::vector<Roman> roman_numerals = {
	"M", "CM", "D", "CD", "C", "XC",
	 "L", "XL", "X", "IX", "V", "IV", "I"
};
const std::unordered_map<Roman, int> rtoi_map = {
	{"I", 1},
	{"IV", 4},
	{"V", 5},
	{"IX", 9},
	{"X", 10},
	{"XL", 40},
	{"L", 50},
	{"XC", 90},
	{"C", 100},
	{"CD", 400},
	{"D", 500},
	{"CM", 900},
	{"M", 1000}
};


std::vector<Roman> read_file() {
	std::ifstream f("89.txt");
	std::vector<Roman> romans;
	Roman line;
	while (std::getline(f, line)) romans.push_back(std::move(line));
	return romans;
}


int rtoi(Roman r) {
	int i = 0;
	int res = 0;
	while (i < r.size()) {
		bool matched = false;
		if (i + 1 < r.size()) {
			Roman cand = r.substr(i, 2);
			if (rtoi_map.find(cand) != rtoi_map.end()) {
				matched = true;
				res += rtoi_map.at(cand);
				i += 2;
			}
		}
		if (!matched) {
			res += rtoi_map.at(r.substr(i, 1));
			++i;
		}
	}
	return res;
}


Roman itor(int i) {
	int k = 0;
	Roman s;
	for (auto &r : roman_numerals) {
		int val = rtoi_map.at(r);
		if (i < val) continue;
		k = i / val;
		for (int i = 0; i < k; ++i) s += r;
		i %= val;
	}
	return s;
}


int main() {
	auto romans = read_file();
	int ans = 0;
	for (auto &roman : romans) {
		auto shortened = itor(rtoi(roman));
		ans += roman.size() - shortened.size();
	}
	std::cout << ans << std::endl;
}




