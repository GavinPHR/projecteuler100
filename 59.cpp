#include <iostream>
#include <fstream>
#include <vector>


std::vector<int> read() {
	std::ifstream f("59.txt");
	std::string s;
	std::getline(f, s);
	std::vector<int> res;
	int i = 0;
	while (i < s.size()) {
		int j = i;
		while (j < s.size() && s[j] != ',') ++j;
		res.push_back(std::stoi(s.substr(i, j - i)));
		i = j + 1;
	}
	return res;
}


std::vector<int> decrypt(int a, int b, int c, const std::vector<int> &f) {
	std::vector<int> res;
	for (int i = 0; i < f.size(); i += 3) {
		res.push_back(f[i] ^ a);
		if (i + 1 < f.size()) res.push_back(f[i + 1] ^ b);
		if (i + 2 < f.size()) res.push_back(f[i + 2] ^ c);
	}
	return res;
}


std::string to_string(const std::vector<int> &f) {
	std::string res;
	for (auto &i : f) res += (char) i;
	return res;
}


int main() {
	constexpr int space = 32;
	const auto f = read();
	for (int a = 0; a < 26; ++a) {
	for (int b = 0; b < 26; ++b) {
	for (int c = 0; c < 26; ++c) {
		// std::cout << a << b << c << std::endl;
		auto attempt = decrypt(a + 'a', b + 'a', c + 'a', f);
		int cnt = 0;
		for (auto &i : attempt) cnt += i == space ? 1 : 0;
		if (cnt > 200) {
			std::cout << to_string(attempt) << std::endl;
			int sum = 0;
			for (auto &c : attempt) sum += c;
			std::cout << sum << std::endl;
		}
	}
	}
	}
}
