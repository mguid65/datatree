/**
 * @brief Tests for number value type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <cstdint>
#include <type_traits>
#include <utility>

#include <catch2/catch_all.hpp>

#include <datatree/node_types/detail/number_type.hpp>

TEST_CASE("Number Type Constructor") {
  SECTION("Default Construction") {
    REQUIRE(std::is_default_constructible_v<mguid::NumberType>);
    mguid::NumberType nt1;
    constexpr mguid::NumberType cnt1{};
    REQUIRE_FALSE(nt1.hasValue());
    REQUIRE_FALSE(cnt1.hasValue());
  }
  SECTION("Copy Construction") {
    REQUIRE(std::is_copy_constructible_v<mguid::NumberType>);
    mguid::NumberType nt1;
    mguid::NumberType nt2(nt1);
    REQUIRE_FALSE(nt1.hasValue());
    REQUIRE_FALSE(nt2.hasValue());
    constexpr mguid::NumberType cnt1{};
    constexpr mguid::NumberType cnt2{cnt1};
    mguid::NumberType nt3{cnt1};
    REQUIRE_FALSE(cnt1.hasValue());
    REQUIRE_FALSE(cnt2.hasValue());
    REQUIRE_FALSE(nt3.hasValue());
  }
  SECTION("Move Construction") {
    REQUIRE(std::is_move_constructible_v<mguid::NumberType>);
    mguid::NumberType nt1;
    mguid::NumberType nt2 = std::move(nt1);
    REQUIRE_FALSE(nt1.hasValue());
    REQUIRE_FALSE(nt2.hasValue());
  }
  SECTION("Copy Assignment") {
    REQUIRE(std::is_copy_assignable_v<mguid::NumberType>);
    mguid::NumberType nt1, nt2;
    nt2 = nt1;
    REQUIRE_FALSE(nt1.hasValue());
    REQUIRE_FALSE(nt2.hasValue());
    constexpr mguid::NumberType cnt1{};
    mguid::NumberType nt3;
    nt3 = cnt1;
    REQUIRE_FALSE(cnt1.hasValue());
    REQUIRE_FALSE(nt3.hasValue());
  }
  SECTION("Move Assignment") {
    REQUIRE(std::is_move_assignable_v<mguid::NumberType>);
    mguid::NumberType nt1, nt2;
    nt2 = std::move(nt1);
    REQUIRE_FALSE(nt1.hasValue());
    REQUIRE_FALSE(nt2.hasValue());
  }
  SECTION("Construct From Nullptr") {
    REQUIRE(std::is_constructible_v<mguid::NumberType, nullptr_t>);
    mguid::NumberType nt1{nullptr};
    REQUIRE_FALSE(nt1.hasValue());
    constexpr mguid::NumberType nt2{nullptr};
    REQUIRE_FALSE(nt2.hasValue());
  }
  SECTION("Construct From Value") {
    REQUIRE(std::is_constructible_v<mguid::NumberType, std::uint8_t>);
    {
      mguid::NumberType nt1{std::uint8_t{}};
      REQUIRE(nt1.hasValue());
    }
    REQUIRE(std::is_constructible_v<mguid::NumberType, std::uint16_t>);
    {
      mguid::NumberType nt1{std::uint16_t{}};
      REQUIRE(nt1.hasValue());
    }
    REQUIRE(std::is_constructible_v<mguid::NumberType, std::uint32_t>);
    {
      mguid::NumberType nt1{std::uint32_t{}};
      REQUIRE(nt1.hasValue());
    }
    REQUIRE(std::is_constructible_v<mguid::NumberType, std::uint64_t>);
    {
      mguid::NumberType nt1{std::uint64_t{}};
      REQUIRE(nt1.hasValue());
    }
    REQUIRE(std::is_constructible_v<mguid::NumberType, std::int8_t>);
    {
      mguid::NumberType nt1{std::int8_t{}};
      REQUIRE(nt1.hasValue());
    }
    REQUIRE(std::is_constructible_v<mguid::NumberType, std::int16_t>);
    {
      mguid::NumberType nt1{std::int16_t{}};
      REQUIRE(nt1.hasValue());
    }
    REQUIRE(std::is_constructible_v<mguid::NumberType, std::int32_t>);
    {
      mguid::NumberType nt1{std::int32_t{}};
      REQUIRE(nt1.hasValue());
    }
    REQUIRE(std::is_constructible_v<mguid::NumberType, std::int64_t>);
    {
      mguid::NumberType nt1{std::int64_t{}};
      REQUIRE(nt1.hasValue());
    }
    REQUIRE(std::is_constructible_v<mguid::NumberType, float>);
    {
      mguid::NumberType nt1{float{}};
      REQUIRE(nt1.hasValue());
    }
    REQUIRE(std::is_constructible_v<mguid::NumberType, double>);
    {
      mguid::NumberType nt1{double{}};
      REQUIRE(nt1.hasValue());
    }
  }

  SECTION("Bool Disallowed") {
    REQUIRE_FALSE(std::is_constructible_v<mguid::NumberType, bool>);
  }
}

TEST_CASE("Number Type Value") {
  SECTION("Default Constructed") {
    mguid::NumberType nt1;
    REQUIRE_FALSE(nt1.hasValue());
  }
  SECTION("Nullptr Constructed") {
    mguid::NumberType nt1{nullptr};
    REQUIRE_FALSE(nt1.hasValue());
  }
  SECTION("Constructed With Integer") {
    {
      mguid::NumberType nt1{std::int8_t{1}};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isInt());
      REQUIRE(nt1.getInt().value() == mguid::IntegerType{1});
    }
    {
      mguid::NumberType nt1{std::int16_t{1}};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isInt());
      REQUIRE(nt1.getInt().value() == mguid::IntegerType{1});
    }
    {
      mguid::NumberType nt1{std::int32_t{1}};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isInt());
      REQUIRE(nt1.getInt().value() == mguid::IntegerType{1});
    }
    {
      mguid::NumberType nt1{std::int64_t{1}};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isInt());
      REQUIRE(nt1.getInt().value() == mguid::IntegerType{1});
    }
  }
  SECTION("Constructed With Unsigned Integer") {
    {
      mguid::NumberType nt1{std::uint8_t{1}};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isUInt());
      REQUIRE(nt1.getUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      mguid::NumberType nt1{std::uint16_t{1}};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isUInt());
      REQUIRE(nt1.getUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      mguid::NumberType nt1{std::uint32_t{1}};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isUInt());
      REQUIRE(nt1.getUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      mguid::NumberType nt1{std::uint64_t{1}};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isUInt());
      REQUIRE(nt1.getUInt().value() == mguid::UnsignedIntegerType{1});
    }
  }
  SECTION("Constructed With Float") {
    {
      mguid::NumberType nt1{float{1}};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isDouble());
      REQUIRE(nt1.getDouble().value() == mguid::DoubleType{1});
    }
    {
      mguid::NumberType nt1{double{1}};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isDouble());
      REQUIRE(nt1.getDouble().value() == mguid::DoubleType{1});
    }
  }
  SECTION("Set Value Integer") {
    {
      mguid::NumberType nt1;
      nt1.setValue(std::int8_t{1});
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isInt());
      REQUIRE(nt1.getInt().value() == mguid::IntegerType{1});
    }
    {
      mguid::NumberType nt1;
      nt1.setValue(std::int16_t{1});
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isInt());
      REQUIRE(nt1.getInt().value() == mguid::IntegerType{1});
    }
    {
      mguid::NumberType nt1;
      nt1.setValue(std::int32_t{1});
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isInt());
      REQUIRE(nt1.getInt().value() == mguid::IntegerType{1});
    }
    {
      mguid::NumberType nt1;
      nt1.setValue(std::int64_t{1});
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isInt());
      REQUIRE(nt1.getInt().value() == mguid::IntegerType{1});
    }
  }
  SECTION("Set Value Unsigned Integer") {
    {
      mguid::NumberType nt1;
      nt1.setValue(std::uint8_t{1});
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isUInt());
      REQUIRE(nt1.getUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      mguid::NumberType nt1;
      nt1.setValue(std::uint16_t{1});
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isUInt());
      REQUIRE(nt1.getUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      mguid::NumberType nt1;
      nt1.setValue(std::uint32_t{1});
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isUInt());
      REQUIRE(nt1.getUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      mguid::NumberType nt1;
      nt1.setValue(std::uint64_t{1});
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isUInt());
      REQUIRE(nt1.getUInt().value() == mguid::UnsignedIntegerType{1});
    }
  }
  SECTION("Set Value Float") {
    {
      mguid::NumberType nt1;
      nt1.setValue(float{1});
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isDouble());
      REQUIRE(nt1.getDouble().value() == mguid::DoubleType{1});
    }
    {
      mguid::NumberType nt1;
      nt1.setValue(double{1});
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isDouble());
      REQUIRE(nt1.getDouble().value() == mguid::DoubleType{1});
    }
  }
  SECTION("Assign Value Integer") {
    {
      mguid::NumberType nt1;
      nt1 = std::int8_t{1};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isInt());
      REQUIRE(nt1.getInt().value() == mguid::IntegerType{1});
    }
    {
      mguid::NumberType nt1;
      nt1 = std::int16_t{1};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isInt());
      REQUIRE(nt1.getInt().value() == mguid::IntegerType{1});
    }
    {
      mguid::NumberType nt1;
      nt1 = std::int32_t{1};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isInt());
      REQUIRE(nt1.getInt().value() == mguid::IntegerType{1});
    }
    {
      mguid::NumberType nt1;
      nt1 = std::int64_t{1};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isInt());
      REQUIRE(nt1.getInt().value() == mguid::IntegerType{1});
    }
  }
  SECTION("Assign Value Unsigned Integer") {
    {
      mguid::NumberType nt1;
      nt1 = std::uint8_t{1};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isUInt());
      REQUIRE(nt1.getUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      mguid::NumberType nt1;
      nt1 = std::uint16_t{1};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isUInt());
      REQUIRE(nt1.getUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      mguid::NumberType nt1;
      nt1 = std::uint32_t{1};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isUInt());
      REQUIRE(nt1.getUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      mguid::NumberType nt1;
      nt1 = std::uint64_t{1};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isUInt());
      REQUIRE(nt1.getUInt().value() == mguid::UnsignedIntegerType{1});
    }
  }
  SECTION("Assign Value Float") {
    {
      mguid::NumberType nt1;
      nt1 = float{1};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isDouble());
      REQUIRE(nt1.getDouble().value() == mguid::DoubleType{1});
    }
    {
      mguid::NumberType nt1;
      nt1 = double{1};
      REQUIRE(nt1.hasValue());
      REQUIRE(nt1.isDouble());
      REQUIRE(nt1.getDouble().value() == mguid::DoubleType{1});
    }
  }
}

TEST_CASE("Number Type Get Value") {
  SECTION("Get Valid") {
    {
      mguid::NumberType nt1{std::int8_t{}};
      REQUIRE(nt1.getInt().has_value());
    }
    {
      mguid::NumberType nt1{std::int16_t{}};
      REQUIRE(nt1.getInt().has_value());
    }
    {
      mguid::NumberType nt1{std::int32_t{}};
      REQUIRE(nt1.getInt().has_value());
    }
    {
      mguid::NumberType nt1{std::int64_t{}};
      REQUIRE(nt1.getInt().has_value());
    }
    {
      mguid::NumberType nt1{std::uint8_t{}};
      REQUIRE(nt1.getUInt().has_value());
    }
    {
      mguid::NumberType nt1{std::uint16_t{}};
      REQUIRE(nt1.getUInt().has_value());
    }
    {
      mguid::NumberType nt1{std::uint32_t{}};
      REQUIRE(nt1.getUInt().has_value());
    }
    {
      mguid::NumberType nt1{std::uint64_t{}};
      REQUIRE(nt1.getUInt().has_value());
    }
    {
      mguid::NumberType nt1{float{}};
      REQUIRE(nt1.getDouble().has_value());
    }
    {
      mguid::NumberType nt1{double{}};
      REQUIRE(nt1.getDouble().has_value());
    }
  }
  SECTION("Get Invalid") {
    {
      mguid::NumberType nt1;
      REQUIRE_FALSE(nt1.getInt().has_value());
    }
    {
      mguid::NumberType nt1;
      REQUIRE_FALSE(nt1.getUInt().has_value());
    }
    {
      mguid::NumberType nt1;
      REQUIRE_FALSE(nt1.getDouble().has_value());
    }
    {
      mguid::NumberType nt1{mguid::IntegerType{}};
      REQUIRE_FALSE(nt1.getUInt().has_value());
    }
    {
      mguid::NumberType nt1{mguid::IntegerType{}};
      REQUIRE_FALSE(nt1.getDouble().has_value());
    }
    {
      mguid::NumberType nt1{mguid::UnsignedIntegerType{}};
      REQUIRE_FALSE(nt1.getInt().has_value());
    }
    {
      mguid::NumberType nt1{mguid::UnsignedIntegerType{}};
      REQUIRE_FALSE(nt1.getDouble().has_value());
    }
    {
      mguid::NumberType nt1{mguid::DoubleType{}};
      REQUIRE_FALSE(nt1.getInt().has_value());
    }
    {
      mguid::NumberType nt1{mguid::DoubleType{}};
      REQUIRE_FALSE(nt1.getUInt().has_value());
    }
  }
}

TEST_CASE("Number Type Tag") {
  SECTION("Default Constructed") {
    mguid::NumberType nt1;
    REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::None);
  }
  SECTION("Nullptr Constructed") {
    mguid::NumberType nt1{nullptr};
    REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::None);
  }
  SECTION("Get Valid") {
    {
      mguid::NumberType nt1{std::int8_t{}};
      REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::Int);
    }
    {
      mguid::NumberType nt1{std::int16_t{}};
      REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::Int);
    }
    {
      mguid::NumberType nt1{std::int32_t{}};
      REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::Int);
    }
    {
      mguid::NumberType nt1{std::int64_t{}};
      REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::Int);
    }
    {
      mguid::NumberType nt1{std::uint8_t{}};
      REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::UInt);
    }
    {
      mguid::NumberType nt1{std::uint16_t{}};
      REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::UInt);
    }
    {
      mguid::NumberType nt1{std::uint32_t{}};
      REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::UInt);
    }
    {
      mguid::NumberType nt1{std::uint64_t{}};
      REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::UInt);
    }
    {
      mguid::NumberType nt1{float{}};
      REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::Double);
    }
    {
      mguid::NumberType nt1{double{}};
      REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::Double);
    }
  }
}

TEST_CASE("Number Type Reset") {
  mguid::NumberType nt1;
  REQUIRE_FALSE(nt1.hasValue());
  nt1 = 1;
  REQUIRE(nt1.hasValue());
  nt1.reset();
  REQUIRE_FALSE(nt1.hasValue());
  nt1 = 1;
  REQUIRE(nt1.hasValue());
}

TEST_CASE("Number Type Constexpr") {
  constexpr auto nt1 = []() {
    mguid::NumberType nt;
    nt.setValue(5);
    nt.reset();
    nt = 4;
    return nt;
  }();
  REQUIRE(nt1.hasValue());
  REQUIRE(nt1.isInt());
  REQUIRE(nt1.getTypeTag() == mguid::NumberType::TypeTag::Int);
  REQUIRE(nt1.getInt().has_value());
  REQUIRE(nt1.getInt().value() == mguid::IntegerType{4});
}

TEST_CASE("Number Type Comparison") {
  SECTION("Equality") {
    REQUIRE(mguid::NumberType() == mguid::NumberType());
    REQUIRE(mguid::NumberType(1) == mguid::NumberType(1));
    REQUIRE(mguid::NumberType(1u) == mguid::NumberType(1u));
    REQUIRE(mguid::NumberType(1.0) == mguid::NumberType(1.0));
    REQUIRE(mguid::NumberType(2) != mguid::NumberType(3));
  }
  SECTION("Ordering") {
    REQUIRE(mguid::NumberType(2) < mguid::NumberType(3));
    // Each type is compared separately so this is correct,
    // We are not attempting to cast the Int to a Double
    // If the types are different, then it is compared by the tag enum value
    // None < Int < UInt < Double
    REQUIRE_FALSE(mguid::NumberType() < mguid::NumberType());
    REQUIRE(mguid::NumberType() < mguid::NumberType(1));
    REQUIRE(mguid::NumberType() < mguid::NumberType(1u));
    REQUIRE(mguid::NumberType(0u) < mguid::NumberType(1u));
    REQUIRE(mguid::NumberType(0.0) < mguid::NumberType(1.0));
    REQUIRE(mguid::NumberType(0) < mguid::NumberType(1));
    REQUIRE(mguid::NumberType() < mguid::NumberType(1.0));
    REQUIRE(mguid::NumberType(1) < mguid::NumberType(1.0));

    REQUIRE(mguid::NumberType(1) > mguid::NumberType());
    REQUIRE(mguid::NumberType(1u) > mguid::NumberType());
    REQUIRE(mguid::NumberType(1.0) > mguid::NumberType());
    REQUIRE(mguid::NumberType(1.0) > mguid::NumberType(1));
  }
}