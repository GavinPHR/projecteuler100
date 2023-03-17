#pragma once
#include <iostream>
#include <vector>
#include <cctype>


// no sanity checks
class BigUInt {
public:
	std::vector<std::uint8_t> xs;

	friend std::ostream &operator<<(std::ostream &os, BigUInt const &n);
	BigUInt multiply(std::uint8_t m, const BigUInt &rhs, int padding);

	BigUInt(std::string s);
	BigUInt(std::uint64_t i);
	BigUInt(std::vector<std::uint8_t> &&xs);

	BigUInt& operator+=(const BigUInt& rhs);
    friend BigUInt operator+(BigUInt lhs, const BigUInt& rhs);
    BigUInt& operator*=(const BigUInt& rhs);
    friend BigUInt operator*(BigUInt lhs, const BigUInt& rhs);
};
