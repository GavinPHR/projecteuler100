#include <cstdio>
#include <string>
#include <unordered_set>
#include "prime_factorization.h"


int main(int argc, char const *argv[])
{
    std::uint64_t n = std::stoi(argv[1]);
    constexpr std::uint64_t limit = 100000;
    std::uint64_t t = 1;

    for (std::uint64_t i = 2; i < limit; ++i) {
        t += i;
        auto primes = trial_division(t);
        std::unordered_set<std::uint64_t> factors;
        factors.insert(1);
        for (auto &p : primes) {
            std::unordered_set<std::uint64_t> copy = factors;
            for (auto &factor : copy) {
                factors.insert(factor * p);
            }
        }
        if (factors.size() > n) {
            printf("%llu", t);
            return 0;
        }
    }
    return 0;
}
