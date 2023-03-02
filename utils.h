#include <iostream>
#include <vector>


template<class T>
inline void print_vector(std::vector<T> v) {
	const size_t n = v.size();
	std::cout << '[';
	for (size_t i = 0; i < n; ++i) {
		std::cout << v[i];
		if (i != n - 1) std::cout << ", ";
	}
	std::cout << ']' << std::endl;
}