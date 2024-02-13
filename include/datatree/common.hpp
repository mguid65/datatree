/**
 * @brief Common utilities
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_COMMON_HPP
#define DATATREE_COMMON_HPP

#include <ranges>

#include <nonstd/expected.hpp>
#include <uuid.h>

namespace mguid {

/**
 * @brief Doing this to get stduuid things
 */
using uuids::to_string;
using uuids::uuid;

/**
 * @brief Doing this to get expected-lite things
 */
using nonstd::expected;
using nonstd::make_unexpected;

// Uses compiler specific extensions if possible.
#ifdef __GNUC__  // GCC, Clang, ICC

inline void Unreachable() { __builtin_unreachable(); }

#elif defined(_MSC_VER)  // MSVC

inline void Unreachable() { __assume(false); }

#else
// Even if no extension is used, undefined behavior is still raised by
// the empty function body and the noreturn attribute.

[[noreturn]] inline void Unreachable() {}

#endif

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
