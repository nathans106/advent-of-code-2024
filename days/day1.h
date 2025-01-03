#pragma once

#include "../Day.h"
#include "../input_parser.h"

#include <algorithm>
#include <array>
#include <ranges>
#include <regex>
#include <vector>
#include <utility>


class Day1Parser : public InputParser<std::array<std::vector<int>, 2>> {
    void parse_line(const std::string& line) override {
        auto re_line = line;
        std::regex re(R"(\d+)");
        auto i = 0;
        for (std::smatch match; std::regex_search(re_line, match, re);) {
            assert(i < 2);
            m_input[i++].push_back(std::stoi(match.str()));
            re_line = match.suffix();
        }
    }

    Input get_input() override {
        return m_input;
    }

    Input m_input;
};

class Day1 : public Day<Day1Parser> {
public:
    auto num() const -> int override {
        return 1;
    }

    auto example_input_str1() const -> std::stringstream override {
        return std::stringstream(R"(3   4
4   3
2   5
1   3
3   9
3   3)");
    }

    auto part1(const Input &input) const -> long long override {
        auto in1 = input[0];
        auto in2 = input[1];
        std::ranges::sort(in1);
        std::ranges::sort(in2);
        auto distances = std::ranges::views::zip(in1, in2) | std::ranges::views::transform([](const std::pair<int, int> &pair) -> int {
            return std::abs(std::get<0>(pair) - std::get<1>(pair));
        });
        return std::ranges::fold_left(distances, 0, std::plus{});
    }

    auto part2(const Input &input) const -> long long override {
        auto in1 = input[0];
        auto in2 = input[1];
        std::map<int, int> frequencies;
        for (auto val : in2) {
            if (frequencies.find(val) == frequencies.end()) {
                frequencies[val] = 1;
            } else {
                frequencies[val]++;
            }
        }

        const auto similarities = in1 | std::ranges::views::transform([&frequencies](int val) -> int {
            if (frequencies.find(val) != frequencies.end()) {
                return frequencies[val] * val;
            } else {
                return 0;
            }
        });

        return std::ranges::fold_left(similarities, 0, std::plus{});
    }

};
