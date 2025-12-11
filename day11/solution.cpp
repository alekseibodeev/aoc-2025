#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

std::unordered_map<std::string, std::vector<std::string>> read_input()
{
    std::unordered_map<std::string, std::vector<std::string>> g;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream ss(line);
        std::string x;
        std::string y;

        std::getline(ss, x, ':');
        std::getline(ss, y, ' '); // skip leading space

        while (std::getline(ss, y, ' ')) {
            g[x].push_back(y);
        }
    }

    return g;
}

long count_paths(std::unordered_map<std::string, std::vector<std::string>>& g,
                 std::string x,
                 std::string y,
                 std::unordered_map<std::string, long>& cache)
{
    if (x == y) {
        return 1;
    }
    if (cache[x] > 0) {
        return cache[x];
    }
    if (cache[x] < 0) {
        return 0;
    }

    long total = 0;

    for (auto& z : g[x]) {
        total += count_paths(g, z, y, cache);
    }

    if (total == 0) {
        cache[x] = -1;
        return 0;
    }

    cache[x] = total;
    return total;
}

int solve_part1(std::unordered_map<std::string, std::vector<std::string>>& g)
{
    std::unordered_map<std::string, long> cache;
    return count_paths(g, "you", "out", cache);
}

std::unordered_map<std::string, std::vector<std::string>> remove_nodes(
    std::unordered_map<std::string, std::vector<std::string>>& g,
    std::vector<std::string> ignore)
{
    std::unordered_map<std::string, std::vector<std::string>> gp;

    for (auto& [x, neighbors] : g) {
        if (std::find(ignore.begin(), ignore.end(), x) != ignore.end()) {
            continue;
        }

        for (auto& y : neighbors) {
            if (std::find(ignore.begin(), ignore.end(), x) == ignore.end()) {
                gp[x].push_back(y);
            }
        }

    }

    return gp;
}

long solve_part2(std::unordered_map<std::string, std::vector<std::string>>& g)
{
    auto g_no_fft = remove_nodes(g, { "fft" });
    auto g_no_dac = remove_nodes(g, { "dac" });
    auto g_no_fft_no_dac = remove_nodes(g, { "fft", "dac" });
    long total, no_fft, no_dac, no_fft_no_dac;

    {
        std::unordered_map<std::string, long> cache;
        total = count_paths(g, "svr", "out", cache);
    }

    {
        std::unordered_map<std::string, long> cache;
        no_fft = count_paths(g_no_fft, "svr", "out", cache);
    }

    {
        std::unordered_map<std::string, long> cache;
        no_dac = count_paths(g_no_dac, "svr", "out", cache);
    }

    {
        std::unordered_map<std::string, long> cache;
        no_fft_no_dac = count_paths(g_no_fft_no_dac, "svr", "out", cache);
    }

    return total - (no_fft + no_dac - no_fft_no_dac);
}

int main()
{
    auto g = read_input();

    std::cout << "part1: " << solve_part1(g) << std::endl;
    std::cout << "part2: " << solve_part2(g) << std::endl;

    return 0;
}
