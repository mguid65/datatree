/**
 * @brief Tests for treenode
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include <datatree/tree_node.hpp>

TEST_CASE("Tree Node Constructor") {
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
}