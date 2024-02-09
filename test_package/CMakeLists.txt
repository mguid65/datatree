cmake_minimum_required(VERSION 3.15)
project(test_package CXX)

find_package(datatree REQUIRED CONFIG)

add_executable(test_package src/example.cpp)
target_link_libraries(test_package PRIVATE datatree::datatree)
target_compile_features(test_package PRIVATE cxx_std_11)