#pragma once

#include "../Day.h"

#include <regex>
#include <sstream>

class Day3 : public Day<std::string> {
public:
    auto num() const -> int override {
        return 3;
    }

    auto example_input_str1() const -> std::stringstream override {
        return std::stringstream(R"(xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5)))");
    }

    auto example_input_str2() const -> std::stringstream override {
        return std::stringstream(R"(xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5)))");
    }

    auto parse_input(std::basic_istream<char> &input_str) const -> Input override {
        return {std::istreambuf_iterator<char>(input_str), {}};
    }

    auto part1(const Input &input) const -> int override {
        std::regex re(R"(mul\((\d+),(\d+)\))");
        std::smatch match;
        auto str = input;
        auto sum = 0;
        for(;std::regex_search(str, match, re);) {
            const auto num1 = std::stoi(match[1].str());
            const auto num2 = std::stoi(match[2].str());
            sum += num1 * num2;
            str = match.suffix();
        }
        return sum;
    }

    auto part2(const Input &input) const -> int override {
        std::regex re(R"((?:mul\((\d+),(\d+)\))|(?:do\(\))|(?:don't\(\)))");
        std::smatch match;
        auto str = input;
        auto sum = 0;
        bool enabled = true;
        for(;std::regex_search(str, match, re);) {
            auto match_str = match[0].str();
            if (match_str == "do()") {
                enabled = true;
                str = match.suffix();
                continue;
            }
            if (match_str == "don't()") {
                enabled = false;
                str = match.suffix();
                continue;
            }
            if (!enabled) {
                str = match.suffix();
                continue;
            }
            const auto num1 = std::stoi(match[1].str());
            const auto num2 = std::stoi(match[2].str());
            sum += num1 * num2;
            str = match.suffix();
        }
        return sum;
    }
};