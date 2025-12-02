#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

struct Range
{
    long start;
    long end;
};

std::vector<Range> read_input()
{
    std::ifstream stream("input.txt");
    std::vector<Range> ranges;
    std::string line;
    std::getline(stream, line);
    std::stringstream line_ss(line);
    std::string range_s;

    while (getline(line_ss, range_s, ',')) {
        std::stringstream id_ss(range_s);
        std::string token;

        std::getline(id_ss, token, '-');
        long start = std::stol(token);

        std::getline(id_ss, token);
        long end = std::stol(token);

        ranges.push_back({ start, end });
    }

    return ranges;
}

bool is_invalid_v1(long x)
{
    auto s = std::to_string(x);
    int n = s.size();

    if (n % 2) {
        return false;
    }

    return s.substr(0, n / 2) == s.substr(n / 2, n / 2);
}

long solve_part1(std::vector<Range>& ranges)
{
    long checksum = 0;

    for (auto& [start, end] : ranges) {
        for (long x = start; x <= end; x++) {
            if (is_invalid_v1(x)) {
                checksum += x;
            }
        }
    }

    return checksum;
}

bool is_invalid_v2(long x)
{
    auto s = std::to_string(x);
    int n = s.size();

    for (int i = 1; i <= n / 2; i++) {
        auto sample = s.substr(0, i);
        bool success = true;

        for (int j = i; j < n; j += i) {
            if (sample != s.substr(j, i)) {
                success = false;
                break;
            }
        }

        if (success) {
            return true;
        }
    }

    return false;
}

long solve_part2(std::vector<Range>& ranges)
{
    long checksum = 0;

    for (auto& [start, end] : ranges) {
        for (long x = start; x <= end; x++) {
            if (is_invalid_v2(x)) {
                checksum += x;
            }
        }
    }

    return checksum;
}

int main()
{
    std::vector<Range> ranges = read_input();

    std::cout << "part1: " << solve_part1(ranges) << std::endl;
    std::cout << "part2: " << solve_part2(ranges) << std::endl;

    return 0;
}
