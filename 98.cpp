#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include "utils.h"


std::vector<std::string> read_file() {
	std::ifstream f("98.txt");
	std::string s;
	f >> s;
	std::vector<std::string> words;
	int i = 0;
	while (i < s.size()) {
		int j = i;
		while (j < s.size() && s[j] != ',') ++j;
		words.push_back(s.substr(i + 1, j - i - 2));
		i = j + 1;
	}
	return words;
}


std::unordered_map<std::uint64_t, std::vector<std::uint64_t>>
get_square_anagrams(int size) {
	std::unordered_map<std::uint64_t, std::vector<std::uint64_t>> anagrams;
	int max_i = std::sqrt(std::pow(10, size) - 1);
	for (std::uint64_t i = 4; i <= max_i; ++i) {
		std::uint64_t sq = i * i;
		std::vector<int> digits;
		std::uint64_t cur = sq;
		while (cur != 0) {
			digits.push_back(cur % 10);
			cur /= 10;
		}
		std::sort(digits.begin(), digits.end());
		for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
			cur = cur * 10 + *it;
		}
		anagrams[cur].push_back(sq);
	}
	return anagrams;
}


std::unordered_map<std::string, std::vector<std::string>> 
get_string_anagrams(const std::vector<std::string> &words) {
	std::unordered_map<std::string, std::vector<std::string>> anagrams;
	for (const auto &word : words) {
		std::vector<char> chars(word.begin(), word.cend());
		std::sort(chars.begin(), chars.end());
		std::string cur;
		for (auto it = chars.rbegin(); it != chars.rend(); ++it) {
			cur += *it;
		}
		anagrams[cur].push_back(word);
	}
	return anagrams;
}

template <class T>
void trim(std::unordered_map<T, std::vector<T>> &map) {
	for (auto it = map.begin(); it != map.end();) {
		if (it->second.size() == 1) {
			it = map.erase(it);
		} else {
			++it;
		}
	}
}



std::unordered_map<char, int> try_map(std::string st, int sq) {
	std::vector<int> sq_vec;
	while (sq != 0) {
		sq_vec.push_back(sq % 10);
		sq /= 10;
	}
	if (st.size() != sq_vec.size()) throw;
	std::reverse(sq_vec.begin(), sq_vec.end());
	std::unordered_map<char, int> map;
	std::unordered_map<int, char> rmap;
	for (int i = 0; i < st.size(); ++i) {
		auto it = map.find(st[i]);
		if (it != map.end() && it->second != sq_vec[i]) return {};
		auto rit = rmap.find(sq_vec[i]);
		if (rit != rmap.end() && rit->second != st[i]) return {};
		map[st[i]] = sq_vec[i];
		rmap[sq_vec[i]] = st[i];
	}
	return map;
}



int main() {
	const auto words = read_file();
	auto string_anagrams = get_string_anagrams(words);
	trim(string_anagrams);
	int max_size = 0;
	for (auto &[k, _] : string_anagrams) max_size = std::max(max_size, (int) k.size());
	auto square_anagrams = get_square_anagrams(max_size);
	trim(square_anagrams);
	// for (auto &[_, v] : square_anagrams) {
	// 	std::sort(v.begin(), v.end(), [](const auto &a, const auto &b) {return b < a;});
	// } 
	std::uint64_t ans = 0;
	for (int size = max_size; size > 0; --size) {
		if (ans != 0) break;
		for (auto &[k_string, v_string] : string_anagrams) {
			if (k_string.size() != size) continue;
			for (auto &[k_square, v_square] : square_anagrams) {
				if (std::to_string(k_square).size() != size) continue;
				for (int idx_st1 = 0; idx_st1 < v_string.size() - 1; ++idx_st1) {
				for (int idx_st2 = idx_st1 + 1; idx_st2 < v_string.size(); ++idx_st2) {
				for (int idx_sq1 = 0; idx_sq1 < v_square.size() - 1; ++idx_sq1) {
				for (int idx_sq2 = idx_sq1 + 1; idx_sq2 < v_square.size(); ++idx_sq2) {
					auto st1 = v_string[idx_st1];
					auto st2 = v_string[idx_st2];
					auto sq1 = v_square[idx_sq1];
					auto sq2 = v_square[idx_sq2];
					auto map1 = try_map(st1, sq1);
					if (map1.empty()) continue;
					auto map2 = try_map(st2, sq2);
					if (map1 != map2) continue;
					std::cout << st1 << " " << st2 << std::endl;
					std::cout << sq1 << " " << sq2 << std::endl;
					ans = std::max(ans, std::max(sq1, sq2));
				}
				}
				}
				}
			}
		}
	}
	std::cout << ans << std::endl;
}
