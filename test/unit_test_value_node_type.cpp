/**
 * @brief Tests for value node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include <datatree/node_types/value_node_type.hpp>

TEST_CASE("Value Node Constructor") {
  SECTION("Default Constructor") {
    REQUIRE(std::is_default_constructible_v<mguid::ValueNodeType>);
  }
}

TEST_CASE("Three Way Comparison") {
  SECTION("Equality") {
    REQUIRE(mguid::ValueNodeType("hello") == mguid::ValueNodeType("hello"));
    REQUIRE(mguid::ValueNodeType("hello") != mguid::ValueNodeType(1));
  }
}