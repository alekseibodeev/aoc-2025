#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

std::vector<std::string> read_lines()
{
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(std::cin, line)) {
        lines.push_back(line);
    }

    return lines;
}

int solve_part1(std::vector<std::string>& lines)
{
    std::unordered_set<int> beams;
    int count = 0;

    for (int i = 0; i < lines[0].size(); i++) {
        if (lines[0][i] == 'S') {
            beams.insert(i);
            break;
        }
    }

    for (int i = 1; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == '^' && beams.contains(j)) {
                if (j - 1 >= 0) {
                    beams.insert(j - 1);
                }
                if (j + 1 < lines[i].size()) {
                    beams.insert(j + 1);
                }
                beams.erase(j);
                count++;
            }
        }
    }

    return count;
}

long solve_part2(std::vector<std::string>& lines)
{
    int m = lines.size();
    int n = lines[0].size();
    std::vector<std::vector<long>> dp(m, std::vector<long>(n));

    for (auto& x : dp.back()) {
        x = 1;
    }

    for (int i = dp.size() - 2; i >= 0; i--) {
        for (int j = 0; j < dp[i].size(); j++) {
            if (lines[i][j] == '^') {
                long l = j - 1 >= 0 ? dp[i + 1][j - 1] : 0;
                long r = j + 1 < n ? dp[i + 1][j + 1] : 0;
                dp[i][j] = l + r;
            } else {
                dp[i][j] = dp[i + 1][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (lines[0][i] == 'S') {
            return dp[0][i];
        }
    }

    return -1;
}

int main()
{
    auto lines = read_lines();

    std::cout << "part1: " << solve_part1(lines) << std::endl;
    std::cout << "part2: " << solve_part2(lines) << std::endl;

    return 0;
}
