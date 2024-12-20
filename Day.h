#pragma once

#include <istream>

template<typename InputT>
class Day {
public:
    using Input = InputT;

    virtual ~Day() = default;

    [[nodiscard]] virtual auto num() const -> int = 0;
    virtual auto example_input_str1() const -> std::stringstream = 0;
    virtual auto example_input_str2() const -> std::stringstream {return example_input_str1();}
    virtual auto parse_input(std::basic_istream<char> & input_str) const -> Input = 0;
    virtual auto part1(const Input& input) const -> int = 0;
    virtual auto part2(const Input& input) const -> int = 0;
};
