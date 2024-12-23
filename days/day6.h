#pragma once

#include "../Day.h"

#include <ranges>
#include <set>
#include <vector>
#include <cassert>

struct Guard {
    std::pair<int, int> pos;
    std::pair<int, int> dir;

    bool operator<(const Guard& other) const {
        return pos < other.pos && dir < other.dir;
    }
};

enum class Space {
    empty,
    obstructed
};

struct Room {
    Guard guard_start;
    std::vector<std::vector<Space>> grid;
};

class Day6Parser : public InputParser<Room> {
    void parse_line(const std::string &line) override {
        std::vector<Space> row;
        m_input.guard_start.dir = {-1, 0};
        for (const auto [i, c] : line | std::ranges::views::enumerate) {
            switch (c) {
                case '.': {
                    row.push_back(Space::empty);
                    break;
                }
                case '#': {
                    row.push_back(Space::obstructed);
                    break;
                }
                case '^': {
                    const auto cur_row = m_input.grid.size();
                    m_input.guard_start.pos = {cur_row, i};
                    row.push_back(Space::empty);
                    break;
                }
                default:
                {
                    assert(false);
                }
            }
        }
        m_input.grid.push_back(row);
    }

    Input get_input() override {
        return m_input;
    }

    Input m_input;
};

std::optional<Guard> next_guard_pos(const Guard& cur_guard, const std::vector<std::vector<Space>>& grid) {
    auto guard = cur_guard;
    while(true) {
        const auto next_pos = std::pair(guard.pos.first + guard.dir.first, guard.pos.second + guard.dir.second);
        if (next_pos.first >= grid.size()) {
            return std::nullopt;
        }
        const auto& row = grid[next_pos.first];
        if (next_pos.second >= row.size()) {
            return std::nullopt;
        }
        const auto space = row[next_pos.second];
        if (space == Space::empty) {
            return Guard{next_pos, guard.dir};
        }
        if (guard.dir == std::pair{-1, 0}) {
            guard.dir = {0,1};
        } else if (guard.dir == std::pair{0,1}) {
            guard.dir = {1,0};
        } else if (guard.dir == std::pair{1,0}) {
            guard.dir = {0,-1};
        } else if (guard.dir == std::pair{0,-1}) {
            guard.dir = {-1,0};
        }
    }
}

class Day6 : public Day<Day6Parser> {
public:
    auto num() const -> int override {
        return 6;
    }

    auto example_input_str1() const -> std::stringstream override {
        return std::stringstream(R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...)");
    }

    auto part1(const Input &input) const -> int override {
        const auto & grid = input.grid;
        auto guard = input.guard_start;
        std::set<std::pair<int, int>> visited = {guard.pos};
        while(true) {
            auto maybe_guard = next_guard_pos(guard, grid);
            if (!maybe_guard.has_value()) {
                break;
            }
            guard = maybe_guard.value();
            visited.insert(guard.pos);
        }
        return visited.size();
    }

    auto part2(const Input &input) const -> int override {
        auto count = 0;
        for (auto x = 0; x < input.grid.size(); ++x) {
            const auto &row = input.grid[x];
            for (auto y = 0; y < row.size(); ++y) {
                if (input.grid[x][y] == Space::obstructed) {
                    // Already obstruction, do nothing
                    continue;
                }

                auto new_grid = input.grid;
                new_grid[x][y] = Space::obstructed;
                auto guard = input.guard_start;
                std::set<Guard> old_guards = {guard};
                while(true) {
                    auto maybe_guard = next_guard_pos(guard, new_grid);
                    if (!maybe_guard.has_value()) {
                        break;
                    }

                    guard = maybe_guard.value();
                    if (old_guards.contains(guard)) {
                        count++;
                        break;
                    }
                    old_guards.insert(guard);
                }
            }
        }

        return count;
    }

};