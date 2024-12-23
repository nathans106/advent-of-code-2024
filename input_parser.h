#pragma once

#include <istream>

template<typename InputT>
class InputParser {
public:
    using Input = InputT;

    virtual ~InputParser() = default;

    auto operator()(std::basic_istream<char> &input_str) -> InputT {
        std::string line;
        while(std::getline(input_str, line)) {
            parse_line(line);
        }
        return get_input();
    }

private:
    virtual void parse_line(const std::string& line) = 0;
    virtual InputT get_input() = 0;
};
