#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.h"

// my solution is very tricky to get right
// much easier to generate all possible dice pairs
// and check whethr the condition holds


using Graph = std::vector<std::vector<int>>;
using Colouring = std::vector<int>;
// colouring the graph below
// 2-5
//   -- 4 -----
// /    |       \
// 9 -- 0 -- 1 -- 6 -- 3
//           |
//           8
// 7 
const Graph G = {
	{1, 4, 9},
	{0, 6, 8},
	{5},
	{6},
	{0, 6, 9},
	{2},
	{1, 3, 4},
	{},
	{1},
	{0, 4}
};
// 4 colours, 0 (not in either set), 1 (in set 1), 2 (in set 2), 3 (in both sets)
// node 7 can take on 0, 1, 2, 3
// other nodes can take on 1, 2, 3
// each colour must be used 6 times


bool is_compatible(const Graph &G, Colouring &cs, int node, int colour) {
	if (colour == 3) return true;
	if (colour == 0 && node != 7) return false;
	// colour can only be 1, 2 at this point, or 0 for node 7
	for (const auto &neigh : G[node]) {
		if (cs[neigh] == colour) return false;
	}
	return true;
}


void dfs(
	const Graph &G,
	Colouring &cs,
	std::vector<Colouring> &ans, 
	int node = 0,
	int remain1 = 6, 
	int remain2 = 6) 
{	
	if (node == G.size()) {
		if (remain1 != 0 || remain2 != 0) return;
		ans.push_back(cs);
		return;
	}
	if (node == 7) {
		cs[node] = 0;
		dfs(G, cs, ans, node + 1, remain1, remain2);
		cs[node] = -1;
	}
	if (remain1 && is_compatible(G, cs, node, 1)) {
		cs[node] = 1;
		dfs(G, cs, ans, node + 1, remain1 - 1, remain2);
		cs[node] = -1;
	}
	if (remain2 && is_compatible(G, cs, node, 2)) {
		cs[node] = 2;
		dfs(G, cs, ans, node + 1, remain1, remain2 - 1);
		cs[node] = -1;
	}
	if (remain1 && remain2 && is_compatible(G, cs, node, 3)) {
		cs[node] = 3;
		dfs(G, cs, ans, node + 1, remain1 - 1, remain2 - 1);
		cs[node] = -1;
	}
}


std::ostream& operator<<(std::ostream &os, std::pair<std::vector<bool>, std::vector<bool>> &pair) {
    auto print = [&](std::vector<bool> &set) {
    	os << "{";
    	for (int i = 0; i < set.size(); ++i) {
    		if (set[i]) os << i << ", ";
    	}
    	os << "}";
    };
    print(pair.first);
    os << " ";
    print(pair.second);
    return os;
}

using Set = std::vector<bool>;

std::vector<Set> mutate(Set s) {
	if (!(s[6] || s[9])) return {s};
	std::vector<Set> res = {s};
	if (s[6] && !s[9]) {
		s[6] = false;
		s[9] = true;
		res.push_back(s);
		return res;
	}
	if (!s[6] && s[9]) {
		s[6] = true;
		s[9] = false;
		res.push_back(s);
		return res;
	}
	for (int i = 6; i < 10; i += 3) {
		s[i] = false;
		for (int j = 0; j < 10; ++j) {
			if (s[j] || i == j) continue;
			s[j] = true;
			res.push_back(s);
			s[j] = false;
		}	
		s[i] = true;
	}
	return res;
}


std::vector<std::pair<Set, Set>> cross(std::vector<Set> vs1, std::vector<Set> vs2) {
	std::vector<std::pair<Set, Set>> res;
	for (auto &s1 : vs1) {
		for (auto &s2 : vs2) {
			if (s1 < s2) res.push_back({s1, s2});
			else res.push_back({s2, s1});
		}
	}
	return res;
}


int main() {
	Colouring cs(10, -1);
	std::vector<Colouring> ans;
	dfs(G, cs, ans);
	// transform into bool arrays indicating existence
	std::vector<std::pair<Set, Set>> pairs;
	for (auto &cand : ans) {
		std::vector<bool> set1(10, false);
		std::vector<bool> set2(10, false);
		for (int i = 0; i < 10; ++i) {
			if (cand[i] == 1) {
				set1[i] = true;
			} else if (cand[i] == 2) {
				set2[i] = true;
			} else if (cand[i] == 3) {
				set1[i] = true;
				set2[i] = true;
			}
		}
		auto to_insert = cross(mutate(set1), mutate(set2));
		pairs.insert(pairs.end(), to_insert.begin(), to_insert.end());
	}
	std::sort(pairs.begin(), pairs.end());
	for (int i = 0; i < pairs.size() - 1; ++i) {
		if (pairs[i] == pairs[i + 1]) {
			pairs.erase(pairs.begin() + i);
			--i;
		}
	}
	std::cout << pairs.size() << std::endl;
}




