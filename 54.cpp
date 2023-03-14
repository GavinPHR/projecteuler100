#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <utility>


struct Card {
	std::uint8_t value;
	std::uint8_t suit;
	Card(char value, char suit) {
		this->value = _parse_value(value);
		this->suit = _parse_suit(suit);
	}
	std::uint8_t _parse_value(char c) {
		std::uint8_t value;
		if (std::isdigit(c)) value = c - '0';
		else if (c == 'T') value = 10;
		else if (c == 'J') value = 11;
		else if (c == 'Q') value = 12;
		else if (c == 'K') value = 13;
		else value = 14;
		return value;
	}
	std::uint8_t _parse_suit(char c) {
		std::uint8_t suit;
		if (c == 'H') suit = 0;
		else if (c == 'S') suit = 1;
		else if (c == 'C') suit = 2;
		else suit = 3;
		return suit;
	}
};


enum Rank {
	high_card, one_pair, two_pairs, three_of_a_kind, 
	straight, flush, full_house, four_of_a_kind, 
	straight_flush, royal_flush 
};


struct Hand {
	std::vector<Card> cards;
	Rank rank;
	std::uint8_t high;
	std::pair<std::uint8_t, std::uint8_t> high_pair;
	Hand(std::string s) {
		for (int i = 0; i < 5; ++i) {
			cards.push_back({s[3 * i], s[3 * i + 1]});
		}
		std::sort(cards.begin(), cards.end(), [](const auto &a, const auto &b) 
			{
				return a.value < b.value;
			});
		determine_rank();
	}
	void determine_rank() {
		bool f = _is_flush();
		bool s = _is_straight();
		int n = _num_pairs();
		if (s && f) {
			if (cards.back().value == 14) rank = royal_flush;
			else rank = straight_flush;
			high = cards.back().value;
		} else if (f) {
			rank = flush;
			high = cards.back().value;
		} else if (s) {
			rank = straight;
			high = cards.back().value;
		} else if (_is_k_of_a_kind(4)) {
			rank = four_of_a_kind;
			for (int i = 1; i < 5; ++i) {
				if (cards[i].value == cards[i - 1].value) {
					high = cards[i].value;
					break;
				}
			}
		} else if (_is_k_of_a_kind(3)) {
			if (n) {
				rank = full_house;
				if (cards[0].value == cards[2].value) {
					high_pair = {cards[0].value, cards[3].value};
				} else {
					high_pair = {cards[3].value, cards[0].value};
				}
			} else {
				rank = three_of_a_kind;
				for (int i = 1; i < 5; ++i) {
					if (cards[i].value == cards[i - 1].value) {
						high = cards[i].value;
						break;
					}
				}
			}
		} else if (n == 2) {
			rank = two_pairs;
			std::uint8_t a = 0;
			std::uint8_t b = 0;
			for (int i = 1; i < 5; ++i) {
				if (cards[i].value == cards[i - 1].value) {
					if (a == 0) a = cards[i].value;
					else b = cards[i].value;
				}
			}
			high_pair = {b, a};
		} else if (n == 1) {
			rank = one_pair;
			for (int i = 1; i < 5; ++i) {
				if (cards[i].value == cards[i - 1].value) {
					high = cards[i].value;
					break;
				}
			}
		} else {
			rank = high_card;
			high = cards.back().value;
		}
	}
	bool _is_flush() {
		auto suit = cards[0].suit;
		for (auto &card : cards) {
			if (card.suit != suit) return false;
		}
		return true;
	}
	bool _is_straight() {
		for (int i = 1; i < 5; ++i) {
			if (cards[i].value != cards[i - 1].value + 1) return false;
		}
		return true;
	}
	bool _is_k_of_a_kind(int k) {
		int acc = 0;
		int prev = -1;
		for (auto &card : cards) {
			if (card.value != prev) {
				acc = 1;
				prev = card.value;
			} else {
				++acc;
			}
			if (acc == k) return true;
		}
		return false;
	}
	int _num_pairs() {
		int acc = 0;
		int ans = 0;
		int prev = -1;
		for (auto &card : cards) {
			if (card.value != prev) {
				if (acc == 2) ++ans;
				acc = 1;
				prev = card.value;
			} else {
				++acc;
			}
		}
		if (acc == 2) ++ans;
		return ans;
	}
	bool operator >(const Hand &other) const {
		if (rank > other.rank) return true;
		if (rank < other.rank) return false;
		if ((rank == full_house || rank == two_pairs) && high_pair != other.high_pair) {
			return high_pair > other.high_pair;
		} else if (high != other.high) {
			return high > other.high;
		}
		std::uint8_t a, b;
		for (int i = 4; i >= 0; --i) {
			a = cards[i].value;
			b = other.cards[i].value;
			if (a == b) continue;
			if (a > b) return true;
			return false;
		}
		return false;
	}
};


std::ostream& operator<<(std::ostream &os, const Hand &hand) {
    for (auto &card : hand.cards) {
    	os << '(' << (int) card.value << ',' << (int) card.suit << ')';
    }
    os << hand.rank << ' ' << (int) hand.high << ' ';
    os << '(' << (int) hand.high_pair.first << ',' << (int) hand.high_pair.second << ')';
    return os;
}



std::vector<std::pair<std::string, std::string>> 
test_cases = {{"5H 5C 6S 7S KD", "2C 3S 8S 8D TD"},
              {"5D 8C 9S JS AC", "2C 5C 7D 8S QH"},
              {"2D 9C AS AH AC", "3D 6D 7D TD QD"},
              {"4D 6S 9H QH QC", "3D 6D 7H QD QS"},
              {"2H 2D 4C 4D 4S", "3C 3D 3S 9S 9D"}
             };

 	

int main() {
	// for (auto &[a, b] : test_cases) {
	// 	Hand h1(a);
	// 	Hand h2(b);
	// 	std::cout << h1 << std::endl;
	// 	std::cout << h2 << std::endl;
	// 	std::cout << (h1 > h2) << std::endl;
	// }
	std::ifstream f("54.txt");
	std::string line;
	int ans =  0;
	while(std::getline(f, line)) {
		// std::cout << line << std::endl;
		auto a = line.substr(0, 14);
		auto b = line.substr(15, 14);
		// std::cout << a << std::endl;
		// std::cout << b << std::endl;
		// std::cout << (Hand(a) > Hand(b)) << std::endl;
		ans += Hand(a) > Hand(b);
	}
	std::cout << ans << std::endl;
}








