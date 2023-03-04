#include <iostream>


int main(int argc, char const *argv[])
{
	// sum_{k=1}^n k = n * (n + 1) / 2
	// sum_{k=1}^n k^2 = n * (n + 1) * (2 * n + 1) / 6
	int n = std::stoi(argv[1]);
	int sum1 = n * (n + 1) / 2;
	int sum2 = n * (n + 1) * (2 * n + 1) / 6;
	int ans = sum1 * sum1 - sum2;
	std::cout << ans << std::endl;
	return 0;
}