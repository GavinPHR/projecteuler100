#include <iostream>
#include <vector>
#include <algorithm>


bool is_palindrome(std::string v) {
	int i = 0;
	int j = v.size() - 1;
	while (i < j && v[i] == v[j]) {
		++i;
		--j;
	}
	return i >= j;
}


std::string iterate(std::string a) {
	auto b = a;
	std::reverse(b.begin(), b.end());
	std::string tmp = "";
	int carry = 0;
	for (int i = a.size() - 1; i >= 0; --i) {
		int sum = a[i] + b[i] - 2 * '0' + carry;
		tmp = (char) (sum % 10 + '0') + tmp;
		carry = sum / 10;
	}
	if (carry) {
		tmp = (char) (carry + '0') + tmp;
	}
	return tmp;
}


int main() {
	constexpr int limit = 10000;
	int ans = 0;
	for (int i = 1; i < limit; ++i) {
		int iter = 0;
		std::string cur = std::to_string(i);
		while (iter < 50) {
			cur = iterate(cur);
			if (is_palindrome(cur)) break;
			++iter;
		}
		if (iter == 50) ++ans;
	}
	std::cout << ans << std::endl;
}