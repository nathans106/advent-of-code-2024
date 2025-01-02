#pragma once

#include "../Day.h"

#include <regex>
#include <sstream>

class Day3Parser : public InputParser<std::vector<std::string>> {
    void parse_line(const std::string &line) override {
        m_input.push_back(line);
    }

    Input get_input() override {
        return m_input;
    }

    Input m_input;
};

class Day3 : public Day<Day3Parser> {
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

    auto part1(const Input &input) const -> long long override {
        std::regex re(R"(mul\((\d+),(\d+)\))");
        std::smatch match;
        auto sum = 0;
        for (auto str : input) {
            for(;std::regex_search(str, match, re);) {
                const auto num1 = std::stoi(match[1].str());
                const auto num2 = std::stoi(match[2].str());
                sum += num1 * num2;
                str = match.suffix();
            }
        }
        return sum;
    }

    auto part2(const Input &input) const -> long long override {
        std::regex re(R"((?:mul\((\d+),(\d+)\))|(?:do\(\))|(?:don't\(\)))");
        std::smatch match;
        auto sum = 0;
        bool enabled = true;
        for (auto str : input) {
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
        }
        return sum;
    }
};