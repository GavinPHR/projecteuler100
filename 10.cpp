#include <iostream>
#include <vector>


int main(int argc, char const *argv[])
{	
	constexpr int size = 2000000;
	std::vector<bool> v(size, true);
	std::uint64_t ans = 0;
	for (int i = 2; i < size; ++i) {
		if (!v[i]) continue;
		ans += i;
		int mult = 2;
		while (mult * i < size) {
			v[mult * i] = false;
			++mult;
		}
	}
	std::cout << ans << std::endl;
	return 0;
}