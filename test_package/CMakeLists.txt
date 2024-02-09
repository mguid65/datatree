cmake_minimum_required(VERSION 3.15)
project(test_package CXX)

find_package(datatree REQUIRED CONFIG)

add_executable(example src/example.cpp)
target_link_libraries(example PRIVATE datatree::datatree)
