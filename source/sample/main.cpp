/**
 * @brief Main for sample executable
 * @author Matthew Guidry(github: mguid65)
 * @date 2024-02-21
 */

#include <chrono>
#include <iostream>

#include "datatree/data_tree.hpp"

auto main() -> int {
  static constexpr auto time_it = [](auto name, auto func,
                                     std::size_t samples = 1) {
    std::cout << "Timing " << name << std::endl << "Warmup Runs 1";
    std::chrono::nanoseconds time_span{0};
    // Allow for cache warmup
    for (std::size_t i{1}; i < 13; ++i) {
      std::cout << "..." << i + 1 << std::flush;
      (void)func();
    }

    std::cout << std::endl
              << "Timing With " << samples << " Samples..." << std::endl;
    for (std::size_t i{0}; i < samples; ++i) {
      auto t1 = std::chrono::steady_clock::now();
      func();
      auto t2 = std::chrono::steady_clock::now();

      auto duration =
          std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
      time_span += duration;
    }

    std::cout << "Avg Time: " << (time_span / samples).count() << "ns"
              << std::endl;
  };

  const auto iterations = 8192;
  // const auto iterations = 4194303;
  const auto samples = 12;

  time_it(
      "Data Tree",
      []() {
        mguid::DataTree dt;

        dt["first"]["second"]["third"] = mguid::ArrayNodeType{};
        auto& third = dt["first"]["second"]["third"];
        for (std::size_t i{0}; i < iterations; ++i) { third[i] = i; }
      },
      samples);

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

  std::cout << "DT1 Num Direct Children: " << dt1.GetObject().Size()
            << std::endl;
  std::cout << "DT1[\"first\"][\"second\"] Num Direct Children: "
            << dt1["first"]["second"].GetObject().Size() << std::endl;

  // Set path to another tree
  mguid::DataTree dt2;
  dt2["some_key"] = dt1;

  std::cout << "DT2 Num Direct Children: " << dt2.GetObject().Size()
            << std::endl;

  dt2.Erase("some_key");

  std::cout << "DT2 Num Direct Children After Erase: " << dt2.GetObject().Size()
            << std::endl;
}