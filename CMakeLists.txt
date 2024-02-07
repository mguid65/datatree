cmake_minimum_required(VERSION 3.16)
project(datatree VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(utilities.cmake)

enable_warnings()

set(DATATREE_SOURCES
        source/datatree/datatree.cpp
        source/datatree/tree_node.cpp
        source/datatree/node_types/array_node.cpp
        source/datatree/node_types/object_node.cpp
        source/datatree/node_types/value_node.cpp
)

find_package(expected-lite REQUIRED)

# Static because I don't feel like dealing with shared shenanigans
add_library(datatree STATIC)
target_include_directories(datatree PUBLIC include)
target_sources(datatree PRIVATE ${DATATREE_SOURCES})
target_link_libraries(datatree PUBLIC nonstd::expected-lite)

include(CTest)

install(DIRECTORY include/ DESTINATION include)
install(TARGETS datatree DESTINATION lib)

add_executable(sample)
target_sources(sample PRIVATE source/sample/main.cpp)
target_link_libraries(sample PRIVATE datatree)

enable_testing()

add_test(NAME sample
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND sample)

find_package(Catch2 COMPONENTS Catch2WithMain)

if (Catch2_FOUND)
    add_subdirectory(test)
endif()