/**
 * @brief Tests for datatree
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include "data_tree/data_tree.hpp"

TEST_CASE("DataTree Is TreeNode") {
  STATIC_REQUIRE(std::is_same_v<mguid::DataTree, mguid::TreeNode>);
}