#include <cctype>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <utility>

std::vector<std::string> read_lines()
{
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(std::cin, line)) {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::vector<int>> get_nums_v1(std::vector<std::string>& lines)
{
    std::vector<std::vector<int>> nums;

    for (int i = 0; i < lines.size() - 1; i++) {
        std::istringstream ss(lines[i]);
        std::string token;
        int n = 0;

        while (std::getline(ss, token, ' ')) {
            if (token.empty()) {
                continue;
            }

            if (n == nums.size()) {
                nums.push_back({});
            }

            nums[n++].push_back(std::stoi(token));

        }
    }

    return nums;
}


std::vector<std::pair<int, int>> get_ranges(std::string& ops)
{
    std::vector<std::pair<int, int>> ranges;
    int start = 0;

    for (int i = 1; i < ops.size(); i++) {
        if (ops[i] != ' ') {
            ranges.push_back({ start, i - 1 });
            start = i;
        }
    }

    ranges.push_back({ start, ops.size() });
    return ranges;
}

std::vector<std::vector<int>> get_nums_v2(
        std::vector<std::string>& lines,
        std::vector<std::pair<int, int>>& ranges)
{
    std::vector<std::vector<int>> nums;

    for (auto& range : ranges) {
        nums.push_back(std::vector<int>(range.second - range.first));
    }

    for (int i = 0; i < lines.size() - 1; i++) {
        for (int j = 0; j < ranges.size(); j++) {
            int n = 0;

            for (int k = ranges[j].first; k < ranges[j].second; k++, n++) {
                if (lines[i][k] == ' ') {
                    continue;
                }
                nums[j][n] = nums[j][n] * 10 + lines[i][k] - '0';
            }
        }
    }

    return nums;
}

std::vector<char> get_ops(std::string& ops_str)
{
    std::vector<char> ops;

    for (auto c : ops_str) {
        if (c != ' ') {
            ops.push_back(c);
        }
    }

    return ops;
}

long add(std::vector<int>& nums)
{
    long total = 0;

    for (auto num : nums) {
        total += num;
    }

    return total;
}

long mul(std::vector<int>& nums)
{
    long total = 1;

    for (auto num : nums) {
        total *= num;
    }

    return total;
}

long calc(std::vector<int>& nums, char op)
{
    if (op == '+') {
        return add(nums);
    }

    return mul(nums);
}

long solve_part1(std::vector<std::string>& lines, std::vector<char>& ops)
{
    auto nums = get_nums_v1(lines);
    long total = 0;

    for (int i = 0; i < ops.size(); i++) {
        total += calc(nums[i], ops[i]);
    }

    return total;
}

long solve_part2(std::vector<std::string>& lines, std::vector<char>& ops)
{
    auto ranges = get_ranges(lines.back());
    auto nums = get_nums_v2(lines, ranges);
    long total = 0;

    for (int i = 0; i < ops.size(); i++) {
        total += calc(nums[i], ops[i]);
    }

    return total;
}

int main()
{
    auto lines = read_lines();
    auto ops = get_ops(lines.back());

    std::cout << "part1: " << solve_part1(lines, ops) << std::endl;
    std::cout << "part2: " << solve_part2(lines, ops) << std::endl;

    return 0;
}
