/**
 * @brief Declarations for value node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_VALUE_NODE_TYPE_HPP
#define DATATREE_VALUE_NODE_TYPE_HPP

#include <utility>
#include <variant>

#include "datatree/node_types/detail/value_types.hpp"

namespace mguid {

/**
 * @brief A class to represent a node that stores a value
 */
class ValueNodeType {
public:
  /**
   * @brief Default construct a ValueNode with value Null
   */
  constexpr ValueNodeType() noexcept = default;

  /**
   * @brief Explicit defaults for copy/move construction/assignment
   */
  ValueNodeType(const ValueNodeType&) = default;
  ValueNodeType(ValueNodeType&&) noexcept = default;
  ValueNodeType& operator=(const ValueNodeType&) = default;
  ValueNodeType& operator=(ValueNodeType&&) noexcept = default;

  /**
   * @brief Explicitly construct a null ValueNode
   */
  constexpr explicit ValueNodeType(nullptr_t) noexcept {}

  /**
   * @brief Construct a value node from a value
   * @tparam TValueType a valid value type
   * @param value some value
   */
  template <ValidValueNodeTypeValueType TValueType>
  constexpr explicit ValueNodeType(TValueType&& value) noexcept(
      !SatisfiesStringType<TValueType>) {
    // This is for the case where the value is a number primitive
    if constexpr (SatisfiesNumberType<TValueType>) {
      m_variant_value = NumberType(std::forward<TValueType>(value));
    } else {
      m_variant_value = std::forward<TValueType>(value);
    }
  }

  /**
   * @brief Assign a value to this value node type
   * @tparam TValueType type of value
   * @param val value
   * @return reference to this value node type
   */
  template <ValidValueNodeTypeValueType TValueType>
  constexpr auto operator=(TValueType&& val) noexcept(
      !SatisfiesStringType<TValueType>) -> ValueNodeType& {
    m_variant_value = std::forward<TValueType>(val);
    return *this;
  }

  /**
   * @brief Is this value node type holding a NullType value
   * @return true if this value node type holding a NullType value, otherwise
   * false
   */
  [[nodiscard]] constexpr auto hasNull() const noexcept -> bool {
    return std::holds_alternative<NullType>(m_variant_value);
  }
  /**
   * @brief Is this value node type holding a StringType value
   * @return true if this value node type holding a StringType value, otherwise
   * false
   */
  [[nodiscard]] constexpr auto hasString() const noexcept -> bool {
    return std::holds_alternative<StringType>(m_variant_value);
  }
  /**
   * @brief Is this value node type holding a NumberType value
   * @return true if this value node type holding a NumberType value, otherwise
   * false
   */
  [[nodiscard]] constexpr auto hasNumber() const noexcept -> bool {
    return std::holds_alternative<NumberType>(m_variant_value);
  }
  /**
   * @brief Is this value node type holding a BoolType value
   * @return true if this value node type holding a BoolType value, otherwise
   * false
   */
  [[nodiscard]] constexpr auto hasBool() const noexcept -> bool {
    return std::holds_alternative<BoolType>(m_variant_value);
  }

  /**
   * @brief Try to get a NullType value from this value node type
   * @return Expected with a NullType value or an Error
   */
  [[nodiscard]] auto getNull() const noexcept -> expected<NullType, Error> {
    if (auto* val = std::get_if<NullType>(&m_variant_value); val != nullptr) {
      return *val;
    }
    return make_unexpected(Error{.category = Error::Status::BadAccess});
  }
  /**
   * @brief Try to get a StringType value from this value node type
   * @return Expected with a StringType value or an Error
   */
  [[nodiscard]] auto getString() const noexcept -> expected<StringType, Error> {
    if (auto* val = std::get_if<StringType>(&m_variant_value); val != nullptr) {
      return *val;
    }
    return make_unexpected(Error{.category = Error::Status::BadAccess});
  }
  /**
   * @brief Try to get a NumberType value from this value node type
   * @return Expected with a NumberType value or an Error
   */
  [[nodiscard]] auto getNumber() const noexcept -> expected<NumberType, Error> {
    if (auto* val = std::get_if<NumberType>(&m_variant_value); val != nullptr) {
      return *val;
    }
    return make_unexpected(Error{.category = Error::Status::BadAccess});
  }
  /**
   * @brief Try to get a BoolType value from this value node type
   * @return Expected with a BoolType value or an Error
   */
  [[nodiscard]] auto getBool() const noexcept -> expected<BoolType, Error> {
    if (auto* val = std::get_if<BoolType>(&m_variant_value); val != nullptr) {
      return *val;
    }
    return make_unexpected(Error{.category = Error::Status::BadAccess});
  }

