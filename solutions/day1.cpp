#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <fstream>
#include <unordered_map>

using namespace std;

bool is_dig(const char ch) {
        return isdigit(ch);
}

int calibration_value(const string& str) {
        auto lpos = find_if(str.cbegin(), str.cend(), is_dig);
        int left = (lpos == str.cend()) ? 0: *lpos - '0';
        auto rpos = find_if(str.crbegin(), str.crend(), is_dig);
        int right = (rpos == str.crend()) ? 0: *rpos - '0';
        return left * 10 + right;
}

const unordered_map<string, int> digits = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
};

int my_stoi(const string& str) {
        if (str.size() == 1)
                return stoi(str);
        return digits.at(str);
}


int calibration_value2(const string& str) {
        size_t lpos = str.size();
        int lval = 0;
        for (auto [key, value]: digits) {
                auto word_pos = str.find(key);
                if (word_pos < lpos) {
                        lpos = word_pos;
                        lval = value;
                }
        }
        auto digit_pos = find_if(str.cbegin(), str.cend(), is_dig);
        if (digit_pos - str.cbegin() < static_cast<long int>(lpos)) {
                lval = *digit_pos - '0';
        }

        int rpos = -1;
        int rval = 0;
        for (auto [key, value]: digits) {
                auto word_pos = str.rfind(key);
                if (word_pos == string::npos)
                        continue;
                if (rpos == -1 || word_pos > rpos) {
                        rpos = word_pos;
                        rval = value;
                        continue;
                }
        }
        auto rdigit_pos = find_if(str.crbegin(), str.crend(), is_dig);
        if (rdigit_pos != str.crend() && rdigit_pos.base() - str.cbegin() > rpos) {
                rval = *rdigit_pos - '0';
        }
        return lval*10 + rval;
}

int main() {
        ifstream input("../inputs/input1.txt");
        long long ans_a = 0;
        long long ans_b = 0;
        std::string line;
        while (getline(input, line)) {
                ans_a += calibration_value(line);
                ans_b += calibration_value2(line);
        }
        std::cout << ans_a << " " << ans_b;
        return 0;
}
