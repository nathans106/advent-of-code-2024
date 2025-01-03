#pragma once

#include "../Day.h"

#include <ranges>
#include <unordered_map>
#include <set>
#include <vector>

using Point = std::pair<long long, long long>;

using Antennas = std::unordered_multimap<char, Point>;

struct Map {
    Antennas antennas;
    long long x_size;
    long long y_size;
};

/*class Line {
    Line(const Point& p1, const Point& p2) : gradient((p1.first - p2.first) / (p1.second - p2.second)), intersect(p1.first - (gradient * p1.second)) {}

private:
    long long gradient;
    long long intersect;
};*/

std::optional<Point> calculate_antinode(const Point& p1, const Point& p2, const long long x_size, const long long y_size) {
    const auto dx = p2.first - p1.first;
    const auto dy = p2.second - p1.second;
    const Point loc{p2.first + dx, p2.second + dy};
    if (loc.first < 0 || loc.first >= x_size || loc.second < 0 || loc.second >= y_size) {
        return std::nullopt;
    }

    return loc;
}

class Day8Parser : public InputParser<Map> {
    void parse_line(const std::string &line) override {
        y_size = static_cast<long long>(line.size());
        for(const auto[y, c] : line | std::views::enumerate) {
            antennas.insert({c, std::make_pair(x, y)});
        }
        ++x;
    }

    Input get_input() override {
        return Map{antennas, x, y_size};
    }

    Antennas antennas;
    long long x = 0;
    long long y_size = 0;
};


std::set<Point> calculate_antinodes(const std::span<const Point> & points, const long long x_size, const long long y_size) {
    std::set<Point> antinodes;
    for (const auto& p1 : points) {
        for (const auto& p2 : points) {
            if (p1 == p2) {
                continue;
            }

            const auto n1 = calculate_antinode(p1, p2, x_size, y_size);
            if (n1.has_value()) {
                antinodes.insert(n1.value());
            }
            const auto n2 = calculate_antinode(p2, p1, x_size, y_size);
            if (n2.has_value()) {
                antinodes.insert(n2.value());
            }
        }
    }

    return antinodes;
}

class Day8 : public Day<Day8Parser> {
public:
    auto num() const -> int override {
        return 8;
    }

    auto example_input_str1() const -> std::stringstream override {
        return std::stringstream(R"(............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............)");
    }

    auto part1(const Input &map) const -> long long override {
        std::set<Point> antinodes;
        for (const auto c: map.antennas | std::views::keys) {
            auto [points_begin, points_end] = map.antennas.equal_range(c);
            const auto points_view = std::ranges::subrange(points_begin, points_end) | std::views::transform([](const auto& pair){return pair.second;});
            std::vector<Point> points(points_view.begin(), points_view.end());
            auto new_nodes = calculate_antinodes(points, map.x_size, map.y_size);
            antinodes.merge(new_nodes);
        }

        return antinodes.size();
    }

    auto part2(const Input &input) const -> long long override {
        return 0;
    }

};