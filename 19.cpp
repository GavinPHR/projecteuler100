#include <iostream>
#include <cstdio>

int main() {
	int day = 1;
	int y = 1900;
	int m = 1;
	int d = 1;
	int ans = 0;
	auto leap = [&]() {return (y % 4 == 0) && ((y % 1000 != 0) || (y % 400 == 0));};
	while (y != 2001) {
		if (y > 1900 && day == 7 && d == 1) ++ans;
		++d;
		if (d < 29) {
			day = day % 7 + 1;
			continue;
		}
		bool over = false;
		if (m == 2) {
			if ((leap() && d == 30) || (!leap() && d == 29)) {
				over = true;
			} 
		} else if ((m == 4 || m == 6 || m == 9 || m == 11) && d == 31) {
			over = true;
		} else if (d == 32) {
			over = true;
		}
		if (over) {
			d = 1;
			++m;
			if (m == 13) {
				m = 1;
				++y;
			}
		}
		day = day % 7 + 1;
	}
	std::cout << ans << std::endl;
	return 0;
}