#include "big_int.h"


std::ostream& operator<<(std::ostream &os, BigUInt const &n) {
    return os << n.to_string();
}

BigUInt BigUInt::multiply(std::uint8_t m, const BigUInt &rhs, int padding) {
	auto &ys = rhs.xs;
	int s = ys.size();
	std::vector<std::uint8_t> ans(padding + s, 0);
	std::uint8_t carry = 0;
	for (int i = 0; i < s; ++i) {
		std::uint8_t prod = m * ys[i] + carry;
		ans[padding + i] = prod % 10;
		carry = prod / 10;
	}
	if (carry) ans.push_back(carry);
	return BigUInt(std::move(ans));
}

BigUInt::BigUInt(std::string s) {
	for (int i = s.size() - 1; i >= 0; --i) {
		xs.push_back(s[i] - '0');
	}
}
BigUInt::BigUInt(std::uint64_t i) {
	while (i != 0) {
		xs.push_back(i % 10);
		i /= 10;
	}
}
BigUInt::BigUInt(std::vector<std::uint8_t> &&xs) {
	this->xs = std::move(xs);
}

BigUInt& BigUInt::operator+=(const BigUInt& rhs) {   
	auto &ys = rhs.xs; 
    int s1 = xs.size();
    int s2 = ys.size();
    int i = 0;
    std::uint8_t carry = 0;
    while (i < s1 || i < s2) {
    	std::uint8_t x = i < s1 ? xs[i] : 0;
    	std::uint8_t y = i < s2 ? ys[i] : 0;
    	std::uint8_t sum = x + y + carry;
    	if (i < s1) xs[i] = sum % 10;
    	else xs.push_back(sum % 10);
    	carry = sum / 10;
    	++i;
    }
    if (carry) xs.push_back(carry);
    return *this;
}
BigUInt operator+(BigUInt lhs, const BigUInt& rhs) {
    lhs += rhs;
    return lhs;
}
BigUInt& BigUInt::operator*=(const BigUInt& rhs) {   
	int s1 = xs.size();
	int s2 = rhs.xs.size();
	BigUInt ans(std::vector<std::uint8_t>(s1 + s2, 0));
	for (int i = 0; i < s1; ++i) {
		ans += multiply(xs[i], rhs, i);
	}
	if (ans.xs.back() == 0) ans.xs.pop_back();
	xs = std::move(ans.xs);
    return *this;
}
BigUInt operator*(BigUInt lhs, const BigUInt& rhs) {
    lhs *= rhs;
    return lhs;
}



// int main() {
// 	std::uint64_t n1 = 28475639;
// 	std::uint64_t n2 = 88473612;
// 	BigUInt s1(std::to_string(n1));
// 	BigUInt s2(std::to_string(n2));
// 	BigUInt i1(n1);
// 	BigUInt i2(n2);
// 	std::cout << (n1 + n2) << std::endl;
// 	std::cout << (s1 + s2) << std::endl;
// 	std::cout << (i1 + i2) << std::endl;
// 	std::cout << (n1 * n2) << std::endl;
// 	std::cout << (s1 * s2) << std::endl;
// 	std::cout << (i1 * i2) << std::endl;
// }
