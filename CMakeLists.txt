cmake_minimum_required(VERSION 3.16)
project(datatree VERSION 0.0.2 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(cmake/utilities.cmake)

enable_warnings()

option(COVERAGE "Enable code coverage flags")
option(SANITIZER "Enable sanitizer flags")

if (COVERAGE)
    enable_coverage()
endif ()

if (SANITIZER)
    enable_sanitizer()
endif ()

find_package(expected-lite REQUIRED)

set(DATATREE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/datatree/common.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/datatree/data_tree.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/datatree/tree_node.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/datatree/error/error_type.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/datatree/node_types/detail/array_node_type.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/datatree/node_types/detail/value_node_type.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/datatree/node_types/detail/object_node_type.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/datatree/node_types/node_types.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/include/datatree/node_types/detail/null_type.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/datatree/node_types/detail/number_type.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/datatree/node_types/detail/value_types.hpp
)


add_library(datatree INTERFACE)
target_include_directories(datatree INTERFACE include)
target_sources(datatree INTERFACE ${DATATREE_HEADERS})
target_link_libraries(datatree INTERFACE nonstd::expected-lite)
set_target_properties(datatree PROPERTIES LINKER_LANGUAGE CXX)

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
endif ()