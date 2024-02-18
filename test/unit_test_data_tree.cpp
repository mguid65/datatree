/**
 * @brief Tests for datatree
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include "datatree/data_tree.hpp"

TEST_CASE("Datatree Constructor") {
  SECTION("Default Constructor") { [[maybe_unused]] mguid::DataTree dt; }
}