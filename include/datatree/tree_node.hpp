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
#include <type_traits>
#include <variant>

#include "datatree/common.hpp"
#include "datatree/error/error_type.hpp"
#include "datatree/node_types/detail/value_types.hpp"

namespace mguid {

class ObjectNodeType;
class ArrayNodeType;
class ValueNodeType;

enum class NodeTypeTag : std::uint8_t { Object, Array, Value };

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
  inline TreeNode();

  /**
   * @brief Explicit defaults for copy/move construction/assignment
   */
  inline TreeNode(const TreeNode&);
  inline TreeNode(TreeNode&&) noexcept;
  inline TreeNode& operator=(const TreeNode&);
  inline TreeNode& operator=(TreeNode&&) noexcept;

  inline ~TreeNode();

  /**
   * @brief Construct a TreeNode from an TNodeType
   * @tparam TNodeType type restricted by a concept to be ObjectNodeType,
   * ArrayNodeType, or ValueNodeType so we can use perfect forwarding
   * @param node_data one of the valid node types
   */
  explicit inline TreeNode(const ObjectNodeType& node_data);
  explicit inline TreeNode(ObjectNodeType&& node_data);

  explicit inline TreeNode(const ArrayNodeType& node_data);
  explicit inline TreeNode(ArrayNodeType&& node_data);

  explicit inline TreeNode(const ValueNodeType& node_data);
  explicit inline TreeNode(ValueNodeType&& node_data);

  inline TreeNode& operator=(const ObjectNodeType& node_data);
  inline TreeNode& operator=(ObjectNodeType&& node_data);

  inline TreeNode& operator=(const ArrayNodeType& node_data);
  inline TreeNode& operator=(ArrayNodeType&& node_data);

  inline TreeNode& operator=(const ValueNodeType& node_data);
  inline TreeNode& operator=(ValueNodeType&& node_data);

  template <ValidValueNodeTypeValueType TValueType>
  TreeNode& operator=(TValueType&& value) noexcept(
      !SatisfiesStringType<TValueType>);

  /**
   * @brief Construct a TreeNode with the proper alternative given the tag
   *
   * NodeTypeTag::Object, NodeTypeTag::Array, or NodeTypeTag::Value
   *
   * @tparam tag tag corresponding with one of the node types
   */
  explicit inline TreeNode(NodeTypeTag tag);

  /**
   * @brief TryGet type tag for this tree node
   * @return type tag
   */
  [[nodiscard]] inline NodeTypeTag Tag() const noexcept;

  /**
   * @brief Try to get the requested type from this TreeNode
   * @tparam TRequestedType the type requested
   * @return The requested type if it is the type being held, otherwise Error
   */
  template <typename TRequestedType>
  [[nodiscard]] auto Has() const noexcept -> bool;

  /**
   * @brief Is this node holding an ObjectNodeType
   * @return true if holding an ObjectNodeType, otherwise false
   */
  [[nodiscard]] inline auto HasObject() const noexcept -> bool;

  /**
   * @brief Is this node holding an ArrayNodeType
   * @return true if holding an ArrayNodeType, otherwise false
   */
  [[nodiscard]] inline auto HasArray() const noexcept -> bool;

  /**
   * @brief Is this node holding an ValueNodeType
   * @return true if holding an ValueNodeType, otherwise false
   */
  [[nodiscard]] inline auto HasValue() const noexcept -> bool;

  /**
   * @brief Try to get the requested type from this TreeNode
   * @tparam TRequestedType the type requested
   * @return The requested type if it is the type being held, otherwise Error
   */
  template <typename TRequestedType>
  [[nodiscard]] auto TryGet() const -> expected<TRequestedType, Error>;

  /**
   * @brief Try to get an ObjectNodeType from this node
   * @return ObjectNodeType if holding an ObjectNodeType, otherwise Error
   */
  [[nodiscard]] inline auto TryGetObject() const
      -> expected<ObjectNodeType, Error>;

  /**
   * @brief Try to get an ArrayNodeType from this node
   * @return ArrayNodeType if holding an ArrayNodeType, otherwise Error
   */
  [[nodiscard]] inline auto TryGetArray() const
      -> expected<ArrayNodeType, Error>;

