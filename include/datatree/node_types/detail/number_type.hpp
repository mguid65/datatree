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

#include "datatree/common.hpp"
#include "datatree/error/error_type.hpp"
#include "datatree/node_types/detail/null_type.hpp"

namespace mguid {

using IntegerType = std::int64_t;
using UnsignedIntegerType = std::uint64_t;
using DoubleType = double;

namespace detail {
/**
 * @brief A type satisfies this concept if it is an integral or floating point
 * but not a bool
 * @tparam TType A type we are attempting to constrain
 */
template <typename TType>
concept AllowedNumericType =
    (!std::same_as<std::remove_cvref_t<TType>, bool> &&
     (std::integral<std::remove_cvref_t<TType>> ||
      std::floating_point<std::remove_cvref_t<TType>>));

/**
 * @brief A type satisfies this concept if it is a signed integer type but not
 * boolean
 * @tparam TType A type we are attempting to constrain
 */
template <typename TType>
concept SignedIntegerLike = (!std::same_as<std::remove_cvref_t<TType>, bool> &&
                             (std::integral<std::remove_cvref_t<TType>>)) &&
                            std::is_signed_v<std::remove_cvref_t<TType>>;

/**
 * @brief A type satisfies this concept if it is an unsigned integer type but
 * not boolean
 * @tparam TType A type we are attempting to constrain
 */
template <typename TType>
concept UnsignedIntegerLike =
    (!std::same_as<std::remove_cvref_t<TType>, bool> &&
     (std::integral<std::remove_cvref_t<TType>>)) &&
    std::is_unsigned_v<std::remove_cvref_t<TType>>;
}  // namespace detail

/**
 * @brief A class that holds numeric values
 *
 * NOTE: Maybe use tl::expected everywhere
 */
class NumberType {
public:
  enum class TypeTag { Double, UInt, Int, None };

  /**
   * @brief Default construct a number with no value
   *
   * Sets the tag to None
   */
  constexpr NumberType() noexcept = default;
  constexpr NumberType(const NumberType&) noexcept = default;
  constexpr NumberType(NumberType&&) noexcept = default;
  constexpr NumberType& operator=(const NumberType&) noexcept = default;
  constexpr NumberType& operator=(NumberType&&) noexcept = default;

  /**
   * @brief Nullptr constructor overload
   *
   * This does the same thing as the default constructor but
   * it may help readability in usage scenarios by being explicit.
   */
  constexpr NumberType(std::nullptr_t) noexcept {}

  /**
   * @brief Construct a NumberType from a value
   * @tparam TValueType type of value constrained by AllowedNumericType
   * @param val numeric value
   */
  template <detail::AllowedNumericType TValueType>
  constexpr NumberType(TValueType&& val) noexcept {
    this->operator=(val);
  }

  /**
   * @brief Does this number have a value
   * @return True if it has a value, otherwise false
   */
  [[nodiscard]] constexpr auto hasValue() const noexcept -> bool {
    return m_tag != TypeTag::None;
  }

  /**
   * @brief Is this number holding a double value
   * @return True if it is a double, otherwise false
   */
  [[nodiscard]] constexpr auto isDouble() const noexcept -> bool {
    return m_tag == TypeTag::Double;
  }

  /**
   * @brief Is this number holding an integer value
   * @return True if it is an integer, otherwise false
   */
  [[nodiscard]] constexpr auto isInt() const noexcept -> bool {
    return m_tag == TypeTag::Int;
  }

  /**
   * @brief Is this number holding an unsigned integer value
   * @return True if it is an unsigned integer, otherwise false
   */
  [[nodiscard]] constexpr auto isUInt() const noexcept -> bool {
    return m_tag == TypeTag::UInt;
  }

  /**
   * @brief Try to get a double from this number type
   * @return the double value if it exists, otherwise error
   */
  [[nodiscard]] auto getDouble() const -> expected<DoubleType, Error> {
    if (m_tag == TypeTag::Double) return m_f_value;
    return nonstd::make_unexpected(Error{.category = Error::Status::BadAccess});
  }

  /**
   * @brief Try to get an integer from this number type
   * @return the integer value if it exists, otherwise error
   */
  [[nodiscard]] auto getInt() const -> expected<IntegerType, Error> {
    if (m_tag == TypeTag::Int) return m_i_value;
    return nonstd::make_unexpected(Error{.category = Error::Status::BadAccess});
  }

  /**
   * @brief Try to get an integer from this number type
   * @return the integer value if it exists, otherwise error
   */
  [[nodiscard]] auto getUInt() const -> expected<UnsignedIntegerType, Error> {
    if (m_tag == TypeTag::UInt) return m_u_value;
    return nonstd::make_unexpected(Error{.category = Error::Status::BadAccess});
  }

  /**
   * @brief Assign a value to this number container
   * @tparam TValueType type of value constrained by AllowedNumericType
   * @param val numeric value
   * @return reference to this number instance
   */
  template <detail::AllowedNumericType TValueType>
  constexpr auto operator=(TValueType&& val) noexcept -> NumberType& {
    setValue(std::forward<TValueType>(val));
    return *this;
  }

  /**
   * @brief Get the type tag of this number container
   * @return the type tag of this number container
   */
  [[nodiscard]] constexpr auto getTypeTag() const noexcept -> TypeTag {
    return m_tag;
  }

  /**
   * @brief Set the value of this numeric type
   * @tparam TValueType type of value constrained by AllowedNumericType
   * @param val numeric value
   */
  template <detail::AllowedNumericType TValueType>
  constexpr void setValue(TValueType&& val) noexcept {
    if constexpr (std::floating_point<std::remove_cvref_t<TValueType>>) {
      m_f_value = std::forward<TValueType>(val);
      m_tag = TypeTag::Double;
    } else if constexpr (detail::SignedIntegerLike<TValueType>) {
      m_i_value = std::forward<TValueType>(val);
      m_tag = TypeTag::Int;
    } else if constexpr (detail::UnsignedIntegerLike<TValueType>) {
      m_u_value = std::forward<TValueType>(val);
      m_tag = TypeTag::UInt;
    } else {
      // The concept should prevent this from happening but just in case,
      // we put a throw here which isn't allowed in constexpr contexts so this
      // will fail to compile
      unreachable();
    }
  }

  /**
   * @brief Reset the state of this number container
   */
  constexpr void reset() noexcept {
    m_tag = TypeTag::None;
    m_none = NullType{};
  }

private:
  TypeTag m_tag{TypeTag::None};
  union {
    // Default value and initialized for constexpr contexts
    NullType m_none{};
    DoubleType m_f_value;
    IntegerType m_i_value;
    UnsignedIntegerType m_u_value;
  };
};

}  // namespace mguid

#endif  // DATATREE_NUMBER_TYPE_HPP
