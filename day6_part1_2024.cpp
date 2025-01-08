#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Position {
    int x;
    int y;
};

bool read_map(const std::string&, std::vector<std::vector<char>>&);
Position find_guard(const std::vector<std::vector<char>>&);
void turn_right(Position&);
void move_guard(Position&, const std::vector<std::vector<char>>&, std::vector<std::vector<int>>&);
int count_distinct_pos(std::vector<std::vector<int>>&);
void day6_part1();


int main() {
    day6_part1();
    return 0;
}


void day6_part1() {
    std::vector<std::vector<char>> vec;
    if (read_map("advent_day6.txt", vec)) {
        Position pos = find_guard(vec);
        std::vector<std::vector<int>> visited;
        move_guard(pos, vec, visited);
        std::cout << "The guard will visit " << count_distinct_pos(visited) << " distinct positions.\n";
    }
}

bool read_map(const std::string& f_name, std::vector<std::vector<char>>& vec) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File not found\n";
        return false;
    }
    std::string temp_str;
    while (getline(file, temp_str)) {
        std::vector<char> temp_vec;
        for (auto c : temp_str) {
            temp_vec.push_back(c);
        }
        vec.push_back(temp_vec);
    }
    return true;
}

void turn_right(Position& adj) {
    if (adj.x == -1) { // >East
        adj = {0, 1};
    } else if (adj.x == 1) { // >West
        adj = {0, -1};
    } else {
        if (adj.y == 1) { // >South
            adj = {1, 0};
        } else { // >North
            adj = {-1, 0};
        }
    }
}

void move_guard(Position& pos, const std::vector<std::vector<char>>& vec, std::vector<std::vector<int>>& visited) {
    int x_max = vec.size();
    int y_max = vec[0].size();
    Position adj {-1, 0}; // >North
    while ((pos.x + adj.x >= 0) && (pos.x + adj.x < x_max) &&
           (pos.y + adj.y >= 0) && (pos.y + adj.y < y_max)) {
        if (vec[pos.x + adj.x][pos.y + adj.y] == '#') {
            turn_right(adj);
        }
        pos.x += adj.x;
        pos.y += adj.y;
        visited.push_back({pos.x, pos.y});
    }
}

int count_distinct_pos(std::vector<std::vector<int>>& visited) {
    std::sort(visited.begin(), visited.end());
    auto it = unique(visited.begin(), visited.end());
    visited.erase(it, visited.end());
    return visited.size();
}


Position find_guard(const std::vector<std::vector<char>>& vec) {
    Position pos {0, 0};
    for (std::size_t i=0; i!=vec.size(); ++i) {
        for (std::size_t j=0; j!=vec[i].size(); ++j) {
            if (vec[i][j] == '^') {
                pos.x = i;
                pos.y = j;
                break;
            }
        }
    }
    return pos;
}