/**
 * @brief Main for sample executable
 * @author Matthew Guidry(github: mguid65)
 * @date 2024-02-21
 */

#include "datatree/data_tree.hpp"

auto main() -> int {
  mguid::DataTree dt;
  dt.SetArray(mguid::Path{"first", "second", "third"});

  for(std::size_t i{0}; i < 65535; ++i) {
    dt.SetValue(mguid::Path{"first", "second", "third", i}, mguid::ValueNodeType{i});
  }

  dt.Print<true>();
}