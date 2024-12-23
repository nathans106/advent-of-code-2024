#pragma once

#include <istream>
#include <sstream>
#include "input_parser.h"

template<typename ParserT>
class Day {
public:
    using Input = ParserT::Input;
    using Parser = ParserT;

    virtual ~Day() = default;

    [[nodiscard]] virtual auto num() const -> int = 0;
    virtual auto example_input_str1() const -> std::stringstream = 0;
    virtual auto example_input_str2() const -> std::stringstream {return example_input_str1();}
    virtual auto part1(const Input& input) const -> int = 0;
    virtual auto part2(const Input& input) const -> int = 0;
};
