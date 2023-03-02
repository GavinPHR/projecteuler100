#include <iostream>
#include "prime_factorization.h"
#include "utils.h"



int main(int argc, char const *argv[])
{	
	std::uint64_t n = std::stoull(argv[1]);
	auto v = trial_division(n);
	print_vector(v);
	return 0;
}