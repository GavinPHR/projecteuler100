#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>


inline int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}


std::pair<int, int> reduce(int a, int b) {
	int g = gcd(a, b);
	return {a / g, b / g};
}


int main(int argc, char const *argv[]) {
	std::unordered_set<int> ans;
	for (int num = 10; num < 99; ++num) {
		int a = num / 10;
		int b = num % 10;
		if (b == 0) continue;
		for (int i = 1; i < 10; ++i) {
			//ia, ai, bi, ib 
			// > ab
			int ia = i * 10 + a;
			int ib = i * 10 + b;
			int ai = a * 10 + i;
			int bi = b * 10 + i;
			if (ia > num) {
				auto p1 = reduce(num, ia);
				auto p2 = reduce(b, i);
				if (p1 == p2) ans.insert(p1.first * 100 + p1.second);
			}
			if (ib > num) {
				auto p1 = reduce(num, ib);
				auto p2 = reduce(a, i);
				if (p1 == p2) ans.insert(p1.first * 100 + p1.second);
			}
			if (ai > num) {
				auto p1 = reduce(num, ai);
				auto p2 = reduce(b, i);
				if (p1 == p2) ans.insert(p1.first * 100 + p1.second);
			}
			if (bi > num) {
				auto p1 = reduce(num, bi);
				auto p2 = reduce(a, i);
				if (p1 == p2) ans.insert(p1.first * 100 + p1.second);
			}
		}
	}
	for (auto &x: ans) std::cout << x << std::endl;
	return 0;
}
