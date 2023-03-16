#include <iostream>

// 1 1 1
// 2 4 8 16 32 64 128 256
// 3 9 27 81 243 729 
// 7 49, 343, 
// 10 100 1000
// 11 121 1331

std::string mult(std::string a, int b) {
	int carry = 0;
	std::string ans;
	for (auto it = a.rbegin(); it != a.rend(); ++it) {
		int sum = b * (*it - '0') + carry;
		ans = (char) (sum % 10 + '0') + ans;
		carry = sum / 10;
	}
	if (carry) ans = (char) (carry + '0') + ans;
	return ans;
}


int main() {
	int ans = 0;
	for (int base = 1; base < 10; ++base) {
		int exp = 0;
		std::string cur = "1";
		while (true) {
			++exp;
			cur = mult(cur, base);
			if (cur.size() != exp) break;
			++ans;
			std::cout << base << "^" << exp << "=" << cur << std::endl;
		}
	}
	std::cout << ans << std::endl;
}
