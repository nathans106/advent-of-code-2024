#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cassert>
#include "days/day4.h"

auto read_input(int day_num) -> std::ifstream {
    std::filesystem::path file_path("inputs/day" + std::to_string(day_num) + ".txt");
    assert(exists(file_path));
    std::ifstream file(file_path);
    return file;
}

int main() {
    const Day4 day;
    std::cout << "Executing day " << day.num() << std::endl;
    auto example_input_buf1 = day.example_input_str1();
    const auto example_input1 = day.parse_input(example_input_buf1);
    auto example_input_buf2 = day.example_input_str2();
    const auto example_input2 = day.parse_input(example_input_buf2);
    auto input_buf = read_input(day.num());
    const auto input = day.parse_input(input_buf);
    std::cout << "Part 1 example: " << day.part1(example_input1) << std::endl;
    std::cout << "Part 1: " << day.part1(input) << std::endl;
    std::cout << "Part 2 example: " << day.part2(example_input2) << std::endl;
    std::cout << "Part 2: " << day.part2(input) << std::endl;
}
