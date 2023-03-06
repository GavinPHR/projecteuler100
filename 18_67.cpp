#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "utils.h"


using Triangle = std::vector<std::vector<std::uint32_t>>;


std::vector<std::uint32_t> process_line(const std::string &s) {
    std::vector<std::uint32_t> row;
    int i = 0;
    while (i < s.size()) {
        row.push_back(std::stoi(s.substr(i, 2)));
        i += 3;
    }
    return row;
}


int main(int argc, char const *argv[])
{	
	std::ifstream f(std::string(argv[1]) + ".txt");
    std::string line;
    Triangle triangle;
    while (std::getline(f, line)) triangle.push_back(process_line(line));
    f.close();
    for (int i = 1; i < triangle.size(); ++i) {
    	int n = triangle[i].size();
    	triangle[i][0] += triangle[i - 1][0];
    	triangle[i][n - 1] += triangle[i - 1][n - 2];
    	for (int j = 1; j < n -  1; ++j) {
    		triangle[i][j] += std::max(triangle[i - 1][j - 1], triangle[i - 1][j]);
    	}
    }
    auto &row = triangle[triangle.size() - 1];
    std::cout << *std::max_element(row.begin(), row.end()) << std::endl;
	return 0;
}
