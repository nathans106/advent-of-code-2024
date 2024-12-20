#pragma once

#include "../Day.h"

#include <ranges>
#include <vector>

constexpr std::array<char, 4> TARGET({'X', 'M', 'A', 'S'});

struct Point {
    int x;
    int y;
};

auto operator+(const Point& lhs, const Point& rhs) -> Point {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

auto operator*(const Point& lhs, int rhs) -> Point {
    return {lhs.x * rhs, lhs.y * rhs};
}

class Crossword {
public:
    Crossword(std::vector<std::string>&& data) : m_data(std::move(data)) {}

    auto at(const Point& point) const -> std::optional<char> {
        if (point.x < 0 || point.x >= m_data.size()) {
            return std::nullopt;
        }
        const auto row = m_data[point.x];
        if (point.y < 0 || point.y >= row.size()) {
            return std::nullopt;
        }
        return row[point.y];
    }

    auto csize() const -> std::size_t {
        return m_data.size();
    }

    auto col(const std::size_t i) const -> std::string {
        return m_data[i];
    }

private:
    std::vector<std::string> m_data;
};

class Day4 : public Day<Crossword> {
public:
    auto num() const -> int override {
        return 4;
    }

    auto example_input_str1() const -> std::stringstream override {
        return std::stringstream(R"(MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX)");
    }

    auto parse_input(std::basic_istream<char> &input_str) const -> Input override {
        std::vector<std::string> input;
        std::string line;
        while(std::getline(input_str, line)) {
            input.push_back(line);
        }
        return input;
    }

    auto part1(const Input &input) const -> int override {
        std::size_t xmas_count = 0;
        for (auto x = 0; x < input.csize(); ++x) {
            const auto& line = input.col(x);
            for (auto y = 0; y < line.size(); ++y) {
                const Point point(x, y);
                auto directions = std::vector<Point>({{0, 1}, {1,1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}});

                for (auto [multiplier, target_c] : TARGET | std::ranges::views::enumerate) {
                    std::vector<Point> new_directions;
                    for (const auto& dir : directions) {
                        auto new_point = point + (dir * static_cast<int>(multiplier));
                        auto new_c = input.at(new_point);
                        if (new_c.has_value() && new_c == target_c) {
                            new_directions.push_back(dir);
                        }
                    }
                    directions = new_directions;
                }
                xmas_count += directions.size();
            }
        }

        return xmas_count;
    }

    auto part2(const Input &input) const -> int override {
        std::size_t xmas_count = 0;
        for (auto x = 0; x < input.csize(); ++x) {
            const auto& line = input.col(x);
            for (auto y = 0; y < line.size(); ++y) {
                const Point point(x, y);

                const auto c = input.at(point).value();
                if (c != 'A') {
                    continue;
                }

                int m_count = 0;
                int s_count = 0;
                const auto directions = std::vector<Point>({{1,1}, {1, -1}, {-1, -1}, {-1, 1}});
                for (const auto& dir : directions) {
                    auto new_point = point + dir;
                    auto new_c = input.at(new_point);
                    if (new_c.has_value() && new_c == 'M') {
                        m_count++;
                    }
                    if (new_c.has_value() && new_c == 'S') {
                        s_count++;
                    }
                }

                if (m_count == 2 && s_count == 2) {
                    xmas_count++;
                }
            }
        }

        return xmas_count;
    }

};