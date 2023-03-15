#include <vector>


inline std::vector<std::uint64_t> trial_division(std::uint64_t n) {
	// n is the integer to be factored.
	// only need to test factors f <= sqrt(n)
	// because if n is divisible by p, then n = p * q
	// if p > q, n would have been reduced to n / q already.
	std::vector<std::uint64_t> ans;
	while (n % 2 == 0) {
		ans.push_back(2);
		n /= 2;
	}
	std::uint64_t f = 3;
	while (f * f <= n) {
		if (n % f == 0) {
			ans.push_back(f);
			n /= f;
		} else {
			f += 2;
		}
	}
	if (n != 1) ans.push_back(n);  // n is prime
	return ans;
}


inline bool is_prime(std::uint64_t n) {
	// n is the integer to be factored.
	// only need to test factors f <= sqrt(n)
	// because if n is divisible by p, then n = p * q
	// if p > q, n would have been reduced to n / q already.
	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	std::uint64_t f = 3;
	while (f * f <= n) {
		if (n % f == 0) return false;
		f += 2;
	}
	return true;
}
