#include <iostream>
#include <vector>
// #include <unordered_map>


using Num = std::vector<std::uint8_t>;


Num multiply_(const Num &xs, const std::uint8_t y) {
	Num ans;
	std::uint8_t carry = 0;
	for (auto &x : xs) {
		auto sum = x * y + carry;
		ans.push_back(sum % 10);
		carry = sum / 10;
	}
	if (carry) ans.push_back(carry);
	return ans;
}


Num add_(const std::vector<Num> rows) {
	Num ans;
	for (int offset = 0; offset < rows.size(); ++offset) {
		int carry = 0;
		auto &row = rows[offset];
		for (int i = 0; i < row.size(); ++i) {
			int j = i + offset;
			if (ans.size() == j) ans.push_back(0);
			auto sum = ans[j] + row[i] + carry;
			ans[j] = sum % 10;
			carry = sum / 10;
		}
		if (carry) {
			if (offset + row.size() == ans.size()) ans.push_back(carry);
			else throw;
		}
	}
	return ans;
}


Num multiply(Num xs, Num ys) {
	std::vector<Num> rows;
	for (auto &y : ys) {
		rows.push_back(multiply_(xs, y));
	}
	return add_(rows);
}


Num exp(Num xs, int n) {
	if (n == 0) return {1};
	if (n % 2 == 0) return exp(multiply(xs, xs), n / 2);
	return multiply(xs, exp(multiply(xs, xs), n / 2));
}

int sum_digit(Num xs) {
	int ans = 0;
	for (auto &x : xs) ans += x;
	return ans;
}


Num get_num(int a) {
	Num xs;
	while (a != 0) {
		xs.push_back(a % 10);
		a /= 10;
	}
	return xs;
}


int main() {
	int max_sum = 0;
	for (int a = 1; a < 100; ++a) {
		auto xs = get_num(a);
		decltype(xs) res = {1};
		for (int b = 1; b < 100; ++b) {
			res = multiply(res, xs);
			int local = sum_digit(res);
			if (local > max_sum) {
				max_sum = local;
			}
		}
	}
	std::cout << max_sum << std::endl;
}
