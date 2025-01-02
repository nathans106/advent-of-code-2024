#pragma once

#include "../Day.h"

#include <ranges>
#include <regex>
#include <sstream>
#include <vector>

class Day2Parser : public InputParser<std::vector<std::vector<int>>> {
    void parse_line(const std::string &line) override {
        auto re_line = line;
        std::vector<int> line_vec;
        std::regex re(R"(\d+)");
        for (std::smatch match; std::regex_search(re_line, match, re);) {
            line_vec.push_back(std::stoi(match.str()));
            re_line = match.suffix();
        }
        m_input.push_back(line_vec);
    }

    Input get_input() override {
        return m_input;
    }

    Input m_input;
};

auto first_unsafe_level(const std::vector<int> &report) -> std::optional<int> {
    std::optional<bool> is_positive = std::nullopt;
    int i = 0;
    for (const auto &[level1, level2] : report | std::ranges::views::pairwise) {
        const auto diff = level1 - level2;
        const auto abs_diff = std::abs(diff);
        if (abs_diff < 1) {
            return i;
        }
        if (abs_diff > 3) {
            return i;
        }
        if (is_positive.has_value()) {
            if (is_positive.value() != (diff > 0)) {
                return i;
            }
        } else {
            is_positive = diff > 0;
        }
        i++;
    }
    return std::nullopt;
}

class Day2 : public Day<Day2Parser> {
public:
    auto num() const -> int override {
        return 2;
    }

    auto example_input_str1() const -> std::stringstream override {
        return std::stringstream(R"(7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9)");
    }

    auto part1(const Input &input) const -> long long override {
        int num_safe = 0;

        for (const auto &report : input) {
            if (!first_unsafe_level(report).has_value()) {
                num_safe++;
            }
        }

        return num_safe;
    }

    auto part2(const Input &input) const -> long long override {
        int num_safe = 0;

        for (const auto &report : input) {
            const auto failing_index = first_unsafe_level(report);
            if (failing_index.has_value()) {
                auto new_report = report;
                new_report.erase(new_report.begin() + failing_index.value());
                if (!first_unsafe_level(new_report).has_value()) {
                    num_safe++;
                    continue;
                }
                new_report = report;
                new_report.erase(new_report.begin() + failing_index.value() + 1);
                if (!first_unsafe_level(new_report).has_value()) {
                    num_safe++;
                    continue;
                }
                if (failing_index.value() > 0) {
                    new_report = report;
                    new_report.erase(new_report.begin() + failing_index.value() - 1);
                    if (!first_unsafe_level(new_report).has_value()) {
                        num_safe++;
                        continue;
                    }
                }
            } else {
                num_safe++;
            }
        }

        return num_safe;
    }
};
