#include <iostream>
#include "prime_factorization.h"
#include "sieve.h"
#include "utils.h"



int main(int argc, char const *argv[])
{	
	constexpr int limit = 10000000;
	const auto s = sieve(limit);
	for (int i = 0; i <= limit; ++i) {
		if (s[i] != is_prime(i)) std::cout << "bug" << std::endl;
	}
	print_vector(trial_division(95384));
	return 0;
}