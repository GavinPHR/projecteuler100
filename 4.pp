#include <iostream>
#include <algorithm>
#include <vector>

inline bool check(int n) {
	std::vector<int> vec;
	while (n != 0) {
		vec.push_back(n % 10);
		n /= 10;
	}
	int i = 0;
	int j = vec.size() - 1;
	while (i < j && vec[i] == vec[j]) {
		++i;
		--j;
	}
	return i >= j;
}


int main(int argc, char const *argv[]) {
	int ans = 0;
	for (int i = 100; i < 1000; ++i) {
		for (int j = 100; j < 1000; ++j) {
			if (check(i * j)) ans = std::max(ans, i * j);
		}
	}
	std::cout << ans << std::endl;
	return 0;
}
