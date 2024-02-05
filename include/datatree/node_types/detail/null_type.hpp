/**
 * @brief TODO
 * @author Matthew Guidry (github: mguid65)
 * @date 2/5/24
 */

#ifndef DATATREE_NULL_TYPE_HPP
#define DATATREE_NULL_TYPE_HPP

#include <compare>
#include <cstdint>
#include <functional>

namespace mguid {

/**
 * @brief Class that represents a well behaved null state similar
 * to std::monostate
 */
struct null_type {};

inline constexpr bool operator==(null_type, null_type) noexcept { return true; }

inline constexpr std::strong_ordering operator<=>(null_type,
                                                  null_type) noexcept {
  return std::strong_ordering::equal;
}

}  // namespace mguid

namespace std {
template <>
struct hash<mguid::null_type> {
  using argument_type = mguid::null_type;
  using result_type = std::size_t;

  inline result_type operator()(const argument_type&) const noexcept {
    return 66740831;
  }
};
}  // namespace std

#endif  // DATATREE_NULL_TYPE_HPP
