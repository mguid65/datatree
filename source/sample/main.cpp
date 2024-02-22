/**
 * @brief Main for sample executable
 * @author Matthew Guidry(github: mguid65)
 * @date 2024-02-21
 */

#include "datatree/data_tree.hpp"

auto main() -> int {
  using namespace mguid::key_literals;
  [[maybe_unused]] mguid::DataTree dt;
  dt.Set(mguid::Path{"first", "second", "third", 1}, mguid::ValueNodeType{4});
  dt.Print<true>();
//  dt.Set({"first"_k, "second"_k, "third"_k, 0_k}, mguid::ValueNodeType{8});
//  dt.Print();
//  dt.Set(mguid::Path{"first", "second", "third_alt", 10}, mguid::ValueNodeType{8});
//  dt.Print();
}