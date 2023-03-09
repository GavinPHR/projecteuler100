#include <cstdio>
#include <vector>
#include <unordered_set>


bool test(int a, int b, int c){
	int i = (1 << 9) - 1;
	// printf("%d\n", i);
	std::vector<int> xs = {a, b, c};
	for (auto x : xs) {
		// printf("%d\n", x);
		while (x != 0) {
			if (x % 10 == 0) return false;
			int j = 1 << ((x % 10) - 1);
			// printf("%d ", j);
			if ((i & j) == 0) return false;
			i ^= j;
			x /= 10;
		}
		// printf("\n");
	}
	// printf("%d\n", i);
	return i == 0;
}


int main() {
	// can only be 1 digit * 4 digit = 4 digit
	// or 2 digit * 3 digit = 4 digit
	// test(39, 186, 7254);
	// return 0;
	std::unordered_set<int> ans;
	for (int a = 1; a < 10; ++a) {
		for (int b = 1000; b < 10000; ++b) {
			int c = a * b;
			if (test(a, b, c)) {
				printf("%d * %d = %d\n", a, b, c);
				ans.insert(c);
			}
		}
	}
	for (int a = 10; a < 100; ++a) {
		for (int b = 100; b < 1000; ++b) {
			int c = a * b;
			if (test(a, b, c)) {
				printf("%d * %d = %d\n", a, b, c);
				ans.insert(c);
			}
		}
	}
	int sum = 0;
	for (auto &x : ans) sum += x;
	printf("%d\n", sum);
	return 0;
}