  /**
   * @brief Try to get a NullType value from this value node type, otherwise,
   * return the provided default
   *
   * For consistency with get<Type>, these functions will also return expected,
   * even though they will never return the Error
   *
   * @param default_value value to return in case this value doesn't hold a
   * NullType
   * @return Expected with a NullType value or an Error
   */
  template <typename TDefault>
  [[nodiscard]] auto getNullOr(TDefault&& default_value) const noexcept
      -> expected<NullType, Error> {
    auto* val = std::get_if<NullType>(&m_variant_value);
    return val != nullptr
               ? *val
               : static_cast<NullType>(std::forward<TDefault>(default_value));
  }
  /**
   * @brief Try to get a StringType value from this value node type, otherwise,
   * return the provided default
   *
   * For consistency with get<Type>, these functions will also return expected,
   * even though they will never return the Error
   *
   * @param default_value value to return in case this value doesn't hold a
   * StringType
   * @return Expected with a StringType value
   */
  template <typename TDefault>
  [[nodiscard]] auto getStringOr(TDefault&& default_value) const noexcept
      -> expected<StringType, Error> {
    auto* val = std::get_if<StringType>(&m_variant_value);
    return val != nullptr
               ? *val
               : static_cast<StringType>(std::forward<TDefault>(default_value));
  }
  /**
   * @brief Try to get a NumberType value from this value node type, otherwise,
   * return the provided default
   *
   * For consistency with get<Type>, these functions will also return expected,
   * even though they will never return the Error
   *
   * @param default_value value to return in case this value doesn't hold a
   * NumberType
   * @return Expected with a NumberType value
   */
  template <typename TDefault>
  [[nodiscard]] auto getNumberOr(TDefault&& default_value) const noexcept
      -> expected<NumberType, Error> {
    auto* val = std::get_if<NumberType>(&m_variant_value);
    return val != nullptr
               ? *val
               : static_cast<NumberType>(std::forward<TDefault>(default_value));
  }
  /**
   * @brief Try to get a BoolType value from this value node type, otherwise,
   * return the provided default
   *
   * For consistency with get<Type>, these functions will also return expected,
   * even though they will never return the Error
   *
   * @param default_value value to return in case this value doesn't hold a
   * BoolType
   * @return Expected with a BoolType value
   */
  template <typename TDefault>
  [[nodiscard]] auto getBoolOr(TDefault&& default_value) const noexcept
      -> expected<BoolType, Error> {
    auto* val = std::get_if<BoolType>(&m_variant_value);
    return val != nullptr
               ? *val
               : static_cast<BoolType>(std::forward<TDefault>(default_value));
  }

