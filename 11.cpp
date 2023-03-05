#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "utils.h"


using Grid = std::vector<std::vector<std::uint32_t>>;

std::vector<std::uint32_t> process_line(const std::string &s) {
    std::vector<std::uint32_t> row;
    int i = 0;
    while (i < s.size()) {
        row.push_back(std::stoi(s.substr(i, 2)));
        i += 3;
    }
    return row;
}


std::uint32_t check_row(const Grid &grid) {
    std::uint32_t best = 0;
    size_t size  = grid.size();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size - 3; ++j) {
            best = std::max(best, grid[i][j] 
                                * grid[i][j + 1]
                                * grid[i][j + 2]
                                * grid[i][j + 3]);
        }
    }
    return best;
}


std::uint32_t check_col(const Grid &grid) {
    std::uint32_t best = 0;
    size_t size  = grid.size();
    for (size_t j = 0; j < size; ++j) {
        for (size_t i = 0; i < size - 3; ++i) {
            best = std::max(best, grid[i][j] 
                                * grid[i + 1][j]
                                * grid[i + 2][j]
                                * grid[i + 3][j]);
        }
    }
    return best;
}


std::uint32_t check_dia(const Grid &grid) {
    std::uint32_t best = 0;
    size_t size  = grid.size();
    // tl -> br
    for (size_t j = 0; j < size - 3; ++j) {
        for (size_t i = 0; i < size - 3; ++i) {
            best = std::max(best, grid[i][j] 
                                * grid[i + 1][j + 1]
                                * grid[i + 2][j + 2]
                                * grid[i + 3][j + 3]);
        }
    }
    // tr -> bl
    for (size_t j = 3; j < size; ++j) {
        for (size_t i = 0; i < size - 3; ++i) {
            best = std::max(best, grid[i][j] 
                                * grid[i + 1][j - 1]
                                * grid[i + 2][j - 2]
                                * grid[i + 3][j - 3]);
        }
    }
    return best;
}


int main(int argc, char const *argv[]) {
    std::ifstream f("11.txt");
    std::string line;
    Grid grid;
    while (std::getline(f, line)) grid.push_back(process_line(line));
    f.close();
    std::uint32_t best = 0;
    best = std::max(best, check_row(grid));
    best = std::max(best, check_col(grid));
    best = std::max(best, check_dia(grid));
    std::cout << best << std::endl;
    return 0;
}