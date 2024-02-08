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
  // BEGIN CONSTRUCTORS TODO: remove this comment
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
      !SatisfiesStringType<TValueType>)
      : m_variant_value{std::forward<TValueType>(value)} {}
  // END CONSTRUCTORS TODO: remove this comment

  // BEGIN ASSIGNMENT OPERATORS TODO: remove this comment
  /**
   * @brief
   * @tparam TValueType
   * @param val
   * @return
   */
  template <ValidValueNodeTypeValueType TValueType>
  constexpr auto operator=(TValueType&& val) noexcept(
      !SatisfiesStringType<TValueType>) -> ValueNodeType& {
    m_variant_value = std::forward<TValueType>(val);
    return *this;
  }


  // END ASSIGNMENT OPERATORS TODO: remove this comment

  // BEGIN TYPE QUERY TODO: remove this comment
  // END TYPE QUERY TODO: remove this comment

  // BEGIN MONADIC ACCESSORS TODO: remove this comment
  // END MONADIC ACCESSORS TODO: remove this comment

  // BEGIN EQUALITY OPERATOR TODO: remove this comment
  // END QUALITY OPERATOR TODO: remove this comment

private:
  VariantValueType m_variant_value{NullType{}};
};

}  // namespace mguid

#endif  // DATATREE_VALUE_NODE_TYPE_HPP
