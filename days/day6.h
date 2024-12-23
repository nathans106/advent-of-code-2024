#pragma once

#include "../Day.h"

#include <ranges>
#include <set>
#include <vector>
#include <cassert>

enum class Space {
    empty,
    obstructed
};

struct Room {
    std::pair<int, int> start_pos;
    std::vector<std::vector<Space>> grid;
};

class Day6Parser : public InputParser<Room> {
    void parse_line(const std::string &line) override {
        std::vector<Space> row;
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
                    m_input.start_pos = {cur_row, i};
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
        std::set<std::pair<int, int>> visited = {input.start_pos};
        std::pair<int, int> cur_pos = input.start_pos;
        std::pair<int, int> cur_dir = {-1, 0};
        bool in_bounds = true;
        while(in_bounds) {
            while(true) {
                const auto next_pos = std::pair(cur_pos.first + cur_dir.first, cur_pos.second + cur_dir.second);
                if (next_pos.first >= grid.size()) {
                    in_bounds = false;
                    break;
                }
                const auto& row = grid[next_pos.first];
                if (next_pos.second >= row.size()) {
                    in_bounds = false;
                    break;
                }
                const auto space = row[next_pos.second];
                if (space == Space::empty) {
                    cur_pos = next_pos;
                    visited.insert(cur_pos);
                    break;
                }
                if (cur_dir == std::pair{-1, 0}) {
                    cur_dir = {0,1};
                } else if (cur_dir == std::pair{0,1}) {
                    cur_dir = {1,0};
                } else if (cur_dir == std::pair{1,0}) {
                    cur_dir = {0,-1};
                } else if (cur_dir == std::pair{0,-1}) {
                    cur_dir = {-1,0};
                }
            }
        }
        return visited.size();
    }

    auto part2(const Input &input) const -> int override {
        return 0;
    }

};