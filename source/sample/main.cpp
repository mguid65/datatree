/**
 * @brief Main for sample executable
 * @author Matthew Guidry(github: mguid65)
 * @date 2024-02-04
 */

#include <iostream>

#include "datatree/data_tree.hpp"
#include <datatree/node_types/value_node_type.hpp>

auto main() -> int {
  using namespace mguid::key_literals;
  [[maybe_unused]] mguid::DataTree dt;
  dt.Set({"first"_k, "second"_k, "third"_k, 1_k}, mguid::ValueNodeType{4});
  dt.Set(mguid::Path{"first", "second", "third", 1}, mguid::ValueNodeType{4});
  auto result1 = dt.Get({"first"_k, "second"_k, "third"_k, 1_k});
  auto result2 = dt.Get(mguid::Path{"first", "second", "third", 1});
}