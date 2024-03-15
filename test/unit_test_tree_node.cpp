/**
 * @brief Tests for treenode
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include "data_tree/tree_node/tree_node.hpp"

TEST_CASE("Tree Node Construction/Assignment") {
  SECTION("Default Constructor") { REQUIRE(std::is_default_constructible_v<mguid::TreeNode>); }
  SECTION("Copy Constructor") { REQUIRE(std::is_copy_constructible_v<mguid::TreeNode>); }
  SECTION("Move Constructor") { REQUIRE(std::is_nothrow_move_constructible_v<mguid::TreeNode>); }
  SECTION("Copy Assignment") { REQUIRE(std::is_copy_assignable_v<mguid::TreeNode>); }
  SECTION("Move Assignment") { REQUIRE(std::is_nothrow_move_assignable_v<mguid::TreeNode>); }
  SECTION("Constructible From Object") {
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::ObjectNodeType&>);
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::ObjectNodeType>);
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::ObjectNodeType&&>);
    REQUIRE(std::is_constructible_v<mguid::TreeNode, const mguid::ObjectNodeType>);
    REQUIRE(std::is_constructible_v<mguid::TreeNode, const mguid::ObjectNodeType&>);
  }
  SECTION("Constructible From Array") {
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::ArrayNodeType&>);
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::ArrayNodeType>);
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::ArrayNodeType&&>);
    REQUIRE(std::is_constructible_v<mguid::TreeNode, const mguid::ArrayNodeType>);
    REQUIRE(std::is_constructible_v<mguid::TreeNode, const mguid::ArrayNodeType&>);
  }
  SECTION("Constructible From Value") {
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::ValueNodeType&>);
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::ValueNodeType>);
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::ValueNodeType&&>);
    REQUIRE(std::is_constructible_v<mguid::TreeNode, const mguid::ValueNodeType>);
    REQUIRE(std::is_constructible_v<mguid::TreeNode, const mguid::ValueNodeType&>);
  }
  SECTION("Assignable From Object") {
    REQUIRE(std::is_assignable_v<mguid::TreeNode, mguid::ObjectNodeType&>);
    REQUIRE(std::is_assignable_v<mguid::TreeNode, mguid::ObjectNodeType>);
    REQUIRE(std::is_assignable_v<mguid::TreeNode, mguid::ObjectNodeType&&>);
    REQUIRE(std::is_assignable_v<mguid::TreeNode, const mguid::ObjectNodeType>);
    REQUIRE(std::is_assignable_v<mguid::TreeNode, const mguid::ObjectNodeType&>);
    mguid::TreeNode tn1;
    mguid::ObjectNodeType ont1;
    tn1 = ont1;
    REQUIRE(tn1.HasObject());

    mguid::TreeNode tn2;
    mguid::ObjectNodeType ont2{};
    tn2 = std::move(ont2);
    REQUIRE(tn2.HasObject());
  }
  SECTION("Assignable From Array") {
    REQUIRE(std::is_assignable_v<mguid::TreeNode, mguid::ArrayNodeType&>);
    REQUIRE(std::is_assignable_v<mguid::TreeNode, mguid::ArrayNodeType>);
    REQUIRE(std::is_assignable_v<mguid::TreeNode, mguid::ArrayNodeType&&>);
    REQUIRE(std::is_assignable_v<mguid::TreeNode, const mguid::ArrayNodeType>);
    REQUIRE(std::is_assignable_v<mguid::TreeNode, const mguid::ArrayNodeType&>);
    mguid::TreeNode tn1;
    mguid::ArrayNodeType ant1;
    tn1 = ant1;
    REQUIRE(tn1.HasArray());

    mguid::TreeNode tn2;
    mguid::ArrayNodeType ant2;
    tn2 = std::move(ant2);
    REQUIRE(tn2.HasArray());
  }
  SECTION("Assignable From Value") {
    REQUIRE(std::is_assignable_v<mguid::TreeNode, mguid::ValueNodeType&>);
    REQUIRE(std::is_assignable_v<mguid::TreeNode, mguid::ValueNodeType>);
    REQUIRE(std::is_assignable_v<mguid::TreeNode, mguid::ValueNodeType&&>);
    REQUIRE(std::is_assignable_v<mguid::TreeNode, const mguid::ValueNodeType>);
    REQUIRE(std::is_assignable_v<mguid::TreeNode, const mguid::ValueNodeType&>);
    mguid::TreeNode tn1;
    mguid::ValueNodeType vnt1;
    tn1 = vnt1;
    REQUIRE(tn1.HasValue());

    mguid::TreeNode tn2;
    mguid::ValueNodeType vnt2;
    tn2 = std::move(vnt2);
    REQUIRE(tn2.HasValue());
  }
  SECTION("From Tag") {
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::NodeTypeTag>);
    [[maybe_unused]] mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    [[maybe_unused]] mguid::TreeNode tn2{mguid::NodeTypeTag::Array};
    [[maybe_unused]] mguid::TreeNode tn3{mguid::NodeTypeTag::Value};
    SUCCEED("Constructed From Tag");
  }
  SECTION("Construction From Value") {
    {
      REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::NullType>);
      mguid::TreeNode tn1{mguid::NullType{}};
      REQUIRE(tn1.HasNull());
    }
    {
      REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::BoolType>);
      mguid::TreeNode tn1{true};
      REQUIRE(tn1.HasBool());
      mguid::TreeNode vnt2{false};
      REQUIRE(tn1.HasBool());
    }
    {
      REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::NumberType>);
      {
        mguid::TreeNode tn1{mguid::NumberType{}};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_constructible_v<mguid::TreeNode, std::uint8_t>);
      {
        mguid::TreeNode tn1{std::uint8_t{}};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_constructible_v<mguid::TreeNode, std::uint16_t>);
      {
        mguid::TreeNode tn1{std::uint16_t{}};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_constructible_v<mguid::TreeNode, std::uint32_t>);
      {
        mguid::TreeNode tn1{std::uint32_t{}};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_constructible_v<mguid::TreeNode, std::uint64_t>);
      {
        mguid::TreeNode tn1{std::uint64_t{}};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_constructible_v<mguid::TreeNode, std::int8_t>);
      {
        mguid::TreeNode tn1{std::int8_t{}};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_constructible_v<mguid::TreeNode, std::int16_t>);
      {
        mguid::TreeNode tn1{std::int16_t{}};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_constructible_v<mguid::TreeNode, std::int32_t>);
      {
        mguid::TreeNode tn1{std::int32_t{}};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_constructible_v<mguid::TreeNode, std::int64_t>);
      {
        mguid::TreeNode tn1{std::int64_t{}};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_constructible_v<mguid::TreeNode, float>);
      {
        mguid::TreeNode tn1{float{}};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_constructible_v<mguid::TreeNode, double>);
      {
        mguid::TreeNode tn1{double{}};
        REQUIRE(tn1.HasNumber());
      }
    }
    {
      REQUIRE(std::is_constructible_v<mguid::TreeNode, std::string>);
      {
        mguid::TreeNode tn1{std::string{}};
        REQUIRE(tn1.HasString());
      }
      REQUIRE(std::is_constructible_v<mguid::TreeNode, const char*>);
      {
        mguid::TreeNode tn1{""};
        REQUIRE(tn1.HasString());
      }
      REQUIRE(std::is_constructible_v<mguid::TreeNode, char[]>);
      {
        char c_array[] = "";
        mguid::TreeNode tn1{c_array};
        REQUIRE(tn1.HasString());
      }
    }
  }
  SECTION("Assignment From Value") {
    {
      REQUIRE(std::is_assignable_v<mguid::TreeNode, mguid::NullType>);
      mguid::TreeNode tn1;
      tn1 = mguid::NullType{};
      REQUIRE(tn1.HasNull());
    }
    {
      REQUIRE(std::is_assignable_v<mguid::TreeNode, mguid::BoolType>);
      mguid::TreeNode tn1;
      tn1 = true;
      REQUIRE(tn1.HasBool());
      mguid::TreeNode vnt2;
      vnt2 = false;
      REQUIRE(vnt2.HasBool());
    }
    {
      REQUIRE(std::is_assignable_v<mguid::TreeNode, mguid::NumberType>);
      {
        mguid::TreeNode tn1;
        tn1 = mguid::NumberType{};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_assignable_v<mguid::TreeNode, std::uint8_t>);
      {
        mguid::TreeNode tn1;
        tn1 = std::uint8_t{};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_assignable_v<mguid::TreeNode, std::uint16_t>);
      {
        mguid::TreeNode tn1;
        tn1 = std::uint16_t{};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_assignable_v<mguid::TreeNode, std::uint32_t>);
      {
        mguid::TreeNode tn1;
        tn1 = std::uint32_t{};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_assignable_v<mguid::TreeNode, std::uint64_t>);
      {
        mguid::TreeNode tn1;
        tn1 = std::uint64_t{};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_assignable_v<mguid::TreeNode, std::int8_t>);
      {
        mguid::TreeNode tn1;
        tn1 = std::int8_t{};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_assignable_v<mguid::TreeNode, std::int16_t>);
      {
        mguid::TreeNode tn1;
        tn1 = std::int16_t{};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_assignable_v<mguid::TreeNode, std::int32_t>);
      {
        mguid::TreeNode tn1;
        tn1 = std::int32_t{};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_assignable_v<mguid::TreeNode, std::int64_t>);
      {
        mguid::TreeNode tn1;
        tn1 = std::int64_t{};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_assignable_v<mguid::TreeNode, float>);
      {
        mguid::TreeNode tn1;
        tn1 = float{};
        REQUIRE(tn1.HasNumber());
      }
      REQUIRE(std::is_assignable_v<mguid::TreeNode, double>);
      {
        mguid::TreeNode tn1;
        tn1 = double{};
        REQUIRE(tn1.HasNumber());
      }
    }
    {
      REQUIRE(std::is_assignable_v<mguid::TreeNode, std::string>);
      {
        mguid::TreeNode tn1;
        tn1 = std::string{};
        REQUIRE(tn1.HasString());
      }
      REQUIRE(std::is_assignable_v<mguid::TreeNode, const char*>);
      {
        mguid::TreeNode tn1;
        tn1 = "";
        REQUIRE(tn1.HasString());
      }
      REQUIRE(std::is_assignable_v<mguid::TreeNode, char[]>);
      {
        char c_array[] = "";
        mguid::TreeNode tn1;
        tn1 = c_array;
        REQUIRE(tn1.HasString());
      }
    }
  }
}

TEST_CASE("Tree Node Tag") {
  mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
  REQUIRE(tn1.Tag() == mguid::NodeTypeTag::Object);

  mguid::TreeNode tn2{mguid::NodeTypeTag::Array};
  REQUIRE(tn2.Tag() == mguid::NodeTypeTag::Array);

  mguid::TreeNode tn3{mguid::NodeTypeTag::Value};
  REQUIRE(tn3.Tag() == mguid::NodeTypeTag::Value);

  // Constructing with a tag outside the valid enum range will give you a
  // node with Object type
  mguid::TreeNode tn4{static_cast<mguid::NodeTypeTag>(3)};
  REQUIRE(tn4.Tag() == mguid::NodeTypeTag::Object);

  mguid::TreeNode tn5{static_cast<mguid::NodeTypeTag>(32)};
  REQUIRE(tn5.Tag() == mguid::NodeTypeTag::Object);
}

TEST_CASE("Tree Node Has Type") {
  SECTION("Has Type") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    REQUIRE(tn1.Has<mguid::ObjectNodeType>());

    mguid::TreeNode tn2{mguid::NodeTypeTag::Array};
    REQUIRE(tn2.Has<mguid::ArrayNodeType>());

    mguid::TreeNode tn3{mguid::NodeTypeTag::Value};
    REQUIRE(tn3.Has<mguid::ValueNodeType>());
  }
  SECTION("Has Type Wrong Type") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    mguid::TreeNode tn2{mguid::NodeTypeTag::Value};
    REQUIRE_FALSE(tn1.Has<mguid::ObjectNodeType>());
    REQUIRE_FALSE(tn2.Has<mguid::ObjectNodeType>());

    mguid::TreeNode tn3{mguid::NodeTypeTag::Object};
    mguid::TreeNode tn4{mguid::NodeTypeTag::Value};
    REQUIRE_FALSE(tn3.Has<mguid::ArrayNodeType>());
    REQUIRE_FALSE(tn4.Has<mguid::ArrayNodeType>());

    mguid::TreeNode tn5{mguid::NodeTypeTag::Object};
    mguid::TreeNode tn6{mguid::NodeTypeTag::Array};
    REQUIRE_FALSE(tn5.Has<mguid::ValueNodeType>());
    REQUIRE_FALSE(tn6.Has<mguid::ValueNodeType>());
  }
  SECTION("Has Object") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    REQUIRE(tn1.HasObject());
  }
  SECTION("Has Array") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    REQUIRE(tn1.HasArray());
  }
  SECTION("Has Value") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
    REQUIRE(tn1.HasValue());
  }
  SECTION("Has Object Wrong Type") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    mguid::TreeNode tn2{mguid::NodeTypeTag::Value};
    REQUIRE_FALSE(tn1.HasObject());
    REQUIRE_FALSE(tn2.HasObject());
  }
  SECTION("Has Array Wrong Type") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    mguid::TreeNode tn2{mguid::NodeTypeTag::Value};
    REQUIRE_FALSE(tn1.HasArray());
    REQUIRE_FALSE(tn2.HasArray());
  }
  SECTION("Has Value Wrong Type") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    mguid::TreeNode tn2{mguid::NodeTypeTag::Array};
    REQUIRE_FALSE(tn1.HasValue());
    REQUIRE_FALSE(tn2.HasValue());
  }
}

TEST_CASE("Tree Node Has Value Type") {
  SECTION("Constructed With Null") {
    {
      mguid::TreeNode tn1{mguid::NullType{}};
      REQUIRE(tn1.HasNull());
    }
    {
      const mguid::TreeNode tn1{mguid::NullType{}};
      REQUIRE(tn1.HasNull());
    }
  }
  SECTION("Constructed With Integer") {
    {
      mguid::TreeNode tn1{std::int8_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      const mguid::TreeNode tn1{std::int8_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      mguid::TreeNode tn1{std::int16_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      const mguid::TreeNode tn1{std::int16_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      mguid::TreeNode tn1{std::int32_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      const mguid::TreeNode tn1{std::int32_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      mguid::TreeNode tn1{std::int64_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      const mguid::TreeNode tn1{std::int64_t{1}};
      REQUIRE(tn1.HasNumber());
    }
  }
  SECTION("Constructed With Unsigned Integer") {
    {
      mguid::TreeNode tn1{std::uint8_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      const mguid::TreeNode tn1{std::uint8_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      mguid::TreeNode tn1{std::uint16_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      const mguid::TreeNode tn1{std::uint16_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      mguid::TreeNode tn1{std::uint32_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      const mguid::TreeNode tn1{std::uint32_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      mguid::TreeNode tn1{std::uint64_t{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      const mguid::TreeNode tn1{std::uint64_t{1}};
      REQUIRE(tn1.HasNumber());
    }
  }
  SECTION("Constructed With Float") {
    {
      mguid::TreeNode tn1{float{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      const mguid::TreeNode tn1{float{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      mguid::TreeNode tn1{double{1}};
      REQUIRE(tn1.HasNumber());
    }
    {
      const mguid::TreeNode tn1{double{1}};
      REQUIRE(tn1.HasNumber());
    }
  }
  SECTION("Constructed With Bool") {
    {
      mguid::TreeNode tn1{true};
      REQUIRE(tn1.HasBool());
    }
    {
      const mguid::TreeNode tn1{true};
      REQUIRE(tn1.HasBool());
    }
    {
      mguid::TreeNode tn1{false};
      REQUIRE(tn1.HasBool());
    }
    {
      const mguid::TreeNode tn1{false};
      REQUIRE(tn1.HasBool());
    }
  }
  SECTION("Constructed With String") {
    {
      mguid::TreeNode tn1{std::string{"test"}};
      REQUIRE(tn1.HasString());
    }
    {
      const mguid::TreeNode tn1{std::string{"test"}};
      REQUIRE(tn1.HasString());
    }
    {
      mguid::TreeNode tn1{"test"};
      REQUIRE(tn1.HasString());
    }
    {
      const mguid::TreeNode tn1{"test"};
      REQUIRE(tn1.HasString());
    }
    {
      char test[] = "test";
      mguid::TreeNode tn1{test};
      REQUIRE(tn1.HasString());
    }
    {
      char test[] = "test";
      const mguid::TreeNode tn1{test};
      REQUIRE(tn1.HasString());
    }
  }
}

TEST_CASE("Tree Node Try Get Key/Index") {
  SECTION("Object") {
    SECTION("Empty") {
      mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
      REQUIRE_FALSE(tn1.TryGet("test_key").has_value());
      REQUIRE_FALSE(tn1.TryGet(0).has_value());
      REQUIRE_FALSE(tn1.TryGet(2).has_value());
      REQUIRE_FALSE(tn1.TryGet(512).has_value());
      REQUIRE_FALSE(tn1.TryGet(65535).has_value());
    }
    SECTION("Not Empty Key Not Found") {
      mguid::ObjectNodeType ont{{{"key1", {}}, {"key2", {}}, {"key3", {}}}};
      mguid::TreeNode tn1{ont};
      REQUIRE_FALSE(tn1.TryGet("test_key").has_value());
      REQUIRE_FALSE(tn1.TryGet(0).has_value());
      REQUIRE_FALSE(tn1.TryGet(2).has_value());
      REQUIRE_FALSE(tn1.TryGet(512).has_value());
      REQUIRE_FALSE(tn1.TryGet(65535).has_value());
    }
    SECTION("Key Found") {
      mguid::ObjectNodeType ont{{{"key1", {}}, {"key2", {}}, {"key3", {}}}};
      mguid::TreeNode tn1{ont};
      REQUIRE(tn1.TryGet("key1").has_value());
      REQUIRE(tn1.TryGet("key2").has_value());
      REQUIRE(tn1.TryGet("key3").has_value());
      REQUIRE_FALSE(tn1.TryGet(0).has_value());
      REQUIRE_FALSE(tn1.TryGet(2).has_value());
      REQUIRE_FALSE(tn1.TryGet(512).has_value());
      REQUIRE_FALSE(tn1.TryGet(65535).has_value());
    }
  }
  SECTION("Const Object") {
    SECTION("Empty") {
      const mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
      REQUIRE_FALSE(tn1.TryGet("test_key").has_value());
      REQUIRE_FALSE(tn1.TryGet(0).has_value());
      REQUIRE_FALSE(tn1.TryGet(2).has_value());
      REQUIRE_FALSE(tn1.TryGet(512).has_value());
      REQUIRE_FALSE(tn1.TryGet(65535).has_value());
    }
    SECTION("Not Empty Key Not Found") {
      mguid::ObjectNodeType ont{{{"key1", {}}, {"key2", {}}, {"key3", {}}}};
      const mguid::TreeNode tn1{ont};
      REQUIRE_FALSE(tn1.TryGet("test_key").has_value());
      REQUIRE_FALSE(tn1.TryGet(0).has_value());
      REQUIRE_FALSE(tn1.TryGet(2).has_value());
      REQUIRE_FALSE(tn1.TryGet(512).has_value());
      REQUIRE_FALSE(tn1.TryGet(65535).has_value());
    }
    SECTION("Key Found") {
      mguid::ObjectNodeType ont{{{"key1", {}}, {"key2", {}}, {"key3", {}}}};
      const mguid::TreeNode tn1{ont};
      REQUIRE(tn1.TryGet("key1").has_value());
      REQUIRE(tn1.TryGet("key2").has_value());
      REQUIRE(tn1.TryGet("key3").has_value());
      REQUIRE_FALSE(tn1.TryGet(0).has_value());
      REQUIRE_FALSE(tn1.TryGet(2).has_value());
      REQUIRE_FALSE(tn1.TryGet(512).has_value());
      REQUIRE_FALSE(tn1.TryGet(65535).has_value());
    }
  }
  SECTION("Array") {
    SECTION("Empty") {
      mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
      REQUIRE_FALSE(tn1.TryGet(0).has_value());
      REQUIRE_FALSE(tn1.TryGet(2).has_value());
      REQUIRE_FALSE(tn1.TryGet(512).has_value());
      REQUIRE_FALSE(tn1.TryGet(65535).has_value());
      REQUIRE_FALSE(tn1.TryGet("test_key").has_value());
    }
    SECTION("Not Empty Idx Not Found") {
      mguid::ArrayNodeType ant{{{}, {}, {}}};
      mguid::TreeNode tn1{ant};
      REQUIRE_FALSE(tn1.TryGet(3).has_value());
      REQUIRE_FALSE(tn1.TryGet(512).has_value());
      REQUIRE_FALSE(tn1.TryGet(65535).has_value());
      REQUIRE_FALSE(tn1.TryGet("test_key").has_value());
    }
    SECTION("Idx Found") {
      mguid::ArrayNodeType ant{{{}, {}, {}}};
      mguid::TreeNode tn1{ant};
      REQUIRE(tn1.TryGet(0).has_value());
      REQUIRE(tn1.TryGet(1).has_value());
      REQUIRE(tn1.TryGet(2).has_value());
      REQUIRE_FALSE(tn1.TryGet("test_key").has_value());
    }
  }
  SECTION("Const Array") {
    SECTION("Empty") {
      const mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
      REQUIRE_FALSE(tn1.TryGet(0).has_value());
      REQUIRE_FALSE(tn1.TryGet(2).has_value());
      REQUIRE_FALSE(tn1.TryGet(512).has_value());
      REQUIRE_FALSE(tn1.TryGet(65535).has_value());
    }
    SECTION("Not Empty Idx Not Found") {
      mguid::ArrayNodeType ant{{{}, {}, {}}};
      const mguid::TreeNode tn1{ant};
      REQUIRE_FALSE(tn1.TryGet(3).has_value());
      REQUIRE_FALSE(tn1.TryGet(512).has_value());
      REQUIRE_FALSE(tn1.TryGet(65535).has_value());
    }
    SECTION("Idx Found") {
      mguid::ArrayNodeType ant{{{}, {}, {}}};
      const mguid::TreeNode tn1{ant};
      REQUIRE(tn1.TryGet(0).has_value());
      REQUIRE(tn1.TryGet(1).has_value());
      REQUIRE(tn1.TryGet(2).has_value());
    }
  }
  SECTION("Value") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
    REQUIRE_FALSE(tn1.TryGet("test_key").has_value());
    REQUIRE_FALSE(tn1.TryGet(0).has_value());
    REQUIRE_FALSE(tn1.TryGet(2).has_value());
    REQUIRE_FALSE(tn1.TryGet(512).has_value());
    REQUIRE_FALSE(tn1.TryGet(65535).has_value());
  }
  SECTION("Const Value") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
    REQUIRE_FALSE(tn1.TryGet("test_key").has_value());
    REQUIRE_FALSE(tn1.TryGet(0).has_value());
    REQUIRE_FALSE(tn1.TryGet(2).has_value());
    REQUIRE_FALSE(tn1.TryGet(512).has_value());
    REQUIRE_FALSE(tn1.TryGet(65535).has_value());
  }
}

TEST_CASE("Tree Node Exists") {
  SECTION("Object") {
    SECTION("Empty") {
      mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
      REQUIRE_FALSE(tn1.Exists(mguid::Path{"test_key"}));
      std::vector<mguid::KeyOrIdxType> path0{mguid::KeyOrIdxType{"test_key"}};
      REQUIRE_FALSE(tn1.Exists(path0));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{0}));
      std::vector<mguid::KeyOrIdxType> path1{mguid::KeyOrIdxType{0}};
      REQUIRE_FALSE(tn1.Exists(path1));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{2}));
      std::vector<mguid::KeyOrIdxType> path2{mguid::KeyOrIdxType{2}};
      REQUIRE_FALSE(tn1.Exists(path2));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{512}));
      std::vector<mguid::KeyOrIdxType> path3{mguid::KeyOrIdxType{512}};
      REQUIRE_FALSE(tn1.Exists(path3));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{65535}));
      std::vector<mguid::KeyOrIdxType> path4{mguid::KeyOrIdxType{65535}};
      REQUIRE_FALSE(tn1.Exists(path4));
    }
    SECTION("Not Empty Path Not Found") {
      mguid::ObjectNodeType ont{{{"key1", {}}, {"key2", {}}, {"key3", {}}}};
      mguid::TreeNode tn1{ont};
      REQUIRE_FALSE(tn1.Exists(mguid::Path{"test_key"}));
      std::vector<mguid::KeyOrIdxType> path0{mguid::KeyOrIdxType{"test_key"}};
      REQUIRE_FALSE(tn1.Exists(path0));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{0}));
      std::vector<mguid::KeyOrIdxType> path1{mguid::KeyOrIdxType{0}};
      REQUIRE_FALSE(tn1.Exists(path1));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{2}));
      std::vector<mguid::KeyOrIdxType> path2{mguid::KeyOrIdxType{2}};
      REQUIRE_FALSE(tn1.Exists(path2));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{512}));
      std::vector<mguid::KeyOrIdxType> path3{mguid::KeyOrIdxType{512}};
      REQUIRE_FALSE(tn1.Exists(path3));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{65535}));
      std::vector<mguid::KeyOrIdxType> path4{mguid::KeyOrIdxType{65535}};
      REQUIRE_FALSE(tn1.Exists(path4));
    }
    SECTION("Path Found") {
      mguid::ObjectNodeType ont{{{"key1", {}}, {"key2", {}}, {"key3", {}}}};
      mguid::TreeNode tn1{ont};
      REQUIRE(tn1.Exists(mguid::Path{"key1"}));
      REQUIRE(tn1.Exists(mguid::Path{"key2"}));
      REQUIRE(tn1.Exists(mguid::Path{"key3"}));

      REQUIRE_FALSE(tn1.Exists(mguid::Path{0}));
      std::vector<mguid::KeyOrIdxType> path1{mguid::KeyOrIdxType{0}};
      REQUIRE_FALSE(tn1.Exists(path1));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{2}));
      std::vector<mguid::KeyOrIdxType> path2{mguid::KeyOrIdxType{2}};
      REQUIRE_FALSE(tn1.Exists(path2));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{512}));
      std::vector<mguid::KeyOrIdxType> path3{mguid::KeyOrIdxType{512}};
      REQUIRE_FALSE(tn1.Exists(path3));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{65535}));
      std::vector<mguid::KeyOrIdxType> path4{mguid::KeyOrIdxType{65535}};
      REQUIRE_FALSE(tn1.Exists(path4));
    }
  }
  SECTION("Const Object") {
    SECTION("Empty") {
      const mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
      REQUIRE_FALSE(tn1.Exists(mguid::Path{"test_key"}));
      std::vector<mguid::KeyOrIdxType> path0{mguid::KeyOrIdxType{"test_key"}};
      REQUIRE_FALSE(tn1.Exists(path0));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{0}));
      std::vector<mguid::KeyOrIdxType> path1{mguid::KeyOrIdxType{0}};
      REQUIRE_FALSE(tn1.Exists(path1));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{2}));
      std::vector<mguid::KeyOrIdxType> path2{mguid::KeyOrIdxType{2}};
      REQUIRE_FALSE(tn1.Exists(path2));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{512}));
      std::vector<mguid::KeyOrIdxType> path3{mguid::KeyOrIdxType{512}};
      REQUIRE_FALSE(tn1.Exists(path3));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{65535}));
      std::vector<mguid::KeyOrIdxType> path4{mguid::KeyOrIdxType{65535}};
      REQUIRE_FALSE(tn1.Exists(path4));
    }
    SECTION("Not Empty Key Not Found") {
      mguid::ObjectNodeType ont{{{"key1", {}}, {"key2", {}}, {"key3", {}}}};
      const mguid::TreeNode tn1{ont};
      REQUIRE_FALSE(tn1.Exists(mguid::Path{"test_key"}));
      std::vector<mguid::KeyOrIdxType> path0{mguid::KeyOrIdxType{"test_key"}};
      REQUIRE_FALSE(tn1.Exists(path0));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{0}));
      std::vector<mguid::KeyOrIdxType> path1{mguid::KeyOrIdxType{0}};
      REQUIRE_FALSE(tn1.Exists(path1));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{2}));
      std::vector<mguid::KeyOrIdxType> path2{mguid::KeyOrIdxType{2}};
      REQUIRE_FALSE(tn1.Exists(path2));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{512}));
      std::vector<mguid::KeyOrIdxType> path3{mguid::KeyOrIdxType{512}};
      REQUIRE_FALSE(tn1.Exists(path3));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{65535}));
      std::vector<mguid::KeyOrIdxType> path4{mguid::KeyOrIdxType{65535}};
      REQUIRE_FALSE(tn1.Exists(path4));
    }
    SECTION("Key Found") {
      mguid::ObjectNodeType ont{{{"key1", {}}, {"key2", {}}, {"key3", {}}}};
      const mguid::TreeNode tn1{ont};
      REQUIRE(tn1.Exists(mguid::Path{"key1"}));
      REQUIRE(tn1.Exists(mguid::Path{"key2"}));
      REQUIRE(tn1.Exists(mguid::Path{"key3"}));

      REQUIRE_FALSE(tn1.Exists(mguid::Path{0}));
      std::vector<mguid::KeyOrIdxType> path1{mguid::KeyOrIdxType{0}};
      REQUIRE_FALSE(tn1.Exists(path1));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{2}));
      std::vector<mguid::KeyOrIdxType> path2{mguid::KeyOrIdxType{2}};
      REQUIRE_FALSE(tn1.Exists(path2));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{512}));
      std::vector<mguid::KeyOrIdxType> path3{mguid::KeyOrIdxType{512}};
      REQUIRE_FALSE(tn1.Exists(path3));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{65535}));
      std::vector<mguid::KeyOrIdxType> path4{mguid::KeyOrIdxType{65535}};
      REQUIRE_FALSE(tn1.Exists(path4));
    }
  }
  SECTION("Array") {
    SECTION("Empty") {
      mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
      REQUIRE_FALSE(tn1.Exists(mguid::Path{"test_key"}));
      std::vector<mguid::KeyOrIdxType> path0{mguid::KeyOrIdxType{"test_key"}};
      REQUIRE_FALSE(tn1.Exists(path0));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{0}));
      std::vector<mguid::KeyOrIdxType> path1{mguid::KeyOrIdxType{0}};
      REQUIRE_FALSE(tn1.Exists(path1));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{2}));
      std::vector<mguid::KeyOrIdxType> path2{mguid::KeyOrIdxType{2}};
      REQUIRE_FALSE(tn1.Exists(path2));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{512}));
      std::vector<mguid::KeyOrIdxType> path3{mguid::KeyOrIdxType{512}};
      REQUIRE_FALSE(tn1.Exists(path3));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{65535}));
      std::vector<mguid::KeyOrIdxType> path4{mguid::KeyOrIdxType{65535}};
      REQUIRE_FALSE(tn1.Exists(path4));
    }
    SECTION("Not Empty Idx Not Found") {
      mguid::ArrayNodeType ant{{{}, {}, {}}};
      mguid::TreeNode tn1{ant};
      REQUIRE_FALSE(tn1.Exists(mguid::Path{"test_key"}));
      std::vector<mguid::KeyOrIdxType> path0{mguid::KeyOrIdxType{"test_key"}};
      REQUIRE_FALSE(tn1.Exists(path0));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{3}));
      std::vector<mguid::KeyOrIdxType> path2{mguid::KeyOrIdxType{3}};
      REQUIRE_FALSE(tn1.Exists(path2));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{512}));
      std::vector<mguid::KeyOrIdxType> path3{mguid::KeyOrIdxType{512}};
      REQUIRE_FALSE(tn1.Exists(path3));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{65535}));
      std::vector<mguid::KeyOrIdxType> path4{mguid::KeyOrIdxType{65535}};
      REQUIRE_FALSE(tn1.Exists(path4));
    }
    SECTION("Idx Found") {
      mguid::ArrayNodeType ant{{{}, {}, {}}};
      mguid::TreeNode tn1{ant};
      REQUIRE(tn1.Exists(mguid::Path{0}));
      REQUIRE(tn1.Exists(mguid::Path{1}));
      REQUIRE(tn1.Exists(mguid::Path{2}));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{"test_key"}));
      std::vector<mguid::KeyOrIdxType> path0{mguid::KeyOrIdxType{"test_key"}};
      REQUIRE_FALSE(tn1.Exists(path0));
    }
  }
  SECTION("Const Array") {
    SECTION("Empty") {
      const mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
      REQUIRE_FALSE(tn1.Exists(mguid::Path{"test_key"}));
      std::vector<mguid::KeyOrIdxType> path0{mguid::KeyOrIdxType{"test_key"}};
      REQUIRE_FALSE(tn1.Exists(path0));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{0}));
      std::vector<mguid::KeyOrIdxType> path1{mguid::KeyOrIdxType{0}};
      REQUIRE_FALSE(tn1.Exists(path1));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{2}));
      std::vector<mguid::KeyOrIdxType> path2{mguid::KeyOrIdxType{2}};
      REQUIRE_FALSE(tn1.Exists(path2));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{512}));
      std::vector<mguid::KeyOrIdxType> path3{mguid::KeyOrIdxType{512}};
      REQUIRE_FALSE(tn1.Exists(path3));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{65535}));
      std::vector<mguid::KeyOrIdxType> path4{mguid::KeyOrIdxType{65535}};
      REQUIRE_FALSE(tn1.Exists(path4));
    }
    SECTION("Not Empty Idx Not Found") {
      mguid::ArrayNodeType ant{{{}, {}, {}}};
      const mguid::TreeNode tn1{ant};
      REQUIRE_FALSE(tn1.Exists(mguid::Path{"test_key"}));
      std::vector<mguid::KeyOrIdxType> path0{mguid::KeyOrIdxType{"test_key"}};
      REQUIRE_FALSE(tn1.Exists(path0));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{3}));
      std::vector<mguid::KeyOrIdxType> path2{mguid::KeyOrIdxType{3}};
      REQUIRE_FALSE(tn1.Exists(path2));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{512}));
      std::vector<mguid::KeyOrIdxType> path3{mguid::KeyOrIdxType{512}};
      REQUIRE_FALSE(tn1.Exists(path3));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{65535}));
      std::vector<mguid::KeyOrIdxType> path4{mguid::KeyOrIdxType{65535}};
      REQUIRE_FALSE(tn1.Exists(path4));
    }
    SECTION("Idx Found") {
      mguid::ArrayNodeType ant{{{}, {}, {}}};
      const mguid::TreeNode tn1{ant};
      REQUIRE(tn1.Exists(mguid::Path{0}));
      REQUIRE(tn1.Exists(mguid::Path{1}));
      REQUIRE(tn1.Exists(mguid::Path{2}));
      REQUIRE_FALSE(tn1.Exists(mguid::Path{"test_key"}));
      std::vector<mguid::KeyOrIdxType> path0{mguid::KeyOrIdxType{"test_key"}};
      REQUIRE_FALSE(tn1.Exists(path0));
    }
  }
  SECTION("Value") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
    REQUIRE_FALSE(tn1.Exists(mguid::Path{"test_key"}));
    std::vector<mguid::KeyOrIdxType> path0{mguid::KeyOrIdxType{"test_key"}};
    REQUIRE_FALSE(tn1.Exists(path0));
    REQUIRE_FALSE(tn1.Exists(mguid::Path{0}));
    std::vector<mguid::KeyOrIdxType> path1{mguid::KeyOrIdxType{0}};
    REQUIRE_FALSE(tn1.Exists(path1));
    REQUIRE_FALSE(tn1.Exists(mguid::Path{2}));
    std::vector<mguid::KeyOrIdxType> path2{mguid::KeyOrIdxType{2}};
    REQUIRE_FALSE(tn1.Exists(path2));
    REQUIRE_FALSE(tn1.Exists(mguid::Path{512}));
    std::vector<mguid::KeyOrIdxType> path3{mguid::KeyOrIdxType{512}};
    REQUIRE_FALSE(tn1.Exists(path3));
    REQUIRE_FALSE(tn1.Exists(mguid::Path{65535}));
    std::vector<mguid::KeyOrIdxType> path4{mguid::KeyOrIdxType{65535}};
    REQUIRE_FALSE(tn1.Exists(path4));
  }
  SECTION("Const Value") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
    REQUIRE_FALSE(tn1.Exists(mguid::Path{"test_key"}));
    std::vector<mguid::KeyOrIdxType> path0{mguid::KeyOrIdxType{"test_key"}};
    REQUIRE_FALSE(tn1.Exists(path0));
    REQUIRE_FALSE(tn1.Exists(mguid::Path{0}));
    std::vector<mguid::KeyOrIdxType> path1{mguid::KeyOrIdxType{0}};
    REQUIRE_FALSE(tn1.Exists(path1));
    REQUIRE_FALSE(tn1.Exists(mguid::Path{2}));
    std::vector<mguid::KeyOrIdxType> path2{mguid::KeyOrIdxType{2}};
    REQUIRE_FALSE(tn1.Exists(path2));
    REQUIRE_FALSE(tn1.Exists(mguid::Path{512}));
    std::vector<mguid::KeyOrIdxType> path3{mguid::KeyOrIdxType{512}};
    REQUIRE_FALSE(tn1.Exists(path3));
    REQUIRE_FALSE(tn1.Exists(mguid::Path{65535}));
    std::vector<mguid::KeyOrIdxType> path4{mguid::KeyOrIdxType{65535}};
    REQUIRE_FALSE(tn1.Exists(path4));
  }
  SECTION("Complex Path") {
    mguid::TreeNode tn1;
    tn1["first"][0]["second"][2]["third"][4]["fourth"][8] = mguid::Null;
    std::vector<mguid::KeyOrIdxType> path{{"first", 0, "second", 2, "third", 4, "fourth", 8}};

    REQUIRE(tn1.Exists(mguid::Path{"first", 0, "second", 2, "third", 4, "fourth", 8}));
    REQUIRE(tn1.Exists(path));

    const mguid::TreeNode tn2 = tn1;
    REQUIRE(tn2.Exists(mguid::Path{"first", 0, "second", 2, "third", 4, "fourth", 8}));
    REQUIRE(tn2.Exists(path));
  }
  SECTION("Deep Path") {
    mguid::TreeNode tn1;
    mguid::TreeNode tn2;
    std::reference_wrapper<mguid::TreeNode> current1{tn1};
    std::reference_wrapper<mguid::TreeNode> current2{tn2};

    std::vector<mguid::KeyOrIdxType> path1;
    std::vector<mguid::KeyOrIdxType> path2;

    for (std::size_t i{0}; i < 1024; ++i) {
      current1 = current1.get()["key"];
      current2 = current2.get()[0];
      path1.emplace_back("key");
      path2.emplace_back(0);
    }

    REQUIRE(tn1.Exists(path1));
    REQUIRE(tn2.Exists(path2));
  }
}

TEST_CASE("Tree Node Try Get Type") {
  SECTION("Try Get Object") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    REQUIRE(tn1.TryGetObject().has_value());
    REQUIRE(tn1.TryGet<mguid::ObjectNodeType>().has_value());
  }
  SECTION("Try Get Object Const") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    REQUIRE(tn1.TryGetObject().has_value());
    REQUIRE(tn1.TryGet<mguid::ObjectNodeType>().has_value());
  }
  SECTION("Try Get Array") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    REQUIRE(tn1.TryGetArray().has_value());
    REQUIRE(tn1.TryGet<mguid::ArrayNodeType>().has_value());
  }
  SECTION("Try Get Array Const") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    REQUIRE(tn1.TryGetArray().has_value());
    REQUIRE(tn1.TryGet<mguid::ArrayNodeType>().has_value());
  }
  SECTION("Try Get Value") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
    REQUIRE(tn1.TryGetValue().has_value());
    REQUIRE(tn1.TryGet<mguid::ValueNodeType>().has_value());
  }
  SECTION("Try Get Value Const") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
    REQUIRE(tn1.TryGetValue().has_value());
    REQUIRE(tn1.TryGet<mguid::ValueNodeType>().has_value());
  }
  SECTION("Try Get Object Bad Access") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    mguid::TreeNode tn2{mguid::NodeTypeTag::Value};
    REQUIRE_FALSE(tn1.TryGetObject().has_value());
    REQUIRE_FALSE(tn2.TryGetObject().has_value());
    REQUIRE_FALSE(tn1.TryGet<mguid::ObjectNodeType>().has_value());
    REQUIRE_FALSE(tn2.TryGet<mguid::ObjectNodeType>().has_value());
  }
  SECTION("Try Get Object Bad Access Const") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    const mguid::TreeNode tn2{mguid::NodeTypeTag::Value};
    REQUIRE_FALSE(tn1.TryGetObject().has_value());
    REQUIRE_FALSE(tn2.TryGetObject().has_value());
    REQUIRE_FALSE(tn1.TryGet<mguid::ObjectNodeType>().has_value());
    REQUIRE_FALSE(tn2.TryGet<mguid::ObjectNodeType>().has_value());
  }
  SECTION("Try Get Array Bad Access") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    mguid::TreeNode tn2{mguid::NodeTypeTag::Value};
    REQUIRE_FALSE(tn1.TryGetArray().has_value());
    REQUIRE_FALSE(tn2.TryGetArray().has_value());
    REQUIRE_FALSE(tn1.TryGet<mguid::ArrayNodeType>().has_value());
    REQUIRE_FALSE(tn2.TryGet<mguid::ArrayNodeType>().has_value());
  }
  SECTION("Try Get Array Bad Access Const") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    const mguid::TreeNode tn2{mguid::NodeTypeTag::Value};
    REQUIRE_FALSE(tn1.TryGetArray().has_value());
    REQUIRE_FALSE(tn2.TryGetArray().has_value());
    REQUIRE_FALSE(tn1.TryGet<mguid::ArrayNodeType>().has_value());
    REQUIRE_FALSE(tn2.TryGet<mguid::ArrayNodeType>().has_value());
  }
  SECTION("Try Get Value Bad Access") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    mguid::TreeNode tn2{mguid::NodeTypeTag::Array};
    REQUIRE_FALSE(tn1.TryGetValue().has_value());
    REQUIRE_FALSE(tn2.TryGetValue().has_value());
    REQUIRE_FALSE(tn1.TryGet<mguid::ValueNodeType>().has_value());
    REQUIRE_FALSE(tn2.TryGet<mguid::ValueNodeType>().has_value());
  }
  SECTION("Try Get Value Bad Access Const") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    const mguid::TreeNode tn2{mguid::NodeTypeTag::Array};
    REQUIRE_FALSE(tn1.TryGetValue().has_value());
    REQUIRE_FALSE(tn2.TryGetValue().has_value());
    REQUIRE_FALSE(tn1.TryGet<mguid::ValueNodeType>().has_value());
    REQUIRE_FALSE(tn2.TryGet<mguid::ValueNodeType>().has_value());
  }
}

TEST_CASE("Tree Node Contains Type") {
  SECTION("String Empty Path") {
    mguid::TreeNode tn1;
    tn1 = "test";
    REQUIRE(tn1.ContainsType<mguid::StringType>(mguid::Path{}));
    std::vector<mguid::KeyOrIdxType> path;
    REQUIRE(tn1.ContainsType<mguid::StringType>(path));
  }
  SECTION("Bool Empty Path") {
    mguid::TreeNode tn1;
    tn1 = true;
    REQUIRE(tn1.ContainsType<mguid::BoolType>(mguid::Path{}));
    std::vector<mguid::KeyOrIdxType> path;
    REQUIRE(tn1.ContainsType<mguid::BoolType>(path));
  }
  SECTION("Number Empty Path") {
    mguid::TreeNode tn1;
    tn1 = 5;
    REQUIRE(tn1.ContainsType<mguid::NumberType>(mguid::Path{}));
    std::vector<mguid::KeyOrIdxType> path;
    REQUIRE(tn1.ContainsType<mguid::NumberType>(path));
  }
  SECTION("Null Empty Path") {
    mguid::TreeNode tn1;
    tn1 = mguid::Null;
    REQUIRE(tn1.ContainsType<mguid::NullType>(mguid::Path{}));
    std::vector<mguid::KeyOrIdxType> path;
    REQUIRE(tn1.ContainsType<mguid::NullType>(path));
  }
  SECTION("Const String Empty Path") {
    mguid::TreeNode init;
    init = "test";
    const mguid::TreeNode tn1{init};
    REQUIRE(tn1.ContainsType<mguid::StringType>(mguid::Path{}));
    std::vector<mguid::KeyOrIdxType> path;
    REQUIRE(tn1.ContainsType<mguid::StringType>(path));
  }
  SECTION("Const Bool Empty Path") {
    mguid::TreeNode init;
    init = true;
    const mguid::TreeNode tn1{init};
    REQUIRE(tn1.ContainsType<mguid::BoolType>(mguid::Path{}));
    std::vector<mguid::KeyOrIdxType> path;
    REQUIRE(tn1.ContainsType<mguid::BoolType>(path));
  }
  SECTION("Const Number Empty Path") {
    mguid::TreeNode init;
    init = 5;
    const mguid::TreeNode tn1{init};
    REQUIRE(tn1.ContainsType<mguid::NumberType>(mguid::Path{}));
    std::vector<mguid::KeyOrIdxType> path;
    REQUIRE(tn1.ContainsType<mguid::NumberType>(path));
  }
  SECTION("Const Null Empty Path") {
    mguid::TreeNode init;
    init = mguid::Null;
    const mguid::TreeNode tn1{init};
    REQUIRE(tn1.ContainsType<mguid::NullType>(mguid::Path{}));
    std::vector<mguid::KeyOrIdxType> path;
    REQUIRE(tn1.ContainsType<mguid::NullType>(path));
  }
  SECTION("String") {
    mguid::TreeNode tn1;
    tn1["key1"]["key2"][2] = "test";
    REQUIRE(tn1.ContainsType<mguid::StringType>(mguid::Path{"key1", "key2", 2}));
    std::vector<mguid::KeyOrIdxType> path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsType<mguid::StringType>(path));
  }
  SECTION("Bool") {
    mguid::TreeNode tn1;
    tn1["key1"]["key2"][2] = true;
    REQUIRE(tn1.ContainsType<mguid::BoolType>(mguid::Path{"key1", "key2", 2}));
    std::vector<mguid::KeyOrIdxType> path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsType<mguid::BoolType>(path));
  }
  SECTION("Number") {
    mguid::TreeNode tn1;
    tn1["key1"]["key2"][2] = 5;
    REQUIRE(tn1.ContainsType<mguid::NumberType>(mguid::Path{"key1", "key2", 2}));
    std::vector<mguid::KeyOrIdxType> path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsType<mguid::NumberType>(path));
  }
  SECTION("Null") {
    mguid::TreeNode tn1;
    tn1["key1"]["key2"][2] = mguid::Null;
    REQUIRE(tn1.ContainsType<mguid::NullType>(mguid::Path{"key1", "key2", 2}));
    std::vector<mguid::KeyOrIdxType> path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsType<mguid::NullType>(path));
  }
  SECTION("Const String") {
    mguid::TreeNode init;
    init["key1"]["key2"][2] = "test";
    const mguid::TreeNode tn1{init};
    REQUIRE(tn1.ContainsType<mguid::StringType>(mguid::Path{"key1", "key2", 2}));
    std::vector<mguid::KeyOrIdxType> path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsType<mguid::StringType>(path));
  }
  SECTION("Const Bool") {
    mguid::TreeNode init;
    init["key1"]["key2"][2] = true;
    const mguid::TreeNode tn1{init};
    REQUIRE(tn1.ContainsType<mguid::BoolType>(mguid::Path{"key1", "key2", 2}));
    std::vector<mguid::KeyOrIdxType> path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsType<mguid::BoolType>(path));
  }
  SECTION("Const Number") {
    mguid::TreeNode init;
    init["key1"]["key2"][2] = 5;
    const mguid::TreeNode tn1{init};
    REQUIRE(tn1.ContainsType<mguid::NumberType>(mguid::Path{"key1", "key2", 2}));
    std::vector<mguid::KeyOrIdxType> path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsType<mguid::NumberType>(path));
  }
  SECTION("Const Null") {
    mguid::TreeNode init;
    init["key1"]["key2"][2] = mguid::Null;
    const mguid::TreeNode tn1{init};
    REQUIRE(tn1.ContainsType<mguid::NullType>(mguid::Path{"key1", "key2", 2}));
    std::vector<mguid::KeyOrIdxType> path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsType<mguid::NullType>(path));
  }
  SECTION("Not A Value") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    mguid::TreeNode tn2{mguid::NodeTypeTag::Array};
    const mguid::TreeNode ctn1{mguid::NodeTypeTag::Object};
    const mguid::TreeNode ctn2{mguid::NodeTypeTag::Array};
    REQUIRE_FALSE(tn1.ContainsType<mguid::NullType>(mguid::Path{"key1", "key2", 2}));
    REQUIRE_FALSE(tn2.ContainsType<mguid::NullType>(mguid::Path{"key1", "key2", 2}));
    REQUIRE_FALSE(ctn1.ContainsType<mguid::NullType>(mguid::Path{"key1", "key2", 2}));
    REQUIRE_FALSE(ctn2.ContainsType<mguid::NullType>(mguid::Path{"key1", "key2", 2}));
  }
  SECTION("Invalid Path") {
    {
      mguid::TreeNode tn1;
      tn1["key1"]["key2"][2] = mguid::Null;
      REQUIRE_FALSE(tn1.ContainsType<mguid::NullType>(mguid::Path{"key1", "missing", 2}));
      std::vector<mguid::KeyOrIdxType> path{"key1", "missing", 2};
      REQUIRE_FALSE(tn1.ContainsType<mguid::NullType>(path));
    }
    {
      mguid::TreeNode init;
      init["key1"]["key2"][2] = mguid::Null;
      const mguid::TreeNode tn1{init};
      REQUIRE_FALSE(tn1.ContainsType<mguid::NullType>(mguid::Path{"key1", "missing", 2}));
      std::vector<mguid::KeyOrIdxType> path{"key1", "missing", 2};
      REQUIRE_FALSE(tn1.ContainsType<mguid::NullType>(path));
    }
  }
}

TEST_CASE("Tree Node Contains Node Type") {
  SECTION("Empty Path Object") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    auto path = mguid::Path{};
    REQUIRE(tn1.ContainsNodeType<mguid::ObjectNodeType>(path));
    REQUIRE(tn1.ContainsNodeType<mguid::ObjectNodeType>(path.Items()));
  }
  SECTION("Const Empty Path Object") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    auto path = mguid::Path{};
    REQUIRE(tn1.ContainsNodeType<mguid::ObjectNodeType>(path));
    REQUIRE(tn1.ContainsNodeType<mguid::ObjectNodeType>(path.Items()));
  }
  SECTION("Empty Path Array") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    auto path = mguid::Path{};
    REQUIRE(tn1.ContainsNodeType<mguid::ArrayNodeType>(path));
    REQUIRE(tn1.ContainsNodeType<mguid::ArrayNodeType>(path.Items()));
  }
  SECTION("Const Empty Path Array") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    auto path = mguid::Path{};
    REQUIRE(tn1.ContainsNodeType<mguid::ArrayNodeType>(path));
    REQUIRE(tn1.ContainsNodeType<mguid::ArrayNodeType>(path.Items()));
  }
  SECTION("Empty Path Value") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
    auto path = mguid::Path{};
    REQUIRE(tn1.ContainsNodeType<mguid::ValueNodeType>(path));
    REQUIRE(tn1.ContainsNodeType<mguid::ValueNodeType>(path.Items()));
  }
  SECTION("Const Empty Path Value") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
    auto path = mguid::Path{};
    REQUIRE(tn1.ContainsNodeType<mguid::ValueNodeType>(path));
    REQUIRE(tn1.ContainsNodeType<mguid::ValueNodeType>(path.Items()));
  }
  SECTION("Not Empty Path Object") {
    mguid::TreeNode tn1;
    tn1["key1"]["key2"][2] = mguid::ObjectNodeType{};
    auto path = mguid::Path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsNodeType<mguid::ObjectNodeType>(path));
    REQUIRE(tn1.ContainsNodeType<mguid::ObjectNodeType>(path.Items()));
  }
  SECTION("Const Not Empty Path Object") {
    mguid::TreeNode init;
    init["key1"]["key2"][2] = mguid::ObjectNodeType{};
    const mguid::TreeNode tn1{init};
    auto path = mguid::Path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsNodeType<mguid::ObjectNodeType>(path));
    REQUIRE(tn1.ContainsNodeType<mguid::ObjectNodeType>(path.Items()));
  }
  SECTION("Not Empty Path Array") {
    mguid::TreeNode tn1;
    tn1["key1"]["key2"][2] = mguid::ArrayNodeType{};
    auto path = mguid::Path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsNodeType<mguid::ArrayNodeType>(path));
    REQUIRE(tn1.ContainsNodeType<mguid::ArrayNodeType>(path.Items()));
  }
  SECTION("Const Not Empty Path Array") {
    mguid::TreeNode init;
    init["key1"]["key2"][2] = mguid::ArrayNodeType{};
    const mguid::TreeNode tn1{init};
    auto path = mguid::Path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsNodeType<mguid::ArrayNodeType>(path));
    REQUIRE(tn1.ContainsNodeType<mguid::ArrayNodeType>(path.Items()));
  }
  SECTION("Not Empty Path Value") {
    mguid::TreeNode tn1;
    tn1["key1"]["key2"][2] = mguid::ValueNodeType{};
    auto path = mguid::Path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsNodeType<mguid::ValueNodeType>(path));
    REQUIRE(tn1.ContainsNodeType<mguid::ValueNodeType>(path.Items()));
  }
  SECTION("Const Not Empty Path Value") {
    mguid::TreeNode init;
    init["key1"]["key2"][2] = mguid::ValueNodeType{};
    const mguid::TreeNode tn1{init};
    auto path = mguid::Path{"key1", "key2", 2};
    REQUIRE(tn1.ContainsNodeType<mguid::ValueNodeType>(path));
    REQUIRE(tn1.ContainsNodeType<mguid::ValueNodeType>(path.Items()));
  }
  SECTION("Invalid Path") {
    {
      mguid::TreeNode tn1;
      tn1["key1"]["key2"][2] = mguid::ObjectNodeType{};
      REQUIRE_FALSE(tn1.ContainsNodeType<mguid::ObjectNodeType>(mguid::Path{"key1", "missing", 2}));
      std::vector<mguid::KeyOrIdxType> path{"key1", "missing", 2};
      REQUIRE_FALSE(tn1.ContainsNodeType<mguid::ObjectNodeType>(path));
    }
    {
      mguid::TreeNode init;
      init["key1"]["key2"][2] = mguid::ObjectNodeType{};
      const mguid::TreeNode tn1{init};
      REQUIRE_FALSE(tn1.ContainsNodeType<mguid::ObjectNodeType>(mguid::Path{"key1", "missing", 2}));
      std::vector<mguid::KeyOrIdxType> path{"key1", "missing", 2};
      REQUIRE_FALSE(tn1.ContainsNodeType<mguid::ObjectNodeType>(path));
    }
  }
}

TEST_CASE("Tree Node Try Get Value Type") {
  SECTION("Constructed With Null") {
    {
      mguid::TreeNode tn1{mguid::NullType{}};
      REQUIRE(tn1.TryGetNull().value() == mguid::NullType{});
    }
    {
      const mguid::TreeNode tn1{mguid::NullType{}};
      REQUIRE(tn1.TryGetNull().value() == mguid::NullType{});
    }
  }
  SECTION("Constructed With Integer") {
    {
      mguid::TreeNode tn1{std::int8_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetInt().value() == mguid::IntegerType{1});
    }
    {
      const mguid::TreeNode tn1{std::int8_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetInt().value() == mguid::IntegerType{1});
    }
    {
      mguid::TreeNode tn1{std::int16_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetInt().value() == mguid::IntegerType{1});
    }
    {
      const mguid::TreeNode tn1{std::int16_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetInt().value() == mguid::IntegerType{1});
    }
    {
      mguid::TreeNode tn1{std::int32_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetInt().value() == mguid::IntegerType{1});
    }
    {
      const mguid::TreeNode tn1{std::int32_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetInt().value() == mguid::IntegerType{1});
    }
    {
      mguid::TreeNode tn1{std::int64_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetInt().value() == mguid::IntegerType{1});
    }
    {
      const mguid::TreeNode tn1{std::int64_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetInt().value() == mguid::IntegerType{1});
    }
  }
  SECTION("Constructed With Unsigned Integer") {
    {
      mguid::TreeNode tn1{std::uint8_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      const mguid::TreeNode tn1{std::uint8_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      mguid::TreeNode tn1{std::uint16_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      const mguid::TreeNode tn1{std::uint16_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      mguid::TreeNode tn1{std::uint32_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      const mguid::TreeNode tn1{std::uint32_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      mguid::TreeNode tn1{std::uint64_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetUInt().value() == mguid::UnsignedIntegerType{1});
    }
    {
      const mguid::TreeNode tn1{std::uint64_t{1}};
      REQUIRE(tn1.TryGetNumber().value().GetUInt().value() == mguid::UnsignedIntegerType{1});
    }
  }
  SECTION("Constructed With Float") {
    {
      mguid::TreeNode tn1{float{1}};
      REQUIRE(tn1.TryGetNumber().value().GetDouble().value() == mguid::DoubleType{1});
    }
    {
      const mguid::TreeNode tn1{float{1}};
      REQUIRE(tn1.TryGetNumber().value().GetDouble().value() == mguid::DoubleType{1});
    }
    {
      mguid::TreeNode tn1{double{1}};
      REQUIRE(tn1.TryGetNumber().value().GetDouble().value() == mguid::DoubleType{1});
    }
    {
      const mguid::TreeNode tn1{double{1}};
      REQUIRE(tn1.TryGetNumber().value().GetDouble().value() == mguid::DoubleType{1});
    }
  }
  SECTION("Constructed With Bool") {
    {
      mguid::TreeNode tn1{true};
      REQUIRE(tn1.TryGetBool().value());
    }
    {
      const mguid::TreeNode tn1{true};
      REQUIRE(tn1.TryGetBool().value());
    }
    {
      mguid::TreeNode tn1{false};
      REQUIRE_FALSE(tn1.TryGetBool().value());
    }
    {
      const mguid::TreeNode tn1{false};
      REQUIRE_FALSE(tn1.TryGetBool().value());
    }
  }
  SECTION("Constructed With String") {
    {
      mguid::TreeNode tn1{std::string{"test"}};
      REQUIRE(tn1.TryGetString().value() == "test");
    }
    {
      const mguid::TreeNode tn1{std::string{"test"}};
      REQUIRE(tn1.TryGetString().value() == "test");
    }
    {
      mguid::TreeNode tn1{"test"};
      REQUIRE(tn1.TryGetString().value() == "test");
    }
    {
      const mguid::TreeNode tn1{"test"};
      REQUIRE(tn1.TryGetString().value() == "test");
    }
    {
      char test[] = "test";
      mguid::TreeNode tn1{test};
      REQUIRE(tn1.TryGetString().value() == "test");
    }
    {
      char test[] = "test";
      const mguid::TreeNode tn1{test};
      REQUIRE(tn1.TryGetString().value() == "test");
    }
  }
}

TEST_CASE("Tree Node Get Value Type") {
  SECTION("Constructed With Null") {
    {
      mguid::TreeNode tn1{mguid::NullType{}};
      tn1.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetNull() == mguid::NullType{}); });
    }
    {
      const mguid::TreeNode tn1{mguid::NullType{}};
      tn1.ConstUnsafe([](const auto&& unsafe) { REQUIRE(unsafe.GetNull() == mguid::NullType{}); });
    }
  }
  SECTION("Constructed With Integer") {
    {
      mguid::TreeNode tn1{std::int8_t{1}};
      tn1.Unsafe([](auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetInt().value() == mguid::IntegerType{1});
      });
    }
    {
      const mguid::TreeNode tn1{std::int8_t{1}};
      tn1.ConstUnsafe([](const auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetInt().value() == mguid::IntegerType{1});
      });
    }
    {
      mguid::TreeNode tn1{std::int16_t{1}};
      tn1.Unsafe([](auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetInt().value() == mguid::IntegerType{1});
      });
    }
    {
      const mguid::TreeNode tn1{std::int16_t{1}};
      tn1.ConstUnsafe([](const auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetInt().value() == mguid::IntegerType{1});
      });
    }
    {
      mguid::TreeNode tn1{std::int32_t{1}};
      tn1.Unsafe([](auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetInt().value() == mguid::IntegerType{1});
      });
    }
    {
      const mguid::TreeNode tn1{std::int32_t{1}};
      tn1.ConstUnsafe([](const auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetInt().value() == mguid::IntegerType{1});
      });
    }
    {
      mguid::TreeNode tn1{std::int64_t{1}};
      tn1.Unsafe([](auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetInt().value() == mguid::IntegerType{1});
      });
    }
    {
      const mguid::TreeNode tn1{std::int64_t{1}};
      tn1.ConstUnsafe([](const auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetInt().value() == mguid::IntegerType{1});
      });
    }
  }
  SECTION("Constructed With Unsigned Integer") {
    {
      mguid::TreeNode tn1{std::uint8_t{1}};
      tn1.Unsafe([](auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetUInt().value() == mguid::UnsignedIntegerType{1});
      });
    }
    {
      const mguid::TreeNode tn1{std::uint8_t{1}};
      tn1.ConstUnsafe([](const auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetUInt().value() == mguid::UnsignedIntegerType{1});
      });
    }
    {
      mguid::TreeNode tn1{std::uint16_t{1}};
      tn1.Unsafe([](auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetUInt().value() == mguid::UnsignedIntegerType{1});
      });
    }
    {
      const mguid::TreeNode tn1{std::uint16_t{1}};
      tn1.ConstUnsafe([](const auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetUInt().value() == mguid::UnsignedIntegerType{1});
      });
    }
    {
      mguid::TreeNode tn1{std::uint32_t{1}};
      tn1.Unsafe([](auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetUInt().value() == mguid::UnsignedIntegerType{1});
      });
    }
    {
      const mguid::TreeNode tn1{std::uint32_t{1}};
      tn1.ConstUnsafe([](const auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetUInt().value() == mguid::UnsignedIntegerType{1});
      });
    }
    {
      mguid::TreeNode tn1{std::uint64_t{1}};
      tn1.Unsafe([](auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetUInt().value() == mguid::UnsignedIntegerType{1});
      });
    }
    {
      const mguid::TreeNode tn1{std::uint64_t{1}};
      tn1.ConstUnsafe([](const auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetUInt().value() == mguid::UnsignedIntegerType{1});
      });
    }
  }
  SECTION("Constructed With Float") {
    {
      mguid::TreeNode tn1{float{1}};
      tn1.Unsafe([](auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetDouble().value() == mguid::DoubleType{1});
      });
    }
    {
      const mguid::TreeNode tn1{float{1}};
      tn1.ConstUnsafe([](const auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetDouble().value() == mguid::DoubleType{1});
      });
    }
    {
      mguid::TreeNode tn1{double{1}};
      tn1.Unsafe([](auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetDouble().value() == mguid::DoubleType{1});
      });
    }
    {
      const mguid::TreeNode tn1{double{1}};
      tn1.ConstUnsafe([](const auto&& unsafe) {
        REQUIRE(unsafe.GetNumber().GetDouble().value() == mguid::DoubleType{1});
      });
    }
  }
  SECTION("Constructed With Bool") {
    {
      mguid::TreeNode tn1{true};
      tn1.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetBool()); });
    }
    {
      const mguid::TreeNode tn1{true};
      tn1.ConstUnsafe([](const auto&& unsafe) { REQUIRE(unsafe.GetBool()); });
    }
    {
      mguid::TreeNode tn1{false};
      tn1.Unsafe([](auto&& unsafe) { REQUIRE_FALSE(unsafe.GetBool()); });
    }
    {
      const mguid::TreeNode tn1{false};
      tn1.ConstUnsafe([](const auto&& unsafe) { REQUIRE_FALSE(unsafe.GetBool()); });
    }
  }
  SECTION("Constructed With String") {
    {
      mguid::TreeNode tn1{std::string{"test"}};
      tn1.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetString() == "test"); });
    }
    {
      const mguid::TreeNode tn1{std::string{"test"}};
      tn1.ConstUnsafe([](const auto&& unsafe) { REQUIRE(unsafe.GetString() == "test"); });
    }
    {
      mguid::TreeNode tn1{"test"};
      tn1.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetString() == "test"); });
    }
    {
      const mguid::TreeNode tn1{"test"};
      tn1.ConstUnsafe([](const auto&& unsafe) { REQUIRE(unsafe.GetString() == "test"); });
    }
    {
      char test[] = "test";
      mguid::TreeNode tn1{test};
      tn1.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetString() == "test"); });
    }
    {
      char test[] = "test";
      const mguid::TreeNode tn1{test};
      tn1.ConstUnsafe([](const auto&& unsafe) { REQUIRE(unsafe.GetString() == "test"); });
    }
  }
}

TEST_CASE("Tree Node Get Type") {
  SECTION("Get Object") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    tn1.Unsafe([](mguid::TreeNode::UnsafeProxy&& unsafe) {
      REQUIRE(unsafe.GetObject() == mguid::ObjectNodeType());
      REQUIRE(unsafe.Get<mguid::ObjectNodeType>() == mguid::ObjectNodeType());
    });
  }
  SECTION("Get Object Const") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    tn1.ConstUnsafe([](mguid::TreeNode::ConstUnsafeProxy&& unsafe) {
      REQUIRE(unsafe.GetObject() == mguid::ObjectNodeType());
      REQUIRE(unsafe.Get<mguid::ObjectNodeType>() == mguid::ObjectNodeType());
    });
  }
  SECTION("Get Array") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    tn1.Unsafe([](mguid::TreeNode::UnsafeProxy&& unsafe) {
      REQUIRE(unsafe.GetArray() == mguid::ArrayNodeType());
      REQUIRE(unsafe.Get<mguid::ArrayNodeType>() == mguid::ArrayNodeType());
    });
  }
  SECTION("Get Array Const") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    tn1.ConstUnsafe([](mguid::TreeNode::ConstUnsafeProxy&& unsafe) {
      REQUIRE(unsafe.GetArray() == mguid::ArrayNodeType());
      REQUIRE(unsafe.Get<mguid::ArrayNodeType>() == mguid::ArrayNodeType());
    });
  }
  SECTION("Get Value") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
    tn1.Unsafe([](mguid::TreeNode::UnsafeProxy&& unsafe) {
      REQUIRE(unsafe.GetValue() == mguid::ValueNodeType());
      REQUIRE(unsafe.Get<mguid::ValueNodeType>() == mguid::ValueNodeType());
    });
  }
  SECTION("Get Value Const") {
    const mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
    tn1.ConstUnsafe([](mguid::TreeNode::ConstUnsafeProxy&& unsafe) {
      REQUIRE(unsafe.GetValue() == mguid::ValueNodeType());
      REQUIRE(unsafe.Get<mguid::ValueNodeType>() == mguid::ValueNodeType());
    });
  }
}

TEST_CASE("Tree Node Set") {
  SECTION("Set Object") {
    mguid::TreeNode tn1;
    tn1.Set(mguid::ObjectNodeType{});
    REQUIRE(tn1.TryGetObject().has_value());
  }
  SECTION("Set Array") {
    mguid::TreeNode tn1;
    tn1.Set(mguid::ArrayNodeType{});
    REQUIRE(tn1.TryGetArray().has_value());
  }
  SECTION("Set Value") {
    mguid::TreeNode tn1;
    tn1.Set(mguid::ValueNodeType{});
    REQUIRE(tn1.TryGetValue().has_value());
  }
}

TEST_CASE("Tree Node Reset") {
  SECTION("Reset Object") {
    mguid::TreeNode tn1;
    tn1.Set(mguid::ObjectNodeType{});
    tn1.Reset();
    REQUIRE(tn1.HasObject());
    tn1.Reset(mguid::NodeTypeTag::Array);
    REQUIRE(tn1.HasArray());
    tn1.Reset(mguid::NodeTypeTag::Value);
    REQUIRE(tn1.HasValue());
    tn1.Reset(mguid::NodeTypeTag::Object);
    REQUIRE(tn1.HasObject());
  }
  SECTION("Reset Static") {
    mguid::TreeNode tn1;
    tn1.Set(mguid::ObjectNodeType{});
    tn1.Reset<>();
    REQUIRE(tn1.HasObject());
    tn1.Reset<mguid::NodeTypeTag::Array>();
    REQUIRE(tn1.HasArray());
    tn1.Reset<mguid::NodeTypeTag::Value>();
    REQUIRE(tn1.HasValue());
    tn1.Reset<mguid::NodeTypeTag::Object>();
    REQUIRE(tn1.HasObject());
  }
}

TEST_CASE("Tree Node Visit") {
  SECTION("Visit Object") {
    SECTION("Three Overloads Return") {
      mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
      int result = tn1.Visit([](const mguid::ObjectNodeType&) { return 0; },
                             [](const mguid::ArrayNodeType&) { return 1; },
                             [](const mguid::ValueNodeType&) { return 2; });
      REQUIRE(result == 0);
    }
    SECTION("Three Overloads Assign Reference Capture") {
      mguid::TreeNode tn1{mguid::NodeTypeTag::Object};

      int result;
      tn1.Visit([&result](const mguid::ObjectNodeType&) { result = 0; },
                [&result](const mguid::ArrayNodeType&) { result = 1; },
                [&result](const mguid::ValueNodeType&) { result = 2; });

      REQUIRE(result == 0);
    }
    SECTION("Visit Object Const") {
      SECTION("Three Overloads Return") {
        const mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
        int result = tn1.Visit([](const mguid::ObjectNodeType&) { return 0; },
                               [](const mguid::ArrayNodeType&) { return 1; },
                               [](const mguid::ValueNodeType&) { return 2; });
        REQUIRE(result == 0);
      }
      SECTION("Three Overloads Assign Reference Capture") {
        const mguid::TreeNode tn1{mguid::NodeTypeTag::Object};

        int result;
        tn1.Visit([&result](const mguid::ObjectNodeType&) { result = 0; },
                  [&result](const mguid::ArrayNodeType&) { result = 1; },
                  [&result](const mguid::ValueNodeType&) { result = 2; });

        REQUIRE(result == 0);
      }
      SECTION("One Templated Overload Return") {
        mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
        int result = tn1.Visit([]<typename T>(T&&) {
          using Underlying = std::remove_cvref_t<T>;
          if constexpr (std::same_as<Underlying, mguid::ObjectNodeType>) {
            return 0;
          } else if constexpr (std::same_as<Underlying, mguid::ArrayNodeType>) {
            return 1;
          } else {
            return 2;
          }
        });
        REQUIRE(result == 0);
      }
      SECTION("One Templated Overload Return Const") {
        const mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
        int result = tn1.Visit([]<typename T>(T&&) {
          using Underlying = std::remove_cvref_t<T>;
          if constexpr (std::same_as<Underlying, mguid::ObjectNodeType>) {
            return 0;
          } else if constexpr (std::same_as<Underlying, mguid::ArrayNodeType>) {
            return 1;
          } else {
            return 2;
          }
        });
        REQUIRE(result == 0);
      }
    }
    SECTION("Visit Array") {
      SECTION("Three Overloads Return") {
        mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
        int result = tn1.Visit([](const mguid::ObjectNodeType&) { return 0; },
                               [](const mguid::ArrayNodeType&) { return 1; },
                               [](const mguid::ValueNodeType&) { return 2; });
        REQUIRE(result == 1);
      }
      SECTION("Three Overloads Return Const") {
        const mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
        int result = tn1.Visit([](const mguid::ObjectNodeType&) { return 0; },
                               [](const mguid::ArrayNodeType&) { return 1; },
                               [](const mguid::ValueNodeType&) { return 2; });
        REQUIRE(result == 1);
      }
      SECTION("Three Overloads Assign Reference Capture") {
        mguid::TreeNode tn1{mguid::NodeTypeTag::Array};

        int result;
        tn1.Visit([&result](const mguid::ObjectNodeType&) { result = 0; },
                  [&result](const mguid::ArrayNodeType&) { result = 1; },
                  [&result](const mguid::ValueNodeType&) { result = 2; });

        REQUIRE(result == 1);
      }
      SECTION("Three Overloads Assign Reference Capture Const") {
        const mguid::TreeNode tn1{mguid::NodeTypeTag::Array};

        int result;
        tn1.Visit([&result](const mguid::ObjectNodeType&) { result = 0; },
                  [&result](const mguid::ArrayNodeType&) { result = 1; },
                  [&result](const mguid::ValueNodeType&) { result = 2; });

        REQUIRE(result == 1);
      }
      SECTION("One Templated Overload Return") {
        mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
        int result = tn1.Visit([]<typename T>(T&&) {
          using Underlying = std::remove_cvref_t<T>;
          if constexpr (std::same_as<Underlying, mguid::ObjectNodeType>) {
            return 0;
          } else if constexpr (std::same_as<Underlying, mguid::ArrayNodeType>) {
            return 1;
          } else {
            return 2;
          }
        });
        REQUIRE(result == 1);
      }
      SECTION("One Templated Overload Return Const") {
        const mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
        int result = tn1.Visit([]<typename T>(T&&) {
          using Underlying = std::remove_cvref_t<T>;
          if constexpr (std::same_as<Underlying, mguid::ObjectNodeType>) {
            return 0;
          } else if constexpr (std::same_as<Underlying, mguid::ArrayNodeType>) {
            return 1;
          } else {
            return 2;
          }
        });
        REQUIRE(result == 1);
      }
    }
    SECTION("Visit Value") {
      SECTION("Three Overloads Return") {
        mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
        int result = tn1.Visit([](const mguid::ObjectNodeType&) { return 0; },
                               [](const mguid::ArrayNodeType&) { return 1; },
                               [](const mguid::ValueNodeType&) { return 2; });
        REQUIRE(result == 2);
      }
      SECTION("Three Overloads Return Const") {
        const mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
        int result = tn1.Visit([](const mguid::ObjectNodeType&) { return 0; },
                               [](const mguid::ArrayNodeType&) { return 1; },
                               [](const mguid::ValueNodeType&) { return 2; });
        REQUIRE(result == 2);
      }
      SECTION("Three Overloads Assign Reference Capture") {
        mguid::TreeNode tn1{mguid::NodeTypeTag::Value};

        int result;
        tn1.Visit([&result](const mguid::ObjectNodeType&) { result = 0; },
                  [&result](const mguid::ArrayNodeType&) { result = 1; },
                  [&result](const mguid::ValueNodeType&) { result = 2; });

        REQUIRE(result == 2);
      }
      SECTION("Three Overloads Assign Reference Capture Const") {
        const mguid::TreeNode tn1{mguid::NodeTypeTag::Value};

        int result;
        tn1.Visit([&result](const mguid::ObjectNodeType&) { result = 0; },
                  [&result](const mguid::ArrayNodeType&) { result = 1; },
                  [&result](const mguid::ValueNodeType&) { result = 2; });

        REQUIRE(result == 2);
      }
      SECTION("One Templated Overload Return") {
        mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
        int result = tn1.Visit([]<typename T>(T&&) {
          using Underlying = std::remove_cvref_t<T>;
          if constexpr (std::same_as<Underlying, mguid::ObjectNodeType>) {
            return 0;
          } else if constexpr (std::same_as<Underlying, mguid::ArrayNodeType>) {
            return 1;
          } else {
            return 2;
          }
        });
        REQUIRE(result == 2);
      }
      SECTION("One Templated Overload Return Const") {
        const mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
        int result = tn1.Visit([]<typename T>(T&&) {
          using Underlying = std::remove_cvref_t<T>;
          if constexpr (std::same_as<Underlying, mguid::ObjectNodeType>) {
            return 0;
          } else if constexpr (std::same_as<Underlying, mguid::ArrayNodeType>) {
            return 1;
          } else {
            return 2;
          }
        });
        REQUIRE(result == 2);
      }
    }
  }
}

TEST_CASE("Tree Node Operator []") {
  SECTION("Key Exists") {
    mguid::TreeNode ont1{mguid::ObjectNodeType{{"key", mguid::TreeNode{}}}};
    REQUIRE(ont1["key"].HasObject());
    const std::string key{"key"};
    REQUIRE(ont1[key].HasObject());
  }
  SECTION("Key Exists Const") {
    const mguid::TreeNode ont1{mguid::ObjectNodeType{{"key", mguid::TreeNode{}}}};
    ont1.ConstUnsafe([](auto&& unsafe) {
      REQUIRE(unsafe["key"].Safe().HasObject());
      const std::string key{"key"};
      REQUIRE(unsafe[key].Safe().HasObject());
    });
  }
  SECTION("Key Doesn't Exist") {
    mguid::TreeNode ont1;
    ont1.Unsafe([](auto&& unsafe, auto& safe) {
      REQUIRE(unsafe.GetObject().Empty());
      REQUIRE(safe["key1"].HasObject());
      REQUIRE(unsafe.GetObject().Size() == 1);
      const std::string key2{"key2"};
      REQUIRE(safe[key2].HasObject());
      REQUIRE(unsafe.GetObject().Size() == 2);
    });
  }
  SECTION("Get Non-Existent Index Empty") {
    mguid::TreeNode ont1{mguid::ArrayNodeType{}};
    ont1.Unsafe([](auto&& unsafe, auto& safe) {
      REQUIRE(unsafe.GetArray().Empty());
      const auto& result = safe[0];
      REQUIRE(unsafe.GetArray().Size() == 1);
      REQUIRE(result.HasValue());
    });
  }
  SECTION("Get Not Empty") {
    {
      mguid::TreeNode tn1{mguid::ArrayNodeType{{}, {}, {}, {}}};

      tn1.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetArray().Size() == 4); });

      const auto& result1 = tn1[0];
      const auto& result2 = tn1[1];
      const auto& result3 = tn1[2];
      const auto& result4 = tn1[3];

      tn1.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetArray().Size() == 4); });

      REQUIRE(result1.HasObject());
      REQUIRE(result2.HasObject());
      REQUIRE(result3.HasObject());
      REQUIRE(result4.HasObject());
    }
    {
      const mguid::TreeNode tn1{mguid::ArrayNodeType{{}, {}, {}, {}}};

      tn1.ConstUnsafe([](auto&& unsafe) {
        REQUIRE(unsafe.GetArray().Size() == 4);

        const auto& result1 = unsafe[0];
        const auto& result2 = unsafe[1];
        const auto& result3 = unsafe[2];
        const auto& result4 = unsafe[3];

        REQUIRE(unsafe.GetArray().Size() == 4);

        REQUIRE(result1.Safe().HasObject());
        REQUIRE(result2.Safe().HasObject());
        REQUIRE(result3.Safe().HasObject());
        REQUIRE(result4.Safe().HasObject());
      });
    }
  }
  SECTION("Get Non-Existent Index Index Not Empty") {
    mguid::TreeNode tn1{mguid::ArrayNodeType{{}, {}, {}, {}}};
    tn1.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetArray().Size() == 4); });
    const auto& result = tn1[4];
    tn1.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetArray().Size() == 5); });
    REQUIRE(result.HasValue());
  }
}

TEST_CASE("Tree Node Comparison") {
  SECTION("Equality") {
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::StringType{})) ==
            mguid::TreeNode(mguid::ValueNodeType(mguid::StringType{})));
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::BoolType{})) ==
            mguid::TreeNode(mguid::ValueNodeType(mguid::BoolType{})));
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::NullType{})) ==
            mguid::TreeNode(mguid::ValueNodeType(mguid::NullType{})));
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::NumberType{})) ==
            mguid::TreeNode(mguid::ValueNodeType(mguid::NumberType{})));

    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::StringType{"test"})) ==
            mguid::TreeNode(mguid::ValueNodeType(mguid::StringType{"test"})));
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::BoolType{true})) ==
            mguid::TreeNode(mguid::ValueNodeType(mguid::BoolType{true})));
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::NullType{})) ==
            mguid::TreeNode(mguid::ValueNodeType(mguid::NullType{})));
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::NumberType{1})) ==
            mguid::TreeNode(mguid::ValueNodeType(mguid::NumberType{1})));

    REQUIRE(mguid::TreeNode(mguid::ObjectNodeType()) == mguid::TreeNode(mguid::ObjectNodeType()));

    REQUIRE(mguid::TreeNode(mguid::ObjectNodeType({{"key", {}}})) ==
            mguid::TreeNode(mguid::ObjectNodeType({{"key", {}}})));

    REQUIRE(mguid::TreeNode(mguid::ArrayNodeType()) == mguid::TreeNode(mguid::ArrayNodeType()));

    REQUIRE(mguid::TreeNode(mguid::ArrayNodeType({{}, {}})) ==
            mguid::TreeNode(mguid::ArrayNodeType({{}, {}})));
  }
  SECTION("Inequality") {
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::BoolType{})) !=
            mguid::TreeNode(mguid::ValueNodeType(mguid::StringType{})));
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::BoolType{})) !=
            mguid::TreeNode(mguid::ValueNodeType(mguid::NumberType{})));
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::NullType{})) !=
            mguid::TreeNode(mguid::ValueNodeType(mguid::BoolType{})));
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::NumberType{})) !=
            mguid::TreeNode(mguid::ValueNodeType(mguid::StringType{})));

    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::StringType{"test"})) !=
            mguid::TreeNode(mguid::ValueNodeType(mguid::StringType{"nottest"})));
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::BoolType{true})) !=
            mguid::TreeNode(mguid::ValueNodeType(mguid::BoolType{false})));
    // NullType is always equal to itself since it only has 1 value
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType(mguid::NumberType{1})) !=
            mguid::TreeNode(mguid::ValueNodeType(mguid::NumberType{2})));

    REQUIRE(mguid::TreeNode(mguid::ObjectNodeType()) !=
            mguid::TreeNode(mguid::ObjectNodeType({{"key", {}}})));

    REQUIRE(mguid::TreeNode(mguid::ObjectNodeType({{"key", {}}})) !=
            mguid::TreeNode(mguid::ObjectNodeType({{"notkey", {}}})));

    REQUIRE(mguid::TreeNode(mguid::ArrayNodeType()) != mguid::TreeNode(mguid::ArrayNodeType({{}})));

    REQUIRE(mguid::TreeNode(mguid::ArrayNodeType({{}, {}})) !=
            mguid::TreeNode(mguid::ArrayNodeType({{}, {}, {}})));

    REQUIRE(mguid::TreeNode(mguid::ArrayNodeType()) != mguid::TreeNode(mguid::ObjectNodeType()));
    REQUIRE(mguid::TreeNode(mguid::ArrayNodeType()) != mguid::TreeNode(mguid::ValueNodeType()));

    REQUIRE(mguid::TreeNode(mguid::ObjectNodeType()) != mguid::TreeNode(mguid::ArrayNodeType()));
    REQUIRE(mguid::TreeNode(mguid::ObjectNodeType()) != mguid::TreeNode(mguid::ValueNodeType()));

    REQUIRE(mguid::TreeNode(mguid::ValueNodeType()) != mguid::TreeNode(mguid::ArrayNodeType()));
    REQUIRE(mguid::TreeNode(mguid::ValueNodeType()) != mguid::TreeNode(mguid::ObjectNodeType()));
  }
}

TEST_CASE("Tree Node Erase") {
  mguid::TreeNode tn1;
  tn1["object"]["first"];
  tn1["object"]["second"];
  tn1["object"]["third"];
  tn1["array"][9];

  tn1.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetObject().Size() == 2); });

  auto& obj = tn1["object"];
  obj.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetObject().Size() == 3); });
  obj.Erase("second");
  obj.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetObject().Size() == 2); });

  auto& arr = tn1["array"];
  arr.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetArray().Size() == 10); });
  arr.Erase(5);
  arr.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.GetArray().Size() == 9); });
}

TEST_CASE("Tree Node Recursive Visit") {
  mguid::TreeNode tn1;
  tn1["first"]["second"]["array"] = mguid::ArrayNodeType{};
  tn1["first"]["second"]["object"] = mguid::ObjectNodeType{};
  tn1["first"]["second"]["value"] = mguid::ValueNodeType{};
  tn1["first"]["second"]["number_value_signed"] = 1;
  tn1["first"]["second"]["number_value_unsigned"] = 1u;
  tn1["first"]["second"]["number_value_double"] = 1.2345;
  tn1["first"]["second"]["bool_value_true"] = true;
  tn1["first"]["second"]["bool_value_false"] = false;
  tn1["first"]["second"]["null_value"] = mguid::Null;
  tn1["first"]["second"]["string_literal_value"] = "Hello, World!";
  tn1["first"]["second"]["string_value"] = std::string("42");
  tn1["first"]["second"]["array"][3] = 4;

  const mguid::TreeNode tn2{tn1};

  tn1.Unsafe([](auto&& unsafe){
    int count{0};
    unsafe.RecursiveVisit([&](auto){count++;});

    REQUIRE(count == 18);
  });

  tn1.ConstUnsafe([](const auto&& unsafe){
    int count{0};
    unsafe.RecursiveVisit([&](auto){count++;});

    REQUIRE(count == 18);
  });

  tn2.ConstUnsafe([](const auto&& unsafe){
    int count{0};
    unsafe.RecursiveVisit([&](auto){count++;});

    REQUIRE(count == 18);
  });
}