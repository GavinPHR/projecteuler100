#include <cstdio>
#include <vector>
#include <cmath>


int main() {
	std::vector<int> targets = {1000000, 100000, 10000, 1000, 100, 10, 1};
	int i = 0;
	int next = 1;
	int ans = 1;
	while (!targets.empty()) {
		// printf("%d\n", i);
		int j = i + (int) log10(next) + 1;
		if (j >= targets.back()) {
			int diff = j - targets.back();
			int tmp = next;
			while (diff-- != 0) tmp /= 10;
			ans *= tmp % 10;
			targets.pop_back();
		}
		i = j;
		++next;
	}
	printf("%d\n", ans);
}
