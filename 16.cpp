#include <iostream>
#include <vector>
#include <string>


int main(int argc, char const *argv[])
{
	size_t n = std::stoi(argv[1]);
	std::vector<std::uint8_t> v;
	v.push_back(1);
	for (size_t iter = 0; iter < n; ++iter) {
		std::uint8_t carry = 0;
		for (size_t i = 0; i < v.size(); ++i) {
			std::uint8_t tmp = 2 * v[i] + carry;
			v[i] = tmp % 10;
			carry = tmp / 10;
		}
		if (carry) v.push_back(carry);
	}
	std::uint32_t sum = 0;
	for (auto &d : v) sum += d;
	std::cout << sum << std::endl;
	return 0;
}
