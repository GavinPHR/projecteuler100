#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "utils.h"

std::vector<std::string> get_words(std::string fname) {
	std::ifstream f("42.txt");
	std::string line;
	f >> line;
	int i = 0;
	int j = 0;
	std::vector<std::string> words;
	while (i < line.size()) {
		j = i;
		while (j < line.size() && line[j] != ',') ++j;
		words.push_back(line.substr(i + 1, j - i - 2));
		i = j + 1;
	}
	return words;
}


std::unordered_map<int, int> transform(std::vector<std::string> words) {
	std::unordered_map<int, int> cnt;
	for (auto &word : words) {
		int sum = 0;
		for (auto &x : word) {
			sum += x - 'A' + 1;
		}
		++cnt[sum];
	}
	return cnt;
}


std::unordered_set<int> triangle(int max) {
	int n = 1;
	std::unordered_set<int> ans;
	int t = n * (n + 1) / 2;
	while (t < max) {
		ans.insert(t);
		++n;
		t = n * (n + 1) / 2;
	}
	return ans;
}


int main() {
	auto cnt = transform(get_words("42.txt"));
	auto max_val = 0;
	for (auto &[a, b] : cnt) max_val = std::max(max_val, a);
	auto ts = triangle(max_val);
	int ans = 0;
	for (auto &[a, b] : cnt) {
		if (ts.find(a) != ts.end()) ans += b;
	}
	std::cout << ans << std::endl;
	return 0;
}
