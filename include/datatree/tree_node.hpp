/**
 * @brief Declarations for TreeNode
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 *
 * @cond IGNORE_LICENSE
 *
 * MIT License
 *
 * Copyright (c) 2024 Matthew Guidry
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @endcond
 */

#ifndef DATATREE_TREE_NODE_HPP
#define DATATREE_TREE_NODE_HPP

#include <concepts>
#include <memory>
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
  /**
   * @brief
   * @tparam TConst
   */
  template <bool TConst = false>
  class UnsafeProxy {
  public:
    /**
     * @brief Delete Move/Copy Constructors/Assignment Operators
     */
    UnsafeProxy(const UnsafeProxy&) = delete;
    UnsafeProxy& operator=(const UnsafeProxy&) = delete;
    UnsafeProxy(UnsafeProxy&&) = delete;
    UnsafeProxy& operator=(UnsafeProxy&&) = delete;

    /**
     * @brief Try to get the requested type from this Unsafe Proxy TreeNode
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
     * @brief Get an ObjectNodeType from this node
     * @return reference to ObjectNodeType
     */
    [[nodiscard]] inline auto GetObject() const -> const ObjectNodeType&;

    /**
     * @brief Get an ObjectNodeType from this node
     * @return reference to ObjectNodeType
     */
    [[nodiscard]] inline auto GetObject() -> ObjectNodeType&;

    /**
     * @brief Get an ArrayNodeType from this node
     * @return reference to ArrayNodeType
     */
    [[nodiscard]] inline auto GetArray() const -> const ArrayNodeType&;

    /**
     * @brief Get an ArrayNodeType from this node
     * @return reference to ArrayNodeType
     */
    [[nodiscard]] inline auto GetArray() -> ArrayNodeType&;

    /**
     * @brief Get an ValueNodeType from this node
     * @return reference to ValueNodeType
     */
    [[nodiscard]] inline auto GetValue() const -> const ValueNodeType&;

    /**
     * @brief Get an ValueNodeType from this node
     * @return reference to ValueNodeType
     */
    [[nodiscard]] inline auto GetValue() -> ValueNodeType&;

    /**
     * @brief Get Null value from this TreeNode
     * @return Null value from this TreeNode
     */
    [[nodiscard]] inline auto GetNull() const -> const NullType&;

    /**
     * @brief Get Bool value from this TreeNode
     * @return Bool value from this TreeNode
     */
    [[nodiscard]] inline auto GetBool() const -> const BoolType&;

    /**
     * @brief Get Number value from this TreeNode
     * @return Number value from this TreeNode
     */
    [[nodiscard]] inline auto GetNumber() const -> const NumberType&;

    /**
     * @brief Get String value from this TreeNode
     * @return String value from this TreeNode
     */
    [[nodiscard]] inline auto GetString() const -> const std::string&;

    /**
     * @brief Get Null value from this TreeNode
     * @return Null value from this TreeNode
     */
    [[nodiscard]] inline auto GetNull() -> NullType&;

    /**
     * @brief Get Bool value from this TreeNode
     * @return Bool value from this TreeNode
     */
    [[nodiscard]] inline auto GetBool() -> BoolType&;

    /**
     * @brief Get Number value from this TreeNode
     * @return Number value from this TreeNode
     */
    [[nodiscard]] inline auto GetNumber() -> NumberType&;

    /**
     * @brief Get String value from this TreeNode
     * @return String value from this TreeNode
     */
    [[nodiscard]] inline auto GetString() -> std::string&;

  private:
    explicit UnsafeProxy(
        std::conditional_t<TConst, const TreeNode&, TreeNode&> ref)
        : m_node_ref{ref} {}

    friend TreeNode;
    std::conditional_t<TConst, const TreeNode&, TreeNode&> m_node_ref;
  };

