/**
 * @brief Tests for value node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include <datatree/node_types/value_node_type.hpp>

TEST_CASE("Value Node Type Constructor") {
  SECTION("Default Constructor") {
    REQUIRE(std::is_default_constructible_v<mguid::ValueNodeType>);
  }
}

TEST_CASE("Value Node Type Three Way Comparison") {
  SECTION("Equality") {
    REQUIRE(mguid::ValueNodeType(mguid::StringType{}) == mguid::ValueNodeType(mguid::StringType{}));
    REQUIRE(mguid::ValueNodeType(mguid::BoolType{}) == mguid::ValueNodeType(mguid::BoolType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NullType{}) == mguid::ValueNodeType(mguid::NullType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{}) == mguid::ValueNodeType(mguid::NumberType{}));

    REQUIRE(mguid::ValueNodeType(mguid::StringType{"test"}) == mguid::ValueNodeType(mguid::StringType{"test"}));
    REQUIRE(mguid::ValueNodeType(mguid::BoolType{true}) == mguid::ValueNodeType(mguid::BoolType{true}));
    REQUIRE(mguid::ValueNodeType(mguid::NullType{}) == mguid::ValueNodeType(mguid::NullType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1}) == mguid::ValueNodeType(mguid::NumberType{1}));
  }
  SECTION("Inequality") {
    // Type Difference
    REQUIRE(mguid::ValueNodeType(mguid::StringType{}) != mguid::ValueNodeType(mguid::NumberType{}));
    REQUIRE(mguid::ValueNodeType(mguid::StringType{}) != mguid::ValueNodeType(mguid::BoolType{}));
    REQUIRE(mguid::ValueNodeType(mguid::StringType{}) != mguid::ValueNodeType(mguid::NullType{}));

    REQUIRE(mguid::ValueNodeType(mguid::BoolType{}) != mguid::ValueNodeType(mguid::StringType{}));
    REQUIRE(mguid::ValueNodeType(mguid::BoolType{}) != mguid::ValueNodeType(mguid::NullType{}));
    REQUIRE(mguid::ValueNodeType(mguid::BoolType{}) != mguid::ValueNodeType(mguid::NumberType{}));

    REQUIRE(mguid::ValueNodeType(mguid::NullType{}) != mguid::ValueNodeType(mguid::StringType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NullType{}) != mguid::ValueNodeType(mguid::BoolType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NullType{}) != mguid::ValueNodeType(mguid::NumberType{}));

    REQUIRE(mguid::ValueNodeType(mguid::NumberType{}) != mguid::ValueNodeType(mguid::StringType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{}) != mguid::ValueNodeType(mguid::NullType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{}) != mguid::ValueNodeType(mguid::BoolType{}));

    // NullType only has 1 value, so it is always equal to itself
    // Value Difference
    REQUIRE(mguid::ValueNodeType(mguid::StringType{"test"}) != mguid::ValueNodeType(mguid::StringType{"notTest"}));
    REQUIRE(mguid::ValueNodeType(mguid::BoolType{true}) != mguid::ValueNodeType(mguid::BoolType{false}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1}) != mguid::ValueNodeType(mguid::NumberType{2}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1u}) != mguid::ValueNodeType(mguid::NumberType{2u}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1.0}) != mguid::ValueNodeType(mguid::NumberType{2.0}));

    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1}) != mguid::ValueNodeType(mguid::NumberType{2.0}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1.0}) != mguid::ValueNodeType(mguid::NumberType{2}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1u}) != mguid::ValueNodeType(mguid::NumberType{2.0}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1.0}) != mguid::ValueNodeType(mguid::NumberType{2u}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1u}) != mguid::ValueNodeType(mguid::NumberType{2}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1}) != mguid::ValueNodeType(mguid::NumberType{2u}));
  }
}