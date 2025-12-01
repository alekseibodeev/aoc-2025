#include <fstream>
#include <iostream>
#include <vector>

struct Rotation
{
    char direction;
    int distance;
};

std::vector<Rotation> read_input()
{
    std::vector<Rotation> rotations;
    std::ifstream stream("input.txt");
    char direction;
    int distance;

    while (stream >> direction >> distance) {
        rotations.push_back({ direction, distance });
    }

    return rotations;
}

int solve_part1(std::vector<Rotation>& rotations)
{
    int password = 0;
    int position = 50;

    for (auto& [direction, distance] : rotations) {
        if (direction == 'R') {
            position = (position + distance) % 100;
        } else {
            position = (100 + position - distance % 100) % 100;
        }
        if (position == 0) {
            password++;
        }
    }

    return password;
}

int solve_part2(std::vector<Rotation>& rotations)
{
    int password = 0;
    int position = 50;

    for (auto& [direction, distance] : rotations) {
        password += distance / 100;

        if (direction == 'R') {
            if (position && distance % 100 >= 100 - position) {
                password++;
            }

            position = (position + distance) % 100;
        } else {
            if (position && distance % 100 >= position) {
                password++;
            }

            position = (100 + position - distance % 100) % 100;
        }
    }

    return password;
}

int main()
{
    std::vector<Rotation> rotations = read_input();

    std::cout << "part1: " << solve_part1(rotations) << std::endl;
    std::cout << "part2: " << solve_part2(rotations) << std::endl;

    return 0;
}