public:
  /**
   * @brief Default construct a TreeNode
   */
  inline TreeNode();

  /**
   * @brief Copy construct a TreeNode
   */
  inline TreeNode(const TreeNode&);
  /**
   * @brief Move construct a TreeNode
   */
  inline TreeNode(TreeNode&&) noexcept;
  /**
   * @brief Copy assign a TreeNode
   * @return reference to this TreeNode
   */
  inline TreeNode& operator=(const TreeNode&);
  /**
   * @brief Move assign a TreeNode
   * @return reference to this TreeNode
   */
  inline TreeNode& operator=(TreeNode&&) noexcept;

  /**
   * @brief Destroy a TreeNode
   */
  inline ~TreeNode();

  /**
   * @brief Construct a TreeNode from an ObjectNodeType
   * @param node_data an ObjectNodeType
   */
  explicit inline TreeNode(const ObjectNodeType& node_data);

  /**
   * @brief Construct a TreeNode from an ObjectNodeType
   * @param node_data an ObjectNodeType
   */
  explicit inline TreeNode(ObjectNodeType&& node_data);

  /**
   * @brief Construct a TreeNode from an ArrayNodeType
   * @param node_data an ArrayNodeType
   */
  explicit inline TreeNode(const ArrayNodeType& node_data);

  /**
   * @brief Construct a TreeNode from an ArrayNodeType
   * @param node_data an ArrayNodeType
   */
  explicit inline TreeNode(ArrayNodeType&& node_data);

  /**
   * @brief Construct a TreeNode from an ValueNodeType
   * @param node_data an ValueNodeType
   */
  explicit inline TreeNode(const ValueNodeType& node_data);
  /**
   * @brief Construct a TreeNode from an ValueNodeType
   * @param node_data an ValueNodeType
   */
  explicit inline TreeNode(ValueNodeType&& node_data);

  /**
   * @brief Construct from a value that satisfies ValidValueNodeTypeValueType
   * @tparam TValueType type of value that satisfies ValidValueNodeTypeValueType
   * @param value value to use to construct inner value node
   */
  template <ValidValueNodeTypeValueType TValueType>
  explicit TreeNode(TValueType&& value);

  /**
   * @brief Copy assign a TreeNode from an ObjectNodeType
   * @param node_data an ObjectNodeType
   * @return reference to this TreeNode
   */
  inline TreeNode& operator=(const ObjectNodeType& node_data);
  /**
   * @brief Move assign a TreeNode from an ObjectNodeType
   * @param node_data an ObjectNodeType
   * @return reference to this TreeNode
   */
  inline TreeNode& operator=(ObjectNodeType&& node_data);
  /**
   * @brief Copy assign a TreeNode from an ArrayNodeType
   * @param node_data an ArrayNodeType
   * @return reference to this TreeNode
   */
  inline TreeNode& operator=(const ArrayNodeType& node_data);
  /**
   * @brief Move assign a TreeNode from an ArrayNodeType
   * @param node_data an ArrayNodeType
   * @return reference to this TreeNode
   */
  inline TreeNode& operator=(ArrayNodeType&& node_data);
  /**
   * @brief Copy assign a TreeNode from an ValueNodeType
   * @param node_data an ValueNodeType
   * @return reference to this TreeNode
   */
  inline TreeNode& operator=(const ValueNodeType& node_data);
  /**
   * @brief Move assign a TreeNode from an ValueNodeType
   * @param node_data an ValueNodeType
   * @return reference to this TreeNode
   */
  inline TreeNode& operator=(ValueNodeType&& node_data);

  /**
   * @brief Assign a value that satisfies ValidValueNodeTypeValueType to this
   *
   * If this TreeNode is not a ValueNodeType, reset it to ValueNodeType then
   * assign the value
   *
   * @tparam TValueType type of value that satisfies ValidValueNodeTypeValueType
   * @param value value to assign
   * @return reference to this TreeNode
   */
  template <ValidValueNodeTypeValueType TValueType>
  TreeNode& operator=(TValueType&& value);

  /**
   * @brief Construct a TreeNode with the proper alternative given the tag
   *
   * NodeTypeTag::Object, NodeTypeTag::Array, or NodeTypeTag::Value
   *
   * @tparam tag tag corresponding with one of the node types
   */
  explicit inline TreeNode(NodeTypeTag tag);

  /**
   * @brief Get type tag for this tree node
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
   * @brief Check if this TreeNode is holding a ValueNodeType and if it is Null
   * type
   * @return
   */
  [[nodiscard]] inline auto HasNull() const noexcept -> bool;
  /**
   * @brief Check if this TreeNode is holding a ValueNodeType and if it is
   * Boolean type
   * @return
   */
  [[nodiscard]] inline auto HasBool() const noexcept -> bool;
  /**
   * @brief Check if this TreeNode is holding a ValueNodeType and if it is
   * Number type
   * @return
   */
  [[nodiscard]] inline auto HasNumber() const noexcept -> bool;
  /**
   * @brief Check if this TreeNode is holding a ValueNodeType and if it is
   * String type
   * @return
   */
  [[nodiscard]] inline auto HasString() const noexcept -> bool;

  /**
   * @brief Try to get the requested type from this TreeNode
   * @tparam TRequestedType the type requested
   * @return The requested type if it is the type being held, otherwise Error
   */
  template <typename TRequestedType>
  [[nodiscard]] auto TryGet() const -> RefExpected<const TRequestedType, Error>;

  /**
   * @brief Try to get the requested type from this TreeNode
   * @tparam TRequestedType the type requested
   * @return The requested type if it is the type being held, otherwise Error
   */
  template <typename TRequestedType>
  [[nodiscard]] auto TryGet() -> RefExpected<TRequestedType, Error>;

  /**
   * @brief Try to get an ObjectNodeType from this node
   * @return ObjectNodeType if holding an ObjectNodeType, otherwise Error
   */
  [[nodiscard]] inline auto TryGetObject() const
      -> RefExpected<const ObjectNodeType, Error>;

  /**
   * @brief Try to get an ArrayNodeType from this node
   * @return ArrayNodeType if holding an ArrayNodeType, otherwise Error
   */
  [[nodiscard]] inline auto TryGetArray() const
      -> RefExpected<const ArrayNodeType, Error>;

  /**
   * @brief Try to get an ValueNodeType from this node
   * @return ValueNodeType if holding an ValueNodeType, otherwise Error
   */
  [[nodiscard]] inline auto TryGetValue() const
      -> RefExpected<const ValueNodeType, Error>;

  /**
   * @brief Try to get an ObjectNodeType from this node
   * @return ObjectNodeType if holding an ObjectNodeType, otherwise Error
   */
  [[nodiscard]] inline auto TryGetObject()
      -> RefExpected<ObjectNodeType, Error>;

  /**
   * @brief Try to get an ArrayNodeType from this node
   * @return ArrayNodeType if holding an ArrayNodeType, otherwise Error
   */
  [[nodiscard]] inline auto TryGetArray() -> RefExpected<ArrayNodeType, Error>;

  /**
   * @brief Try to get an ValueNodeType from this node
   * @return ValueNodeType if holding an ValueNodeType, otherwise Error
   */
  [[nodiscard]] inline auto TryGetValue() -> RefExpected<ValueNodeType, Error>;

  /**
   * @brief Try to get the requested type from this TreeNode
   *
   * TODO: Move to UnsafeProxy
   *
   * @tparam TRequestedType the type requested
   * @return The requested type if it is the type being held or exception
   */
  template <typename TRequestedType>
  [[nodiscard]] auto Get() const -> const TRequestedType&;

  /**
   * @brief Try to get the requested type from this TreeNode
   *
   * TODO: Move to UnsafeProxy
   *
   * @tparam TRequestedType the type requested
   * @return The requested type if it is the type being held or exception
   */
  template <typename TRequestedType>
  [[nodiscard]] auto Get() -> TRequestedType&;

  /**
   * @brief Get an ObjectNodeType from this node
   *
   * TODO: Move to UnsafeProxy
   *
   * @return reference to ObjectNodeType
   */
  [[nodiscard]] inline auto GetObject() const -> const ObjectNodeType&;

  /**
   * @brief Get an ObjectNodeType from this node
   *
   * TODO: Move to UnsafeProxy
   *
   * @return reference to ObjectNodeType
   */
  [[nodiscard]] inline auto GetObject() -> ObjectNodeType&;

  /**
   * @brief Get an ArrayNodeType from this node
   *
   * TODO: Move to UnsafeProxy
   *
   * @return reference to ArrayNodeType
   */
  [[nodiscard]] inline auto GetArray() const -> const ArrayNodeType&;

  /**
   * @brief Get an ArrayNodeType from this node
   *
   * TODO: Move to UnsafeProxy
   *
   * @return reference to ArrayNodeType
   */
  [[nodiscard]] inline auto GetArray() -> ArrayNodeType&;

  /**
   * @brief Get an ValueNodeType from this node
   *
   * TODO: Move to UnsafeProxy
   *
   * @return reference to ValueNodeType
   */
  [[nodiscard]] inline auto GetValue() const -> const ValueNodeType&;

  /**
   * @brief Get an ValueNodeType from this node
   *
   * TODO: Move to UnsafeProxy
   *
   * @return reference to ValueNodeType
   */
  [[nodiscard]] inline auto GetValue() -> ValueNodeType&;

  /**
   * @brief Get Null value from this TreeNode
   *
   * TODO: Move to UnsafeProxy
   *
   * @return Null value from this TreeNode
   */
  [[nodiscard]] inline auto GetNull() const -> const NullType&;

  /**
   * @brief Get Bool value from this TreeNode
   *
   * TODO: Move to UnsafeProxy
   *
   * @return Bool value from this TreeNode
   */
  [[nodiscard]] inline auto GetBool() const -> const BoolType&;

  /**
   * @brief Get Number value from this TreeNode
   *
   * TODO: Move to UnsafeProxy
   *
   * @return Number value from this TreeNode
   */
  [[nodiscard]] inline auto GetNumber() const -> const NumberType&;

  /**
   * @brief Get String value from this TreeNode
   *
   * TODO: Move to UnsafeProxy
   *
   * @return String value from this TreeNode
   */
  [[nodiscard]] inline auto GetString() const -> const std::string&;

  /**
   * @brief Get Null value from this TreeNode
   *
   * TODO: Move to UnsafeProxy
   *
   * @return Null value from this TreeNode
   */
  [[nodiscard]] inline auto GetNull() -> NullType&;

  /**
   * @brief Get Bool value from this TreeNode
   *
   * TODO: Move to UnsafeProxy
   *
   * @return Bool value from this TreeNode
   */
  [[nodiscard]] inline auto GetBool() -> BoolType&;

  /**
   * @brief Get Number value from this TreeNode
   *
   * TODO: Move to UnsafeProxy
   *
   * @return Number value from this TreeNode
   */
  [[nodiscard]] inline auto GetNumber() -> NumberType&;

  /**
   * @brief Get String value from this TreeNode
   *
   * TODO: Move to UnsafeProxy
   *
   * @return String value from this TreeNode
   */
  [[nodiscard]] inline auto GetString() -> std::string&;

  /**
   * @brief Try to get NullType value from this TreeNode
   * @return NullType value from this TreeNode
   */
  [[nodiscard]] inline auto TryGetNull() const
      -> RefExpected<const NullType, Error>;

  /**
   * @brief Try to get boolean value from this node
   * @return boolean value from this node
   */
  [[nodiscard]] inline auto TryGetBool() const
      -> RefExpected<const BoolType, Error>;

  /**
   * @brief Try to get integer value from this node
   * @return integer value from this node
   */
  [[nodiscard]] inline auto TryGetNumber() const
      -> RefExpected<const NumberType, Error>;

  /**
   * @brief Try to get string value from this node
   * @return string value from this node
   */
  [[nodiscard]] inline auto TryGetString() const
      -> RefExpected<const StringType, Error>;

  /**
   * @brief Try to get Null value from this TreeNode
   * @return Null value from this TreeNode
   */
  [[nodiscard]] inline auto TryGetNull() -> RefExpected<NullType, Error>;

  /**
   * @brief Try to get Bool value from this TreeNode
   * @return Bool value from this TreeNode
   */
  [[nodiscard]] inline auto TryGetBool() -> RefExpected<BoolType, Error>;

  /**
   * @brief Try to get Number value from this TreeNode
   * @return Number value from this TreeNode
   */
  [[nodiscard]] inline auto TryGetNumber() -> RefExpected<NumberType, Error>;

  /**
   * @brief Try to get String value from this TreeNode
   * @return String value from this TreeNode
   */
  [[nodiscard]] inline auto TryGetString() -> RefExpected<StringType, Error>;

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

  /**
   * @brief Get a reference to the TreeNode that is mapped to the key equivalent
   * to `key_or_idx`
   *
   * If an TreeNode corresponding to key in the path is not the correct type for
   * the key or does not exist, reset or create that node
   *
   * @param key_or_idx the key of the TreeNode to find
   * @return A reference to the requested element
   */
  inline auto operator[](const KeyOrIdxType& key_or_idx) -> TreeNode&;

  /**
   * @brief Get a reference to the TreeNode that is mapped to the key/idx
   * equivalent to `key_or_idx`
   *
   * TODO: Move to UnsafeProxy
   *
   * @param key_or_idx the key/idx of the TreeNode to find
   * @return A reference to the requested element
   */
  [[nodiscard]] inline auto operator[](const KeyOrIdxType& key_or_idx) const
      -> const TreeNode&;

  /**
   * @brief Equality compare this TreeNode to another
   * @return true if they are equal, otherwise false
   */
  [[nodiscard]] inline bool operator==(const TreeNode& other) const noexcept;

  /**
   * @brief Erase TreeNode that is mapped to the key/idx or value equivalent to
   * `key_or_idx`
   * @param key_or_idx the key/idx of the TreeNode to erase
   * @return true if element was removed, otherwise false
   */
  inline bool Erase(const KeyOrIdxType& key_or_idx);

  /**
   * @brief Use the unsafe API within a lambda function
   * @tparam TFunc type of function
   * @param func unsafe block function
   */
  template <typename TFunc>
    requires(std::is_invocable_r_v<void, TFunc, UnsafeProxy<true>>)
  void Unsafe(TFunc&& func);

  /**
   * @brief Use the unsafe API within a lambda function
   * @tparam TFunc type of function
   * @param func unsafe block function
   */
  template <typename TFunc>
    requires(std::is_invocable_r_v<void, TFunc, UnsafeProxy<true>>)
  void Unsafe(TFunc&& func) const;

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
TreeNode::TreeNode(TValueType&& value)
    : m_data_impl{std::make_unique<NodeType>(
          ValueNodeType{std::forward<TValueType>(value)})} {}

