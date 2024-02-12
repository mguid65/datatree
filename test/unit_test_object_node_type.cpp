/**
 * @brief Tests for object node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include <datatree/node_types/object_node_type.hpp>

using TestMapType = std::unordered_map<std::string, mguid::uuid>;

TEST_CASE("Object Node Constructor") {
  SECTION("Default Constructor") {
    REQUIRE(std::is_default_constructible_v<mguid::ObjectNodeType>);
    mguid::ObjectNodeType ont1;
    REQUIRE(ont1.Empty());
    REQUIRE(ont1.Size() == 0);
  }
  SECTION("Copy Constructor") {
    REQUIRE(std::is_copy_constructible_v<mguid::ObjectNodeType>);
    mguid::ObjectNodeType ont1{{"key", mguid::uuid{}}};
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    mguid::ObjectNodeType ont2{ont1};
    REQUIRE_FALSE(ont2.Empty());
    REQUIRE(ont2.Size() == 1);
  }
  SECTION("Move Constructor") {
    REQUIRE(std::is_nothrow_move_constructible_v<mguid::ObjectNodeType>);
    mguid::ObjectNodeType ont1{{"key", mguid::uuid{}}};
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    mguid::ObjectNodeType ont2{std::move(ont1)};
    REQUIRE_FALSE(ont2.Empty());
    REQUIRE(ont2.Size() == 1);
  }
  SECTION("Copy Assignment") {
    REQUIRE(std::is_copy_assignable_v<mguid::ObjectNodeType>);
    mguid::ObjectNodeType ont1{{"key", mguid::uuid{}}};
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
    mguid::ObjectNodeType ont1{{"key", mguid::uuid{}}};
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
    TestMapType init_map{{"key", mguid::uuid{}}};
    mguid::ObjectNodeType ont1{init_map};
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Construction From Initializer List") {
    REQUIRE(std::is_constructible_v<mguid::ObjectNodeType, TestMapType>);
    mguid::ObjectNodeType ont1{{"key", mguid::uuid{}}};
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
}

TEST_CASE("Object Node Type Get") {
  SECTION("Key Exists") {
    mguid::ObjectNodeType ont1{{"key", mguid::uuid{}}};
    REQUIRE(ont1.Get("key").has_value());
  }
  SECTION("Key Doesn't Exist") {
    mguid::ObjectNodeType ont1;
    auto result = ont1.Get("key");
    REQUIRE(result.has_exception<mguid::Error>());
    REQUIRE(result.error().category == mguid::Error::Category::KeyError);
  }
}

TEST_CASE("Object Node Type Get Or") {
  SECTION("Key Exists") {
    mguid::ObjectNodeType ont1{{"key", mguid::uuid{}}};
    REQUIRE(ont1.GetOr("key", mguid::uuid{}).has_value());
  }
  SECTION("Key Doesn't Exist") {
    mguid::ObjectNodeType ont1;
    REQUIRE(ont1.GetOr("key", mguid::uuid{}).has_value());
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
    for (auto i{0}; i < 1024; ++i) {
      ont1.Emplace(std::to_string(i), mguid::uuid{});
    }
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
    const std::pair<const std::string, mguid::uuid> p1{"key", {}};
    auto result = ont1.Insert(p1);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert const & Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    const std::pair<const std::string, mguid::uuid> p1{"key", {}};
    auto result = ont1.Insert(p1);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert &&") {
    mguid::ObjectNodeType ont1;
    std::pair<const std::string, mguid::uuid> p1{"key", {}};
    auto result = ont1.Insert(std::move(p1));
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert && Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    std::pair<const std::string, mguid::uuid> p1{"key", {}};
    auto result = ont1.Insert(std::move(p1));
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Convertible Type") {
    mguid::ObjectNodeType ont1;
    std::pair<std::string, mguid::uuid> p1{"key", {}};
    auto result = ont1.Insert(p1);
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Convertible Type Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    std::pair<std::string, mguid::uuid> p1{"key", {}};
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
    const std::pair<const std::string, mguid::uuid> p1{"key", {}};
    auto iter = ont1.InsertHint(ont1.Begin(), p1);
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Hint const & Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    const std::pair<const std::string, mguid::uuid> p1{"key", {}};
    auto iter = ont1.InsertHint(ont1.Begin(), p1);
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Hint &&") {
    mguid::ObjectNodeType ont1;
    std::pair<const std::string, mguid::uuid> p1{"key", {}};
    auto iter = ont1.InsertHint(ont1.Begin(), std::move(p1));
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert && Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    std::pair<const std::string, mguid::uuid> p1{"key", {}};
    auto iter = ont1.InsertHint(ont1.Begin(), std::move(p1));
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Convertible Type") {
    mguid::ObjectNodeType ont1;
    auto iter = ont1.InsertHint(ont1.Begin(), {"key", mguid::uuid{}});
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
  SECTION("Insert Convertible Type Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto iter = ont1.InsertHint(ont1.Begin(), {"key", mguid::uuid{}});
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
  }
}

TEST_CASE("Object Node Insert Or Assign") {
  SECTION("Insert const &") {
    mguid::ObjectNodeType ont1;
    auto id = mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    auto result = ont1.InsertOrAssign("key", id.value());
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.Get("key").value() == id);
  }
  SECTION("Insert const & Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto id = mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    auto result = ont1.InsertOrAssign("key", id.value());
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.Get("key").value() == id);
  }
  SECTION("Insert const & Key, && Value") {
    mguid::ObjectNodeType ont1;
    auto id = mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    const std::string key{"key"};
    auto result = ont1.InsertOrAssign(key, std::move(id.value()));
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.Get("key").value() == id);
  }
  SECTION("Insert const & Key, && Value Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto id = mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    const std::string key{"key"};
    auto result = ont1.InsertOrAssign(key, std::move(id.value()));
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.Get("key").value() == id);
  }
}

TEST_CASE("Object Node Insert Or Assign Hint") {
  SECTION("Insert const &") {
    mguid::ObjectNodeType ont1;
    auto id = mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    auto iter = ont1.InsertOrAssignHint(ont1.Begin(), "key", id.value());
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.Get("key").value() == id);
  }
  SECTION("Insert const & Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto id = mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    auto iter = ont1.InsertOrAssignHint(ont1.Begin(), "key", id.value());
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.Get("key").value() == id);
  }
  SECTION("Insert const & Key, && Value") {
    mguid::ObjectNodeType ont1;
    auto id = mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    const std::string key{"key"};
    auto iter =
        ont1.InsertOrAssignHint(ont1.Begin(), key, std::move(id.value()));
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.Get("key").value() == id);
  }
  SECTION("Insert const & Key, && Value Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto id = mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    const std::string key{"key"};
    auto iter =
        ont1.InsertOrAssignHint(ont1.Begin(), key, std::move(id.value()));
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.Get("key").value() == id);
  }
}

TEST_CASE("Object Node Type Emplace") {
  SECTION("Emplace") {
    mguid::ObjectNodeType ont1;
    auto id = mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    auto result = ont1.Emplace("key", id.value());
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.Get("key").value() == id);
  }
  SECTION("Emplace Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto id = mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    auto result = ont1.Emplace("key", id.value());
    const auto& [iter, inserted] = result;
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(inserted);
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.Get("key").value().is_nil());
  }
}

TEST_CASE("Object Node Type Emplace Hint") {
  SECTION("Emplace") {
    mguid::ObjectNodeType ont1;
    auto id = mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    auto iter = ont1.EmplaceHint(ont1.Begin(), "key", id.value());
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.Get("key").value() == id);
  }
  SECTION("Emplace Key Already Exists") {
    mguid::ObjectNodeType ont1{{"key", {}}};
    auto id = mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    auto iter = ont1.EmplaceHint(ont1.Begin(), "key", id.value());
    REQUIRE(iter != ont1.End());
    REQUIRE_FALSE(ont1.Empty());
    REQUIRE(ont1.Size() == 1);
    REQUIRE(ont1.Get("key").value().is_nil());
  }
}