  /**
   * @brief Try to get an ValueNodeType from this node
   * @return ValueNodeType if holding an ValueNodeType, otherwise Error
   */
  [[nodiscard]] inline auto TryGetValue() const
      -> expected<ValueNodeType, Error>;

  /**
   * @brief Try to get the requested type from this TreeNode
   * @tparam TRequestedType the type requested
   * @return The requested type if it is the type being held or exception
   */
  template <typename TRequestedType>
  [[nodiscard]] auto Get() const -> const TRequestedType&;

  /**
   * @brief Try to get the requested type from this TreeNode
   * @tparam TRequestedType the type requested
   * @return The requested type if it is the type being held or exception
   */
  template <typename TRequestedType>
  [[nodiscard]] auto Get() -> TRequestedType&;

  /**
   * @brief Try to get an ObjectNodeType from this node
   * @return ObjectNodeType if holding an ObjectNodeType or exception
   */
  [[nodiscard]] inline auto GetObject() const -> const ObjectNodeType&;

  /**
   * @brief Try to get an ObjectNodeType from this node
   * @return ObjectNodeType if holding an ObjectNodeType or exception
   */
  [[nodiscard]] inline auto GetObject() -> ObjectNodeType&;

  /**
   * @brief Try to get an ArrayNodeType from this node
   * @return ArrayNodeType if holding an ArrayNodeType or exception
   */
  [[nodiscard]] inline auto GetArray() const -> const ArrayNodeType&;

  /**
   * @brief Try to get an ArrayNodeType from this node
   * @return ArrayNodeType if holding an ArrayNodeType or exception
   */
  [[nodiscard]] inline auto GetArray() -> ArrayNodeType&;

  /**
   * @brief Try to get an ValueNodeType from this node
   * @return ValueNodeType if holding an ValueNodeType or exception
   */
  [[nodiscard]] inline auto GetValue() -> ValueNodeType&;

  /**
   * @brief Try to get an ValueNodeType from this node
   * @return ValueNodeType if holding an ValueNodeType or exception
   */
  [[nodiscard]] inline auto GetValue() const -> const ValueNodeType&;

  /**
   * @brief Set this TreeNode to an TNodeType
   * @tparam TNodeType type restricted by a concept to be ObjectNodeType,
   * ArrayNodeType, or ValueNodeType so we can use perfect forwarding
   * @param node_data one of the valid node types
   */
  template <typename TNodeType>
  void Set(TNodeType&& node_data);

  /**
   * @brief Reset this node, optionally specifying a new default node type by
   * tag
   * @tparam TTag tag corresponding with one of the node types
   */
  template <NodeTypeTag TTag = NodeTypeTag::Object>
    requires(static_cast<std::uint8_t>(TTag) < 3)
  void Reset();

  /**
   * @brief Reset this node, optionally specifying a new default node type by
   * tag
   * @param tag tag corresponding with one of the node types
   */
  inline void Reset(NodeTypeTag tag);

  /**
   * @brief Visit a tree node with a visitor overload set
   * @tparam TCallables set of non final callable types
   * @param callables set of non final callables
   * @return the common return type of all callables provided
   */
  template <typename... TCallables>
  decltype(auto) Visit(TCallables&&... callables);

  /**
   * @brief Visit a tree node with a visitor overload set
   * @tparam TCallables set of non final callable types
   * @param callables set of non final callables
   * @return the common return type of all callables provided
   */
  template <typename... TCallables>
  decltype(auto) Visit(TCallables&&... callables) const;

  // Get If ?
  // Emplace ?

  [[nodiscard]] inline TreeNode& operator[](const KeyType& key);

  /**
   * @brief Equality compare this TreeNode to another
   * @return true if they are equal, otherwise false
   */
  [[nodiscard]] inline bool operator==(const TreeNode& other) const noexcept;

private:
  /**
   * @brief Based on a tag, create the corresponding node type
   *
   * This is effectively a static factory function
   *
   * @param tag tag corresponding with one of the node types
   */
  [[nodiscard]] static inline NodeType FromTag(NodeTypeTag tag);
  /**
   * @brief Based on a tag, create the corresponding node type
   *
   * This is effectively a static factory function
   *
   * @tparam TTag tag corresponding with one of the node types
   */
  template <NodeTypeTag TTag>
  [[nodiscard]] static inline auto FromTagTemplate();

