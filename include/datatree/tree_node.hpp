/**
 * @brief Declarations for treenode
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_TREE_NODE_HPP
#define DATATREE_TREE_NODE_HPP

#include <variant>

#include "datatree/node_types/array_node_type.hpp"
#include "datatree/node_types/object_node_type.hpp"
#include "datatree/node_types/value_node_type.hpp"

namespace mguid {

using NodeType = std::variant<ObjectNodeType, ArrayNodeType, ValueNodeType>;

/**
 * @brief Represents a node in the data tree that can be an Object, Array, or
 * Value
 */
class TreeNode {
public:
  /**
   * @brief Default construct a TreeNode
   */
  TreeNode() = default;

  /**
   * @brief Explicit defaults for copy/move construction/assignment
   */
  TreeNode(const TreeNode&) = default;
  TreeNode(TreeNode&&) noexcept = default;
  TreeNode& operator=(const TreeNode&) = default;
  TreeNode& operator=(TreeNode&&) noexcept = default;

  /**
   * @brief Construct a TreeNode from an ObjectNodeType
   * @param node_item an ObjectNodeType
   */
  explicit TreeNode(const ObjectNodeType& node_item) : m_node_data{node_item} {}

  /**
   * @brief Construct a TreeNode from an option array
   * @param node_item an ArrayNodeType
   */
  explicit TreeNode(const ArrayNodeType& node_item) : m_node_data{node_item} {}

  /**
   * @brief Construct a TreeNode from an option value
   * @param node_item a ValueNodeType
   */
  explicit TreeNode(const ValueNodeType& node_item) : m_node_data{node_item} {}

  /**
   * @brief Is this node holding an ObjectNodeType
   * @return true if holding an ObjectNodeType, otherwise false
   */
  [[nodiscard]] auto HasObject() const -> bool {
    return std::holds_alternative<ObjectNodeType>(m_node_data);
  }

  /**
   * @brief Is this node holding an ArrayNodeType
   * @return true if holding an ArrayNodeType, otherwise false
   */
  [[nodiscard]] auto HasArray() const -> bool {
    return std::holds_alternative<ArrayNodeType>(m_node_data);
  }

  /**
   * @brief Is this node holding an ValueNodeType
   * @return true if holding an ValueNodeType, otherwise false
   */
  [[nodiscard]] auto HasValue() const -> bool {
    return std::holds_alternative<ValueNodeType>(m_node_data);
  }

  /**
   * @brief Try to get an ObjectNodeType from this node
   * @return ObjectNodeType if holding an ObjectNodeType, otherwise Error
   */
  [[nodiscard]] auto GetObject() const -> bool {
    return std::holds_alternative<ObjectNodeType>(m_node_data);
  }

  /**
   * @brief Try to get an ArrayNodeType from this node
   * @return ArrayNodeType if holding an ArrayNodeType, otherwise Error
   */
  [[nodiscard]] auto GetArray() const -> bool {
    return std::holds_alternative<ArrayNodeType>(m_node_data);
  }

  /**
   * @brief Try to get an ValueNodeType from this node
   * @return ValueNodeType if holding an ValueNodeType, otherwise Error
   */
  [[nodiscard]] auto GetValue() const -> bool {
    return std::holds_alternative<ValueNodeType>(m_node_data);
  }
private:
  NodeType m_node_data{ObjectNodeType{}};
};

}  // namespace mguid

#endif  // DATATREE_TREE_NODE_HPP
