/**
 * @brief Tests for null value type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <string>
#include <type_traits>

#include <catch2/catch_all.hpp>

#include <datatree/common.hpp>

TEST_CASE("Pick First Convertible To") {
  STATIC_REQUIRE(
      std::is_same_v<mguid::PickFirstConvertible<std::size_t, std::string,
                                                 std::uint8_t>::type,
                     std::uint8_t>);
  STATIC_REQUIRE(std::is_same_v<
                 mguid::PickFirstConvertible<std::size_t, std::string,
                                             std::uint8_t, std::uint16_t>::type,
                 std::uint8_t>);
  STATIC_REQUIRE(
      std::is_same_v<mguid::PickFirstConvertible<std::string, std::string,
                                                 std::uint8_t>::type,
                     std::string>);
  STATIC_REQUIRE(
      std::is_same_v<mguid::PickFirstConvertible<std::string, std::string,
                                                 std::string>::type,
                     std::string>);
}

TEST_CASE("Path Construction") {
  mguid::Path test_path{"first", "second", "third", 1, 2, 3};
  const auto& items = test_path.Items();
  REQUIRE(items.size() == 6);
  REQUIRE(std::get<mguid::StringKeyType>(items.at(0)) == "first");
  REQUIRE(std::get<mguid::StringKeyType>(items.at(1)) == "second");
  REQUIRE(std::get<mguid::StringKeyType>(items.at(2)) == "third");
  REQUIRE(std::get<mguid::IntegerKeyType>(items.at(3)) == 1);
  REQUIRE(std::get<mguid::IntegerKeyType>(items.at(4)) == 2);
  REQUIRE(std::get<mguid::IntegerKeyType>(items.at(5)) == 3);
}
