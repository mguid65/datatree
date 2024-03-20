cmake_minimum_required(VERSION 3.16)
project(data_tree LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(cmake/utilities.cmake)

enable_warnings()

option(COVERAGE "Enable code coverage flags")
option(SANITIZE "Enable sanitizer flags")

if (COVERAGE)
    enable_coverage()
endif ()

if (SANITIZE)
    enable_sanitizer()
endif ()

find_package(tl-expected REQUIRED)

set(DATA_TREE_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/data_tree/common/common.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/data_tree/data_tree.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/data_tree/tree_node/tree_node.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/data_tree/error/error_type.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/data_tree/node_types/detail/array_node_type.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/data_tree/node_types/detail/value_node_type.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/data_tree/node_types/detail/object_node_type.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/data_tree/node_types/node_types.inc
        ${CMAKE_CURRENT_SOURCE_DIR}/include/data_tree/node_types/detail/value_types/null_type.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/data_tree/node_types/detail/value_types/number_type.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/data_tree/node_types/detail/value_types/value_types.hpp
)

add_library(data_tree INTERFACE)
target_include_directories(data_tree INTERFACE include)
target_sources(data_tree INTERFACE ${DATA_TREE_HEADERS})
target_link_libraries(data_tree INTERFACE tl::expected)
set_target_properties(data_tree PROPERTIES LINKER_LANGUAGE CXX)

include(CTest)

install(DIRECTORY include/ DESTINATION include)
install(TARGETS data_tree DESTINATION lib)

add_executable(sample)
target_sources(sample PRIVATE source/sample/main.cpp)
target_link_libraries(sample PRIVATE data_tree)

enable_testing()

add_test(NAME sample
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND sample)

find_package(Catch2 COMPONENTS Catch2WithMain)

if (Catch2_FOUND)
    add_subdirectory(test)
endif ()