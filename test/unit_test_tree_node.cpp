/**
 * @brief Tests for treenode
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include <datatree/tree_node.hpp>

TEST_CASE("Tree Node Construction/Assignment") {
  SECTION("Default Constructor") {
    REQUIRE(std::is_default_constructible_v<mguid::TreeNode>);
  }
  SECTION("Copy Constructor") {
    REQUIRE(std::is_copy_constructible_v<mguid::TreeNode>);
  }
  SECTION("Move Constructor") {
    REQUIRE(std::is_move_constructible_v<mguid::TreeNode>);
  }
  SECTION("Copy Assignment") {
    REQUIRE(std::is_copy_assignable_v<mguid::TreeNode>);
  }
  SECTION("Move Assignment") {
    REQUIRE(std::is_move_assignable_v<mguid::TreeNode>);
  }
  SECTION("From Object") {
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::ObjectNodeType>);
  }
  SECTION("From Array") {
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::ArrayNodeType>);
  }
  SECTION("From Value") {
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::ValueNodeType>);
  }
  SECTION("From Tag") {
    REQUIRE(std::is_constructible_v<mguid::TreeNode, mguid::NodeTypeTag>);
    [[maybe_unused]] mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    [[maybe_unused]] mguid::TreeNode tn2{mguid::NodeTypeTag::Array};
    [[maybe_unused]] mguid::TreeNode tn3{mguid::NodeTypeTag::Value};
    SUCCEED("Constructed From Tag");
  }
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

TEST_CASE("Tree Node Get Type") {
  SECTION("Get Object") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    REQUIRE(tn1.GetObject().has_value());
  }
  SECTION("Get Array") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    REQUIRE(tn1.GetArray().has_value());
  }
  SECTION("Get Value") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
    REQUIRE(tn1.GetValue().has_value());
  }
  SECTION("Get Object Bad Access") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
    mguid::TreeNode tn2{mguid::NodeTypeTag::Value};
    REQUIRE(tn1.GetObject().has_exception<mguid::Error>());
    REQUIRE(tn2.GetObject().has_exception<mguid::Error>());
  }
  SECTION("Get Array Bad Access") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    mguid::TreeNode tn2{mguid::NodeTypeTag::Value};
    REQUIRE(tn1.GetArray().has_exception<mguid::Error>());
    REQUIRE(tn2.GetArray().has_exception<mguid::Error>());
  }
  SECTION("Get Value Bad Access") {
    mguid::TreeNode tn1{mguid::NodeTypeTag::Object};
    mguid::TreeNode tn2{mguid::NodeTypeTag::Array};
    REQUIRE(tn1.GetValue().has_exception<mguid::Error>());
    REQUIRE(tn2.GetValue().has_exception<mguid::Error>());
  }
}

TEST_CASE("Tree Node Set") {
  SECTION("Set Object") {
    mguid::TreeNode tn1;
    tn1.Set(mguid::ObjectNodeType{});
    REQUIRE(tn1.GetObject().has_value());
  }
  SECTION("Set Array") {
    mguid::TreeNode tn1;
    tn1.Set(mguid::ArrayNodeType{});
    REQUIRE(tn1.GetArray().has_value());
  }
  SECTION("Set Value") {
    mguid::TreeNode tn1;
    tn1.Set(mguid::ValueNodeType{});
    REQUIRE(tn1.GetValue().has_value());
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
  }
  SECTION("Visit Array") {
    SECTION("Three Overloads Return") {
      mguid::TreeNode tn1{mguid::NodeTypeTag::Array};
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
  }
  SECTION("Visit Value") {
    SECTION("Three Overloads Return") {
      mguid::TreeNode tn1{mguid::NodeTypeTag::Value};
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
  }
}