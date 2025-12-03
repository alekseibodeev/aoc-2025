#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::vector<std::vector<int>> read_input()
{
    std::ifstream stream("input.txt");
    std::vector<std::vector<int>> banks;
    std::string s;

    while (std::getline(stream, s)) {
        std::vector<int> bank;

        for (auto c : s) {
            bank.push_back(c - '0');
        }

        banks.push_back(bank);
    }

    return banks;
}

long get_total(std::vector<std::vector<int>>& banks, int required)
{
    long total = 0;

    for (auto& bank : banks) {
        std::vector<int> draft(required);
        int n = bank.size();

        for (int i = 0; i < n; i++) {
            int j = required - std::min(required, n - i);

            for (; j < required; j++) {
                if (bank[i] > draft[j]) {
                    draft[j++] = bank[i];
                    break;
                }
            }

            for (; j < required; j++) {
                draft[j] = 0;
            }
        }

        long joltage = 0;

        for (int i = 0; i < required; i++) {
            joltage = joltage * 10 + draft[i];
        }

        total += joltage;
    }

    return total;
}

long solve_part1(std::vector<std::vector<int>>& banks)
{
    return get_total(banks, 2);
}

long solve_part2(std::vector<std::vector<int>>& banks)
{
    return get_total(banks, 12);
}

int main()
{
    auto banks = read_input();

    std::cout << "part1: " << solve_part1(banks) << std::endl;
    std::cout << "part2: " << solve_part2(banks) << std::endl;

    return 0;
}
