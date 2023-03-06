#include <iostream>


// one, two, three, four, five, six, seven, eight, nine
const std::uint32_t units[10] = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4};
// eleven, twelve, thirteen, fourteen, fifteen, 
// sixteen, seventeen, eighteen, nineteen
const std::uint32_t teens[10] = {0, 6, 6, 8, 8, 7, 7, 9, 8, 8};
// ten, twenty, thirty, forty, fifty, sixty, seventy, eighty, ninety
const std::uint32_t tens[10] = {0, 3, 6, 6, 5, 5, 5, 7, 6, 6};
constexpr std::uint32_t one_thousand = 11;


inline std::uint32_t count(int n) {
	std::uint32_t ans = 0;
	int unit = n % 10;
	ans += units[unit];
	n /= 10;
	if (n) {
		int ten = n % 10;
		if (ten == 1 && unit != 0) {
			ans -= units[unit];
			ans += teens[unit];
		} else {
			ans += tens[ten];
		}
		n /= 10;
		if (n) {
			ans += units[n % 10] + 7;
			if (unit || ten) ans += 3;
		}
	}
	return ans;
}

int main() {
	std::uint32_t ans = one_thousand;
	for (int i = 1; i < 1000; ++i) {
		ans += count(i);
		// std::cout << i << ": " << count(i) << std::endl;
	}
	std::cout << ans << std::endl;
}