#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

int neighbors[8][2] = {
    {-1, -1}, {-1,  0}, {-1, 1}, {0, -1},
    { 0,  1}, { 1, -1}, { 1, 0}, {1,  1}
};

std::vector<std::string> read_input()
{
    std::ifstream stream("input.txt");
    std::vector<std::string> rolls;
    std::string line;

    while (std::getline(stream, line)) {
        rolls.push_back(line);
    }

    return rolls;
}

int count_neighbors(std::vector<std::string>& rolls, int i, int j)
{
    int m = rolls.size();
    int n = rolls[0].size();
    int count = 0;

    for (auto& nbr : neighbors) {
        int ni = i + nbr[0];
        int nj = j + nbr[1];

        if (std::min(ni, nj) >= 0 &&
            ni < m && nj < n &&
            rolls[ni][nj] == '@')
        {
            count++;
        }
    }

    return count;
}

int solve_part1(std::vector<std::string>& rolls)
{
    int m = rolls.size();
    int n = rolls[0].size();
    int accessible = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (rolls[i][j] == '@' && count_neighbors(rolls, i, j) < 4) {
                accessible++;
            }
        }
    }

    return accessible;
}

/* Count neighbors for each cell, cells with no roll have negative count */
std::vector<std::vector<int>> get_ncount(std::vector<std::string>& rolls)
{
    int m = rolls.size();
    int n = rolls[0].size();
    std::vector<std::vector<int>> ncount(m, std::vector<int>(n, -1));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (rolls[i][j] == '@') {
                ncount[i][j] = count_neighbors(rolls, i, j);
            }
        }
    }

    return ncount;
}

int solve_part2(std::vector<std::string>& rolls)
{
    auto ncount = get_ncount(rolls);
    int m = rolls.size();
    int n = rolls[0].size();
    int accessible = 0;
    std::queue<std::pair<int, int>> q;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (ncount[i][j] > -1 && ncount[i][j] < 4) {
                q.push({ i, j });
                ncount[i][j] = -1;
            }
        }
    }

    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        accessible++;

        for (auto nb : neighbors) {
            int ni = i + nb[0];
            int nj = j + nb[1];

            if (std::min(ni, nj) >= 0 &&
                ni < m && nj < n &&
                ncount[ni][nj] > -1)
            {
                ncount[ni][nj] = ncount[ni][nj] - 1;

                if (ncount[ni][nj] < 4) {
                    q.push({ ni, nj });
                    ncount[ni][nj] = -1;
                }
            }
        }
    }

    return accessible;
}

int main()
{
    auto rolls = read_input();

    std::cout << "part1: " << solve_part1(rolls) << std::endl;
    std::cout << "part2: " << solve_part2(rolls) << std::endl;

    return 0;
}
