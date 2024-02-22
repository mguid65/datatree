/**
 * Copyright (c) 2024 Matthew Guidry
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 *
 * @brief Declarations for treenode
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_TREE_NODE_HPP
#define DATATREE_TREE_NODE_HPP

#include <concepts>
#include <variant>

#include "datatree/node_types/array_node_type.hpp"
#include "datatree/node_types/object_node_type.hpp"
#include "datatree/node_types/value_node_type.hpp"

namespace mguid {

using NodeType = std::variant<ObjectNodeType, ArrayNodeType, ValueNodeType>;

template <typename TNodeType>
concept ValidNodeType =
    std::same_as<std::remove_cvref_t<TNodeType>, ObjectNodeType> ||
    std::same_as<std::remove_cvref_t<TNodeType>, ArrayNodeType> ||
    std::same_as<std::remove_cvref_t<TNodeType>, ValueNodeType>;

enum class NodeTypeTag : std::uint8_t { Object, Array, Value };

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
   * @brief Construct a TreeNode from an TNodeType
   * @tparam TNodeType type restricted by a concept to be ObjectNodeType,
   * ArrayNodeType, or ValueNodeType so we can use perfect forwarding
   * @param node_data one of the valid node types
   */
  template <ValidNodeType TNodeType>
  explicit TreeNode(TNodeType&& node_data)
      : m_node_data{std::forward<TNodeType>(node_data)} {}

  /**
   * @brief Construct a TreeNode with the proper alternative given the tag
   *
   * NodeTypeTag::Object, NodeTypeTag::Array, or NodeTypeTag::Value
   *
   * @tparam tag tag corresponding with one of the node types
   */
  explicit TreeNode(NodeTypeTag tag) : m_node_data{TreeNode::FromTag(tag)} {}

  /**
   * @brief TryGet type tag for this tree node
   * @return type tag
   */
  [[nodiscard]] constexpr NodeTypeTag Tag() const noexcept {
    switch (m_node_data.index()) {
      case 0:
        return NodeTypeTag::Object;
      case 1:
        return NodeTypeTag::Array;
      case 2:
        return NodeTypeTag::Value;
      default:
        Unreachable();
    }
  }

  /**
   * @brief Try to get the requested type from this TreeNode
   * @tparam TRequestedType the type requested
   * @return The requested type if it is the type being held, otherwise Error
   */
  template <ValidNodeType TRequestedType>
  [[nodiscard]] auto Has() const -> bool {
    return std::holds_alternative<TRequestedType>(m_node_data);
  }

  /**
   * @brief Is this node holding an ObjectNodeType
   * @return true if holding an ObjectNodeType, otherwise false
   */
  [[nodiscard]] auto HasObject() const noexcept -> bool {
    return Has<ObjectNodeType>();
  }

  /**
   * @brief Is this node holding an ArrayNodeType
   * @return true if holding an ArrayNodeType, otherwise false
   */
  [[nodiscard]] auto HasArray() const noexcept -> bool {
    return Has<ArrayNodeType>();
  }

  /**
   * @brief Is this node holding an ValueNodeType
   * @return true if holding an ValueNodeType, otherwise false
   */
  [[nodiscard]] auto HasValue() const noexcept -> bool {
    return Has<ValueNodeType>();
  }

  /**
   * @brief Try to get the requested type from this TreeNode
   * @tparam TRequestedType the type requested
   * @return The requested type if it is the type being held, otherwise Error
   */
  template <ValidNodeType TRequestedType>
  [[nodiscard]] auto TryGet() const -> expected<TRequestedType, Error> {
    if (auto* result = std::get_if<TRequestedType>(&m_node_data);
        result != nullptr) {
      return *result;
    }
    return make_unexpected(Error{.category = Error::Category::BadAccess});
  }

  /**
   * @brief Try to get an ObjectNodeType from this node
   * @return ObjectNodeType if holding an ObjectNodeType, otherwise Error
   */
  [[nodiscard]] auto TryGetObject() const -> expected<ObjectNodeType, Error> {
    return TryGet<ObjectNodeType>();
  }

  /**
   * @brief Try to get an ArrayNodeType from this node
   * @return ArrayNodeType if holding an ArrayNodeType, otherwise Error
   */
  [[nodiscard]] auto TryGetArray() const -> expected<ArrayNodeType, Error> {
    return TryGet<ArrayNodeType>();
  }

  /**
   * @brief Try to get an ValueNodeType from this node
   * @return ValueNodeType if holding an ValueNodeType, otherwise Error
   */
  [[nodiscard]] auto TryGetValue() const -> expected<ValueNodeType, Error> {
    return TryGet<ValueNodeType>();
  }

  /**
   * @brief Try to get the requested type from this TreeNode
   * @tparam TRequestedType the type requested
   * @return The requested type if it is the type being held or exception
   */
  template <ValidNodeType TRequestedType>
  [[nodiscard]] auto Get() const -> const TRequestedType& {
    return std::get<TRequestedType>(m_node_data);
  }

  /**
   * @brief Try to get the requested type from this TreeNode
   * @tparam TRequestedType the type requested
   * @return The requested type if it is the type being held or exception
   */
  template <ValidNodeType TRequestedType>
  [[nodiscard]] auto Get() -> TRequestedType& {
    return std::get<TRequestedType>(m_node_data);
  }

  /**
   * @brief Try to get an ObjectNodeType from this node
   * @return ObjectNodeType if holding an ObjectNodeType or exception
   */
  [[nodiscard]] auto GetObject() const -> const ObjectNodeType& {
    return Get<ObjectNodeType>();
  }


  /**
   * @brief Try to get an ObjectNodeType from this node
   * @return ObjectNodeType if holding an ObjectNodeType or exception
   */
  [[nodiscard]] auto GetObject() -> ObjectNodeType& {
    return Get<ObjectNodeType>();
  }

  /**
   * @brief Try to get an ArrayNodeType from this node
   * @return ArrayNodeType if holding an ArrayNodeType or exception
   */
  [[nodiscard]] auto GetArray() const -> const ArrayNodeType& {
    return Get<ArrayNodeType>();
  }

  /**
   * @brief Try to get an ArrayNodeType from this node
   * @return ArrayNodeType if holding an ArrayNodeType or exception
   */
  [[nodiscard]] auto GetArray() -> ArrayNodeType& {
    return Get<ArrayNodeType>();
  }

  /**
   * @brief Try to get an ValueNodeType from this node
   * @return ValueNodeType if holding an ValueNodeType or exception
   */
  [[nodiscard]] auto GetValue() -> ValueNodeType& {
    return Get<ValueNodeType>();
  }

  /**
   * @brief Try to get an ValueNodeType from this node
   * @return ValueNodeType if holding an ValueNodeType or exception
   */
  [[nodiscard]] auto GetValue() const -> const ValueNodeType& {
    return Get<ValueNodeType>();
  }

  /**
   * @brief Set this TreeNode to an TNodeType
   * @tparam TNodeType type restricted by a concept to be ObjectNodeType,
   * ArrayNodeType, or ValueNodeType so we can use perfect forwarding
   * @param node_data one of the valid node types
   */
  template <ValidNodeType TNodeType>
  void Set(TNodeType&& node_data) {
    m_node_data = std::forward<TNodeType>(node_data);
  }

  /**
   * @brief Reset this node, optionally specifying a new default node type by
   * tag
   * @tparam TTag tag corresponding with one of the node types
   */
  template <NodeTypeTag TTag = NodeTypeTag::Object>
    requires(static_cast<std::uint8_t>(TTag) < 3)
  void Reset() {
    m_node_data = FromTagTemplate<TTag>();
  }

  /**
   * @brief Reset this node, optionally specifying a new default node type by
   * tag
   * @param tag tag corresponding with one of the node types
   */
  void Reset(NodeTypeTag tag) { m_node_data = FromTag(tag); }

  /**
   * @brief Visit a tree node with a visitor overload set
   * @tparam TCallables set of non final callable types
   * @param callables set of non final callables
   * @return the common return type of all callables provided
   */
  template <typename... TCallables>
  auto Visit(TCallables&&... callables) {
    auto overload_set = Overload{std::forward<TCallables>(callables)...};
    return std::visit(overload_set, m_node_data);
  }

  /**
   * @brief Visit a tree node with a visitor overload set
   * @tparam TCallables set of non final callable types
   * @param callables set of non final callables
   * @return the common return type of all callables provided
   */
  template <typename... TCallables>
  auto Visit(TCallables&&... callables) const {
    auto overload_set = Overload{std::forward<TCallables>(callables)...};
    return std::visit(overload_set, m_node_data);
  }

  // Get If ?
  // Emplace ?

  /**
   * @brief Equality compare this TreeNode to another
   * @return true if they are equal, otherwise false
   */
  [[nodiscard]] bool operator==(const TreeNode&) const noexcept = default;

private:
  /**
   * @brief Based on a tag, create the corresponding node type
   *
   * This is effectively a static factory function
   *
   * @param tag tag corresponding with one of the node types
   */
  [[nodiscard]] static NodeType FromTag(NodeTypeTag tag) {
    switch (tag) {
      case NodeTypeTag::Array:
        return {ArrayNodeType{}};
      case NodeTypeTag::Value:
        return {ValueNodeType{}};
      default:
        return {ObjectNodeType{}};
    }
  }

  /**
   * @brief Based on a tag, create the corresponding node type
   *
   * This is effectively a static factory function
   *
   * @tparam TTag tag corresponding with one of the node types
   */
  template <NodeTypeTag TTag>
  [[nodiscard]] static auto FromTagTemplate() {
    if constexpr (TTag == NodeTypeTag::Array) {
      return ArrayNodeType{};
    } else if constexpr (TTag == NodeTypeTag::Value) {
      return ValueNodeType{};
    } else {
      return ObjectNodeType{};
    }
  }

  NodeType m_node_data{ObjectNodeType{}};
};

}  // namespace mguid

#endif  // DATATREE_TREE_NODE_HPP
