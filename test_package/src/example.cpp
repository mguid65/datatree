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
}