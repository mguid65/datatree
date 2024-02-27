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

#include <cstdint>
#include <mutex>
#include <ranges>
#include <string>

#include <nonstd/expected.hpp>

namespace mguid {

/**
 * @brief Prettify a JSON string
 * @param json a JSON string
 * @param tab_width width of indentation in pretty printed output
 * @return pretty formatted json
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
 * @brief Extension for expected that hides the usage of a reference wrapper for
 * reference types
 * @tparam TExpectedType reference value type
 * @tparam TErrorType error type
 */
template <typename TExpectedType, typename TErrorType>
struct RefExpected
    : private nonstd::expected<std::reference_wrapper<TExpectedType>,
                               TErrorType> {
  using BaseType = expected<std::reference_wrapper<TExpectedType>, TErrorType>;
  using ValueType = TExpectedType;

  using BaseType::BaseType;
  using BaseType::operator=;
  using BaseType::operator bool;
  using BaseType::emplace;
  using BaseType::error;
  using BaseType::has_exception;
  using BaseType::has_value;
  using BaseType::swap;

  /**
   * @brief Construct a RefExpected from a TExpectedType reference
   * @param ref a TExpectedType reference
   */
  constexpr RefExpected(TExpectedType& ref) : BaseType(std::ref(ref)) {}

  /**
   * @brief Get const reference to value from this
   *
   * The normal expected::value overloads are private
   *
   * @return const reference to ValueType
   */
  [[nodiscard]] constexpr const ValueType& value() const& {
    return this->BaseType::value().get();
  }

  /**
   * @brief Get value from this
   *
   * The normal expected::value overloads are private
   *
   * @return reference to ValueType
   */
  [[nodiscard]] ValueType& value() & { return this->BaseType::value().get(); }

  /**
   * @brief Get const pointer to value from this
   *
   * The normal expected::operator-> overloads are private
   *
   * @return const pointer to ValueType
   */
  [[nodiscard]] constexpr const ValueType* operator->() const {
    return &(this->BaseType::value().get());
  }

  /**
   * @brief Get pointer to value from this
   *
   * The normal expected::operator-> overloads are private
   *
   * @return pointer to ValueType
   */
  [[nodiscard]] ValueType* operator->() {
    return &(this->BaseType::value().get());
  }

  /**
   * @brief Get const reference to value from this
   *
   * The normal expected::operator* overloads are private
   *
   * @return const reference to ValueType
   */
  [[nodiscard]] constexpr const ValueType& operator*() const& {
    return this->BaseType::value().get();
  }

  /**
   * @brief Get reference to value from this
   *
   * The normal expected::operator* overloads are private
   *
   * @return reference to ValueType
   */
  [[nodiscard]] ValueType& operator*() & {
    return this->BaseType::value().get();
  }
};

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
