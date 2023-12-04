#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

bool is_dig(char c) {
        return isdigit(c);
}

bool is_symbol(char c) {
        return !is_dig(c) && c != '.';
}

bool is_touching(const vector<string>& lines, size_t line_number, size_t beg, size_t end) {
        size_t left = (beg == 0) ? 0: beg-1;
        size_t right = (end == lines[0].size()) ? end: end+1;
        if (line_number != 0) {
                auto top = lines[line_number-1];
                for (size_t i = left; i < right; ++i) {
                        if (is_symbol(top[i]))
                                return true;
                }
        }
        if (line_number != lines.size() - 1) {
                auto bottom = lines[line_number+1];
                for (size_t i = left; i < right; ++i) {
                        if (is_symbol(bottom[i]))
                                return true;
                }
        }
        auto current = lines[line_number];
        if (beg != 0 && is_symbol(current[left])) {
                return true;
        }
        if (end != current.size() && is_symbol(current[end])) {
                return true; 
        }
        return false;
}

long long parse_line(const vector<string>& lines, size_t line_number) {
        const string& line = lines[line_number];
        auto iter = find_if(line.cbegin(), line.cend(), is_dig);
        long long ans = 0;
        while (iter != line.cend()) {
                auto num_end = iter+1;
                while (num_end != line.cend() && is_dig(*num_end)) {
                        ++num_end;
                }
                auto beg = distance(line.cbegin(), iter);
                auto end = beg + distance(iter, num_end);
                if (is_touching(lines, line_number, beg, end)) {
                        string num{};
                        while (iter != num_end) {
                                num += *iter++;
                        }
                        ans += stoi(num);
                }
                iter = find_if(num_end, line.cend(), is_dig);
        }
        return ans;
}

//part 2
bool is_star(char c) {
        return c == '*';
}

using star_map = map<pair<int, int>, pair<int, long>>;

void increment_star(star_map& asterisks,
               int x, int y, int n) {
        if (!asterisks.contains({x, y})) {
                asterisks[{x, y}] = {1, n};
                return;
        }
        auto& [times, val] = asterisks.at({x, y});
        ++times;
        if (times <= 2) {
                val *= n;
        } 

}

void check_star(const vector<string>& lines, size_t line_number, 
                 size_t beg, size_t end, int n,
                 star_map& asterisks) {
        size_t left = (beg == 0) ? 0: beg-1;
        size_t right = (end == lines[0].size()) ? end: end+1;
        if (line_number != 0) {
                auto top = lines[line_number-1];
                for (size_t i = left; i < right; ++i) {
                        if (is_star(top[i])) {
                                increment_star(asterisks,
                                               line_number-1,
                                               i, n);
                        }
                }
        }
        if (line_number != lines.size() - 1) {
                auto bottom = lines[line_number+1];
                for (size_t i = left; i < right; ++i) {
                        if (is_star(bottom[i]))
                                increment_star(asterisks, line_number+1, i, n);
                }
        }

        auto current = lines[line_number];
        if (beg != 0 && is_symbol(current[left])) {
                increment_star(asterisks, line_number, left, n);
        }
        if (end != current.size() && is_symbol(current[end])) {
                increment_star(asterisks, line_number, end, n);
        }
}
long long parse_line(const vector<string>& lines, size_t line_number,
                     star_map& stars) {
        const string& line = lines[line_number];
        auto iter = find_if(line.cbegin(), line.cend(), is_dig);
        long long ans = 0;
        while (iter != line.cend()) {
                auto num_end = iter+1;
                while (num_end != line.cend() && is_dig(*num_end)) {
                        ++num_end;
                }
                auto beg = distance(line.cbegin(), iter);
                auto end = beg + distance(iter, num_end);
                string num{};
                while (iter != num_end) {
                        num += *iter++;
                }
                check_star(lines, line_number, beg, end, stoi(num), stars);
                iter = find_if(num_end, line.cend(), is_dig);
        }
        return ans;
}

long long evaluate_gears(const star_map& stars) {
        long long ans = 0; 
        for (auto [coordinate, value]: stars) {
                if (value.first == 2) {
                        ans += value.second;
                }
        }
        return ans;
}
int main() {
        // ifstream input("../test.txt");
        ifstream input("../inputs/input3.txt");
        vector<string> lines;
        string line;
        while (getline(input, line)) {
                lines.push_back(line);
        }
        long long ans_a = 0;
        star_map stars;
        for (size_t i = 0; i < lines.size(); ++i) {
                ans_a += parse_line(lines, i);
                parse_line(lines, i, stars);
        }
        long long ans_b = evaluate_gears(stars);
        std::cout << ans_a << "\n";
        std::cout << ans_b << "\n";
        return 0;
}

