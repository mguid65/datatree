/**
 * @brief Common utilities
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_COMMON_HPP
#define DATATREE_COMMON_HPP

#include <mutex>
#include <ranges>

#include <nonstd/expected.hpp>
#include <uuid.h>

namespace mguid {

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
 * @brief Doing this to get stduuid things
 */
using uuids::to_string;
using uuids::uuid;

/**
 * @brief TryGet a random uuid
 * @return a random uuid
 */
[[nodiscard]] inline uuid RandomUUID() {
  using uuids::uuid_random_generator;
  static std::mutex uuid_mutex;
  static auto gen = std::invoke([]() -> uuid_random_generator {
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size>{};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    // Not sure if this needs to stay alive as long as the generator, the
    // generator takes it by reference
    static std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    static std::mt19937 generator(seq);
    return uuid_random_generator{generator};
  });
  std::lock_guard lock(uuid_mutex);
  return gen();
}

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
