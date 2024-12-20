#pragma once

#include "../Day.h"

#include <ranges>
#include <regex>
#include <sstream>
#include <vector>

auto is_safe(const std::vector<int> &report) -> std::optional<int> {
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

class Day2 : public Day<std::vector<std::vector<int>>> {
using Input = std::vector<std::vector<int>>;

public:
    auto num() const -> int override {
        return 2;
    }

    auto example_input_str() const -> std::stringstream override {
        return std::stringstream(R"(7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9)");
    }

    auto parse_input(std::basic_istream<char> &input_str) const -> Input override {
        Input input;
        std::string line;
        while(std::getline(input_str, line)) {
            std::vector<int> line_vec;
            std::regex re(R"(\d+)");
            auto i = 0;
            for (std::smatch match; std::regex_search(line, match, re);) {
                line_vec.push_back(std::stoi(match.str()));
                line = match.suffix();
            }
            input.push_back(line_vec);
        }
        return input;
    }

    auto part1(const Input &input) const -> int override {
        int num_safe = 0;

        for (const auto &report : input) {
            if (!is_safe(report).has_value()) {
                num_safe++;
            }
        }

        return num_safe;
    }

    auto part2(const Input &input) const -> int override {
        int num_safe = 0;

        for (const auto &report : input) {
            const auto failing_index = is_safe(report);
            if (failing_index.has_value()) {
                auto new_report = report;
                new_report.erase(new_report.begin() + failing_index.value());
                if (!is_safe(new_report).has_value()) {
                    num_safe++;
                    continue;
                }
                new_report = report;
                new_report.erase(new_report.begin() + failing_index.value() + 1);
                if (!is_safe(new_report).has_value()) {
                    num_safe++;
                    continue;
                }
                if (failing_index.value() > 0) {
                    new_report = report;
                    new_report.erase(new_report.begin() + failing_index.value() - 1);
                    if (!is_safe(new_report).has_value()) {
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
