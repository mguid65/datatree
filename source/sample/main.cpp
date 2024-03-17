/**
 * @brief Main for sample executable
 * @author Matthew Guidry(github: mguid65)
 * @date 2024-02-21
 */

#include <chrono>
#include <iostream>

#include "data_tree/data_tree.hpp"

auto main() -> int {
  static constexpr auto time_it = [](auto name, auto func, std::size_t samples = 1) {
    std::cout << "Timing " << name << std::endl << "Warmup Runs 1";
    std::chrono::nanoseconds time_span{0};
    // Allow for cache warmup
    for (std::size_t i{1}; i < 13; ++i) {
      std::cout << "..." << i + 1 << std::flush;
      func();
    }

    std::cout << std::endl << "Timing With " << samples << " Samples..." << std::endl;
    for (std::size_t i{0}; i < samples; ++i) {
      auto t1 = std::chrono::steady_clock::now();
      func();
      auto t2 = std::chrono::steady_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
      time_span += duration;
    }

    std::cout << "Avg Time: " << (time_span / samples).count() << "ns" << std::endl;
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
  dt1["first"]["second"]["number_value_double"] = 1.2345;
  dt1["first"]["second"]["bool_value_true"] = true;
  dt1["first"]["second"]["bool_value_false"] = false;
  dt1["first"]["second"]["null_value"] = mguid::Null;
  dt1["first"]["second"]["string_literal_value"] = "Hello, World!";
  dt1["first"]["second"]["string_value"] = std::string("42");
  dt1["first"]["second"]["array"][3] = 4;

  std::cout << std::boolalpha
            << dt1.ContainsType<mguid::NullType>(mguid::Path{"first", "second", "array", 2})
            << std::noboolalpha << std::endl;

  dt1.ConstUnsafe([](const auto&& unsafe) {
    std::cout << "DT1 Num Direct Children: " << unsafe.GetObject().Size() << std::endl;
    std::cout << R"(DT1["first"]["second"] Num Direct Children: )"
              << unsafe["first"]["second"].GetObject().Size() << std::endl;
  });

  // Set path to another tree
  mguid::DataTree dt2;
  dt2["some_key"] = dt1;

  dt2.ConstUnsafe([](const auto&& unsafe) {
    std::cout << "DT2 Num Direct Children: " << unsafe.GetObject().Size() << std::endl;
  });

  dt2.Erase("some_key");

  dt2.ConstUnsafe([](const auto&& unsafe) {
    std::cout << "DT2 Num Direct Children After Erase: " << unsafe.GetObject().Size() << std::endl;
  });

  dt1.Unsafe([](auto&& unsafe) {
    unsafe.RecursiveVisit(
        [](mguid::ObjectNodeType&) { std::cout << "Object:" << std::endl; },
        [](mguid::ArrayNodeType&) { std::cout << "Array:" << std::endl; },
        [](mguid::ValueNodeType& value_node) {
          std::cout << "Value: ";
          value_node.Visit(
              [](mguid::NumberType& value) {
                value.Visit([](auto number) { std::cout << "Number: " << number << std::endl; });
              },
              [](mguid::BoolType& value) {
                std::cout << "Bool: " << std::boolalpha << value << std::noboolalpha << std::endl;
              },
              [](mguid::StringType& value) { std::cout << "String: " << value << std::endl; },
              [](mguid::NullType& value) { std::cout << "Null: " << value << std::endl; });
        });
  });

  mguid::DataTree dt4;

  std::reference_wrapper<mguid::DataTree> ref{dt4};
  for (int i{0}; i < 64; ++i) { ref = ref.get()["key"]; }

  ref.get()["key"] = mguid::ValueNodeType{};

  dt4.Unsafe([](auto&& unsafe) {
    unsafe.RecursiveVisit(
        [](mguid::ObjectNodeType&) { std::cout << "Object:" << std::endl; },
        [](mguid::ArrayNodeType&) { std::cout << "Array:" << std::endl; },
        [](mguid::ValueNodeType& value_node) {
          std::cout << "Value: ";
          value_node.Visit(
              [](mguid::NumberType& value) {
                value.Visit([](auto number) { std::cout << "Number: " << number << std::endl; });
              },
              [](mguid::BoolType& value) {
                std::cout << "Bool: " << std::boolalpha << value << std::noboolalpha << std::endl;
              },
              [](mguid::StringType& value) { std::cout << "String: " << value << std::endl; },
              [](mguid::NullType& value) { std::cout << "Null: " << value << std::endl; });
        });
  });

  std::cout << mguid::DataTree{mguid::NumberType{5} % mguid::NumberType{3}} << std::endl;
  std::cout << mguid::DataTree{mguid::NumberType{5} % mguid::NumberType{3.5}} << std::endl;
  std::cout << mguid::DataTree{mguid::NumberType{5} % mguid::NumberType{3u}} << std::endl;
  std::cout << mguid::DataTree{mguid::NumberType{5.0} % mguid::NumberType{3.0}} << std::endl;

  std::cout << mguid::TrueValueTree << std::endl;
  std::cout << dt1 << std::endl;
}