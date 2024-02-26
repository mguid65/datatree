/**
 * Copyright (c) 2024 Matthew Guidry
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 *
 * @brief Common utilities
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_COMMON_HPP
#define DATATREE_COMMON_HPP

#include <mutex>
#include <ranges>
#include <string>
#include <cstdint>

#include <nonstd/expected.hpp>

namespace mguid {

/**
 * @brief
 * @param json
 * @param tab_width
 * @return
 */
[[nodiscard]] inline std::string PrettifyJson(const std::string& json,
                                              std::size_t tab_width = 2) {
  std::size_t indent{0};
  std::string result;

  auto append_indent = [&]() { result.append(indent * tab_width, ' '); };

  for (const auto& ch : json) {
    switch (ch) {
      case '{':
        [[fallthrough]];
      case '[': {
        indent += 1;
        result += ch;
        result += '\n';
        append_indent();
        break;
      }
      case '}':
        [[fallthrough]];
      case ']': {
        indent -= 1;
        result += '\n';
        append_indent();
        result += ch;
        break;
      }
      case ',': {
        result += ch;
        result += '\n';
        append_indent();
        break;
      }
      default:
        result += ch;
    }
  }

  return result;
}

/**
 * @brief A type to hold a set of callable overloads
 * @tparam TNonFinalCallables a set of non-final callables
 */
template <typename... TNonFinalCallables>
struct Overload : TNonFinalCallables... {
  using TNonFinalCallables::operator()...;
};

/**
 * @brief Deduction guide for Overload
 */
template <class... TNonFinalCallables>
Overload(TNonFinalCallables...) -> Overload<TNonFinalCallables...>;

/**
 * @brief Doing this to get expected-lite things
 */
using nonstd::expected;
using nonstd::make_unexpected;

/**
 * @brief Invokes undefined behavior. An implementation may use this to optimize
 * impossible code branches away (typically, in optimized builds) or to trap
 * them to prevent further execution (typically, in debug builds).
 *
 * From "Possible implementation" section for `std::unreachable` here:
 * https://en.cppreference.com/w/cpp/utility/unreachable
 */
[[noreturn]] inline void Unreachable() {
  // Uses compiler specific extensions if possible.
  // Even if no extension is used, undefined behavior is still raised by
  // an empty function body and the noreturn attribute.
#if defined(_MSC_VER) && !defined(__clang__)  // MSVC
  __assume(false);
#else  // GCC, Clang
  __builtin_unreachable();
#endif
}

/**
 * @brief Check if something is a range of TValueType
 * @tparam TRange some range
 * @tparam TValueType range value type
 */
template <typename TValueType, typename TRange>
concept RangeOf = std::ranges::range<TRange> &&
                  std::same_as<std::ranges::range_value_t<TRange>, TValueType>;

}  // namespace mguid

#endif  // DATATREE_COMMON_HPP
