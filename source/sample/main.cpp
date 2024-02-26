/**
 * @brief Main for sample executable
 * @author Matthew Guidry(github: mguid65)
 * @date 2024-02-21
 */

#include <chrono>
#include <iostream>

#include "datatree/data_tree.hpp"

#include <nlohmann/json.hpp>

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
  //
  //  time_it("With Reserve",
  //      []() {
  //        mguid::DataTree dt;
  //
  //        dt.SetArray(mguid::Path{"first", "second", "third"});
  //
  //        dt.Reserve(2048);
  //
  //        for (std::size_t i{0}; i < 2048; ++i) {
  //          dt.SetValue(mguid::Path{"first", "second", "third", i},
  //                      mguid::ValueNodeType{i});
  //        }
  //      },
  //      48);

  // const auto iterations = 8192;
  const auto iterations = 4194303;
  const auto samples = 12;

  time_it(
      "Data Tree",
      []() {
        mguid::DataTree dt;

        dt["first"]["second"]["third"] = mguid::ArrayNodeType{};
        auto& third = dt["first"]["second"]["third"];
        for (std::size_t i{0}; i < iterations; ++i) {
          third[i] = i;
        }
      },
      samples);

  time_it(
      "Nlohmann JSON",
      []() {
        nlohmann::json j;

        j["first"]["second"]["third"] = nlohmann::json::array();
        auto& third = j["first"]["second"]["third"];
        for (std::size_t i{0}; i < iterations; ++i) {
          third[i] = i;
        }
      },
      samples);

  //  dt.Print<true>();
}