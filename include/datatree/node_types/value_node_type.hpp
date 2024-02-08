/**
 * @brief Declarations for value node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_VALUE_NODE_TYPE_HPP
#define DATATREE_VALUE_NODE_TYPE_HPP

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
  ValueNodeType() noexcept = default;

  /**
   * @brief Explicit defaults for copy/move construction/assignment
   */
  ValueNodeType(const ValueNodeType&) noexcept = default;
  ValueNodeType(ValueNodeType&&) noexcept = default;
  ValueNodeType& operator=(const ValueNodeType&) noexcept = default;
  ValueNodeType& operator=(ValueNodeType&&) noexcept = default;

  /**
   * @brief Explicitly construct a null ValueNode
   */
  explicit ValueNodeType(nullptr_t) noexcept {}

  /**
   * @brief Construct a value node from a value
   * @tparam TValueType a valid value type
   * @param value some value
   */
  template <ValidValueNodeTypeValueType TValueType>
  explicit ValueNodeType(TValueType&& value)
      : m_variant_value{std::forward<TValueType>(value)} {}


private:
  VariantValueType m_variant_value{NullType{}};
};

}  // namespace mguid

#endif  // DATATREE_VALUE_NODE_TYPE_HPP
