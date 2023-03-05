#include <cstdio>
#include <fstream>
#include "utils.h"


std::vector<std::uint32_t> process_line(std::string &line) {
    std::vector<std::uint32_t> row;
    row.push_back(0);
    row.push_back(0);
    for (const char &c : line) {
        row.push_back(c - '0');
    }
    return row;
}


bool add(std::vector<std::vector<std::uint32_t>> &table) {
    std::uint32_t carry;
    for (int j = table[0].size() - 1; j >= 0; --j) {
        uint32_t sum = carry;
        for (int i = 0; i < table.size() - 1; ++i) sum += table[i][j];
        table[table.size() - 1][j] = sum % 10;
        carry = sum / 10;
    }
    return carry == 0;
}


int main() {
    std::ifstream f("13.txt");
    std::string line;
    std::vector<std::vector<std::uint32_t>> table;
    while (std::getline(f, line)) table.push_back(process_line(line));
    f.close();
    table.push_back(std::vector<std::uint32_t>(52, 0));
    if (!add(table)) printf("***\n");
    print_vector(table[table.size() - 1]);
    for (int j = 0; j < 10; ++j) printf("%u", table[table.size() - 1][j]);
    printf("\n");
    return 0;
}