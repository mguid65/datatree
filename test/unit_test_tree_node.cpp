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
}

TEST_CASE("Tree Node Has Type") {
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
}