/**
 * @brief Tests for null value type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <array>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

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

TEST_CASE("Path Ostream <<") {
  auto test_path = mguid::Path{"first", "second", "third", 1, 2, 3};
  std::ostringstream oss;
  oss << test_path;
  REQUIRE(oss.str() == "[\"first\"][\"second\"][\"third\"][1][2][3]");
}

TEST_CASE("KeyOrIdxType Construction") {
  SECTION("Default") {
    REQUIRE(std::is_default_constructible_v<mguid::KeyOrIdxType>);
  }
  SECTION("Copy Construction") {
    REQUIRE(std::is_copy_constructible_v<mguid::KeyOrIdxType>);
  }
  SECTION("Move Construction") {
    REQUIRE(std::is_nothrow_move_constructible_v<mguid::KeyOrIdxType>);
  }
  SECTION("Copy Assignment") {
    REQUIRE(std::is_copy_assignable_v<mguid::KeyOrIdxType>);
  }
  SECTION("Move Assignment") {
    REQUIRE(std::is_nothrow_move_assignable_v<mguid::KeyOrIdxType>);
  }
  SECTION("From String") {
    REQUIRE(std::is_constructible_v<mguid::KeyOrIdxType, mguid::StringKeyType>);
    REQUIRE(
        std::is_constructible_v<mguid::KeyOrIdxType, mguid::StringKeyType&>);
    REQUIRE(std::is_constructible_v<mguid::KeyOrIdxType,
                                    const mguid::StringKeyType>);
    REQUIRE(std::is_constructible_v<mguid::KeyOrIdxType,
                                    const mguid::StringKeyType&>);
    REQUIRE(
        std::is_constructible_v<mguid::KeyOrIdxType, mguid::StringKeyType&&>);
    REQUIRE(std::is_constructible_v<mguid::KeyOrIdxType, const char*>);
  }
  SECTION("From Integer") {
    REQUIRE(
        std::is_constructible_v<mguid::KeyOrIdxType, mguid::IntegerKeyType>);
    REQUIRE(
        std::is_constructible_v<mguid::KeyOrIdxType, mguid::IntegerKeyType&>);
    REQUIRE(std::is_constructible_v<mguid::KeyOrIdxType,
                                    const mguid::IntegerKeyType>);
    REQUIRE(std::is_constructible_v<mguid::KeyOrIdxType,
                                    const mguid::IntegerKeyType&>);
    REQUIRE(
        std::is_constructible_v<mguid::KeyOrIdxType, mguid::IntegerKeyType&&>);
  }
}

TEST_CASE("KeyOrIdxType Visit") {
  SECTION("Visit") {
    mguid::KeyOrIdxType test_key_or_idx_1{""};
    REQUIRE(test_key_or_idx_1.Visit(
        [](const mguid::StringKeyType&) { return true; },
        [](auto) { return false; }));
    mguid::KeyOrIdxType test_key_or_idx_2{1};
    REQUIRE(test_key_or_idx_2.Visit(
        [](const mguid::IntegerKeyType&) { return true; },
        [](auto) { return false; }));
  }
  SECTION("Visit Const") {
    mguid::KeyOrIdxType test_key_or_idx_1{""};
    REQUIRE(test_key_or_idx_1.Visit(
        [](const mguid::StringKeyType&) { return true; },
        [](auto) { return false; }));
    mguid::KeyOrIdxType test_key_or_idx_2{1};
    REQUIRE(test_key_or_idx_2.Visit(
        [](const mguid::IntegerKeyType&) { return true; },
        [](auto) { return false; }));
  }
}

TEST_CASE("Integer Indexable") {
  REQUIRE(mguid::IntegerIndexable<std::vector<int>>);
  REQUIRE(mguid::IntegerIndexable<std::array<int, 1>>);
  REQUIRE(mguid::IntegerIndexable<std::string>);
}

TEST_CASE("Prettify Json") {
  // samples from https://json.org/example.html

  REQUIRE(mguid::PrettifyJson(
              "{\"fruit\":\"Apple\",\"size\":\"Large\",\"color\":\"Red\"}") ==
          "{\n"
          "  \"fruit\":\"Apple\",\n"
          "  \"size\":\"Large\",\n"
          "  \"color\":\"Red\"\n"
          "}");
  REQUIRE(
      mguid::PrettifyJson(
          "{\"widget\":{\"debug\":\"on\",\"window\":{\"title\":\"Sample "
          "Konfabulator "
          "Widget\",\"name\":\"main_window\",\"width\":500,\"height\":500},"
          "\"image\":{\"src\":\"Images/"
          "Sun.png\",\"name\":\"sun1\",\"hOffset\":250,\"vOffset\":250,"
          "\"alignment\":\"center\"},\"text\":{\"data\":\"Click "
          "Here\",\"size\":36,\"style\":\"bold\",\"name\":\"text1\","
          "\"hOffset\":250,\"vOffset\":100,\"alignment\":\"center\","
          "\"onMouseUp\":\"sun1.opacity = (sun1.opacity / 100) * 90;\"}}}") ==
      "{\n"
      "  \"widget\":{\n"
      "    \"debug\":\"on\",\n"
      "    \"window\":{\n"
      "      \"title\":\"Sample Konfabulator Widget\",\n"
      "      \"name\":\"main_window\",\n"
      "      \"width\":500,\n"
      "      \"height\":500\n"
      "    },\n"
      "    \"image\":{\n"
      "      \"src\":\"Images/Sun.png\",\n"
      "      \"name\":\"sun1\",\n"
      "      \"hOffset\":250,\n"
      "      \"vOffset\":250,\n"
      "      \"alignment\":\"center\"\n"
      "    },\n"
      "    \"text\":{\n"
      "      \"data\":\"Click Here\",\n"
      "      \"size\":36,\n"
      "      \"style\":\"bold\",\n"
      "      \"name\":\"text1\",\n"
      "      \"hOffset\":250,\n"
      "      \"vOffset\":100,\n"
      "      \"alignment\":\"center\",\n"
      "      \"onMouseUp\":\"sun1.opacity = (sun1.opacity / 100) * 90;\"\n"
      "    }\n"
      "  }\n"
      "}");
  REQUIRE(mguid::PrettifyJson("{}") ==
          "{\n"
          "  \n"
          "}");
  REQUIRE(mguid::PrettifyJson("[]") ==
          "[\n"
          "  \n"
          "]");
}

TEST_CASE("Ref Expected") {
  int i{4};
  int j{2};
  auto result_1 = [&i]() -> mguid::RefExpected<int, std::string> {
    return i;
  }();
  REQUIRE(result_1.has_value());
  REQUIRE(result_1.value() == 4);
  REQUIRE(*result_1.operator->() == 4);
  REQUIRE(*result_1 == 4);
  REQUIRE(&result_1.value() == &i);
  auto result_2 = [&j]() -> mguid::RefExpected<int, std::string> {
    return j;
  }();
  REQUIRE(result_2.has_value());
  REQUIRE(result_2.value() == 2);
  REQUIRE(*result_2.operator->() == 2);
  REQUIRE(*result_2 == 2);
  REQUIRE(&result_2.value() == &j);
  auto result_3 = []() -> mguid::RefExpected<int, std::string> {
    return mguid::make_unexpected("unexpected");
  }();
  REQUIRE_FALSE(result_3.has_value());
  REQUIRE(result_3.error() == "unexpected");
}