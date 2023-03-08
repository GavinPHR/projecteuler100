#include <iostream>


int main(int argc, char const *argv[]) {
	int limit = std::stoi(argv[1]);
	int sum = 1;
	int lo = 1;
	int hi = 1;
	for (int i = 2; i < limit; i += 2) {
		lo += i;
		hi += 4 * i;
		sum += 2 * (lo + hi);
		lo = hi;
	}
	std::cout << sum << std::endl;
	return 0;
}