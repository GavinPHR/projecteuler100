#include <iostream>
#include <algorithm>


std::string add(std::string a, std::string b) {
	std::string res;
	int i = 0;
	int carry = 0;
	while (i < std::min(a.size(), b.size())) {
		int sum = a[i] + b[i] - 2 * '0' + carry;
		res += (char) (sum % 10 + '0');
		carry = sum / 10;
		++i;
	}
	while (i < a.size()) {
		int sum = a[i] - '0' + carry;
		res += (char) (sum % 10 + '0');
		carry = sum / 10;
		++i;
	}
	while (i < b.size()) {
		int sum = b[i] - '0' + carry;
		res += (char) (sum % 10 + '0');
		carry = sum / 10;
		++i;
	}
	if (carry) res += (char) (carry + '0');
	return res;
}


void print(std::string num, std::string den) {
	for (auto it = num.rbegin(); it != num.rend(); ++it) {
		std::cout << *it;
	}
	std::cout << '/';
	for (auto it = den.rbegin(); it != den.rend(); ++it) {
		std::cout << *it;
	}
	std::cout << std::endl;
}


int main() {
	std::string x = "0";
	std::string y = "1";
	int ans = 0;
	for (int iter = 0; iter < 1000; ++iter) {
		auto y2_x = add(add(y, y), x);
		auto y3_x = add(y2_x, y);
		if (y3_x.size() > y2_x.size()) ++ans;
		x = y;
		y = y2_x;
		// print(x, y);
	}
	std::cout << ans << std::endl;
}