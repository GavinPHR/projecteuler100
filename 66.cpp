#include <iostream>
#include <utility>
#include <cmath>
#include "utils.h"
#include "big_int.h"

// 3^2-2*2^2=1
// x2-Dy2 = 1
// (x2-1)/y2=D
// sqrt(x2-1)/y=sqrt(D)
// sqrt(D) ~ x/y
// x/y is a continued fraction expansion of sqrt(D) 
// https://en.wikipedia.org/wiki/Pell%27s_equation#Fundamental_solution_via_continued_fractions


void iter(int &n, int &x, int &y, int &z) {
	int ry = n - z * z;
	if (ry % y == 0) {
		y = ry / y;
	} else {
		std::cout << "!";
	}
	x = (int) ((std::sqrt(n) + z) / y);
	z = std::abs(z - x * y);
}


std::vector<int> expand(int n) {
	std::vector<int> cf;
	int x1 = std::sqrt(n);
	cf.push_back(x1);
	int y1 = 1;
	int z1 = x1;
	iter(n, x1, y1, z1);
	int x = x1, y = y1, z = z1;
	cf.push_back(x);
	int i = 0;
	while (true) {
		iter(n, x, y, z);
		++i;
		if (x == x1 && y == y1 && z == z1) {
			break;
		}
		cf.push_back(x);
	}
	return cf;
}


std::string
solve(int n) {
	auto a = expand(n);
	// std::cout << n << ": ";
	// print_vector(a);
	BigUInt h1 = 1, h2 = 0;
	BigUInt k1 = 0, k2 = 1;
	int i = 0;
	while (true) {
		auto hn = a[i] * h1 + h2;
		auto kn = a[i] * k1 + k2;
		// std::cout << hn.xs.size() << " " << kn.xs.size() << std::endl;
		// h^2 - n * k^2 = 1
		// h^2 = 1 + n * k^2
		auto lhs = hn * hn;
		auto rhs = 1 + n * kn * kn;
		if (lhs.xs == rhs.xs) return hn.to_string();
		// std::cout << hn << "/" << kn << std::endl;
		h2 = h1; h1 = hn;
		k2 = k1; k1 = kn;
		++i;
		if (i == a.size()) {
			i = 1;
		}
	}
	std::cout << "not big enough" << std::endl;
	return "";
}


int main() {
	auto comp = [](std::string &a, std::string &b) {
		if (a.size() < b.size()) return true;
		if (a.size() > b.size()) return false;
		return a < b;
	};
	std::string largest = "0";
	int ans = 0;
	int next = 2;
	for (int i = 2; i <= 1000; ++i) {
		if (i == next * next) {
			++next;
			continue;
		}
		auto res = solve(i);
		std::cout << i << ": " << res << std::endl;
		if (comp(largest, res)) {
			largest = res;
			ans = i;
		}
	}
	std::cout << largest << std::endl;
	std::cout << ans << std::endl;
}
