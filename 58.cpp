#include <iostream>
#include "prime_factorization.h"


int main() {
	std::uint64_t cur = 1;
	int side = 1;
	int p = 0;
	int np = 1;
	while (true) {
		side += 2;
		for (int i = 0; i < 4; ++i) {
			cur += side - 1;
			if (trial_division(cur).size() == 1) ++p;
			else ++np;
		}
		double r = p / (double) (p + np);
		if (r < 0.1) {
			std::cout << side << std::endl;
			break;
		}
		// std::cout << side << " ";
		// std::cout << cur << " ";
		// std::cout << r << std::endl;
	}
}
