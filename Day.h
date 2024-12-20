#pragma once

#include <istream>

template<typename Input>
class Day {
public:
    virtual ~Day() = default;

    [[nodiscard]] virtual auto num() const -> int = 0;
    virtual auto example_input_str() const -> std::stringstream = 0;
    virtual auto parse_input(std::basic_istream<char> & input_str) const -> Input = 0;
    virtual auto part1(const Input& input) const -> int = 0;
    virtual auto part2(const Input& input) const -> int = 0;
};
