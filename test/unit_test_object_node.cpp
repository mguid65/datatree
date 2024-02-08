/**
 * @brief Tests for object node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include <datatree/node_types/object_node_type.hpp>

TEST_CASE("Object Node Constructor") {
  SECTION("Default Constructor") { [[maybe_unused]] mguid::ObjectNodeType on; }
}