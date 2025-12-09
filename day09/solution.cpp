#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

std::vector<std::pair<int, int>> read_input()
{
    std::vector<std::pair<int, int>> tiles;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        int x = std::stoi(token);

        std::getline(ss, token, ',');
        int y = std::stoi(token);

        tiles.push_back({ x, y });
    }

    return tiles;
}

long solve_part1(std::vector<std::pair<int, int>>& tiles)
{
    long area = 0;

    for (int i = 0; i < tiles.size(); i++) {
        for (int j = i + 1; j < tiles.size(); j++) {
            int dx = std::abs(tiles[i].first - tiles[j].first) + 1;
            int dy = std::abs(tiles[i].second - tiles[j].second) + 1;

            area = std::max(area, long(dx) * long(dy));
        }
    }

    return area;
}

long solve_part2(std::vector<std::pair<int, int>>& tiles)
{
    return 0L;
}

int main()
{
    auto tiles = read_input();

    std::cout << "part1: " << solve_part1(tiles) << std::endl;
    std::cout << "part2: " << solve_part2(tiles) << std::endl;

    return 0;
}
