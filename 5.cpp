#include <iostream>
#include <vector>
#include "utils.h"

int main(int argc, char const *argv[])
{
	int n = std::stoi(argv[1]);
	std::vector<int> sieve(n + 1);
	for (int i = 0; i <= n; ++i) sieve[i] = i;
	int ans = 1;
	for (int i = 2; i <= n; ++i) {
		int k = sieve[i];
		ans *= k;
		int mult = 2;
		while (mult * k <= n) {
			if (sieve[mult * k] % k == 0) sieve[mult * k] /= k;
			++mult;
		}
	}
	print_vector(sieve);
	std::cout << ans << std::endl;
	return 0;
}