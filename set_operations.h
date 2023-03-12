#include <unordered_set>


template<class T>
inline std::unordered_set<T> 
set_insersect(std::unordered_set<T> a, 
	      std::unordered_set<T> b) {
	std::unordered_set<T> ans;
	for (auto &x : a) {
		if (b.find(x) != b.end()) {
			ans.insert(x);
		}
	}
	return ans;
}


template<class T>
inline std::unordered_set<T> 
set_union(std::unordered_set<T> a, 
	      std::unordered_set<T> b) {
	std::unordered_set<T> ans;
	for (auto &x : a) ans.insert(x);
	for (auto &x : b) ans.insert(x);
	return ans;
}


template<class T>
inline std::unordered_set<T> 
set_difference(std::unordered_set<T> a, 
	           std::unordered_set<T> b) {
	std::unordered_set<T> ans;
	for (auto &x : a) ans.insert(x);
	for (auto &x : b) {
		if (ans.find(x) != ans.end()) ans.erase(x);
	}
	return ans;
}
