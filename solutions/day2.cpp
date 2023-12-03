#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

const unordered_map<string, int> cubes = {
        {"blue", 14},
        {"green", 13},
        {"red", 12},
};

//part a
bool valid_set(const string& str) {
        istringstream set(str);
        string cube_info;
        while (getline(set, cube_info, ',')) {
                istringstream cube_stream(cube_info);
                cube_stream >> ws;
                string num;
                getline(cube_stream, num, ' ');
                string color;
                getline(cube_stream, color, ' ');
                if (cubes.at(color) < stoi(num)) {
                        return false;
                }
        }
        return true;
}

int parse_line(const string& str) {
        auto colon = str.find(':', 5);
        istringstream sets(str.substr(colon+1));
        string set;

        while (getline(sets, set, ';')) {
                if (!valid_set(set)) 
                        return 0;
        }
        int id = stoi(str.substr(5, colon));
        return id;
}

//part b
void min_set(const string& str, unordered_map<string, int>& game_cubes) {
        istringstream set(str);
        string cube_info;
        while (getline(set, cube_info, ',')) {
                istringstream cube_stream(cube_info);
                cube_stream >> ws;
                string num;
                getline(cube_stream, num, ' ');
                string color;
                getline(cube_stream, color, ' ');
                game_cubes[color] = max(game_cubes[color], stoi(num));
        }
}

long long power_line(const string& str) {
        auto colon = str.find(':', 5);
        istringstream sets(str.substr(colon+1));
        string set;
        unordered_map<string, int> game_cubes;
        while (getline(sets, set, ';')) {
                min_set(set, game_cubes);
        }
        long long power = 1;
        for (auto [key, value]: game_cubes) {
                power *= value;
        }
        return power;
}
int main() {
        ifstream input("../inputs/input2.txt");
        long long ans_a = 0;
        long long ans_b = 0;
        string line;
        while (getline(input, line)) {
                ans_a += parse_line(line);
                ans_b += power_line(line);
        }
        std::cout << ans_a << " " << ans_b;
        return 0;
}
