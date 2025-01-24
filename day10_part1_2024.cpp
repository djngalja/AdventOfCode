#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>

struct Coordinates { int x; int y; };
bool operator<(const Coordinates&, const Coordinates&);

void day10_part1();
bool read_input(const std::string&, std::vector<std::vector<int>>&);
std::vector<Coordinates> find_trailheads(const std::vector<std::vector<int>>&);
void find_trails(const std::vector<std::vector<int>>&,
                 Coordinates, std::set<Coordinates>&,
                 int&, int height = 0);


int main() {
    day10_part1();
    return 0;
}


void day10_part1() {
    std::vector<std::vector<int>> topo_map;
    if (read_input("input.txt", topo_map)) {
        std::vector<Coordinates> trailheads = find_trailheads(topo_map);
        int ttl_score {};
        for (const auto& pos : trailheads) {
            std::set<Coordinates> visited;
            find_trails(topo_map, pos, visited, ttl_score);
        }
    std::cout << "The sum of the scores of all trailheads: " << ttl_score << '\n';
    }
}

bool operator<(const Coordinates& c1, const Coordinates& c2) {
    return std::tie(c1.x, c1.y) < std::tie(c2.x, c2.y);
}

bool read_input(const std::string& f_name, std::vector<std::vector<int>>& topo_map) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return false;
    }
    std::string input_str;
    while(getline(file, input_str)) {
        std::vector<int> temp_vec;
        for (char c : input_str) {
            temp_vec.push_back(c-'0');
        }
        topo_map.push_back(temp_vec);
    }
    return true;
}

std::vector<Coordinates> find_trailheads(const std::vector<std::vector<int>>& topo_map) {
    std::vector<Coordinates> trailheads;
    for (std::size_t i=0; i<topo_map.size(); ++i) {
        for (std::size_t j=0; j<topo_map[i].size(); ++j) {
            if (topo_map[i][j] == 0) {
                Coordinates temp;
                temp.x = i;
                temp.y = j;
                trailheads.push_back(temp);
            }
        }
    }
    return trailheads;
}

void find_trails(const std::vector<std::vector<int>>& topo_map,
                 Coordinates pos, std::set<Coordinates>& visited,
                 int& ttl_score, int height) {
    if (height == 9) {
        if (visited.find(pos) != visited.end()) { return; }
        visited.insert(pos);
        ttl_score++;
        return;
    }
    const std::vector<Coordinates> adjustments { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
    const int map_size_x = topo_map.size();
    const int map_size_y = topo_map[0].size();
    for (Coordinates adj : adjustments) {
        Coordinates new_pos {pos.x + adj.x, pos.y + adj.y};
        if (
            ((new_pos.x >= 0) && (new_pos.x < map_size_x) &&
            (new_pos.y >= 0) && (new_pos.y < map_size_y)) &&
            (topo_map[new_pos.x][new_pos.y] - topo_map[pos.x][pos.y] == 1)
            ) {
            find_trails(topo_map, new_pos, visited, ttl_score, topo_map[new_pos.x][new_pos.y]);
            }
    }
}