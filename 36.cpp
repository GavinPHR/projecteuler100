#include <iostream>


bool is_palindrome(std::string s) {
	int i = 0;
	int j = s.size() - 1;
	while (i < j) {
		if (s[i++] != s[j--]) return false;
	}
	return true;
}


std::string itos(int i, int base) {
	std::string ans = "";
	while (i != 0) {
		ans += (char) ('0' + (i % base));
		i /= base;
	}
	return ans;
}


int main(int argc, char const *argv[]) {
	constexpr int limit = 1000000;
	std::uint64_t ans = 0;
	for (int i = 1; i < limit; ++i) {
		if (is_palindrome(itos(i, 10)) && is_palindrome(itos(i, 2))) {
			// std::cout << itos(i, 10) << std::endl;
			// std::cout << itos(i, 2) << std::endl;
			ans += i;
		}
	}
	std::cout << ans << std::endl;
	return 0;
}
