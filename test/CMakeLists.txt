set(UNIT_TEST_SRC
        unit_test_data_tree.cpp
        unit_test_tree_node.cpp
        unit_test_object_node_type.cpp
        unit_test_array_node_type.cpp
        unit_test_value_node_type.cpp
        unit_test_null_type.cpp
        unit_test_number_type.cpp
        unit_test_value_types.cpp
        unit_test_error_type.cpp
        unit_test_common.cpp
)

add_executable(unit_tests)
target_sources(unit_tests PRIVATE ${UNIT_TEST_SRC})
target_link_libraries(unit_tests PRIVATE data_tree Catch2::Catch2WithMain)

enable_testing()

add_test(NAME unit_tests
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND unit_tests)