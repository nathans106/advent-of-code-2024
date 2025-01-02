#pragma once

#include "../Day.h"

#include <list>
#include <regex>
#include <vector>

struct Equation {
    long long result;
    std::vector<int> operands;
};

class Day7Parser : public InputParser<std::vector<Equation>> {
    void parse_line(const std::string &line) override {
        const auto colon_pos = line.find(':');
        const auto result_str = line.substr(0, colon_pos);
        const auto result = std::stoll(result_str);
        auto operand_str = line.substr(colon_pos + 1, line.size() - colon_pos);

        std::vector<int> operands;
        std::regex re(R"(\d+)");
        for(std::smatch match; std::regex_search(operand_str, match, re);) {
            operands.push_back(std::stoi(match.str()));
            operand_str = match.suffix();
        }

        m_result.push_back(Equation{result, operands});
    }

    std::vector<Equation> get_input() override {
        return m_result;
    }

    Input m_result;
};

bool is_valid1(const Equation& equation) {
    std::list<long long> possible_values = {0};
    for(const auto operand : equation.operands) {
        std::list<long long> new_possible_values;
        for (const auto old_value : possible_values) {
            new_possible_values.push_back(old_value + operand);
            new_possible_values.push_back(old_value * operand);
        }
        possible_values = new_possible_values;
    }

    for(const auto potential_result: possible_values) {
        if (potential_result == equation.result) {
            return true;
        }
    }

    return false;
}

bool is_valid2(const Equation& equation) {
    std::list<long long> possible_values = {0};
    for(const auto operand : equation.operands) {
        std::list<long long> new_possible_values;
        for (const auto old_value : possible_values) {
            new_possible_values.push_back(old_value + operand);
            new_possible_values.push_back(old_value * operand);
            std::stringstream conc_str;
            conc_str << old_value;
            conc_str << operand;
            new_possible_values.push_back(std::stoll(conc_str.str()));
        }
        possible_values = new_possible_values;
    }

    for(const auto potential_result: possible_values) {
        if (potential_result == equation.result) {
            return true;
        }
    }

    return false;
}

class Day7 : public Day<Day7Parser> {
public:
    auto num() const -> int override {
        return 7;
    }

    auto example_input_str1() const -> std::stringstream override {
        return std::stringstream(R"(190: 10 19
3267: 81 40 27
83: 17 5
156: 15 6
7290: 6 8 6 15
161011: 16 10 13
192: 17 8 14
21037: 9 7 18 13
292: 11 6 16 20)");
    }

    auto part1(const Input &input) const -> long long override {
        long long result = 0;
        for (const auto& equation: input) {
            if (is_valid1(equation)) {
                result += equation.result;
            }
        }
        return result;
    }

    auto part2(const Input &input) const -> long long override {
        long long result = 0;
        for (const auto& equation: input) {
            if (is_valid2(equation)) {
                result += equation.result;
            }
        }
        return result;
    }
};
