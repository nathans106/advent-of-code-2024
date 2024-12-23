cmake_minimum_required(VERSION 3.22)
project(advent_of_code_2024)

set(CMAKE_CXX_STANDARD 23)

add_executable(advent_of_code_2024 main.cpp
  Day.h
  days/day1.h
  days/day2.h
  days/day3.h
  days/day4.h
  input_parser.h
  days/day5.h
  days/day6.h)
