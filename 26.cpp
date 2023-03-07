#include <iostream>
#include <unordered_map>
#include <vector>
#include "utils.h"


int main() {
	int longest = 0;
	int ans = 0;
	for (int i = 2; i < 1000; ++i) {
		int n = 1;
		int d = i;
		int cnt = 0;
		std::unordered_map<int, int> map;
		std::vector<int> num;
		while (n != 0 && map.find(n) == map.end()) {
			map[n] = cnt++;
			while (n < d) n *= 10;
			num.push_back(n / d);
			n = n % d;
		}
		if (n != 0) {
			int length = cnt - map[n];
			if (length > longest) {
				longest = length;
				ans = i;
			}
			// std::cout << cnt - map[n] << std::endl;
			// print_vector(num);
		}
	}
	std::cout << ans << std::endl;
	return 0;
}
