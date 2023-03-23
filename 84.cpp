#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "utils.h"


constexpr int limit = 10'000'000;
constexpr int die_sides = 4;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> rand1_16(1, 16);
std::uniform_int_distribution<int> die(1, die_sides);

//   00 01 02  03 04 05 06 07  08 09 10
//   GO A1 CC1 A2 T1 R1 B1 CH1 B2 B3 JAIL
//39 H2                              C1  11
//38 T2                              U1  12
//37 H1                              C2  13
//36 CH3                             C3  14
//35 R4                              R2  15
//34 G3                              D1  16
//33 CC3                             CC2 17
//32 G2                              D2  18
//31 G1                              D3  19
//   G2J F3 U2 F2 F1 R3 E3 E2 CH2 E1 FP  20
//   30  29 28 27 26 25 24 23 22  21
enum Square {
	GO, A1, CC1, A2, T1, R1, B1, CH1, B2, B3,
	JAIL, C1, U1, C2, C3, R2, D1, CC2, D2, D3,
	FP, E1, CH2, E2, E3, R3, F1, F2, U2, F3,
	G2J, G1, G2, CC3, G3, R4, CH3, H1, T2, H2
};
const std::vector<std::string> names = {
	"GO", "A1", "CC1", "A2", "T1", "R1", "B1", "CH1", "B2", "B3",
    "JAIL", "C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3",
    "FP", "E1", "CH2", "E2", "E3", "R3", "F1", "F2", "U2", "F3",
    "G2J", "G1", "G2", "CC3", "G3", "R4", "CH3", "H1", "T2", "H2"
};
auto is_CC = [](Square s) {return (s == CC1) || (s == CC2) || (s == CC3);};
auto is_CH = [](Square s) {return (s == CH1) || (s == CH2) || (s == CH3);};
// Community Chest (2/16 cards):
// Advance to GO
// Go to JAIL
// Chance (10/16 cards):
// Advance to GO
// Go to JAIL
// Go to C1
// Go to E3
// Go to H2
// Go to R1
// Go to next R (railway company)
// Go to next R
// Go to next U (utility company)
// Go back 3 squares.


struct Board {
	Square pos = GO;
	std::vector<std::uint64_t> cnt;
	bool pprev_doule = false, prev_double = false;
	Board() {
		cnt = std::vector<std::uint64_t>(40, 0);
		cnt[0] = 1;
	}
	void rand_CC() {
		int k = rand1_16(gen);
		if (k == 1) {
			pos = GO;
		} else if (k == 2) {
			pos = JAIL;
		}
	}
	void rand_CH() {
		int k = rand1_16(gen);
		if (k == 1) {
			pos = GO;
		} else if (k == 2) {
			pos = JAIL;
		} else if (k == 3) {
			pos = C1;
		} else if (k == 4) {
			pos = E3;
		} else if (k == 5) {
			pos = H2;
		} else if (k == 6) {
			pos = R1;
		} else if (k == 7 || k == 8) {
			if (pos == CH1) pos = R2;
			else if (pos == CH2) pos = R3;
			else pos = R1;
		} else if (k == 9) {
			if (pos == CH1) pos = U1;
			else if (pos == CH2) pos = U2;
			else pos = U1;
		} else if (k == 10) {
			if (pos == CH3) {
				pos = CC3;
				rand_CC();
			}
			else pos = static_cast<Square>(pos - 3);
		}
	}
	void go() {
		int roll1 = die(gen);
		int roll2 = die(gen);
		if (roll1 == roll2) {
			if (pprev_doule && prev_double) {
				pos = JAIL;
				++cnt[pos];
				pprev_doule = false;
				prev_double = false;
				return;
			}
		} 
		pos = static_cast<Square>((pos + roll1 + roll2) % 40);
		if (pos == G2J) pos = JAIL;
		else if (is_CC(pos)) rand_CC();
		else if (is_CH(pos)) rand_CH();
		++cnt[pos];
		pprev_doule = prev_double;
		prev_double = roll1 == roll2;
	}
	std::vector<double> get_stats() {
		double total = std::accumulate(cnt.begin(), cnt.end(), 0);
		std::vector<double> ans; ans.reserve(40);
		// print_vector(cnt);
		for (auto &c : cnt) ans.push_back(c / total);
		return ans;
	}
};


void print_stats(std::vector<double> &stats) {
	std::vector<int> idx;
	for (int i = 0; i < stats.size(); ++i) idx.push_back(i);
	std::sort(idx.begin(), idx.end(), [&](auto i, auto j) {
		return stats[i] < stats[j];
	});
	std::cout << std::fixed;
    std::cout << std::setprecision(2);
	for (int i = idx.size() - 1; i >= 0; --i) {
		std::cout << names[idx[i]] << ": " << (stats[idx[i]] * 100) << "%" << "   ";
	}
	std::cout << std::endl;
}



int main() {
	Board board;
	for (int i = 0; i < limit; ++i) board.go();
	auto stats = board.get_stats();
	print_stats(stats);
}
