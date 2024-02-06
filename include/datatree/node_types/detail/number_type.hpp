/**
 * @brief A number holder abstraction
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_NUMBER_TYPE_HPP
#define DATATREE_NUMBER_TYPE_HPP

#include <concepts>
#include <cstdint>
#include <utility>

namespace mguid {

using IntegerType = std::int64_t;
using UnsignedIntegerType = std::uint64_t;
using FloatType = double;

template <typename TType>
concept AllowedNumericType =
    (!std::same_as<std::remove_cvref_t<TType>, bool> &&
     (std::integral<std::remove_cvref_t<TType>> ||
      std::floating_point<std::remove_cvref_t<TType>>));

template <typename TType>
concept SignedIntegerLike = (!std::same_as<std::remove_cvref_t<TType>, bool> &&
                             (std::integral<std::remove_cvref_t<TType>>)) &&
                            std::is_signed_v<std::remove_cvref_t<TType>>;

template <typename TType>
concept UnsignedIntegerLike =
    (!std::same_as<std::remove_cvref_t<TType>, bool> &&
     (std::integral<std::remove_cvref_t<TType>>)) &&
    std::is_unsigned_v<std::remove_cvref_t<TType>>;

/**
 * @brief A class that holds numeric values
 */
class NumberType {
  enum class tag { Float, UInt, Int, None } m_tag{tag::None};
  union {
    FloatType m_f_value;
    IntegerType m_i_value;
    UnsignedIntegerType m_u_value;
  };

public:
  /**
   * @brief Default construct a number with no value
   *
   * Sets the tag to None
   *
   */
  constexpr NumberType() noexcept = default;

  constexpr NumberType(std::nullptr_t) noexcept : m_tag{tag::None} {}

  /**
   * @brief
   * @tparam TValueType
   * @param val
   */
  template <AllowedNumericType TValueType>
  constexpr NumberType(TValueType&& val) noexcept {
    this->operator=(val);
  }

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
    return m_tag == tag::Float;
  }

  /**
   * @brief Is this number holding an integer value
   * @return True if it is an integer, otherwise false
   */
  [[nodiscard]] constexpr bool isInt() const noexcept {
    return m_tag == tag::Int;
  }

  /**
   * @brief Is this number holding an unsigned integer value
   * @return True if it is an unsigned integer, otherwise false
   */
  [[nodiscard]] constexpr bool isUInt() const noexcept {
    return m_tag == tag::UInt;
  }

  /**
   * @brief Try to get a double from this number type
   * @return the double value if it exists, otherwise nullptr
   */
  [[nodiscard]] const FloatType* tryGetDouble() const {
    if (m_tag == tag::Float) return &m_f_value;
    return nullptr;
  }

  /**
   * @brief Try to get an integer from this number type
   * @return the integer value if it exists, otherwise nullptr
   */
  [[nodiscard]] const IntegerType* tryGetInt() const {
    if (m_tag == tag::Int) return &m_i_value;
    return nullptr;
  }

  /**
   * @brief Try to get an integer from this number type
   * @return the integer value if it exists, otherwise nullptr
   */
  [[nodiscard]] const UnsignedIntegerType* tryGetUInt() const {
    if (m_tag == tag::UInt) return &m_u_value;
    return nullptr;
  }

  /**
   * @brief
   * @return
   */
  template <AllowedNumericType TValueType>
  NumberType& operator=(TValueType&& val) {
    if constexpr (std::floating_point<std::remove_cvref_t<TValueType>>) {
      m_f_value = std::forward<TValueType>(val);
      m_tag = tag::Float;
    } else if constexpr (SignedIntegerLike<TValueType>) {
      m_i_value = std::forward<TValueType>(val);
      m_tag = tag::Int;
    } else if constexpr (UnsignedIntegerLike<TValueType>) {
      m_u_value = std::forward<TValueType>(val);
      m_tag = tag::UInt;
    } else {
      // The concept should prevent this from happening but just in case.
      throw std::exception{};
    }
    return *this;
  }
};

}  // namespace mguid

#endif  // DATATREE_NUMBER_TYPE_HPP