  /**
   * @brief If the value held by this ValueNodeType is NullType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a NullType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifNullThen(TThenFunc&& func) & -> ValueNodeType {
    auto* val = std::get_if<NullType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<std::invoke_result_t<TThenFunc, NullType&>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is NullType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a NullType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifNullThen(TThenFunc&& func) const& -> ValueNodeType {
    auto* val = std::get_if<NullType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<
        std::invoke_result_t<TThenFunc, const NullType&>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is NullType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a NullType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifNullThen(TThenFunc&& func) && -> ValueNodeType {
    auto* val = std::get_if<NullType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<std::invoke_result_t<TThenFunc, NullType>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is NullType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a NullType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifNullThen(TThenFunc&& func) const&& -> ValueNodeType {
    auto* val = std::get_if<NullType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<
        std::invoke_result_t<TThenFunc, const NullType>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is StringType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a StringType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifStringThen(TThenFunc&& func) & -> ValueNodeType {
    auto* val = std::get_if<StringType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<std::invoke_result_t<TThenFunc, StringType&>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is StringType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a StringType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifStringThen(TThenFunc&& func) const& -> ValueNodeType {
    auto* val = std::get_if<StringType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<
        std::invoke_result_t<TThenFunc, const StringType&>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is StringType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a StringType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifStringThen(TThenFunc&& func) && -> ValueNodeType {
    auto* val = std::get_if<StringType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), std::move(*val));
    }
    return std::remove_cvref_t<std::invoke_result_t<TThenFunc, StringType>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is StringType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a StringType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifStringThen(TThenFunc&& func) const&& -> ValueNodeType {
    auto* val = std::get_if<StringType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<
        std::invoke_result_t<TThenFunc, const StringType>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is NumberType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a NumberType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifNumberThen(TThenFunc&& func) & -> ValueNodeType {
    auto* val = std::get_if<NumberType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<std::invoke_result_t<TThenFunc, NumberType&>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is NumberType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a NumberType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifNumberThen(TThenFunc&& func) const& -> ValueNodeType {
    auto* val = std::get_if<NumberType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<
        std::invoke_result_t<TThenFunc, const NumberType&>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is NumberType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a NumberType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifNumberThen(TThenFunc&& func) && -> ValueNodeType {
    auto* val = std::get_if<NumberType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<std::invoke_result_t<TThenFunc, NumberType>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is NumberType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a NumberType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifNumberThen(TThenFunc&& func) const&& -> ValueNodeType {
    auto* val = std::get_if<NumberType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<
        std::invoke_result_t<TThenFunc, const NumberType>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is BoolType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a BoolType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifBoolThen(TThenFunc&& func) & -> ValueNodeType {
    auto* val = std::get_if<BoolType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<std::invoke_result_t<TThenFunc, BoolType&>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is BoolType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a BoolType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifBoolThen(TThenFunc&& func) const& -> ValueNodeType {
    auto* val = std::get_if<BoolType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<
        std::invoke_result_t<TThenFunc, const BoolType&>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is BoolType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a BoolType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifBoolThen(TThenFunc&& func) && -> ValueNodeType {
    auto* val = std::get_if<BoolType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<std::invoke_result_t<TThenFunc, BoolType>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is BoolType then call the
   * provided callback function
   * @tparam TThenFunc callback function type
   * @param func callback function that takes a BoolType and returns a
   * ValueNodeType
   * @return An ValueNodeType that was the result of calling the func or a
   * default constructed ValueNodeType
   */
  template <typename TThenFunc>
  auto ifBoolThen(TThenFunc&& func) const&& -> ValueNodeType {
    auto* val = std::get_if<BoolType>(&m_variant_value);
    if (val != nullptr) {
      return std::invoke(std::forward<TThenFunc>(func), *val);
    }
    return std::remove_cvref_t<
        std::invoke_result_t<TThenFunc, const BoolType>>{};
  }

