#include <cctype>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

struct MachineManual {
    int diagram;
    std::vector<std::vector<int>> buttons;
    std::vector<int> joltage;
};

int get_diagram(std::string& s)
{
    int diagram = 0;

    for (int i = 1; i < s.size() - 1; i++) {
        if (s[i] == '#') {
            diagram |= 1 << (i - 1);
        }
    }

    return diagram;
}

std::vector<int> get_button(std::string& s)
{
    std::vector<int> button;

    for (int i = 1; i < s.size() - 1; i++) {
        if (isdigit(s[i])) {
            button.push_back(s[i] - '0');
        }
    }

    return button;
}

std::vector<int> get_joltage(std::string& s)
{
    std::vector<int> joltage;
    std::string line = s.substr(1, s.size() - 2);
    std::istringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ',')) {
        joltage.push_back(std::stoi(token));
    }

    return joltage;
}

std::vector<MachineManual> read_input()
{
    std::vector<MachineManual> manuals;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream ss(line);
        std::string token;
        MachineManual manual;

        while (std::getline(ss, token, ' ')) {
            if (token[0] == '[') {
                manual.diagram = get_diagram(token);
            } else if (token[0] == '(') {
                manual.buttons.push_back(get_button(token));
            } else {
                manual.joltage = get_joltage(token);
            }
        }

        manuals.push_back(manual);
    }

    return manuals;
}

int to_mask(std::vector<int>& button)
{
    int mask = 0;

    for (int n : button) {
        mask |= 1 << n;
    }

    return mask;
}

int count_presses(std::vector<std::vector<int>>& buttons,
                  int diagram,
                  int i = 0)
{
    if (diagram == 0) {
        return 0;
    }
    if (i == buttons.size()) {
        return 99; // big for actual input, but oveflow safe
    }

    int a = 1 + count_presses(buttons, diagram ^ to_mask(buttons[i]), i + 1);
    int b = count_presses(buttons, diagram, i + 1);

    return std::min(a, b);
}

int solve_part1(std::vector<MachineManual>& manuals)
{
    int total = 0;

    for (auto& manual : manuals) {
        total += count_presses(manual.buttons, manual.diagram);
    }

    return total;
}

void solve_part2()
{
}

int main()
{
    auto manuals = read_input();

    for (auto& manual : manuals) {
        std::cout << "variables: " << manual.buttons.size();
        std::cout << " -- euqations: " << manual.joltage.size() << std::endl;
    }

    std::cout << "part1: " << solve_part1(manuals) << std::endl;

    return 0;
}
