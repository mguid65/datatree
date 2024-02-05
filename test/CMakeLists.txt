set(UNIT_TEST_SRC
        unit_test_datatree.cpp
        unit_test_tree_node.cpp
        unit_test_object_node.cpp
        unit_test_array_node.cpp
        unit_test_value_node.cpp
)

add_executable(unit_tests EXCLUDE_FROM_ALL)
target_sources(unit_tests PRIVATE ${UNIT_TEST_SRC})
target_link_libraries(unit_tests PRIVATE datatree Catch2::Catch2WithMain)

add_test(NAME unit_tests
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND unit_tests)