  /**
   * @brief If the value held by this ValueNodeType is NullType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a NullType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifNullTransform(TTransformFunc&& func) & -> ValueNodeType {
    auto* val = std::get_if<NullType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{
        std::remove_cvref_t<std::invoke_result_t<TTransformFunc, NullType&>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is NullType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a NullType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifNullTransform(TTransformFunc&& func) const& -> ValueNodeType {
    auto* val = std::get_if<NullType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{std::remove_cvref_t<
        std::invoke_result_t<TTransformFunc, const NullType&>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is NullType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a NullType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifNullTransform(TTransformFunc&& func) && -> ValueNodeType {
    auto* val = std::get_if<NullType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{
        std::remove_cvref_t<std::invoke_result_t<TTransformFunc, NullType>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is NullType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a NullType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifNullTransform(TTransformFunc&& func) const&& -> ValueNodeType {
    auto* val = std::get_if<NullType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{std::remove_cvref_t<
        std::invoke_result_t<TTransformFunc, const NullType>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is StringType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a StringType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifStringTransform(TTransformFunc&& func) & -> ValueNodeType {
    auto* val = std::get_if<StringType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{std::remove_cvref_t<
        std::invoke_result_t<TTransformFunc, StringType&>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is StringType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a StringType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifStringTransform(TTransformFunc&& func) const& -> ValueNodeType {
    auto* val = std::get_if<StringType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{std::remove_cvref_t<
        std::invoke_result_t<TTransformFunc, const StringType&>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is StringType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a StringType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifStringTransform(TTransformFunc&& func) && -> ValueNodeType {
    auto* val = std::get_if<StringType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), std::move(*val))};
    }
    return ValueNodeType{std::remove_cvref_t<
        std::invoke_result_t<TTransformFunc, StringType>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is StringType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a StringType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifStringTransform(TTransformFunc&& func) const&& -> ValueNodeType {
    auto* val = std::get_if<StringType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{std::remove_cvref_t<
        std::invoke_result_t<TTransformFunc, const StringType>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is NumberType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a NumberType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifNumberTransform(TTransformFunc&& func) & -> ValueNodeType {
    auto* val = std::get_if<NumberType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{std::remove_cvref_t<
        std::invoke_result_t<TTransformFunc, NumberType&>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is NumberType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a NumberType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifNumberTransform(TTransformFunc&& func) const& -> ValueNodeType {
    auto* val = std::get_if<NumberType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{std::remove_cvref_t<
        std::invoke_result_t<TTransformFunc, const NumberType&>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is NumberType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a NumberType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifNumberTransform(TTransformFunc&& func) && -> ValueNodeType {
    auto* val = std::get_if<NumberType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{std::remove_cvref_t<
        std::invoke_result_t<TTransformFunc, NumberType>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is NumberType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a NumberType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifNumberTransform(TTransformFunc&& func) const&& -> ValueNodeType {
    auto* val = std::get_if<NumberType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{std::remove_cvref_t<
        std::invoke_result_t<TTransformFunc, const NumberType>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is BoolType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a BoolType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifBoolTransform(TTransformFunc&& func) & -> ValueNodeType {
    auto* val = std::get_if<BoolType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{
        std::remove_cvref_t<std::invoke_result_t<TTransformFunc, BoolType&>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is BoolType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a BoolType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifBoolTransform(TTransformFunc&& func) const& -> ValueNodeType {
    auto* val = std::get_if<BoolType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{std::remove_cvref_t<
        std::invoke_result_t<TTransformFunc, const BoolType&>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is BoolType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a BoolType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifBoolTransform(TTransformFunc&& func) && -> ValueNodeType {
    auto* val = std::get_if<BoolType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{
        std::remove_cvref_t<std::invoke_result_t<TTransformFunc, BoolType>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is BoolType then call the
   * provided callback function
   * @tparam TTransformFunc callback function type
   * @param func callback function that takes a BoolType and returns something
   * convertible to ValueNodeType
   * @return the result of constructing a ValueNodeType with the default
   * constructed return value type of TTransformFunc
   */
  template <typename TTransformFunc>
  auto ifBoolTransform(TTransformFunc&& func) const&& -> ValueNodeType {
    auto* val = std::get_if<BoolType>(&m_variant_value);
    if (val != nullptr) {
      return ValueNodeType{
          std::invoke(std::forward<TTransformFunc>(func), *val)};
    }
    return ValueNodeType{std::remove_cvref_t<
        std::invoke_result_t<TTransformFunc, const BoolType>>{}};
  }

  /**
   * @brief If the value held by this ValueNodeType is not NullType then call
   * the provided callback function
   * @tparam TElseFunc callback function type
   * @param func callback function that returns a ValueNodeType
   * @return *this, or the result of calling TElseFunc function
   */
  template <typename TElseFunc>
    requires std::same_as<std::remove_cvref_t<std::invoke_result_t<TElseFunc>>,
                          ValueNodeType>
  auto ifNullElse(TElseFunc&& func) const& -> ValueNodeType {
    auto* val = std::get_if<NullType>(&m_variant_value);
    if (val != nullptr) { return *this; }
    return std::invoke(std::forward<TElseFunc>(func));
  }

  /**
   * @brief If the value held by this ValueNodeType is not NullType then call
   * the provided callback function
   * @tparam TElseFunc callback function type
   * @param func callback function that returns a ValueNodeType
   * @return *this, or the result of calling TElseFunc function
   */
  template <typename TElseFunc>
    requires std::same_as<std::remove_cvref_t<std::invoke_result_t<TElseFunc>>,
                          ValueNodeType>
  auto ifNullElse(TElseFunc&& func) && -> ValueNodeType {
    auto* val = std::get_if<NullType>(&m_variant_value);
    if (val != nullptr) { return *this; }
    return std::invoke(std::forward<TElseFunc>(func));
  }

