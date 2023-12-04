#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_set>

using namespace std;
using ll = long long;

ll parse_line(const string& str) {
        auto left = str.find(':');
        auto right = str.find('|');
        string wins = str.substr(left+1, right-left-1);
        istringstream wstream(wins);
        string winner;
        unordered_set<string> winners;
        while (wstream >> ws >> winner) {
                winners.insert(winner);
        }
        istringstream astream(str.substr(right+1)); 
        int pts = 0;
        string number;
        while (astream >> ws >> number) {
                if (winners.contains(number)) {
                        pts = (pts == 0) ? 1: pts*2;
                }
        }
        return pts;
}

ll parse_line2(const string& str) {
        auto left = str.find(':');
        auto right = str.find('|');
        string wins = str.substr(left+1, right-left-1);
        istringstream wstream(wins);
        string winner;
        unordered_set<string> winners;
        while (wstream >> ws >> winner) {
                winners.insert(winner);
        }
        istringstream astream(str.substr(right+1)); 
        int pts = 0;
        string number;
        while (astream >> ws >> number) {
                if (winners.contains(number)) {
                        pts += 1;
                }
        }
        return pts;
}

ll calculate_cards(const vector<int>& cards) {
        ll total = cards.size();
        for (size_t i = 0; i < cards.size(); ++i) {
                stack<int> s;
                s.push(i);
                while (!s.empty()) {
                        auto card = s.top();        
                        s.pop();
                        size_t matches = cards[card];
                        total += matches;
                        for (size_t i = card + 1; i < cards.size() && i < card+matches+1; ++i) {
                                s.push(i);        
                        }
                }
        }
        return total;
}

int main() {
        ifstream input("../inputs/input4.txt");
        string line;
        long long ans_a = 0;
        vector<int> matches;
        while (getline(input, line)) {
                ans_a += parse_line(line);
                matches.push_back(parse_line2(line));
        }
        ll ans_b = calculate_cards(matches);
        std::cout << ans_a << "\n";
        std::cout << ans_b;
        return 0;
}
