#include <iostream>
#include <vector>


// denominator largest multiple of 7;
// num = denom / 7 * 3 - 1;
int main() {  // guess
	constexpr int limit = 1'000'000;
	for (int i = limit; i > 0; --i) {
		if (i % 7 == 0) {
			std::cout << i / 7 * 3 - 1 << std::endl;
			break;
		}
	}
}
