/**
 * @brief Tests for array node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include <datatree/node_types/array_node_type.hpp>

TEST_CASE("Array Node Type Constructor") {
  SECTION("Default Constructor") {
    REQUIRE(std::is_nothrow_default_constructible_v<mguid::ArrayNodeType>);
  }
  SECTION("Copy Constructor") {
    REQUIRE(std::is_copy_constructible_v<mguid::ArrayNodeType>);
  }
  SECTION("Move Constructor") {
    REQUIRE(std::is_nothrow_move_constructible_v<mguid::ArrayNodeType>);
  }
  SECTION("Copy Assignment") {
    REQUIRE(std::is_copy_assignable_v<mguid::ArrayNodeType>);
  }
  SECTION("Move Assignment") {
    REQUIRE(std::is_nothrow_move_assignable_v<mguid::ArrayNodeType>);
  }
  SECTION("Initializer List Constructor") {
    REQUIRE(std::is_constructible_v<mguid::ArrayNodeType,
                                    std::initializer_list<mguid::uuid>>);
  }
  SECTION("Initializer List Assignment") {
    REQUIRE(std::is_assignable_v<mguid::ArrayNodeType,
                                 std::initializer_list<mguid::uuid>>);
  }
}

TEST_CASE("Array Node Type Get") {
  SECTION("Get Invalid Index Empty") {
    mguid::ArrayNodeType ant1;
    auto result = ant1.Get(0);
    REQUIRE(result.has_exception<mguid::Error>());
    REQUIRE(result.error().category == mguid::Error::Category::OutOfRange);
  }
  SECTION("Get Not Empty") {
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    auto result1 = ant1.Get(0);
    auto result2 = ant1.Get(1);
    auto result3 = ant1.Get(2);
    auto result4 = ant1.Get(3);

    REQUIRE(result1.has_value());
    REQUIRE(result2.has_value());
    REQUIRE(result3.has_value());
    REQUIRE(result4.has_value());
  }
  SECTION("Get Invalid Index Not Empty") {
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    auto result = ant1.Get(4);
    REQUIRE(result.has_exception<mguid::Error>());
    REQUIRE(result.error().category == mguid::Error::Category::OutOfRange);
  }
}