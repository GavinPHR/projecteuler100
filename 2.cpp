#include <iostream>



int main(int argc, char const *argv[])
{	

	int a = 1;
	int b = 1;
	int ans = 0;
	constexpr int limit = 4000000;
	while (true) {
		int c = a + b;
		if (c <= limit) ans += c % 2 ? 0 : c;
		else break;
		a = b;
		b = c;
	}
	std::cout << ans << std::endl;
	return 0;
}