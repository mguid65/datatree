/**
 * @brief Main for sample executable
 * @author Matthew Guidry(github: mguid65)
 * @date 2024-02-04
 */

#include <iostream>

#include "datatree/data_tree.hpp"
#include <datatree/node_types/value_node_type.hpp>

auto main() -> int {
  mguid::ValueNodeType vnt("Hello");
  auto v = vnt.IfStringThen(
                  [](auto s) { return mguid::ValueNodeType{s + ", World!"}; })
               .IfNotString([]() { return mguid::ValueNodeType{"Foo Bar"}; });

  std::cout << v.GetString().value() << '\n';
}