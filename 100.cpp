#include <iostream>


// easily derive 2B(B-1)=T(T-1) is the equation to satisfy
// but very difficult without external search for the sequence
// B follows https://oeis.org/A011900
// T follows https://oeis.org/A046090
int main() {
	constexpr std::uint64_t target = 1'000'000'000'000;
	std::uint64_t B0 = 1, B1 = 3;
	std::uint64_t T0 = 1, T1 = 4;
	while (T1 < target) {
		auto B2 = 6 * B1 - B0 - 2;
		auto T2 = 6 * T1 - T0 - 2;
		B0 = B1; B1 = B2;
		T0 = T1; T1 = T2;
	}
	std::cout << B1 << std::endl;
}
