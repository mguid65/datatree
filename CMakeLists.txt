cmake_minimum_required(VERSION 3.16)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif ()

set(CMAKE_CXX_EXTENSIONS OFF)

project(datatree VERSION 0.0.1 LANGUAGES CXX C)

set(DATATREE_SOURCES
        source/datatree/datatree.cpp
)

# Static because I don't feel like dealing with shared shenanigans
add_library(datatree STATIC)
target_include_directories(datatree PUBLIC include)
target_sources(datatree PRIVATE ${DATATREE_SOURCES})

include(CTest)

install(DIRECTORY include/ DESTINATION include)
install(TARGETS datatree DESTINATION lib)

add_executable(sample)
target_sources(sample PRIVATE source/sample/main.cpp)
target_link_libraries(sample PRIVATE datatree)

add_test(NAME sample
        COMMAND sample)

find_package(Catch2 COMPONENTS Catch2WithMain)

if (Catch2_FOUND)
    add_subdirectory(test)
endif()