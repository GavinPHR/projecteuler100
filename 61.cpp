#include <iostream>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include "utils.h"


using namespace std;
using Edges = unordered_map<int, vector<int>>;

constexpr int L = 6;

const function<int(int)> fs[] = {
	[](int n) {return n * (n + 1) / 2;},
	[](int n) {return n * n;},
	[](int n) {return n * (3 * n - 1) / 2;},
	[](int n) {return n * (2 * n - 1);},
	[](int n) {return n * (5 * n - 3) / 2;},
	[](int n) {return n * (3 * n - 2);}
};


void print_edges(const Edges e) {
	for (const auto &[a, bs] : e) {
		std::cout << a << "->";
		print_vector(bs);
	}
}


bool 
dfs(vector<int> &path, 
	Edges (&E)[L], 
	vector<int> &ans, 
	unordered_set<int> unused) {
	if (!ans.empty()) return true;
	if (path.empty()) {
		for (auto &[a, bs] : E[0]) {
			for (auto &b : bs) {
				path.push_back(a);
				path.push_back(b);
				dfs(path, E, ans, unused);
				path.pop_back();
				path.pop_back();
			}
		}
		return false;
	}
	bool is_last = unused.size() == 1;
	int a = path.back();
	auto unused_copy = unused;
	for (auto &k : unused_copy) {
		auto edges = E[k];
		if (edges.find(a) == edges.end()) continue;
		unused.erase(k);
		for (auto &b : edges[a]) {
			if (is_last) {
				if (b == path[0]) {
					path.push_back(b);
					ans = path;
					return true;
				}
			} else {
				path.push_back(b);
				if (dfs(path, E, ans, unused)) return true;
				path.pop_back();
			}
		}
		unused.insert(k);
	}
	return false;
}


int main() {
	Edges E[L];
	for (int i = 0; i < L; ++i) {
		auto f = fs[i];
		int n = 1;
		int fn = f(n);
		while (fn < 10000) {
			if (fn > 999)  {
				// cout << fn << " ";
				int a = fn / 100;
				int b = fn % 100;
				if (b > 9) E[i][a].push_back(b);
			}
			++n;
			fn = f(n);
		}
		// cout << endl;
	}
	// for (int i = 0; i < L; ++i) {
		// print_edges(E[i]);
	// }
	vector<int> path, ans;
	unordered_set<int> unused = {1, 2, 3, 4, 5};
	dfs(path, E, ans, unused);
	if (ans.empty()) cout << "not found" << endl;
	print_vector(ans);
	int sum = 0;
	for (int i = 0; i < L; ++i) {
		sum += ans[i] * 100 + ans[(i + 1) % L];
	}
	cout << sum << endl;
}
