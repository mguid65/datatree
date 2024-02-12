/**
 * @brief Defines an error type to use with expected in interfaces
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-06
 */

#ifndef DATATREE_ERROR_TYPE_HPP
#define DATATREE_ERROR_TYPE_HPP

#include <string>

namespace mguid {
/**
 * @brief Simple aggregate error class
 */
struct Error {
  enum class Category { BadAccess, KeyError, Generic } category{Category::Generic};

  /**
   * @brief Get category as a string
   *
   * In case of an out of bounds status, "Unknown" will be returned.
   *
   * @param cat category value
   * @return category as a string
   */
  [[nodiscard]] static std::string_view CategoryToString(
      Category cat) noexcept {
    switch (cat) {
      case Category::BadAccess:
        return "Status::BadAccess";
      case Category::Generic:
        return "Status::Generic";
      case Category::KeyError:
        return "Status::KeyError";
      default:
        return "Unknown";
    }
  }
};
}  // namespace mguid

#endif  // DATATREE_ERROR_TYPE_HPP
