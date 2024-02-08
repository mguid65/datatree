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
  enum class Status { BadAccess, Generic } category{Status::Generic};

  /**
   * @brief Get status as a string
   *
   * In case of an out of bounds status, "Unknown" will be returned.
   *
   * @param status status code
   * @return status as a string
   */
  [[nodiscard]] static std::string_view StatusToString(Status status) noexcept {
    switch (status) {
      case Status::BadAccess:
        return "Status::BadAccess";
      case Status::Generic:
        return "Status::Generic";
      default:
        return "Unknown";
    }
  }
};
}  // namespace mguid

#endif  // DATATREE_ERROR_TYPE_HPP