template <ValidValueNodeTypeValueType TValueType>
TreeNode& TreeNode::operator=(TValueType&& value) {
  if (!HasValue()) { Reset<NodeTypeTag::Value>(); }
  GetValue() = value;
  return *this;
}

template <typename TRequestedType>
auto TreeNode::Has() const noexcept -> bool {
  return std::holds_alternative<TRequestedType>(*m_data_impl);
}

template <typename TRequestedType>
auto TreeNode::TryGet() const -> RefExpected<const TRequestedType, Error> {
  if (auto* result = std::get_if<TRequestedType>(&(*m_data_impl));
      result != nullptr) {
    return *result;
  }
  return make_unexpected(Error{.category = Error::Category::BadAccess});
}

template <typename TRequestedType>
auto TreeNode::TryGet() -> RefExpected<TRequestedType, Error> {
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

template <typename TFunc>
  requires(std::is_invocable_r_v<void, TFunc, TreeNode::UnsafeProxy<true>>)
void TreeNode::Unsafe(TFunc&& func) {
  std::invoke(std::forward<TFunc>(func), UnsafeProxy{*this});
}

template <typename TFunc>
  requires(std::is_invocable_r_v<void, TFunc, TreeNode::UnsafeProxy<true>>)
void TreeNode::Unsafe(TFunc&& func) const {
  std::invoke(std::forward<TFunc>(func), UnsafeProxy<true>{*this});
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

inline auto TreeNode::HasNull() const noexcept -> bool {
  return HasValue() && GetValue().HasNull();
}
inline auto TreeNode::HasBool() const noexcept -> bool {
  return HasValue() && GetValue().HasBool();
}
inline auto TreeNode::HasNumber() const noexcept -> bool {
  return HasValue() && GetValue().HasNumber();
}
inline auto TreeNode::HasString() const noexcept -> bool {
  return HasValue() && GetValue().HasString();
}

inline auto TreeNode::TryGetObject() const
    -> RefExpected<const ObjectNodeType, Error> {
  return TryGet<ObjectNodeType>();
}
inline auto TreeNode::TryGetArray() const
    -> RefExpected<const ArrayNodeType, Error> {
  return TryGet<ArrayNodeType>();
}
inline auto TreeNode::TryGetValue() const
    -> RefExpected<const ValueNodeType, Error> {
  return TryGet<ValueNodeType>();
}

inline auto TreeNode::TryGetObject() -> RefExpected<ObjectNodeType, Error> {
  return TryGet<ObjectNodeType>();
}
inline auto TreeNode::TryGetArray() -> RefExpected<ArrayNodeType, Error> {
  return TryGet<ArrayNodeType>();
}
inline auto TreeNode::TryGetValue() -> RefExpected<ValueNodeType, Error> {
  return TryGet<ValueNodeType>();
}

inline auto TreeNode::GetNull() const -> const NullType& {
  return GetValue().GetNull();
}
inline auto TreeNode::GetBool() const -> const BoolType& {
  return GetValue().GetBool();
}
inline auto TreeNode::GetNumber() const -> const NumberType& {
  return GetValue().GetNumber();
}
inline auto TreeNode::GetString() const -> const std::string& {
  return GetValue().GetString();
}

inline auto TreeNode::GetNull() -> NullType& { return GetValue().GetNull(); }
inline auto TreeNode::GetBool() -> BoolType& { return GetValue().GetBool(); }
inline auto TreeNode::GetNumber() -> NumberType& {
  return GetValue().GetNumber();
}
inline auto TreeNode::GetString() -> std::string& {
  return GetValue().GetString();
}

inline auto TreeNode::TryGetNull() const -> RefExpected<const NullType, Error> {
  if (!HasValue()) {
    return make_unexpected(Error{.category = Error::Category::BadAccess});
  }
  return GetValue().TryGetNull();
}
inline auto TreeNode::TryGetBool() const -> RefExpected<const BoolType, Error> {
  if (!HasValue()) {
    return make_unexpected(Error{.category = Error::Category::BadAccess});
  }
  return GetValue().TryGetBool();
}
inline auto TreeNode::TryGetNumber() const
    -> RefExpected<const NumberType, Error> {
  if (!HasValue()) {
    return make_unexpected(Error{.category = Error::Category::BadAccess});
  }
  return GetValue().TryGetNumber();
}
inline auto TreeNode::TryGetString() const
    -> RefExpected<const StringType, Error> {
  if (!HasValue()) {
    return make_unexpected(Error{.category = Error::Category::BadAccess});
  }
  return GetValue().TryGetString();
}

inline auto TreeNode::TryGetNull() -> RefExpected<NullType, Error> {
  if (!HasValue()) {
    return make_unexpected(Error{.category = Error::Category::BadAccess});
  }
  return GetValue().TryGetNull();
}
inline auto TreeNode::TryGetBool() -> RefExpected<BoolType, Error> {
  if (!HasValue()) {
    return make_unexpected(Error{.category = Error::Category::BadAccess});
  }
  return GetValue().TryGetBool();
}
inline auto TreeNode::TryGetNumber() -> RefExpected<NumberType, Error> {
  if (!HasValue()) {
    return make_unexpected(Error{.category = Error::Category::BadAccess});
  }
  return GetValue().TryGetNumber();
}
inline auto TreeNode::TryGetString() -> RefExpected<StringType, Error> {
  if (!HasValue()) {
    return make_unexpected(Error{.category = Error::Category::BadAccess});
  }
  return GetValue().TryGetString();
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
inline auto TreeNode::GetValue() const -> const ValueNodeType& {
  return Get<ValueNodeType>();
}
inline auto TreeNode::GetValue() -> ValueNodeType& {
  return Get<ValueNodeType>();
}

inline void TreeNode::Reset(NodeTypeTag tag) { *m_data_impl = FromTag(tag); }

inline auto TreeNode::operator[](const KeyOrIdxType& key_or_idx) -> TreeNode& {
  return key_or_idx.Visit(
      [&](const StringKeyType& key) -> TreeNode& {
        if (!HasObject()) { *m_data_impl = ObjectNodeType{}; }
        return std::get<ObjectNodeType>(*m_data_impl)[key];
      },
      [&](const IntegerKeyType& idx) -> TreeNode& {
        if (!HasArray()) { *m_data_impl = ArrayNodeType{}; }
        return std::get<ArrayNodeType>(*m_data_impl)[idx];
      });
}

inline auto TreeNode::operator[](const KeyOrIdxType& key_or_idx) const
    -> const TreeNode& {
  static constexpr auto as_const = [](const auto& item) -> const auto& {
    return item;
  };
  return key_or_idx.Visit(
      [&](const StringKeyType& key) -> const TreeNode& {
        return as_const(std::get<ObjectNodeType>(*m_data_impl)).At(key);
      },
      [&](const IntegerKeyType& idx) -> const TreeNode& {
        return as_const(std::get<ArrayNodeType>(*m_data_impl)).At(idx);
      });
}

inline bool TreeNode::Erase(const KeyOrIdxType& key_or_idx) {
  return key_or_idx.Visit(
      [&](const StringKeyType& key) -> bool {
        if (!HasObject()) { return false; }
        auto& obj = std::get<ObjectNodeType>(*m_data_impl);
        return static_cast<bool>(obj.Erase(key));
      },
      [&](const IntegerKeyType& idx) -> bool {
        if (!HasArray()) { return false; }
        auto& arr = std::get<ArrayNodeType>(*m_data_impl);
        if (idx >= arr.Size()) { return false; }
        arr.Erase(std::next(arr.Begin(),
                            static_cast<ArrayNodeType::DifferenceType>(idx)));
        return true;
      });
}

inline bool TreeNode::operator==(const TreeNode& other) const noexcept {
  return *m_data_impl == *other.m_data_impl;
}

inline TreeNode::~TreeNode() = default;

}  // namespace mguid

#endif  // DATATREE_TREE_NODE_HPP
