/**
 * @brief Tests for object node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include "data_tree/tree_node/tree_node.hpp"

using TestMapType = std::unordered_map<std::string, mguid::TreeNode>;

TEST_CASE("Object Node Constructor") {
  SECTION("Default Constructor") {
    REQUIRE(std::is_default_constructible_v<mguid::ObjectNodeType>);
    mguid::ObjectNodeType ont1;
    REQUIRE(ont1.Empty());
    REQUIRE(ont1.Size() == 0);
  }
  SECTION("Copy Constructor") {
    REQUIRE(std::is_copy_constructible_v<mguid::ObjectNodeType>);
    mguid::ObjectNodeType ont1{{"key", mguid::TreeNode{}}};
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    mguid::ObjectNodeType ont2{ont1};
    REQUIRE_FALSE(ont2.Empty());
    REQUIRE(ont2.Size() == 1);
  }
  SECTION("Move Constructor") {
    REQUIRE(std::is_nothrow_move_constructible_v<mguid::ObjectNodeType>);
    mguid::ObjectNodeType ont1{{"key", mguid::TreeNode{}}};
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    mguid::ObjectNodeType ont2{std::move(ont1)};
    REQUIRE_FALSE(ont2.Empty());
    REQUIRE(ont2.Size() == 1);
  }
  SECTION("Copy Assignment") {
    REQUIRE(std::is_copy_assignable_v<mguid::ObjectNodeType>);
    mguid::ObjectNodeType ont1{{"key", mguid::TreeNode{}}};
    mguid::ObjectNodeType ont2;
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont2.Empty());
    REQUIRE(ont2.Size() == 0);
    ont2 = ont1;
    REQUIRE_FALSE(ont2.Empty());
    REQUIRE(ont2.Size() == 1);
  }
  SECTION("Move Assignment") {
    REQUIRE(std::is_nothrow_move_assignable_v<mguid::ObjectNodeType>);
    mguid::ObjectNodeType ont1{{"key", mguid::TreeNode{}}};
    mguid::ObjectNodeType ont2;
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont2.Empty());
    REQUIRE(ont2.Size() == 0);
    ont2 = std::move(ont1);
    REQUIRE_FALSE(ont2.Empty());
    REQUIRE(ont2.Size() == 1);
  }
  SECTION("Construction From Map") {
    REQUIRE(std::is_constructible_v<mguid::ObjectNodeType, TestMapType>);
    TestMapType init_map{{"key", mguid::TreeNode{}}};
    mguid::ObjectNodeType ont1{init_map};
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Construction From Initializer List") {
    REQUIRE(std::is_constructible_v<mguid::ObjectNodeType, TestMapType>);
    mguid::ObjectNodeType ont1{{"key", mguid::TreeNode{}}};
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Assignment From Initializer List") {
    REQUIRE(std::is_constructible_v<mguid::ObjectNodeType, TestMapType>);
    mguid::ObjectNodeType ont1;
    ont1 = {{"key", mguid::TreeNode{}}};
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
}

TEST_CASE("Object Node Type Get") {
  SECTION("Key Exists") {
    mguid::ObjectNodeType ont1{{"key", mguid::TreeNode{}}};
    REQUIRE(ont1.TryGet("key").has_value());
  }
  SECTION("Key Exists Const") {
    const mguid::ObjectNodeType ont1{{"key", mguid::TreeNode{}}};
    REQUIRE(ont1.TryGet("key").has_value());
  }
  SECTION("Key Doesn't Exist") {
    mguid::ObjectNodeType ont1;
    auto result = ont1.TryGet("key");
    REQUIRE_FALSE(result.has_value());
    REQUIRE(result.error().category == mguid::Error::Category::KeyError);
  }
  SECTION("Key Doesn't Exist Const") {
    const mguid::ObjectNodeType ont1;
    auto result = ont1.TryGet("key");
    REQUIRE_FALSE(result.has_value());
    REQUIRE(result.error().category == mguid::Error::Category::KeyError);
  }
}

TEST_CASE("Object Node Type At") {
  SECTION("Key Exists") {
    mguid::ObjectNodeType ont1{{"key", mguid::TreeNode{}}};
    ont1.Unsafe([](auto&& unsafe) { REQUIRE(unsafe.At("key").HasObject()); });
  }
  SECTION("Key Exists Const") {
    const mguid::ObjectNodeType ont1{{"key", mguid::TreeNode{}}};
    ont1.ConstUnsafe([](const auto&& unsafe) { REQUIRE(unsafe.At("key").HasObject()); });
  }
  SECTION("Key Doesn't Exist") {
    mguid::ObjectNodeType ont1;
    ont1.Unsafe([](auto&& unsafe) { REQUIRE_THROWS(unsafe.At("key")); });
  }
  SECTION("Key Doesn't Exist Const") {
    const mguid::ObjectNodeType ont1;
    ont1.ConstUnsafe([](const auto&& unsafe) { REQUIRE_THROWS(unsafe.At("key")); });
  }
}

TEST_CASE("Object Node Type Operator []") {
  SECTION("Key Exists") {
    mguid::ObjectNodeType ont1{{"key", mguid::TreeNode{}}};
    REQUIRE(ont1["key"].HasObject());
    const std::string key{"key"};
    REQUIRE(ont1[key].HasObject());
  }
  SECTION("Key Exists Const") {
    const mguid::ObjectNodeType ont1{{"key", mguid::TreeNode{}}};
    ont1.ConstUnsafe([](const auto&& unsafe){
      REQUIRE(unsafe["key"].HasObject());
      const std::string key{"key"};
      REQUIRE(unsafe[key].HasObject());
    });
  }
  SECTION("Key Doesn't Exist") {
    mguid::ObjectNodeType ont1;
    REQUIRE(ont1.Empty());
    REQUIRE(ont1["key1"].HasObject());
    REQUIRE(ont1.Size() == 1);
    const std::string key2{"key2"};
    REQUIRE(ont1[key2].HasObject());
    REQUIRE(ont1.Size() == 2);
  }
  SECTION("Key Exists Move Key") {
    mguid::ObjectNodeType ont1{{"key", mguid::TreeNode{}}};
    std::string key{"key"};
    // NOLINTNEXTLINE(bugprone-use-after-move,hicpp-invalid-access-moved)
    REQUIRE(ont1[std::move(key)].HasObject());
  }
  SECTION("Key Doesn't Exist Move Key") {
    mguid::ObjectNodeType ont1;
    std::string key{"key"};
    REQUIRE(ont1.Empty());
    // NOLINTNEXTLINE(bugprone-use-after-move,hicpp-invalid-access-moved)
    REQUIRE(ont1[std::move(key)].HasObject());
    REQUIRE(ont1.Size() == 1);
  }
}

TEST_CASE("Object Node Type Clear") {
  SECTION("Already Empty") {
    mguid::ObjectNodeType ont1;
    REQUIRE(ont1.Empty());
    ont1.Clear();
    REQUIRE(ont1.Empty());
  }
  SECTION("1 Element") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    ont1.Clear();
    REQUIRE(ont1.Empty());
    REQUIRE(ont1.Size() == 0);
  }
  SECTION("Many Elements") {
    mguid::ObjectNodeType ont1;
    for (auto i{0}; i < 1024; ++i) { ont1.Emplace(std::to_string(i), mguid::TreeNode{}); }
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1024);
    ont1.Clear();
    REQUIRE(ont1.Empty());
    REQUIRE(ont1.Size() == 0);
  }
}

TEST_CASE("Object Node Insert") {
  SECTION("Insert const &") {
    mguid::ObjectNodeType ont1;
    const std::pair<const std::string, mguid::TreeNode> p1{"key", {}};
    auto result = ont1.Insert(p1);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert const & Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    const std::pair<const std::string, mguid::TreeNode> p1{"key", {}};
    auto result = ont1.Insert(p1);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert &&") {
    mguid::ObjectNodeType ont1;
    std::pair<const std::string, mguid::TreeNode> p1{"key", {}};
    auto result = ont1.Insert(std::move(p1));
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert && Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    std::pair<const std::string, mguid::TreeNode> p1{"key", {}};
    auto result = ont1.Insert(std::move(p1));
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Convertible Type") {
    mguid::ObjectNodeType ont1;
    std::pair<std::string, mguid::TreeNode> p1{"key", {}};
    auto result = ont1.Insert(p1);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Convertible Type Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    std::pair<std::string, mguid::TreeNode> p1{"key", {}};
    auto result = ont1.Insert(p1);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Initializer List") {
    mguid::ObjectNodeType ont1;
    ont1.Insert({{"key1", {}}, {"key2", {}}});
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 2);

    mguid::ObjectNodeType ont2;
    ont2.Insert({{"key1", {}}, {"key1", {}}});
    REQUIRE_FALSE(ont2.Empty());
    REQUIRE(ont2.Size() == 1);
  }
  SECTION("Insert Initializer List Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key1", {}}, {"key2", {}}};
    ont1.Insert({{"key1", {}}, {"key2", {}}});
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 2);

    mguid::ObjectNodeType ont2{{"key1", {}}, {"key2", {}}};
    ont2.Insert({{"key1", {}}, {"key3", {}}});
    REQUIRE_FALSE(ont2.Empty());
    REQUIRE(ont2.Size() == 3);
  }
}

TEST_CASE("Object Node Insert Hint") {
  SECTION("Insert Hint const &") {
    mguid::ObjectNodeType ont1;
    const std::pair<const std::string, mguid::TreeNode> p1{"key", {}};
    auto iter = ont1.InsertHint(ont1.Begin(), p1);
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Hint const & Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    const std::pair<const std::string, mguid::TreeNode> p1{"key", {}};
    auto iter = ont1.InsertHint(ont1.Begin(), p1);
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Hint &&") {
    mguid::ObjectNodeType ont1;
    std::pair<const std::string, mguid::TreeNode> p1{"key", {}};
    auto iter = ont1.InsertHint(ont1.Begin(), std::move(p1));
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert && Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    std::pair<const std::string, mguid::TreeNode> p1{"key", {}};
    auto iter = ont1.InsertHint(ont1.Begin(), std::move(p1));
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Convertible Type") {
    mguid::ObjectNodeType ont1;
    auto iter = ont1.InsertHint(ont1.Begin(), {"key", mguid::TreeNode{}});
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Convertible Type Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto iter = ont1.InsertHint(ont1.Begin(), {"key", mguid::TreeNode{}});
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
}

TEST_CASE("Object Node Insert Or Assign") {
  SECTION("Insert const &") {
    mguid::ObjectNodeType ont1;
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto result = ont1.InsertOrAssign("key", node);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == node);
  }
  SECTION("Insert const & Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto result = ont1.InsertOrAssign("key", node);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == node);
  }
  SECTION("Insert const & Key, && Value") {
    mguid::ObjectNodeType ont1;
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto expected = mguid::TreeNode{mguid::ValueNodeType{1}};
    const std::string key{"key"};
    auto result = ont1.InsertOrAssign(key, std::move(node));
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == expected);
  }
  SECTION("Insert const & Key, && Value Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto expected = mguid::TreeNode{mguid::ValueNodeType{1}};
    const std::string key{"key"};
    auto result = ont1.InsertOrAssign(key, std::move(node));
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == expected);
  }
}

TEST_CASE("Object Node Insert Or Assign Hint") {
  SECTION("Insert const &") {
    mguid::ObjectNodeType ont1;
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto iter = ont1.InsertOrAssignHint(ont1.Begin(), "key", node);
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == node);
  }
  SECTION("Insert const & Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto iter = ont1.InsertOrAssignHint(ont1.Begin(), "key", node);
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == node);
  }
  SECTION("Insert const & Key, && Value") {
    mguid::ObjectNodeType ont1;
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto expected = mguid::TreeNode{mguid::ValueNodeType{1}};
    const std::string key{"key"};
    auto iter = ont1.InsertOrAssignHint(ont1.Begin(), key, std::move(node));
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == expected);
  }
  SECTION("Insert const & Key, && Value Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto expected = mguid::TreeNode{mguid::ValueNodeType{1}};
    const std::string key{"key"};
    auto iter = ont1.InsertOrAssignHint(ont1.Begin(), key, std::move(node));
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == expected);
  }
}

TEST_CASE("Object Node Type Emplace") {
  SECTION("Emplace") {
    mguid::ObjectNodeType ont1;
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto result = ont1.Emplace("key", node);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == node);
  }
  SECTION("Emplace Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto result = ont1.Emplace("key", node);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value().HasObject());
  }
}

TEST_CASE("Object Node Type Emplace Hint") {
  SECTION("Emplace") {
    mguid::ObjectNodeType ont1;
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto iter = ont1.EmplaceHint(ont1.Begin(), "key", node);
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == node);
  }
  SECTION("Emplace Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto iter = ont1.EmplaceHint(ont1.Begin(), "key", node);
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value().HasObject());
  }
}

TEST_CASE("Object Node Type Try Emplace") {
  SECTION("Try Emplace const & Key") {
    mguid::ObjectNodeType ont1;
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    const std::string key{"key"};
    auto result = ont1.TryEmplace(key, node);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == node);
  }
  SECTION("Try Emplace Key Already Exists const & Key") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    const std::string key{"key"};
    auto result = ont1.TryEmplace(key, node);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value().HasObject());
  }
  SECTION("Try Emplace && Key") {
    mguid::ObjectNodeType ont1;
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto expected = mguid::TreeNode{mguid::ValueNodeType{1}};
    std::string key{"key"};
    auto result = ont1.TryEmplace(std::move(key), node);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == expected);
  }
  SECTION("Try Emplace Key Already Exists && Key") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    std::string key{"key"};
    auto result = ont1.TryEmplace(std::move(key), node);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value().HasObject());
  }
}

TEST_CASE("Object Node Type Try Emplace Hint") {
  SECTION("Try Emplace Hint const & Key") {
    mguid::ObjectNodeType ont1;
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    const std::string key{"key"};
    auto iter = ont1.TryEmplaceHint(ont1.Begin(), key, node);
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == node);
  }
  SECTION("Try Emplace Hint Key Already Exists const & Key") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    const std::string key{"key"};
    auto iter = ont1.TryEmplaceHint(ont1.Begin(), key, node);
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value().HasObject());
  }
  SECTION("Try Emplace Hint && Key") {
    mguid::ObjectNodeType ont1;
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    auto expected = mguid::TreeNode{mguid::ValueNodeType{1}};
    std::string key{"key"};
    auto iter = ont1.TryEmplaceHint(ont1.Begin(), std::move(key), node);
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value() == expected);
  }
  SECTION("Try Emplace Hint Key Already Exists && Key") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto node = mguid::TreeNode{mguid::ValueNodeType{1}};
    std::string key{"key"};
    auto iter = ont1.TryEmplaceHint(ont1.Begin(), std::move(key), node);
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.TryGet("key").value().HasObject());
  }
}

TEST_CASE("Object Node Type Erase") {
  SECTION("Erase Iterator") {
    {
      mguid::ObjectNodeType ont1{{"key", {}}};
      REQUIRE_FALSE(ont1.Empty());
      REQUIRE(ont1.Size() == 1);
      auto iter = ont1.Erase(ont1.Begin());
      REQUIRE(ont1.Empty());
      REQUIRE(ont1.Size() == 0);
      REQUIRE(iter == ont1.End());
    }
    {
      mguid::ObjectNodeType ont1{{"key1", {}}, {"key2", {}}};
      REQUIRE_FALSE(ont1.Empty());
      REQUIRE(ont1.Size() == 2);
      auto iter1 = ont1.Find("key2");
      REQUIRE(iter1 != ont1.End());
      ont1.Erase(iter1);
      REQUIRE_FALSE(ont1.Empty());
      REQUIRE(ont1.Size() == 1);
    }
  }
  SECTION("Erase Const Iterator") {
    {
      mguid::ObjectNodeType ont1{{"key", {}}};
      REQUIRE_FALSE(ont1.Empty());
      REQUIRE(ont1.Size() == 1);
      auto iter = ont1.Erase(ont1.CBegin());
      REQUIRE(ont1.Empty());
      REQUIRE(ont1.Size() == 0);
      REQUIRE(iter == ont1.End());
    }
    {
      mguid::ObjectNodeType ont1{{"key1", {}}, {"key2", {}}};
      REQUIRE_FALSE(ont1.Empty());
      REQUIRE(ont1.Size() == 2);
      const auto iter1 = ont1.Find("key2");
      REQUIRE(iter1 != ont1.End());
      ont1.Erase(iter1);
      REQUIRE_FALSE(ont1.Empty());
      REQUIRE(ont1.Size() == 1);
    }
  }
  SECTION("Erase Key") {
    {
      mguid::ObjectNodeType ont1{{"key", {}}};
      REQUIRE_FALSE(ont1.Empty());
      REQUIRE(ont1.Size() == 1);
      auto num_erased = ont1.Erase("key");
      REQUIRE(ont1.Empty());
      REQUIRE(ont1.Size() == 0);
      REQUIRE(num_erased == 1);
    }
    {
      mguid::ObjectNodeType ont1{{"key1", {}}, {"key2", {}}};
      REQUIRE_FALSE(ont1.Empty());
      REQUIRE(ont1.Size() == 2);
      auto num_erased = ont1.Erase("key2");
      REQUIRE_FALSE(ont1.Empty());
      REQUIRE(num_erased == 1);
    }
    {
      mguid::ObjectNodeType ont1{{"key1", {}}, {"key2", {}}};
      REQUIRE_FALSE(ont1.Empty());
      REQUIRE(ont1.Size() == 2);
      auto num_erased = ont1.Erase("key3");
      REQUIRE_FALSE(ont1.Empty());
      REQUIRE(ont1.Size() == 2);
      REQUIRE(num_erased == 0);
    }
  }
}

TEST_CASE("Object Node Type Contains") {
  mguid::ObjectNodeType ont1{{"key", {}}};
  REQUIRE(ont1.Contains("key"));
  REQUIRE_FALSE(ont1.Contains("non-existent"));
}

TEST_CASE("Object Node Type Empty") {
  mguid::ObjectNodeType ont1{};
  REQUIRE(ont1.Empty());
  mguid::ObjectNodeType ont2{{"key", {}}};
  REQUIRE_FALSE(ont2.Empty());
  ont2.Clear();
  REQUIRE(ont2.Empty());
}

TEST_CASE("Object Node Type Find") {
  SECTION("Find Element Exists Single Element In Map") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto iter = ont1.Find("key");
    REQUIRE(iter != ont1.End());
  }
  SECTION("Find Element Does Not Exist Single Element In Map") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto iter = ont1.Find("non-existent");
    REQUIRE(iter == ont1.End());
  }
  SECTION("Find Element Exists Many Element In Map") {
    mguid::ObjectNodeType ont1;
    for (auto i{0}; i < 1024; ++i) { ont1.Emplace(std::to_string(i), mguid::TreeNode{}); }
    auto iter = ont1.Find("512");
    REQUIRE(iter != ont1.End());
  }
  SECTION("Find Element Does Not Exist Many Element In Map") {
    mguid::ObjectNodeType ont1;
    for (auto i{0}; i < 1024; ++i) { ont1.Emplace(std::to_string(i), mguid::TreeNode{}); }
    auto iter = ont1.Find("1025");
    REQUIRE(iter == ont1.End());
  }
  SECTION("Find Empty Map") {
    mguid::ObjectNodeType ont1;
    auto iter = ont1.Find("non-existent");
    REQUIRE(iter == ont1.End());
  }
  SECTION("Find Element Exists Single Element In Map Const") {
    const mguid::ObjectNodeType ont1{{"key", {}}};
    auto iter = ont1.Find("key");
    REQUIRE(iter != ont1.End());
  }
  SECTION("Find Element Does Not Exist Single Element In Map Const") {
    const mguid::ObjectNodeType ont1{{"key", {}}};
    auto iter = ont1.Find("non-existent");
    REQUIRE(iter == ont1.End());
  }
  SECTION("Find Element Exists Many Element In Map Const") {
    mguid::ObjectNodeType ont_init;
    for (auto i{0}; i < 1024; ++i) { ont_init.Emplace(std::to_string(i), mguid::TreeNode{}); }
    const mguid::ObjectNodeType ont1{ont_init};
    auto iter = ont1.Find("512");
    REQUIRE(iter != ont1.End());
  }
  SECTION("Find Element Does Not Exist Many Element In Map Const") {
    mguid::ObjectNodeType ont_init;
    for (auto i{0}; i < 1024; ++i) { ont_init.Emplace(std::to_string(i), mguid::TreeNode{}); }
    const mguid::ObjectNodeType ont1{ont_init};
    auto iter = ont1.Find("1025");
    REQUIRE(iter == ont1.End());
  }
  SECTION("Find Empty Map Const") {
    const mguid::ObjectNodeType ont1;
    auto iter = ont1.Find("non-existent");
    REQUIRE(iter == ont1.End());
  }
}

TEST_CASE("Object Node Type Iterators") {
  SECTION("Begin/End") {
    mguid::ObjectNodeType ont1;
    auto iter1 = ont1.Begin();
    auto iter2 = ont1.begin();
    REQUIRE(iter1 == iter2);
    auto iter3 = ont1.End();
    auto iter4 = ont1.end();
    REQUIRE(iter3 == iter4);
  }
  SECTION("Const Begin/End") {
    const mguid::ObjectNodeType ont1;
    auto iter1 = ont1.Begin();
    auto iter2 = ont1.begin();
    REQUIRE(iter1 == iter2);
    auto iter3 = ont1.End();
    auto iter4 = ont1.end();
    REQUIRE(iter3 == iter4);
  }
  SECTION("CBegin/CEnd") {
    const mguid::ObjectNodeType ont1;
    auto iter1 = ont1.CBegin();
    auto iter2 = ont1.cbegin();
    REQUIRE(iter1 == iter2);
    auto iter3 = ont1.CEnd();
    auto iter4 = ont1.cend();
    REQUIRE(iter3 == iter4);
  }
}

TEST_CASE("Object Node Type Equality Comparison") {
  SECTION("Compare Both Empty") {
    const mguid::ObjectNodeType ont1;
    const mguid::ObjectNodeType ont2;
    REQUIRE(ont1 == ont2);
  }
  SECTION("Compare One Empty") {
    const mguid::ObjectNodeType ont1{{"key", {}}};
    const mguid::ObjectNodeType ont2;
    REQUIRE(ont1 != ont2);
  }
  SECTION("Compare Equal Not Empty") {
    const mguid::ObjectNodeType ont1{{"key", {}}};
    const mguid::ObjectNodeType ont2{{"key", {}}};
    REQUIRE(ont1 == ont2);
  }
  SECTION("Compare Not Equal Not Empty") {
    const mguid::ObjectNodeType ont1{{"key1", {}}};
    const mguid::ObjectNodeType ont2{{"key2", {}}};
    REQUIRE(ont1 != ont2);
  }
  SECTION("Compare Equal Many Elements") {
    mguid::ObjectNodeType ont1;
    mguid::ObjectNodeType ont2;
    for (auto i{0}; i < 1024; ++i) {
      ont1.Emplace(std::to_string(i), mguid::TreeNode{});
      ont2.Emplace(std::to_string(i), mguid::TreeNode{});
    }
    REQUIRE(ont1 == ont2);
  }
  SECTION("Compare Not Equal Many Elements") {
    mguid::ObjectNodeType ont1;
    mguid::ObjectNodeType ont2;
    for (auto i{0}; i < 1024; ++i) { ont1.Emplace(std::to_string(i), mguid::TreeNode{}); }
    for (auto i{1024}; i < 2048; ++i) { ont2.Emplace(std::to_string(i), mguid::TreeNode{}); }
    REQUIRE(ont1 != ont2);
  }
}
