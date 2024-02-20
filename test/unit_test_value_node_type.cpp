/**
 * @brief Tests for value node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include <datatree/node_types/value_node_type.hpp>

TEST_CASE("Value Node Type Constructor") {
  SECTION("Default Constructor") {
    REQUIRE(std::is_nothrow_default_constructible_v<mguid::ValueNodeType>);
    mguid::ValueNodeType vnt1{};
    REQUIRE(vnt1.HasNull());
  }
  SECTION("Copy Constructor") {
    REQUIRE(std::is_copy_constructible_v<mguid::ValueNodeType>);
    mguid::ValueNodeType vnt1;
    mguid::ValueNodeType vnt2{vnt1};
    REQUIRE(vnt1.HasNull());
    REQUIRE(vnt2.HasNull());
  }
  SECTION("Move Constructor") {
    REQUIRE(std::is_nothrow_move_constructible_v<mguid::ValueNodeType>);
    mguid::ValueNodeType vnt1;
    mguid::ValueNodeType vnt2{std::move(vnt1)};
    REQUIRE(vnt2.HasNull());
  }
  SECTION("Copy Assignment") {
    REQUIRE(std::is_copy_constructible_v<mguid::ValueNodeType>);
    mguid::ValueNodeType vnt1;
    mguid::ValueNodeType vnt2;
    vnt2 = vnt1;
    REQUIRE(vnt1.HasNull());
    REQUIRE(vnt2.HasNull());
  }
  SECTION("Move Assignment") {
    REQUIRE(std::is_nothrow_move_constructible_v<mguid::ValueNodeType>);
    mguid::ValueNodeType vnt1;
    mguid::ValueNodeType vnt2;
    vnt2 = std::move(vnt1);
    REQUIRE(vnt2.HasNull());
  }
  SECTION("Nullptr Constructor") {
    REQUIRE(std::is_nothrow_constructible_v<mguid::ValueNodeType, nullptr_t>);
    mguid::ValueNodeType vnt1{nullptr};
    REQUIRE(vnt1.HasNull());
  }
  SECTION("Construction From Value") {
    {
      REQUIRE(std::is_nothrow_constructible_v<mguid::ValueNodeType,
                                              mguid::NullType>);
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.HasNull());
    }
    {
      REQUIRE(std::is_nothrow_constructible_v<mguid::ValueNodeType,
                                              mguid::BoolType>);
      mguid::ValueNodeType vnt1{true};
      REQUIRE(vnt1.HasBool());
      mguid::ValueNodeType vnt2{false};
      REQUIRE(vnt1.HasBool());
    }
    {
      REQUIRE(std::is_nothrow_constructible_v<mguid::ValueNodeType,
                                              mguid::NumberType>);
      {
        mguid::ValueNodeType vnt1{mguid::NumberType{}};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(
          std::is_nothrow_constructible_v<mguid::ValueNodeType, std::uint8_t>);
      {
        mguid::ValueNodeType vnt1{std::uint8_t{}};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(
          std::is_nothrow_constructible_v<mguid::ValueNodeType, std::uint16_t>);
      {
        mguid::ValueNodeType vnt1{std::uint16_t{}};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(
          std::is_nothrow_constructible_v<mguid::ValueNodeType, std::uint32_t>);
      {
        mguid::ValueNodeType vnt1{std::uint32_t{}};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(
          std::is_nothrow_constructible_v<mguid::ValueNodeType, std::uint64_t>);
      {
        mguid::ValueNodeType vnt1{std::uint64_t{}};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(
          std::is_nothrow_constructible_v<mguid::ValueNodeType, std::int8_t>);
      {
        mguid::ValueNodeType vnt1{std::int8_t{}};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(
          std::is_nothrow_constructible_v<mguid::ValueNodeType, std::int16_t>);
      {
        mguid::ValueNodeType vnt1{std::int16_t{}};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(
          std::is_nothrow_constructible_v<mguid::ValueNodeType, std::int32_t>);
      {
        mguid::ValueNodeType vnt1{std::int32_t{}};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(
          std::is_nothrow_constructible_v<mguid::ValueNodeType, std::int64_t>);
      {
        mguid::ValueNodeType vnt1{std::int64_t{}};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(std::is_nothrow_constructible_v<mguid::ValueNodeType, float>);
      {
        mguid::ValueNodeType vnt1{float{}};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(std::is_nothrow_constructible_v<mguid::ValueNodeType, double>);
      {
        mguid::ValueNodeType vnt1{double{}};
        REQUIRE(vnt1.HasNumber());
      }
    }
    {
      REQUIRE_FALSE(
          std::is_nothrow_constructible_v<mguid::ValueNodeType, std::string>);
      REQUIRE_FALSE(
          std::is_nothrow_constructible_v<mguid::ValueNodeType, const char*>);
      REQUIRE_FALSE(
          std::is_nothrow_constructible_v<mguid::ValueNodeType, char[]>);
      REQUIRE(std::is_constructible_v<mguid::ValueNodeType, std::string>);
      {
        mguid::ValueNodeType vnt1{std::string{}};
        REQUIRE(vnt1.HasString());
      }
      REQUIRE(std::is_constructible_v<mguid::ValueNodeType, const char*>);
      {
        mguid::ValueNodeType vnt1{""};
        REQUIRE(vnt1.HasString());
      }
      REQUIRE(std::is_constructible_v<mguid::ValueNodeType, char[]>);
      {
        char c_array[] = "";
        mguid::ValueNodeType vnt1{c_array};
        REQUIRE(vnt1.HasString());
      }
    }
  }
  SECTION("Assignment From Value") {
    {
      REQUIRE(
          std::is_nothrow_assignable_v<mguid::ValueNodeType, mguid::NullType>);
      mguid::ValueNodeType vnt1;
      vnt1 = mguid::NullType{};
      REQUIRE(vnt1.HasNull());
    }
    {
      REQUIRE(
          std::is_nothrow_assignable_v<mguid::ValueNodeType, mguid::BoolType>);
      mguid::ValueNodeType vnt1;
      vnt1 = true;
      REQUIRE(vnt1.HasBool());
      mguid::ValueNodeType vnt2;
      vnt2 = false;
      REQUIRE(vnt1.HasBool());
    }
    {
      REQUIRE(std::is_nothrow_assignable_v<mguid::ValueNodeType,
                                           mguid::NumberType>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = mguid::NumberType{};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(std::is_nothrow_assignable_v<mguid::ValueNodeType, std::uint8_t>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = std::uint8_t{};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(
          std::is_nothrow_assignable_v<mguid::ValueNodeType, std::uint16_t>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = std::uint16_t{};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(
          std::is_nothrow_assignable_v<mguid::ValueNodeType, std::uint32_t>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = std::uint32_t{};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(
          std::is_nothrow_assignable_v<mguid::ValueNodeType, std::uint64_t>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = std::uint64_t{};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(std::is_nothrow_assignable_v<mguid::ValueNodeType, std::int8_t>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = std::int8_t{};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(std::is_nothrow_assignable_v<mguid::ValueNodeType, std::int16_t>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = std::int16_t{};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(std::is_nothrow_assignable_v<mguid::ValueNodeType, std::int32_t>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = std::int32_t{};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(std::is_nothrow_assignable_v<mguid::ValueNodeType, std::int64_t>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = std::int64_t{};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(std::is_nothrow_assignable_v<mguid::ValueNodeType, float>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = float{};
        REQUIRE(vnt1.HasNumber());
      }
      REQUIRE(std::is_nothrow_assignable_v<mguid::ValueNodeType, double>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = double{};
        REQUIRE(vnt1.HasNumber());
      }
    }
    {
      REQUIRE_FALSE(
          std::is_nothrow_assignable_v<mguid::ValueNodeType, std::string>);
      REQUIRE_FALSE(
          std::is_nothrow_assignable_v<mguid::ValueNodeType, const char*>);
      REQUIRE_FALSE(std::is_nothrow_assignable_v<mguid::ValueNodeType, char[]>);
      REQUIRE(std::is_assignable_v<mguid::ValueNodeType, std::string>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = std::string{};
        REQUIRE(vnt1.HasString());
      }
      REQUIRE(std::is_assignable_v<mguid::ValueNodeType, const char*>);
      {
        mguid::ValueNodeType vnt1;
        vnt1 = "";
        REQUIRE(vnt1.HasString());
      }
      REQUIRE(std::is_assignable_v<mguid::ValueNodeType, char[]>);
      {
        char c_array[] = "";
        mguid::ValueNodeType vnt1;
        vnt1 = c_array;
        REQUIRE(vnt1.HasString());
      }
    }
  }
}

TEST_CASE("Value Node Type Value") {
  SECTION("Default Constructed") {
    mguid::ValueNodeType vnt1;
    REQUIRE(vnt1.HasNull());
  }
  SECTION("Nullptr Constructed") {
    mguid::ValueNodeType vnt1{nullptr};
    REQUIRE(vnt1.HasNull());
  }
  SECTION("Constructed With Null") {
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.HasNull());
      REQUIRE(vnt1.GetNull() == mguid::NullType{});
    }
  }
  SECTION("Constructed With Integer") {
    {
      mguid::ValueNodeType vnt1{std::int8_t{1}};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetInt().value() ==
              mguid::IntegerType{1});
    }
    {
      mguid::ValueNodeType vnt1{std::int16_t{1}};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetInt().value() ==
              mguid::IntegerType{1});
    }
    {
      mguid::ValueNodeType vnt1{std::int32_t{1}};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetInt().value() ==
              mguid::IntegerType{1});
    }
    {
      mguid::ValueNodeType vnt1{std::int64_t{1}};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetInt().value() ==
              mguid::IntegerType{1});
    }
  }
  SECTION("Constructed With Unsigned Integer") {
    {
      mguid::ValueNodeType vnt1{std::uint8_t{1}};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetUInt().value() ==
              mguid::UnsignedIntegerType{1});
    }
    {
      mguid::ValueNodeType vnt1{std::uint16_t{1}};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetUInt().value() ==
              mguid::UnsignedIntegerType{1});
    }
    {
      mguid::ValueNodeType vnt1{std::uint32_t{1}};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetUInt().value() ==
              mguid::UnsignedIntegerType{1});
    }
    {
      mguid::ValueNodeType vnt1{std::uint64_t{1}};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetUInt().value() ==
              mguid::UnsignedIntegerType{1});
    }
  }
  SECTION("Constructed With Float") {
    {
      mguid::ValueNodeType vnt1{float{1}};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetDouble().value() ==
              mguid::DoubleType{1});
    }
    {
      mguid::ValueNodeType vnt1{double{1}};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetDouble().value() ==
              mguid::DoubleType{1});
    }
  }
  SECTION("Constructed With Bool") {
    {
      mguid::ValueNodeType vnt1{true};
      REQUIRE(vnt1.HasBool());
      REQUIRE(vnt1.GetBool().value());
    }
    {
      mguid::ValueNodeType vnt1{false};
      REQUIRE(vnt1.HasBool());
      REQUIRE_FALSE(vnt1.GetBool().value());
    }
  }
  SECTION("Constructed With String") {
    {
      mguid::ValueNodeType vnt1{std::string{"test"}};
      REQUIRE(vnt1.HasString());
      REQUIRE(vnt1.GetString().value() == "test");
    }
    {
      mguid::ValueNodeType vnt1{"test"};
      REQUIRE(vnt1.HasString());
      REQUIRE(vnt1.GetString().value() == "test");
    }
    {
      char test[] = "test";
      mguid::ValueNodeType vnt1{test};
      REQUIRE(vnt1.HasString());
      REQUIRE(vnt1.GetString().value() == "test");
    }
  }
  SECTION("Assign Null") {
    {
      mguid::ValueNodeType vnt1;
      vnt1 = mguid::NullType{};
      REQUIRE(vnt1.HasNull());
      REQUIRE(vnt1.GetNull() == mguid::NullType{});
    }
  }
  SECTION("Assign Value Integer") {
    {
      mguid::ValueNodeType vnt1;
      vnt1 = std::int8_t{1};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetInt().value() ==
              mguid::IntegerType{1});
    }
    {
      mguid::ValueNodeType vnt1;
      vnt1 = std::int16_t{1};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetInt().value() ==
              mguid::IntegerType{1});
    }
    {
      mguid::ValueNodeType vnt1;
      vnt1 = std::int32_t{1};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetInt().value() ==
              mguid::IntegerType{1});
    }
    {
      mguid::ValueNodeType vnt1;
      vnt1 = std::int64_t{1};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetInt().value() ==
              mguid::IntegerType{1});
    }
  }
  SECTION("Assign Value Unsigned Integer") {
    {
      mguid::ValueNodeType vnt1;
      vnt1 = std::uint8_t{1};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetUInt().value() ==
              mguid::UnsignedIntegerType{1});
    }
    {
      mguid::ValueNodeType vnt1;
      vnt1 = std::uint16_t{1};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetUInt().value() ==
              mguid::UnsignedIntegerType{1});
    }
    {
      mguid::ValueNodeType vnt1;
      vnt1 = std::uint32_t{1};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetUInt().value() ==
              mguid::UnsignedIntegerType{1});
    }
    {
      mguid::ValueNodeType vnt1;
      vnt1 = std::uint64_t{1};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetUInt().value() ==
              mguid::UnsignedIntegerType{1});
    }
  }
  SECTION("Assign Value Float") {
    {
      mguid::ValueNodeType vnt1;
      vnt1 = float{1};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetDouble().value() ==
              mguid::DoubleType{1});
    }
    {
      mguid::ValueNodeType vnt1;
      vnt1 = double{1};
      REQUIRE(vnt1.HasNumber());
      REQUIRE(vnt1.GetNumber().value().GetDouble().value() ==
              mguid::DoubleType{1});
    }
  }
  SECTION("Assign Bool") {
    {
      mguid::ValueNodeType vnt1;
      vnt1 = true;
      REQUIRE(vnt1.HasBool());
      REQUIRE(vnt1.GetBool().value());
    }
    {
      mguid::ValueNodeType vnt1;
      vnt1 = false;
      REQUIRE(vnt1.HasBool());
      REQUIRE_FALSE(vnt1.GetBool().value());
    }
  }
  SECTION("Assign String") {
    {
      mguid::ValueNodeType vnt1;
      vnt1 = std::string{"test"};
      REQUIRE(vnt1.HasString());
      REQUIRE(vnt1.GetString().value() == "test");
    }
    {
      mguid::ValueNodeType vnt1;
      vnt1 = "test";
      REQUIRE(vnt1.HasString());
      REQUIRE(vnt1.GetString().value() == "test");
    }
    {
      char test[] = "test";
      mguid::ValueNodeType vnt1;
      vnt1 = test;
      REQUIRE(vnt1.HasString());
      REQUIRE(vnt1.GetString().value() == "test");
    }
  }
}

TEST_CASE("Value Node Type TryGet Or Default") {
  SECTION("TryGet Null Or const &") {
    {
      mguid::ValueNodeType vnt1{mguid::StringType{}};
      REQUIRE(vnt1.GetNullOr(mguid::NullType{}).value() == mguid::NullType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.GetNullOr(mguid::NullType{}).value() == mguid::NullType{});
    }
  }
  SECTION("TryGet Null Or &&") {
    {
      mguid::ValueNodeType vnt1{mguid::StringType{}};
      REQUIRE(std::move(vnt1).GetNullOr(mguid::NullType{}).value() == mguid::NullType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).GetNullOr(mguid::NullType{}).value() == mguid::NullType{});
    }
  }
  SECTION("TryGet Bool Or const &") {
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.GetBoolOr(true).value());
    }
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE_FALSE(vnt1.GetBoolOr(false).value());
    }
    {
      mguid::ValueNodeType vnt1{mguid::BoolType{true}};
      REQUIRE(vnt1.GetBoolOr(false).value());
    }
    {
      mguid::ValueNodeType vnt1{false};
      REQUIRE_FALSE(vnt1.GetBoolOr(true).value());
    }
  }
  SECTION("TryGet Bool Or &&") {
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).GetBoolOr(true).value());
    }
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE_FALSE(std::move(vnt1).GetBoolOr(false).value());
    }
    {
      mguid::ValueNodeType vnt1{mguid::BoolType{true}};
      REQUIRE(std::move(vnt1).GetBoolOr(false).value());
    }
    {
      mguid::ValueNodeType vnt1{false};
      REQUIRE_FALSE(std::move(vnt1).GetBoolOr(true).value());
    }
  }
  SECTION("TryGet Number Or const &") {
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.GetNumberOr(2).value() == mguid::NumberType(2));
    }
    {
      mguid::ValueNodeType vnt1{mguid::NumberType{3}};
      REQUIRE(vnt1.GetNumberOr(2).value() == mguid::NumberType(3));
    }
  }
  SECTION("TryGet Number Or &&") {
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).GetNumberOr(2).value() == mguid::NumberType(2));
    }
    {
      mguid::ValueNodeType vnt1{mguid::NumberType{3}};
      REQUIRE(std::move(vnt1).GetNumberOr(2).value() == mguid::NumberType(3));
    }
  }
  SECTION("TryGet String Or const &") {
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.GetStringOr("test").value() == "test");
    }
    {
      mguid::ValueNodeType vnt1{mguid::StringType{"test"}};
      REQUIRE(vnt1.GetStringOr("nottest").value() == "test");
    }
  }
  SECTION("TryGet String Or &&") {
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).GetStringOr("test").value() == "test");
    }
    {
      mguid::ValueNodeType vnt1{mguid::StringType{"test"}};
      REQUIRE(std::move(vnt1).GetStringOr("nottest").value() == "test");
    }
  }
}

TEST_CASE("Value Node Type If Type Then") {
  SECTION("If Null Then &") {
    constexpr auto then_func = [](auto) { return mguid::ValueNodeType{}; };
    {
      mguid::ValueNodeType vnt1{mguid::StringType{}};
      REQUIRE(vnt1.IfNullThen(then_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfNullThen(then_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
  }
  SECTION("If Null Then const &") {
    constexpr auto then_func = [](auto) { return mguid::ValueNodeType{}; };
    {
      const mguid::ValueNodeType vnt1{mguid::StringType{}};
      REQUIRE(vnt1.IfNullThen(then_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
    {
      const mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfNullThen(then_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
  }
  SECTION("If Null Then &&") {
    constexpr auto then_func = [](auto) { return mguid::ValueNodeType{}; };
    {
      mguid::ValueNodeType vnt1{mguid::StringType{}};
      REQUIRE(std::move(vnt1).IfNullThen(then_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).IfNullThen(then_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
  }
  SECTION("If Null Then const &&") {
    constexpr auto then_func = [](auto) { return mguid::ValueNodeType{}; };
    {
      mguid::ValueNodeType vnt1{mguid::StringType{}};

      REQUIRE([then_func](const auto&& vnt) {
        return (vnt.IfNullThen(then_func) ==
                mguid::ValueNodeType{mguid::NullType{}});
      }(std::move(vnt1)));
    }
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};

      REQUIRE([then_func](const auto&& vnt) {
        return (vnt.IfNullThen(then_func) ==
                mguid::ValueNodeType{mguid::NullType{}});
      }(std::move(vnt1)));
    }
  }
  SECTION("If Bool Then &") {
    constexpr auto then_func = [](auto val) {
      return mguid::ValueNodeType{!val};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfBoolThen(then_func) == mguid::ValueNodeType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::BoolType{true}};
      REQUIRE_FALSE(vnt1.IfBoolThen(then_func).GetBool().value());
    }
  }
  SECTION("If Bool Then const &") {
    constexpr auto then_func = [](auto val) {
      return mguid::ValueNodeType{!val};
    };
    {
      const mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfBoolThen(then_func) == mguid::ValueNodeType{});
    }
    {
      const mguid::ValueNodeType vnt1{mguid::BoolType{true}};
      REQUIRE_FALSE(vnt1.IfBoolThen(then_func).GetBool().value());
    }
  }
  SECTION("If Bool Then &&") {
    constexpr auto then_func = [](auto val) {
      return mguid::ValueNodeType{!val};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).IfBoolThen(then_func) == mguid::ValueNodeType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::BoolType{true}};
      REQUIRE_FALSE(std::move(vnt1).IfBoolThen(then_func).GetBool().value());
    }
  }
  SECTION("If Bool Then const &&") {
    constexpr auto then_func = [](auto val) {
      return mguid::ValueNodeType{!val};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE([then_func](const auto&& vnt) {
        return (vnt.IfBoolThen(then_func) == mguid::ValueNodeType{});
      }(std::move(vnt1)));
    }
    {
      mguid::ValueNodeType vnt1{mguid::BoolType{true}};
      REQUIRE_FALSE([then_func](const auto&& vnt) {
        return (vnt.IfBoolThen(then_func).GetBool().value());
      }(std::move(vnt1)));
    }
  }
  SECTION("If Number Then &") {
    constexpr auto then_func = [](auto val) {
      return mguid::ValueNodeType{val.GetInt().value() + 2};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfNumberThen(then_func) == mguid::ValueNodeType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::NumberType{3}};
      REQUIRE(vnt1.IfNumberThen(then_func) == mguid::ValueNodeType{5});
    }
  }
  SECTION("If Number Then const &") {
    constexpr auto then_func = [](auto val) {
      return mguid::ValueNodeType{val.GetInt().value() + 2};
    };
    {
      const mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfNumberThen(then_func) == mguid::ValueNodeType{});
    }
    {
      const mguid::ValueNodeType vnt1{mguid::NumberType{3}};
      REQUIRE(vnt1.IfNumberThen(then_func) == mguid::ValueNodeType{5});
    }
  }
  SECTION("If Number Then &&") {
    constexpr auto then_func = [](auto val) {
      return mguid::ValueNodeType{val.GetInt().value() + 2};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).IfNumberThen(then_func) ==
              mguid::ValueNodeType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::NumberType{3}};
      REQUIRE(std::move(vnt1).IfNumberThen(then_func) ==
              mguid::ValueNodeType{5});
    }
  }
  SECTION("If Number Then const &&") {
    constexpr auto then_func = [](auto val) {
      return mguid::ValueNodeType{val.GetInt().value() + 2};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE([then_func](const auto&& vnt) {
        return (vnt.IfNumberThen(then_func) == mguid::ValueNodeType{});
      }(std::move(vnt1)));
    }
    {
      mguid::ValueNodeType vnt1{mguid::NumberType{3}};
      REQUIRE([then_func](const auto&& vnt) {
        return (vnt.IfNumberThen(then_func) == mguid::ValueNodeType{5});
      }(std::move(vnt1)));
    }
  }
  SECTION("If String Then &") {
    constexpr auto then_func = [](auto val) {
      return mguid::ValueNodeType{val + "test"};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfStringThen(then_func) == mguid::ValueNodeType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::StringType{"test"}};
      REQUIRE(vnt1.IfStringThen(then_func) == mguid::ValueNodeType{"testtest"});
    }
  }
  SECTION("If String Then const &") {
    constexpr auto then_func = [](auto val) {
      return mguid::ValueNodeType{val + "test"};
    };
    {
      const mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfStringThen(then_func) == mguid::ValueNodeType{});
    }
    {
      const mguid::ValueNodeType vnt1{mguid::StringType{"test"}};
      REQUIRE(vnt1.IfStringThen(then_func) == mguid::ValueNodeType{"testtest"});
    }
  }
  SECTION("If String Then &&") {
    constexpr auto then_func = [](auto val) {
      return mguid::ValueNodeType{val + "test"};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).IfStringThen(then_func) ==
              mguid::ValueNodeType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::StringType{"test"}};
      REQUIRE(std::move(vnt1).IfStringThen(then_func) ==
              mguid::ValueNodeType{"testtest"});
    }
  }
  SECTION("If String Then const &&") {
    constexpr auto then_func = [](auto val) {
      return mguid::ValueNodeType{val + "test"};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE([then_func](const auto&& vnt) {
        return (vnt.IfStringThen(then_func) == mguid::ValueNodeType{});
      }(std::move(vnt1)));
    }
    {
      mguid::ValueNodeType vnt1{mguid::StringType{"test"}};
      REQUIRE([then_func](const auto&& vnt) {
        return (vnt.IfStringThen(then_func) ==
                mguid::ValueNodeType{"testtest"});
      }(std::move(vnt1)));
    }
  }
}

// These tests look nearly the exact same as the ones for If Type Then
// The difference is internally that If<type>Then must directly construct a
// ValueNodeType where If<type>Transform can return something convertible to
// ValueNodeType which also includes ValueNodeType
TEST_CASE("Value Node Type If Type Transform") {
  SECTION("If Null Then &") {
    constexpr auto transform_func = [](auto) { return mguid::ValueNodeType{}; };
    {
      mguid::ValueNodeType vnt1{mguid::StringType{}};
      REQUIRE(vnt1.IfNullTransform(transform_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfNullTransform(transform_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
  }
  SECTION("If Null Then const &") {
    constexpr auto transform_func = [](auto) { return mguid::ValueNodeType{}; };
    {
      const mguid::ValueNodeType vnt1{mguid::StringType{}};
      REQUIRE(vnt1.IfNullTransform(transform_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
    {
      const mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfNullTransform(transform_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
  }
  SECTION("If Null Then &&") {
    constexpr auto transform_func = [](auto) { return mguid::ValueNodeType{}; };
    {
      mguid::ValueNodeType vnt1{mguid::StringType{}};
      REQUIRE(std::move(vnt1).IfNullTransform(transform_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).IfNullTransform(transform_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
  }
  SECTION("If Null Then const &&") {
    constexpr auto transform_func = [](auto) { return mguid::ValueNodeType{}; };
    {
      mguid::ValueNodeType vnt1{mguid::StringType{}};

      REQUIRE([transform_func](const auto&& vnt) {
        return (vnt.IfNullTransform(transform_func) ==
                mguid::ValueNodeType{mguid::NullType{}});
      }(std::move(vnt1)));
    }
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};

      REQUIRE([transform_func](const auto&& vnt) {
        return (vnt.IfNullTransform(transform_func) ==
                mguid::ValueNodeType{mguid::NullType{}});
      }(std::move(vnt1)));
    }
  }
  SECTION("If Bool Then &") {
    constexpr auto transform_func = [](auto val) {
      return mguid::ValueNodeType{!val};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfBoolTransform(transform_func) == mguid::ValueNodeType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::BoolType{true}};
      REQUIRE_FALSE(vnt1.IfBoolTransform(transform_func).GetBool().value());
    }
  }
  SECTION("If Bool Then const &") {
    constexpr auto transform_func = [](auto val) {
      return mguid::ValueNodeType{!val};
    };
    {
      const mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfBoolTransform(transform_func) == mguid::ValueNodeType{});
    }
    {
      const mguid::ValueNodeType vnt1{mguid::BoolType{true}};
      REQUIRE_FALSE(vnt1.IfBoolTransform(transform_func).GetBool().value());
    }
  }
  SECTION("If Bool Then &&") {
    constexpr auto transform_func = [](auto val) {
      return mguid::ValueNodeType{!val};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).IfBoolTransform(transform_func) ==
              mguid::ValueNodeType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::BoolType{true}};
      REQUIRE_FALSE(
          std::move(vnt1).IfBoolTransform(transform_func).GetBool().value());
    }
  }
  SECTION("If Bool Then const &&") {
    constexpr auto transform_func = [](auto val) {
      return mguid::ValueNodeType{!val};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE([transform_func](const auto&& vnt) {
        return (vnt.IfBoolTransform(transform_func) == mguid::ValueNodeType{});
      }(std::move(vnt1)));
    }
    {
      mguid::ValueNodeType vnt1{mguid::BoolType{true}};
      REQUIRE_FALSE([transform_func](const auto&& vnt) {
        return (vnt.IfBoolTransform(transform_func).GetBool().value());
      }(std::move(vnt1)));
    }
  }
  SECTION("If Number Then &") {
    constexpr auto transform_func = [](auto val) {
      return mguid::ValueNodeType{val.GetInt().value() + 2};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfNumberTransform(transform_func) == mguid::ValueNodeType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::NumberType{3}};
      REQUIRE(vnt1.IfNumberTransform(transform_func) ==
              mguid::ValueNodeType{5});
    }
  }
  SECTION("If Number Then const &") {
    constexpr auto transform_func = [](auto val) {
      return mguid::ValueNodeType{val.GetInt().value() + 2};
    };
    {
      const mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfNumberTransform(transform_func) == mguid::ValueNodeType{});
    }
    {
      const mguid::ValueNodeType vnt1{mguid::NumberType{3}};
      REQUIRE(vnt1.IfNumberTransform(transform_func) ==
              mguid::ValueNodeType{5});
    }
  }
  SECTION("If Number Then &&") {
    constexpr auto transform_func = [](auto val) {
      return mguid::ValueNodeType{val.GetInt().value() + 2};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).IfNumberTransform(transform_func) ==
              mguid::ValueNodeType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::NumberType{3}};
      REQUIRE(std::move(vnt1).IfNumberTransform(transform_func) ==
              mguid::ValueNodeType{5});
    }
  }
  SECTION("If Number Then const &&") {
    constexpr auto transform_func = [](auto val) {
      return mguid::ValueNodeType{val.GetInt().value() + 2};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE([transform_func](const auto&& vnt) {
        return (vnt.IfNumberTransform(transform_func) ==
                mguid::ValueNodeType{});
      }(std::move(vnt1)));
    }
    {
      mguid::ValueNodeType vnt1{mguid::NumberType{3}};
      REQUIRE([transform_func](const auto&& vnt) {
        return (vnt.IfNumberTransform(transform_func) ==
                mguid::ValueNodeType{5});
      }(std::move(vnt1)));
    }
  }
  SECTION("If String Then &") {
    constexpr auto transform_func = [](auto val) {
      return mguid::ValueNodeType{val + "test"};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfStringTransform(transform_func) == mguid::ValueNodeType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::StringType{"test"}};
      REQUIRE(vnt1.IfStringTransform(transform_func) ==
              mguid::ValueNodeType{"testtest"});
    }
  }
  SECTION("If String Then const &") {
    constexpr auto transform_func = [](auto val) {
      return mguid::ValueNodeType{val + "test"};
    };
    {
      const mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfStringTransform(transform_func) == mguid::ValueNodeType{});
    }
    {
      const mguid::ValueNodeType vnt1{mguid::StringType{"test"}};
      REQUIRE(vnt1.IfStringTransform(transform_func) ==
              mguid::ValueNodeType{"testtest"});
    }
  }
  SECTION("If String Then &&") {
    constexpr auto transform_func = [](auto val) {
      return mguid::ValueNodeType{val + "test"};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).IfStringTransform(transform_func) ==
              mguid::ValueNodeType{});
    }
    {
      mguid::ValueNodeType vnt1{mguid::StringType{"test"}};
      REQUIRE(std::move(vnt1).IfStringTransform(transform_func) ==
              mguid::ValueNodeType{"testtest"});
    }
  }
  SECTION("If String Then const &&") {
    constexpr auto transform_func = [](auto val) {
      return mguid::ValueNodeType{val + "test"};
    };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE([transform_func](const auto&& vnt) {
        return (vnt.IfStringTransform(transform_func) ==
                mguid::ValueNodeType{});
      }(std::move(vnt1)));
    }
    {
      mguid::ValueNodeType vnt1{mguid::StringType{"test"}};
      REQUIRE([transform_func](const auto&& vnt) {
        return (vnt.IfStringTransform(transform_func) ==
                mguid::ValueNodeType{"testtest"});
      }(std::move(vnt1)));
    }
  }
}

TEST_CASE("Value Node Type If Not Type") {
  SECTION("If Null Then const &") {
    constexpr auto else_func = []() { return mguid::ValueNodeType{}; };
    {
      const mguid::ValueNodeType vnt1{mguid::StringType{}};
      REQUIRE(vnt1.IfNotNull(else_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
    {
      const mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfNotNull(else_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
  }
  SECTION("If Null Then &&") {
    constexpr auto else_func = []() { return mguid::ValueNodeType{}; };
    {
      mguid::ValueNodeType vnt1{mguid::StringType{}};
      REQUIRE(std::move(vnt1).IfNotNull(else_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).IfNotNull(else_func) ==
              mguid::ValueNodeType{mguid::NullType{}});
    }
  }
  SECTION("If Bool Then const &") {
    constexpr auto else_func = []() { return mguid::ValueNodeType{true}; };
    {
      const mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfNotBool(else_func) == mguid::ValueNodeType{true});
    }
    {
      const mguid::ValueNodeType vnt1{mguid::BoolType{false}};
      REQUIRE_FALSE(vnt1.IfNotBool(else_func).GetBool().value());
    }
  }
  SECTION("If Bool Then &&") {
    constexpr auto else_func = []() { return mguid::ValueNodeType{true}; };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).IfNotBool(else_func) ==
              mguid::ValueNodeType{true});
    }
    {
      mguid::ValueNodeType vnt1{mguid::BoolType{false}};
      REQUIRE_FALSE(std::move(vnt1).IfNotBool(else_func).GetBool().value());
    }
  }
  SECTION("If Number Then const &") {
    constexpr auto else_func = []() { return mguid::ValueNodeType{2}; };
    {
      const mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfNotNumber(else_func) == mguid::ValueNodeType{2});
    }
    {
      const mguid::ValueNodeType vnt1{mguid::NumberType{3}};
      REQUIRE(vnt1.IfNotNumber(else_func) == mguid::ValueNodeType{3});
    }
  }
  SECTION("If Number Then &&") {
    constexpr auto else_func = []() { return mguid::ValueNodeType{2}; };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).IfNotNumber(else_func) ==
              mguid::ValueNodeType{2});
    }
    {
      mguid::ValueNodeType vnt1{mguid::NumberType{3}};
      REQUIRE(std::move(vnt1).IfNotNumber(else_func) ==
              mguid::ValueNodeType{3});
    }
  }
  SECTION("If String Then const &") {
    constexpr auto else_func = []() { return mguid::ValueNodeType{"test"}; };
    {
      const mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(vnt1.IfNotString(else_func) == mguid::ValueNodeType{"test"});
    }
    {
      const mguid::ValueNodeType vnt1{mguid::StringType{"test2"}};
      REQUIRE(vnt1.IfNotString(else_func) == mguid::ValueNodeType{"test2"});
    }
  }
  SECTION("If String Then &&") {
    constexpr auto else_func = []() { return mguid::ValueNodeType{"test"}; };
    {
      mguid::ValueNodeType vnt1{mguid::NullType{}};
      REQUIRE(std::move(vnt1).IfNotString(else_func) ==
              mguid::ValueNodeType{"test"});
    }
    {
      mguid::ValueNodeType vnt1{mguid::StringType{"test2"}};
      REQUIRE(std::move(vnt1).IfNotString(else_func) ==
              mguid::ValueNodeType{"test2"});
    }
  }
}

TEST_CASE("Value Node Type Three Way Comparison") {
  SECTION("Equality") {
    REQUIRE(mguid::ValueNodeType(mguid::StringType{}) ==
            mguid::ValueNodeType(mguid::StringType{}));
    REQUIRE(mguid::ValueNodeType(mguid::BoolType{}) ==
            mguid::ValueNodeType(mguid::BoolType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NullType{}) ==
            mguid::ValueNodeType(mguid::NullType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{}) ==
            mguid::ValueNodeType(mguid::NumberType{}));

    REQUIRE(mguid::ValueNodeType(mguid::StringType{"test"}) ==
            mguid::ValueNodeType(mguid::StringType{"test"}));
    REQUIRE(mguid::ValueNodeType(mguid::BoolType{true}) ==
            mguid::ValueNodeType(mguid::BoolType{true}));
    REQUIRE(mguid::ValueNodeType(mguid::NullType{}) ==
            mguid::ValueNodeType(mguid::NullType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1}) ==
            mguid::ValueNodeType(mguid::NumberType{1}));
  }
  SECTION("Inequality") {
    // Type Difference
    REQUIRE(mguid::ValueNodeType(mguid::StringType{}) !=
            mguid::ValueNodeType(mguid::NumberType{}));
    REQUIRE(mguid::ValueNodeType(mguid::StringType{}) !=
            mguid::ValueNodeType(mguid::BoolType{}));
    REQUIRE(mguid::ValueNodeType(mguid::StringType{}) !=
            mguid::ValueNodeType(mguid::NullType{}));

    REQUIRE(mguid::ValueNodeType(mguid::BoolType{}) !=
            mguid::ValueNodeType(mguid::StringType{}));
    REQUIRE(mguid::ValueNodeType(mguid::BoolType{}) !=
            mguid::ValueNodeType(mguid::NullType{}));
    REQUIRE(mguid::ValueNodeType(mguid::BoolType{}) !=
            mguid::ValueNodeType(mguid::NumberType{}));

    REQUIRE(mguid::ValueNodeType(mguid::NullType{}) !=
            mguid::ValueNodeType(mguid::StringType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NullType{}) !=
            mguid::ValueNodeType(mguid::BoolType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NullType{}) !=
            mguid::ValueNodeType(mguid::NumberType{}));

    REQUIRE(mguid::ValueNodeType(mguid::NumberType{}) !=
            mguid::ValueNodeType(mguid::StringType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{}) !=
            mguid::ValueNodeType(mguid::NullType{}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{}) !=
            mguid::ValueNodeType(mguid::BoolType{}));

    // NullType only has 1 value, so it is always equal to itself
    // Value Difference
    REQUIRE(mguid::ValueNodeType(mguid::StringType{"test"}) !=
            mguid::ValueNodeType(mguid::StringType{"notTest"}));
    REQUIRE(mguid::ValueNodeType(mguid::BoolType{true}) !=
            mguid::ValueNodeType(mguid::BoolType{false}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1}) !=
            mguid::ValueNodeType(mguid::NumberType{2}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1u}) !=
            mguid::ValueNodeType(mguid::NumberType{2u}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1.0}) !=
            mguid::ValueNodeType(mguid::NumberType{2.0}));

    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1}) !=
            mguid::ValueNodeType(mguid::NumberType{2.0}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1.0}) !=
            mguid::ValueNodeType(mguid::NumberType{2}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1u}) !=
            mguid::ValueNodeType(mguid::NumberType{2.0}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1.0}) !=
            mguid::ValueNodeType(mguid::NumberType{2u}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1u}) !=
            mguid::ValueNodeType(mguid::NumberType{2}));
    REQUIRE(mguid::ValueNodeType(mguid::NumberType{1}) !=
            mguid::ValueNodeType(mguid::NumberType{2u}));
  }
}