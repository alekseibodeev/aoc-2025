#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct Range
{
    long start;
    long end;
};

void read_input(std::vector<Range>& ranges,
                std::vector<long>& ids)
{
    std::ifstream stream("input.txt");
    std::string line;

    while (std::getline(stream, line) && line.size() > 0) {
        int i = line.find('-');
        long start = std::stol(line.substr(0, i));
        long end = std::stol(line.substr(i + 1));
        ranges.push_back({ start, end });
    }

    while (std::getline(stream, line)) {
        ids.push_back(std::stol(line));
    }
}

void merge_ranges(std::vector<Range>& ranges)
{
    int i = 0;

    for (int j = 1; j < ranges.size(); j++) {
        if (ranges[i].end >= ranges[j].start) {
            ranges[i].end = std::max(ranges[i].end, ranges[j].end);
        } else {
            i++;
            ranges[i].start = ranges[j].start;
            ranges[i].end = ranges[j].end;
        }
    }

    ranges.resize(i + 1);
}

bool isfresh(std::vector<Range>& ranges, long id)
{
    int l = 0;
    int r = ranges.size() - 1;

    while (l <= r) {
        int m = (l + r) / 2;

        if (id >= ranges[m].start && id <= ranges[m].end) {
            return true;
        }
        if (id < ranges[m].start) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return false;
}

int solve_part1(std::vector<Range>& ranges, std::vector<long>& ids)
{
    int count = 0;

    for (auto id : ids) {
        if (isfresh(ranges, id)) {
            count++;
        }
    }

    return count;
}

long solve_part2(std::vector<Range>& ranges)
{
    long count = 0;

    for (auto& [start, end] : ranges) {
        count += end - start + 1;
    }

    return count;
}

int main()
{
    std::vector<Range> ranges;
    std::vector<long> ids;

    read_input(ranges, ids);
    std::sort(ranges.begin(), ranges.end(), [](auto a, auto b) {
        return a.start < b.start;
    });
    merge_ranges(ranges);

    std::cout << "part1: " << solve_part1(ranges, ids) << std::endl;
    std::cout << "part2: " << solve_part2(ranges) << std::endl;

    return 0;
}
