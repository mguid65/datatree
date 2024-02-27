/**
 * Copyright (c) 2024 Matthew Guidry
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 *
 * @brief A number holder abstraction
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_NUMBER_TYPE_HPP
#define DATATREE_NUMBER_TYPE_HPP

#include <compare>
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
  // The ordering of these enums matter
  // It affects the three-way comparison
  enum class TypeTag { None, Int, UInt, Double };

  /**
   * @brief Default construct a number with no value
   *
   * Sets the tag to None
   */
  constexpr NumberType() noexcept = default;

  /**
   * @brief Explicit defaults for copy/move construction/assignment
   */
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
  constexpr explicit NumberType(std::nullptr_t) noexcept {}

  /**
   * @brief Construct a NumberType from a value
   * @tparam TValueType type of value constrained by AllowedNumericType
   * @param val numeric value
   */
  template <detail::AllowedNumericType TValueType>
  constexpr explicit NumberType(TValueType&& val) noexcept {
    this->operator=(val);
  }

  /**
   * @brief Does this number have a value
   * @return True if it has a value, otherwise false
   */
  [[nodiscard]] constexpr auto HasValue() const noexcept -> bool {
    return m_tag != TypeTag::None;
  }

  /**
   * @brief Is this number holding a double value
   * @return True if it is a double, otherwise false
   */
  [[nodiscard]] constexpr auto IsDouble() const noexcept -> bool {
    return m_tag == TypeTag::Double;
  }

  /**
   * @brief Is this number holding an integer value
   * @return True if it is an integer, otherwise false
   */
  [[nodiscard]] constexpr auto IsInt() const noexcept -> bool {
    return m_tag == TypeTag::Int;
  }

  /**
   * @brief Is this number holding an unsigned integer value
   * @return True if it is an unsigned integer, otherwise false
   */
  [[nodiscard]] constexpr auto IsUInt() const noexcept -> bool {
    return m_tag == TypeTag::UInt;
  }

  /**
   * @brief Try to get a double from this number type
   * @return the double value if it exists, otherwise error
   */
  [[nodiscard]] auto GetDouble() const -> expected<DoubleType, Error> {
    if (m_tag == TypeTag::Double) return m_union.f_value;
    return make_unexpected(Error{.category = Error::Category::BadAccess});
  }

  /**
   * @brief Try to get an integer from this number type
   * @return the integer value if it exists, otherwise error
   */
  [[nodiscard]] auto GetInt() const -> expected<IntegerType, Error> {
    if (m_tag == TypeTag::Int) return m_union.i_value;
    return make_unexpected(Error{.category = Error::Category::BadAccess});
  }

  /**
   * @brief Try to get an integer from this number type
   * @return the integer value if it exists, otherwise error
   */
  [[nodiscard]] auto GetUInt() const -> expected<UnsignedIntegerType, Error> {
    if (m_tag == TypeTag::UInt) return m_union.u_value;
    return make_unexpected(Error{.category = Error::Category::BadAccess});
  }

  /**
   * @brief Assign a value to this number container
   * @tparam TValueType type of value constrained by AllowedNumericType
   * @param val numeric value
   * @return reference to this number instance
   */
  template <detail::AllowedNumericType TValueType>
  constexpr auto operator=(TValueType&& val) noexcept -> NumberType& {
    SetValue(std::forward<TValueType>(val));
    return *this;
  }

  /**
   * @brief Get the type tag of this number container
   * @return the type tag of this number container
   */
  [[nodiscard]] constexpr auto GetTypeTag() const noexcept -> TypeTag {
    return m_tag;
  }

  /**
   * @brief Set the value of this numeric type
   * @tparam TValueType type of value constrained by AllowedNumericType
   * @param val numeric value
   */
  template <detail::AllowedNumericType TValueType>
  constexpr void SetValue(TValueType&& val) noexcept {
    if constexpr (std::floating_point<std::remove_cvref_t<TValueType>>) {
      m_union.f_value = std::forward<TValueType>(val);
      m_tag = TypeTag::Double;
    } else if constexpr (detail::SignedIntegerLike<TValueType>) {
      m_union.i_value = std::forward<TValueType>(val);
      m_tag = TypeTag::Int;
    } else if constexpr (detail::UnsignedIntegerLike<TValueType>) {
      m_union.u_value = std::forward<TValueType>(val);
      m_tag = TypeTag::UInt;
    } else {
      // The concept should prevent this from happening but just in case,
      // we put a throw here which isn't allowed in constexpr contexts so this
      // will fail to compile
      Unreachable();
    }
  }

  /**
   * @brief Reset the state of this number container
   */
  constexpr void Reset() noexcept {
    m_tag = TypeTag::None;
    m_union.none = NullType{};
  }

  /**
   * @brief Visit a tree node with a visitor overload set
   * @tparam TCallables set of non final callable types
   * @param callables set of non final callables
   * @return the common return type of all callables provided
   */
  template <typename... TCallables>
  decltype(auto) Visit(TCallables&&... callables) {
    auto overload_set = Overload{std::forward<TCallables>(callables)...};
    switch (m_tag) {
      case TypeTag::Int: {
        return std::invoke(overload_set, m_union.i_value);
      }
      case TypeTag::UInt: {
        return std::invoke(overload_set, m_union.u_value);
      }
      case TypeTag::Double: {
        return std::invoke(overload_set, m_union.f_value);
      }
      case TypeTag::None: {
        return std::invoke(overload_set, m_union.none);
      }
    }
    return std::invoke(overload_set, NullType{});
  }

  /**
   * @brief Visit a tree node with a visitor overload set
   * @tparam TCallables set of non final callable types
   * @param callables set of non final callables
   * @return the common return type of all callables provided
   */
  template <typename... TCallables>
  decltype(auto) Visit(TCallables&&... callables) const {
    auto overload_set = Overload{std::forward<TCallables>(callables)...};
    switch (m_tag) {
      case TypeTag::Int: {
        return std::invoke(overload_set, m_union.i_value);
      }
      case TypeTag::UInt: {
        return std::invoke(overload_set, m_union.u_value);
      }
      case TypeTag::Double: {
        return std::invoke(overload_set, m_union.f_value);
      }
      case TypeTag::None: {
        return std::invoke(overload_set, m_union.none);
      }
    }
    return std::invoke(overload_set, NullType{});
  }

  /**
   * @brief Compare this NumberType with another NumberType
   * @param other another NumberType
   * @return comparison category
   */
  [[nodiscard]] constexpr auto operator<=>(const NumberType& other) const
      -> std::partial_ordering {
    if (m_tag == TypeTag::None && m_tag == other.m_tag) {
      return std::strong_ordering::equal;
    }
    if (m_tag != other.m_tag) {
      return static_cast<int>(m_tag) <=> static_cast<int>(other.m_tag);
    }
    switch (m_tag) {
      case TypeTag::Double:
        return m_union.f_value <=> other.m_union.f_value;
      case TypeTag::UInt:
        return m_union.u_value <=> other.m_union.u_value;
      case TypeTag::Int:
        return m_union.i_value <=> other.m_union.i_value;
      default:
        return std::partial_ordering::unordered;
    }
  }

  /**
   * @brief Equality compare this NumberType with another NumberType
   * @param other Another NumberType to compare
   * @return true if equal, otherwise false
   */
  [[nodiscard]] constexpr auto operator==(const NumberType& other) const
      -> bool {
    if (m_tag == TypeTag::None && m_tag == other.m_tag) { return true; }
    if (m_tag != other.m_tag) { return false; }
    switch (m_tag) {
      case TypeTag::Double:
        return m_union.f_value == other.m_union.f_value;
      case TypeTag::UInt:
        return m_union.u_value == other.m_union.u_value;
      case TypeTag::Int:
        return m_union.i_value == other.m_union.i_value;
      default:
        return false;
    }
  }

private:
  TypeTag m_tag{TypeTag::None};
  union {
    // Default value and initialized for constexpr contexts
    NullType none{};
    DoubleType f_value;
    IntegerType i_value;
    UnsignedIntegerType u_value;
  } m_union;
};

}  // namespace mguid

#endif  // DATATREE_NUMBER_TYPE_HPP
