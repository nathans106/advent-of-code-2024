#pragma once

#include "../Day.h"

#include <map>
#include <ranges>
#include <regex>
#include <set>
#include <vector>

struct PrintInstructions {
    std::multimap<int, int> ordering;
    std::vector<std::vector<int>> updates;
};

class Day5Parser : public InputParser<PrintInstructions> {
    void parse_line(const std::string &line) override {
        if (line.empty()) {
            m_is_ordering = false;
            return;
        }

        if (m_is_ordering) {
            parse_ordering(line);
        } else {
            parse_update(line);
        }
    }

    PrintInstructions get_input() override {
        return m_input;
    }

    void parse_ordering(const std::string& line) {
        const auto separator = line.find('|');
        const auto first = std::stoi(line.substr(0, separator));
        const auto second = std::stoi(line.substr(separator + 1));
        m_input.ordering.insert({second, first});
    }

    void parse_update(std::string line) {
        std::vector<int> update;
        std::regex re(R"(\d+)");
        for(std::smatch match; std::regex_search(line, match, re);) {
            update.push_back(std::stoi(match.str()));
            line = match.suffix();
        }
        m_input.updates.push_back(update);
    }

    bool m_is_ordering = true;
    PrintInstructions m_input;
};

bool is_valid(const std::vector<int>& update, const std::multimap<int, int>& ordering) {
    std::set remaining(update.begin(), update.end());
    for(const auto page : update) {
        const auto [order_begin, order_end] = ordering.equal_range(page);
        for (auto order_page = order_begin; order_page != order_end; ++order_page) {
            if (remaining.contains(order_page->second)) {
                return false;
            }
        }
        remaining.erase(page);
    }
    return true;
}

class Day5 : public Day<Day5Parser> {
public:
    auto num() const -> int override {
        return 5;
    }

    auto example_input_str1() const -> std::stringstream override {
        return std::stringstream(R"(47|53
97|13
97|61
97|47
75|29
61|13
75|53
29|13
97|29
53|29
61|53
97|53
61|29
47|13
75|47
97|75
47|61
75|61
47|29
75|13
53|13

75,47,61,53,29
97,61,53,29,13
75,29,13
75,97,47,61,53
61,13,29
97,13,75,29,47)");
    }

    auto part1(const Input &input) const -> int override {
        auto sum = 0;
        for (const auto& update : input.updates) {
            if (is_valid(update, input.ordering)) {
                const auto middle_value = update[update.size() / 2];
                sum += middle_value;
            }
        }
        return sum;
    }

    auto part2(const Input &input) const -> int override {
        return 0;
    }

};
