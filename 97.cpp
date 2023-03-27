#include <iostream>
#include <vector>


//28433×2^7830457+1
int main() {
	int a = 28433;
	int b = 7830457;
	std::vector<int> num(10, 0);
	num.back() = 1;
	for (int _ = 1; _ <= b; ++_) {
		int carry = 0;
		for (int i = 9; i >= 0; --i) {
			int sum = 2 * num[i] + carry;
			num[i] = sum % 10;
			carry = sum / 10;
		}
	}
	std::uint64_t prod = 0;
	for (auto &n : num) prod = prod * 10 + n;
	prod *= a;
	++prod;
	std::cout << (prod % 10'000'000'000) << std::endl;
}
