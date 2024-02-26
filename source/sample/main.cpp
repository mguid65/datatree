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
    std::cout << "Timing " << name << std::endl;
    std::chrono::nanoseconds time_span{0};
    // Allow for cache warmup
    for (std::size_t i{0}; i < 12; ++i) {
      std::cout << "Warmup Run #" << i << std::endl;
      (void)func();
    }

    std::cout << "Timing With " << samples << " Samples..." << std::endl;
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

  time_it(
      "Data Tree",
      []() {
        mguid::DataTree dt;

        dt["first"]["second"]["third"] = mguid::ArrayNodeType{};

        for (std::size_t i{0}; i < 2048; ++i) {
          dt["first"]["second"]["third"][i] = i;
        }
      },
      48);

  time_it(
      "Nlohmann JSON",
      []() {
        nlohmann::json j;

        j["first"]["second"]["third"] = nlohmann::json::array();

        for (std::size_t i{0}; i < 2048; ++i) {
          j["first"]["second"]["third"][i] = i;
        }
      },
      48);

  //  dt.Print<true>();
}