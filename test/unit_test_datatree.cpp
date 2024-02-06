/**
 * @brief Tests for datatree
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include <datatree/datatree.hpp>

TEST_CASE("Datatree Constructor") {
  SECTION("Default Constructor") { mguid::DataTree dt; }
}