  std::unique_ptr<NodeType> m_data_impl;
};

}  // namespace mguid

#include "datatree/node_types/node_types.inl"

namespace mguid {

template <typename TNodeType>
concept ValidNodeType =
    std::same_as<std::remove_cvref_t<TNodeType>, ObjectNodeType> ||
    std::same_as<std::remove_cvref_t<TNodeType>, ArrayNodeType> ||
    std::same_as<std::remove_cvref_t<TNodeType>, ValueNodeType>;

template <ValidValueNodeTypeValueType TValueType>
TreeNode& TreeNode::operator=(TValueType&& value) noexcept(
    !SatisfiesStringType<TValueType>) {
  if (!HasValue()) { Reset<NodeTypeTag::Value>(); }
  GetValue() = value;
  return *this;
}

template <typename TRequestedType>
auto TreeNode::Has() const noexcept -> bool {
  return std::holds_alternative<TRequestedType>(*m_data_impl);
}

template <typename TRequestedType>
auto TreeNode::TryGet() const -> expected<TRequestedType, Error> {
  if (auto* result = std::get_if<TRequestedType>(&(*m_data_impl));
      result != nullptr) {
    return *result;
  }
  return make_unexpected(Error{.category = Error::Category::BadAccess});
}

template <typename TRequestedType>
auto TreeNode::Get() const -> const TRequestedType& {
  return std::get<TRequestedType>(*m_data_impl);
}

template <typename TRequestedType>
auto TreeNode::Get() -> TRequestedType& {
  return std::get<TRequestedType>(*m_data_impl);
}

template <typename TNodeType>
void TreeNode::Set(TNodeType&& node_data) {
  *m_data_impl = std::forward<TNodeType>(node_data);
}

template <NodeTypeTag TTag>
  requires(static_cast<std::uint8_t>(TTag) < 3)
void TreeNode::Reset() {
  *m_data_impl = FromTagTemplate<TTag>();
}

template <typename... TCallables>
decltype(auto) TreeNode::Visit(TCallables&&... callables) {
  auto overload_set = Overload{std::forward<TCallables>(callables)...};
  return std::visit(overload_set, *m_data_impl);
}
template <typename... TCallables>
decltype(auto) TreeNode::Visit(TCallables&&... callables) const {
  auto overload_set = Overload{std::forward<TCallables>(callables)...};
  return std::visit(overload_set, *m_data_impl);
}

[[nodiscard]] inline NodeType TreeNode::FromTag(NodeTypeTag tag) {
  switch (tag) {
    case NodeTypeTag::Array:
      return {ArrayNodeType{}};
    case NodeTypeTag::Value:
      return {ValueNodeType{}};
    default:
      return {ObjectNodeType{}};
  }
}

template <NodeTypeTag TTag>
[[nodiscard]] inline auto TreeNode::FromTagTemplate() {
  if constexpr (TTag == NodeTypeTag::Array) {
    return ArrayNodeType{};
  } else if constexpr (TTag == NodeTypeTag::Value) {
    return ValueNodeType{};
  } else {
    return ObjectNodeType{};
  }
}

inline TreeNode::TreeNode()
    : m_data_impl{std::make_unique<NodeType>(ObjectNodeType{})} {}

inline TreeNode::TreeNode(const TreeNode& other)
    : m_data_impl{std::make_unique<NodeType>(*other.m_data_impl)} {}
inline TreeNode& TreeNode::operator=(const TreeNode& other) {
  if (&other != this) {
    m_data_impl = std::make_unique<NodeType>(*other.m_data_impl);
  }
  return *this;
}

inline TreeNode::TreeNode(TreeNode&&) noexcept = default;
inline TreeNode& TreeNode::operator=(TreeNode&&) noexcept = default;

inline TreeNode::TreeNode(const ObjectNodeType& node_data)
    : m_data_impl{std::make_unique<NodeType>(node_data)} {}
inline TreeNode::TreeNode(ObjectNodeType&& node_data)
    : m_data_impl{std::make_unique<NodeType>(node_data)} {}

inline TreeNode::TreeNode(const ArrayNodeType& node_data)
    : m_data_impl{std::make_unique<NodeType>(node_data)} {}
inline TreeNode::TreeNode(ArrayNodeType&& node_data)
    : m_data_impl{std::make_unique<NodeType>(node_data)} {}

inline TreeNode::TreeNode(const ValueNodeType& node_data)
    : m_data_impl{std::make_unique<NodeType>(node_data)} {}
inline TreeNode::TreeNode(ValueNodeType&& node_data)
    : m_data_impl{std::make_unique<NodeType>(node_data)} {}

inline TreeNode& TreeNode::operator=(const ObjectNodeType& node_data) {
  *m_data_impl = node_data;
  return *this;
}
inline TreeNode& TreeNode::operator=(ObjectNodeType&& node_data) {
  *m_data_impl = node_data;
  return *this;
}

inline TreeNode& TreeNode::operator=(const ArrayNodeType& node_data) {
  *m_data_impl = node_data;
  return *this;
}
inline TreeNode& TreeNode::operator=(ArrayNodeType&& node_data) {
  *m_data_impl = node_data;
  return *this;
}

inline TreeNode& TreeNode::operator=(const ValueNodeType& node_data) {
  *m_data_impl = node_data;
  return *this;
}
inline TreeNode& TreeNode::operator=(ValueNodeType&& node_data) {
  *m_data_impl = node_data;
  return *this;
}

inline TreeNode::TreeNode(NodeTypeTag tag)
    : m_data_impl{std::make_unique<NodeType>(FromTag(tag))} {}

inline NodeTypeTag TreeNode::Tag() const noexcept {
  switch (m_data_impl->index()) {
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

inline auto TreeNode::HasObject() const noexcept -> bool {
  return Has<ObjectNodeType>();
}
inline auto TreeNode::HasArray() const noexcept -> bool {
  return Has<ArrayNodeType>();
}
inline auto TreeNode::HasValue() const noexcept -> bool {
  return Has<ValueNodeType>();
}

inline auto TreeNode::TryGetObject() const -> expected<ObjectNodeType, Error> {
  return TryGet<ObjectNodeType>();
}
inline auto TreeNode::TryGetArray() const -> expected<ArrayNodeType, Error> {
  return TryGet<ArrayNodeType>();
}
inline auto TreeNode::TryGetValue() const -> expected<ValueNodeType, Error> {
  return TryGet<ValueNodeType>();
}

inline auto TreeNode::GetObject() const -> const ObjectNodeType& {
  return Get<ObjectNodeType>();
}
inline auto TreeNode::GetObject() -> ObjectNodeType& {
  return Get<ObjectNodeType>();
}
inline auto TreeNode::GetArray() const -> const ArrayNodeType& {
  return Get<ArrayNodeType>();
}
inline auto TreeNode::GetArray() -> ArrayNodeType& {
  return Get<ArrayNodeType>();
}
inline auto TreeNode::GetValue() -> ValueNodeType& {
  return Get<ValueNodeType>();
}
inline auto TreeNode::GetValue() const -> const ValueNodeType& {
  return Get<ValueNodeType>();
}

inline void TreeNode::Reset(NodeTypeTag tag) { *m_data_impl = FromTag(tag); }

inline TreeNode& TreeNode::operator[](const KeyType& key_or_idx) {
  return key_or_idx.Visit(
      [&](const StringKeyType& key) -> TreeNode& {
        auto& obj = std::get<ObjectNodeType>(*m_data_impl);
        auto& node = obj.TryEmplace(key, ObjectNodeType{}).first->second;
        return node;
      },
      [&](const IntegerKeyType& idx) -> TreeNode& {
        auto& arr = std::get<ArrayNodeType>(*m_data_impl);
        auto& node = arr[idx];
        return node;
      });
}

inline bool TreeNode::operator==(const TreeNode& other) const noexcept {
  return *m_data_impl == *other.m_data_impl;
}

inline TreeNode::~TreeNode() = default;

}  // namespace mguid

#endif  // DATATREE_TREE_NODE_HPP