  /**
   * @brief If the value held by this ValueNodeType is not StringType then call
   * the provided callback function
   * @tparam TElseFunc callback function type
   * @param func callback function that returns a ValueNodeType
   * @return *this, or the result of calling TElseFunc function
   */
  template <typename TElseFunc>
    requires std::same_as<std::remove_cvref_t<std::invoke_result_t<TElseFunc>>,
                          ValueNodeType>
  auto ifStringElse(TElseFunc&& func) const& -> ValueNodeType {
    auto* val = std::get_if<StringType>(&m_variant_value);
    if (val != nullptr) { return *this; }
    return std::invoke(std::forward<TElseFunc>(func));
  }

  /**
   * @brief If the value held by this ValueNodeType is not StringType then call
   * the provided callback function
   * @tparam TElseFunc callback function type
   * @param func callback function that returns a ValueNodeType
   * @return *this, or the result of calling TElseFunc function
   */
  template <typename TElseFunc>
    requires std::same_as<std::remove_cvref_t<std::invoke_result_t<TElseFunc>>,
                          ValueNodeType>
  auto ifStringElse(TElseFunc&& func) && -> ValueNodeType {
    auto* val = std::get_if<StringType>(&m_variant_value);
    if (val != nullptr) { return *this; }
    return std::invoke(std::forward<TElseFunc>(func));
  }

  /**
   * @brief If the value held by this ValueNodeType is not NumberType then call
   * the provided callback function
   * @tparam TElseFunc callback function type
   * @param func callback function that returns a ValueNodeType
   * @return *this, or the result of calling TElseFunc function
   */
  template <typename TElseFunc>
    requires std::same_as<std::remove_cvref_t<std::invoke_result_t<TElseFunc>>,
                          ValueNodeType>
  auto ifNumberElse(TElseFunc&& func) const& -> ValueNodeType {
    auto* val = std::get_if<NumberType>(&m_variant_value);
    if (val != nullptr) { return *this; }
    return std::invoke(std::forward<TElseFunc>(func));
  }

  /**
   * @brief If the value held by this ValueNodeType is not NumberType then call
   * the provided callback function
   * @tparam TElseFunc callback function type
   * @param func callback function that returns a ValueNodeType
   * @return *this, or the result of calling TElseFunc function
   */
  template <typename TElseFunc>
    requires std::same_as<std::remove_cvref_t<std::invoke_result_t<TElseFunc>>,
                          ValueNodeType>
  auto ifNumberElse(TElseFunc&& func) && -> ValueNodeType {
    auto* val = std::get_if<NumberType>(&m_variant_value);
    if (val != nullptr) { return *this; }
    return std::invoke(std::forward<TElseFunc>(func));
  }

  /**
   * @brief If the value held by this ValueNodeType is not BoolType then call
   * the provided callback function
   * @tparam TElseFunc callback function type
   * @param func callback function that returns a ValueNodeType
   * @return *this, or the result of calling TElseFunc function
   */
  template <typename TElseFunc>
    requires std::same_as<std::remove_cvref_t<std::invoke_result_t<TElseFunc>>,
                          ValueNodeType>
  auto ifBoolElse(TElseFunc&& func) const& -> ValueNodeType {
    auto* val = std::get_if<BoolType>(&m_variant_value);
    if (val != nullptr) { return *this; }
    return std::invoke(std::forward<TElseFunc>(func));
  }

  /**
   * @brief If the value held by this ValueNodeType is not BoolType then call
   * the provided callback function
   * @tparam TElseFunc callback function type
   * @param func callback function that returns a ValueNodeType
   * @return *this, or the result of calling TElseFunc function
   */
  template <typename TElseFunc>
    requires std::same_as<std::remove_cvref_t<std::invoke_result_t<TElseFunc>>,
                          ValueNodeType>
  auto ifBoolElse(TElseFunc&& func) && -> ValueNodeType {
    auto* val = std::get_if<BoolType>(&m_variant_value);
    if (val != nullptr) { return *this; }
    return std::invoke(std::forward<TElseFunc>(func));
  }

  /**
   * @brief Compare this ValueNodeType with another ValueNodeType
   * @return comparison category
   */
  [[nodiscard]] constexpr auto operator<=>(const ValueNodeType&) const =
      default;

private:
  VariantValueType m_variant_value{NullType{}};
};

}  // namespace mguid

#endif  // DATATREE_VALUE_NODE_TYPE_HPP