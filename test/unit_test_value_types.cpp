/**
 * @brief Tests for array node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <variant>
#include <optional>

#include <catch2/catch_all.hpp>

#include <datatree/node_types/detail/value_types.hpp>

TEST_CASE("Value Type Concepts") {
  SECTION("Null Type") {
    REQUIRE(mguid::SatisfiesNullType<mguid::NullType>);
    REQUIRE(mguid::SatisfiesNullType<mguid::NullType&>);
    REQUIRE(mguid::SatisfiesNullType<mguid::NullType&&>);
    REQUIRE(mguid::SatisfiesNullType<const mguid::NullType>);
    REQUIRE(mguid::SatisfiesNullType<const mguid::NullType&>);
    REQUIRE(mguid::SatisfiesNullType<volatile mguid::NullType>);
    REQUIRE(mguid::SatisfiesNullType<volatile mguid::NullType&>);
    REQUIRE(mguid::SatisfiesNullType<const volatile mguid::NullType>);
    REQUIRE(mguid::SatisfiesNullType<const volatile mguid::NullType&>);
    REQUIRE_FALSE(mguid::SatisfiesNullType<void>);
    REQUIRE_FALSE(mguid::SatisfiesNullType<mguid::NullType*>);
    REQUIRE_FALSE(mguid::SatisfiesNullType<nullptr_t>);
    REQUIRE_FALSE(mguid::SatisfiesNullType<std::monostate>);
    REQUIRE_FALSE(mguid::SatisfiesNullType<std::nullopt_t>);
    REQUIRE_FALSE(mguid::SatisfiesNullType<mguid::StringType>);
    REQUIRE_FALSE(mguid::SatisfiesNullType<mguid::NumberType>);
    REQUIRE_FALSE(mguid::SatisfiesNullType<mguid::BoolType>);
  }
  SECTION("String Type") {
    REQUIRE(mguid::SatisfiesStringType<mguid::StringType>);
    REQUIRE(mguid::SatisfiesStringType<mguid::StringType&>);
    REQUIRE(mguid::SatisfiesStringType<mguid::StringType&&>);
    REQUIRE(mguid::SatisfiesStringType<const mguid::StringType>);
    REQUIRE(mguid::SatisfiesStringType<const mguid::StringType&>);
    REQUIRE(mguid::SatisfiesStringType<volatile mguid::StringType>);
    REQUIRE(mguid::SatisfiesStringType<volatile mguid::StringType&>);
    REQUIRE(mguid::SatisfiesStringType<const volatile mguid::StringType>);
    REQUIRE(mguid::SatisfiesStringType<const volatile mguid::StringType&>);
    REQUIRE(mguid::SatisfiesStringType<const char*>);
    REQUIRE(mguid::SatisfiesStringType<char[]>);
    REQUIRE_FALSE(mguid::SatisfiesStringType<void>);
    REQUIRE_FALSE(mguid::SatisfiesStringType<mguid::StringType*>);
    REQUIRE_FALSE(mguid::SatisfiesStringType<nullptr_t>);
    REQUIRE_FALSE(mguid::SatisfiesStringType<std::monostate>);
    REQUIRE_FALSE(mguid::SatisfiesStringType<std::nullopt_t>);
    REQUIRE_FALSE(mguid::SatisfiesStringType<mguid::NullType>);
    REQUIRE_FALSE(mguid::SatisfiesStringType<mguid::NumberType>);
    REQUIRE_FALSE(mguid::SatisfiesStringType<mguid::BoolType>);
  }
  SECTION("Bool Type") {
    REQUIRE(mguid::SatisfiesBoolType<mguid::BoolType>);
    REQUIRE(mguid::SatisfiesBoolType<mguid::BoolType&>);
    REQUIRE(mguid::SatisfiesBoolType<mguid::BoolType&&>);
    REQUIRE(mguid::SatisfiesBoolType<const mguid::BoolType>);
    REQUIRE(mguid::SatisfiesBoolType<const mguid::BoolType&>);
    REQUIRE(mguid::SatisfiesBoolType<volatile mguid::BoolType>);
    REQUIRE(mguid::SatisfiesBoolType<volatile mguid::BoolType&>);
    REQUIRE(mguid::SatisfiesBoolType<const volatile mguid::BoolType>);
    REQUIRE(mguid::SatisfiesBoolType<const volatile mguid::BoolType&>);
    REQUIRE_FALSE(mguid::SatisfiesBoolType<void>);
    REQUIRE_FALSE(mguid::SatisfiesBoolType<int>);
    REQUIRE_FALSE(mguid::SatisfiesBoolType<mguid::BoolType*>);
    REQUIRE_FALSE(mguid::SatisfiesBoolType<nullptr_t>);
    REQUIRE_FALSE(mguid::SatisfiesBoolType<std::monostate>);
    REQUIRE_FALSE(mguid::SatisfiesBoolType<std::nullopt_t>);
    REQUIRE_FALSE(mguid::SatisfiesBoolType<mguid::NullType>);
    REQUIRE_FALSE(mguid::SatisfiesBoolType<mguid::NumberType>);
    REQUIRE_FALSE(mguid::SatisfiesBoolType<mguid::StringType>);
  }
  SECTION("Number Type") {
    REQUIRE(mguid::SatisfiesNumberType<mguid::NumberType>);
    REQUIRE(mguid::SatisfiesNumberType<mguid::NumberType&>);
    REQUIRE(mguid::SatisfiesNumberType<mguid::NumberType&&>);
    REQUIRE(mguid::SatisfiesNumberType<const mguid::NumberType>);
    REQUIRE(mguid::SatisfiesNumberType<const mguid::NumberType&>);
    REQUIRE(mguid::SatisfiesNumberType<volatile mguid::NumberType>);
    REQUIRE(mguid::SatisfiesNumberType<volatile mguid::NumberType&>);
    REQUIRE(mguid::SatisfiesNumberType<const volatile mguid::NumberType>);
    REQUIRE(mguid::SatisfiesNumberType<std::uint8_t>);
    REQUIRE(mguid::SatisfiesNumberType<std::uint16_t>);
    REQUIRE(mguid::SatisfiesNumberType<std::uint32_t>);
    REQUIRE(mguid::SatisfiesNumberType<std::uint64_t>);
    REQUIRE(mguid::SatisfiesNumberType<std::int8_t>);
    REQUIRE(mguid::SatisfiesNumberType<std::int16_t>);
    REQUIRE(mguid::SatisfiesNumberType<std::int32_t>);
    REQUIRE(mguid::SatisfiesNumberType<std::int64_t>);
    REQUIRE(mguid::SatisfiesNumberType<float>);
    REQUIRE(mguid::SatisfiesNumberType<double>);
    REQUIRE(mguid::SatisfiesNumberType<std::size_t>);
    REQUIRE(mguid::SatisfiesNumberType<std::ptrdiff_t>);
    REQUIRE_FALSE(mguid::SatisfiesNumberType<void>);
    REQUIRE_FALSE(mguid::SatisfiesNumberType<mguid::NumberType*>);
    REQUIRE_FALSE(mguid::SatisfiesNumberType<nullptr_t>);
    REQUIRE_FALSE(mguid::SatisfiesNumberType<std::monostate>);
    REQUIRE_FALSE(mguid::SatisfiesNumberType<std::nullopt_t>);
    REQUIRE_FALSE(mguid::SatisfiesNumberType<mguid::NullType>);
    REQUIRE_FALSE(mguid::SatisfiesNumberType<mguid::BoolType>);
    REQUIRE_FALSE(mguid::SatisfiesNumberType<mguid::StringType>);
  }
}