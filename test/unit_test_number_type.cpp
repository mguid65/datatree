/**
 * @brief Tests for number value type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include <datatree/node_types/detail/number_type.hpp>

TEST_CASE("Number Type Constructor") {
  SECTION("Default Constructor") {
    REQUIRE(std::is_default_constructible_v<mguid::NumberType>);
    mguid::NumberType nt;
  }
}