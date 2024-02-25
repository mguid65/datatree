/**
 * @brief Main for sample executable
 * @author Matthew Guidry(github: mguid65)
 * @date 2024-02-21
 */

#include <chrono>
#include <ctime>
#include <iostream>
#include <ratio>

#include "datatree/data_tree.hpp"

auto main() -> int {
  mguid::DataTree dt;


  std::chrono::high_resolution_clock::time_point t1 =
      std::chrono::high_resolution_clock::now();

  dt.SetArray(mguid::Path{"first", "second", "third"});

  for (std::size_t i{0}; i < 65535; ++i) {
    dt.SetValue(mguid::Path{"first", "second", "third", i},
                mguid::ValueNodeType{i});
  }

  std::chrono::high_resolution_clock::time_point t2 =
      std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

  std::cout << "Time: " << time_span.count() << std::endl;

  dt.Print<true>();
}