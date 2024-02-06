/**
 * @brief A number holder abstraction
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_NUMBER_TYPE_HPP
#define DATATREE_NUMBER_TYPE_HPP

#include <cstdint>

namespace mguid {

/**
 * @brief
 */
class number_type {
  enum class tag { Float64, Int64, None } m_tag{tag::None};
  union {
    double m_f_value;
    std::int64_t m_i_value;
  };

public:
  /**
   * @brief Default construct a number with no value
   *
   * Sets the tag to None
   *
   */
  constexpr number_type() noexcept = default;
  /**
   * @brief Construct a number from a double
   *
   * Sets the tag to Float64
   *
   * @param val double value
   */
  constexpr number_type(double val) noexcept
      : m_f_value{val}, m_tag{tag::Float64} {}

  /**
   * @brief Construct a number from a 64-bit integer
   *
   * Sets the tag to Int64
   *
   * @param val integer value
   */
  constexpr number_type(std::int64_t val) noexcept
      : m_i_value{val}, m_tag{tag::Int64} {}

  /**
   * @brief Does this number have a value
   * @return True if it has a value, otherwise false
   */
  [[nodiscard]] constexpr bool hasValue() const noexcept {
    return m_tag != tag::None;
  }

  /**
   * @brief Is this number holding a double value
   * @return True if it is a double, otherwise false
   */
  [[nodiscard]] constexpr bool isDouble() const noexcept {
    return m_tag == tag::Float64;
  }

  /**
   * @brief Is this number holding an integer value
   * @return True if it is an integer, otherwise false
   */
  [[nodiscard]] constexpr bool isInteger() const noexcept {
    return m_tag == tag::Int64;
  }

  /**
   * @brief Try to get a double from this number type
   * @return the double value if it exists, otherwise nullptr
   */
  [[nodiscard]] const double* try_get_double() const {
    if (m_tag == tag::Float64) return &m_f_value;
    return nullptr;
  }

  /**
   * @brief Try to get an integer from this number type
   * @return the integer value if it exists, otherwise nullptr
   */
  [[nodiscard]] const std::int64_t* try_get_integer() const {
    if (m_tag == tag::Int64) return &m_i_value;
    return nullptr;
  }
};

}  // namespace mguid

#endif  // DATATREE_NUMBER_TYPE_HPP
