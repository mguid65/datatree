/**
 * @brief Tests for error type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-12
 */

#include <catch2/catch_all.hpp>

#include <data_tree/error/error_type.hpp>

TEST_CASE("Error Type Construction") {
  SECTION("Aggregate Initialization") {
    REQUIRE(std::is_aggregate_v<mguid::Error>);
    REQUIRE(std::is_constructible_v<mguid::Error, mguid::Error::Category>);
    mguid::Error e1;
    mguid::Error e2{mguid::Error::Category::BadAccess};
    mguid::Error e3{mguid::Error::Category::KeyError};
    mguid::Error e4{mguid::Error::Category::Generic};
    mguid::Error e5{mguid::Error::Category::OutOfRange};
    REQUIRE(e1.category == mguid::Error::Category::Generic);
    REQUIRE(e2.category == mguid::Error::Category::BadAccess);
    REQUIRE(e3.category == mguid::Error::Category::KeyError);
    REQUIRE(e4.category == mguid::Error::Category::Generic);
    REQUIRE(e5.category == mguid::Error::Category::OutOfRange);
  }
}

TEST_CASE("Error Category To String") {
  SECTION("Within Defined Enumerators") {
    mguid::Error e1;
    mguid::Error e2{mguid::Error::Category::BadAccess};
    mguid::Error e3{mguid::Error::Category::KeyError};
    mguid::Error e4{mguid::Error::Category::Generic};
    mguid::Error e5{mguid::Error::Category::OutOfRange};
    REQUIRE(mguid::Error::CategoryToString(e1.category) == "Category::Generic");
    REQUIRE(mguid::Error::CategoryToString(e2.category) ==
            "Category::BadAccess");
    REQUIRE(mguid::Error::CategoryToString(e3.category) ==
            "Category::KeyError");
    REQUIRE(mguid::Error::CategoryToString(e4.category) == "Category::Generic");
    REQUIRE(mguid::Error::CategoryToString(e5.category) ==
            "Category::OutOfRange");
  }
  SECTION("Outside Defined Enumerators") {
    for (auto i{static_cast<std::uint8_t>(mguid::Error::Category::Generic) + 1};
         i < std::numeric_limits<std::uint8_t>::max(); ++i) {
      mguid::Error e1{static_cast<mguid::Error::Category>(i)};
      REQUIRE(mguid::Error::CategoryToString(e1.category) ==
              "Category::Unknown");
    }
  }
}
