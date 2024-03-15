/**
 * @brief Main for sample executable
 * @author Matthew Guidry(github: mguid65)
 * @date 2024-02-21
 */

#include <iostream>

#include "data_tree/data_tree.hpp"

auto main() -> int {
  mguid::DataTree dt1;

  // Node types
  dt1["first"]["second"]["array"] = mguid::ArrayNodeType{};
  dt1["first"]["second"]["object"] = mguid::ObjectNodeType{};
  dt1["first"]["second"]["value"] = mguid::ValueNodeType{};

  // Value types
  dt1["first"]["second"]["number_value_signed"] = 1;
  dt1["first"]["second"]["number_value_unsigned"] = 1u;
  dt1["first"]["second"]["number_value_double"] = 1.0;
  dt1["first"]["second"]["bool_value_true"] = true;
  dt1["first"]["second"]["bool_value_false"] = false;
  dt1["first"]["second"]["null_value"] = mguid::Null;
  dt1["first"]["second"]["string_literal_value"] = "Hello, World!";
  dt1["first"]["second"]["string_value"] = std::string("42");

  dt1.ConstUnsafe([](const auto&& unsafe) {
    std::cout << "DT1 Num Direct Children: " << unsafe.GetObject().Size()
              << std::endl;
    std::cout << R"(DT1["first"]["second"] Num Direct Children: )"
              << unsafe["first"]["second"].GetObject().Size() << std::endl;
  });

  // Set path to another tree
  mguid::DataTree dt2;
  dt2["some_key"] = dt1;

  dt2.ConstUnsafe([](const auto&& unsafe) {
    std::cout << "DT2 Num Direct Children: " << unsafe.GetObject().Size()
              << std::endl;
  });

  dt2.Erase("some_key");

  dt2.ConstUnsafe([](const auto&& unsafe) {
    std::cout << "DT2 Num Direct Children After Erase: "
              << unsafe.GetObject().Size() << std::endl;
  });
}