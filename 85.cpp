#include <iostream>
#include <algorithm>


int count(int M, int N) {
	// MxN
	int ans = 0;
	for (int x = 1; x <= M; ++x) {
		for (int y = 1; y <= N; ++y) {
			ans += (M - x + 1) * (N - y + 1);
		}
	}
	return ans;
}



int main() {
	constexpr int M_limit = 100;
	constexpr int target = 2'000'000;
	int diff = target;
	int area;
	// let M >= N
	for (int M = 1; M <= M_limit; ++M) {
		for (int N = 1; N <= M; ++N) {
			auto local_diff = std::abs(count(M, N) - target);
			// std::cout << M << "," << N << ": " << count(M, N) << std::endl;
			if (local_diff < diff) {
				diff = local_diff;
				area = M * N;
			}
		}
	}
	// std::cout << diff << std::endl;
	std::cout << area << std::endl;
}
