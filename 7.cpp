#include <iostream>
#include <vector>


int main(int argc, char const *argv[])
{	
	constexpr int size = 500000;
	int k = std::stoi(argv[1]);
	std::vector<bool> v(size, true);
	int n = 0;
	for (int i = 2; i < size; ++i) {
		if (!v[i]) continue;
		++n;
		if (n == k) {
			std::cout << i << std::endl;
			return 0;
		}
		int mult = 2;
		while (mult * i < size) {
			v[mult * i] = false;
			++mult;
		}
	}
	return 0;
}