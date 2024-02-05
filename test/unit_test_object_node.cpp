/**
 * @brief Tests for object node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include <datatree/node_types/object_node.hpp>

TEST_CASE("Object Node Constructor") {
  SECTION("Default Constructor") { mguid::object_node on; }
}