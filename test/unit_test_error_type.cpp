/**
 * @brief Tests for error type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-12
 */

#include <catch2/catch_all.hpp>

#include <datatree/error/error_type.hpp>

TEST_CASE("Error Type Construction") {
  SECTION("Aggregate Initialization") {
    REQUIRE(std::is_aggregate_v<mguid::Error>);
    REQUIRE(std::is_constructible_v<mguid::Error, mguid::Error::Category>);
    mguid::Error e1;
    mguid::Error e2{mguid::Error::Category::BadAccess};
    mguid::Error e3{mguid::Error::Category::KeyError};
    mguid::Error e4{mguid::Error::Category::Generic};
    REQUIRE(e1.category == mguid::Error::Category::Generic);
    REQUIRE(e2.category == mguid::Error::Category::BadAccess);
    REQUIRE(e3.category == mguid::Error::Category::KeyError);
    REQUIRE(e4.category == mguid::Error::Category::Generic);
  }
}

TEST_CASE("Error Category To String") {
  mguid::Error e1;
  mguid::Error e2{mguid::Error::Category::BadAccess};
  mguid::Error e3{mguid::Error::Category::KeyError};
  mguid::Error e4{mguid::Error::Category::Generic};
  REQUIRE(mguid::Error::CategoryToString(e1.category) == "Category::Generic");
  REQUIRE(mguid::Error::CategoryToString(e2.category) == "Category::BadAccess");
  REQUIRE(mguid::Error::CategoryToString(e3.category) == "Category::KeyError");
  REQUIRE(mguid::Error::CategoryToString(e4.category) == "Category::Generic");
}
