/**
 * @brief Declarations for object node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_OBJECT_NODE_TYPE_HPP
#define DATATREE_OBJECT_NODE_TYPE_HPP

#include <string>

// Oh no, horrible bad map type
// Could use martinus/robin-hood-hashing unordered_node_map which provides
// similar reference and pointer stability as std::unordered_map but it is no
// longer being developed in favor of another project: martinus/unordered_dense
// problems with unordered_dense while I sit here at midnight is that I don't
// know if I will need strong reference stability because I haven't
// written any code yet. So for now I will just use std::unordered_map.
// I will eventually create some benchmarks and compare at least
// std::unordered_map vs robin-hood-hashing::unordered_node_map vs
// folly::F14NodeMap
#include <string>
#include <unordered_map>

#include "datatree/common.hpp"
#include "datatree/error/error_type.hpp"

namespace mguid {

class ObjectNodeType {
  using MapType = std::unordered_map<std::string, uuid>;
  using ValueType = MapType::value_type;
  using KeyType = MapType::key_type;
  using MappedType = MapType::mapped_type;
  using SizeType = MapType::size_type;
  using Iterator = MapType::iterator;
  using ConstIterator = MapType::const_iterator;

public:
  /**
   * @brief Default construct an ObjectNodeType
   */
  ObjectNodeType() = default;

  /**
   * @brief Explicit defaults for copy/move construction/assignment
   */
  ObjectNodeType(const ObjectNodeType&) = default;
  ObjectNodeType(ObjectNodeType&&) noexcept = default;
  ObjectNodeType& operator=(const ObjectNodeType&) = default;
  ObjectNodeType& operator=(ObjectNodeType&&) noexcept = default;

  /**
   * @brief Construct an ObjectNodeType from an existing map
   * @param init_mapping an initial mapping to initialize this with
   */
  explicit ObjectNodeType(MapType init_mapping)
      : m_key_id_mapping{std::move(init_mapping)} {}

  /**
   * @brief Try to get a copy of the node id with the specified key
   * @param key the key of the node id to find
   * @return the associated node id if the key it exists; otherwise BadAccess
   * error
   */
  [[nodiscard]] auto Get(const KeyType& key) const
      -> expected<MappedType, Error> {
    if (auto iter = m_key_id_mapping.find(key);
        iter != m_key_id_mapping.end()) {
      return iter->second;
    }
    return make_unexpected(Error{.category = Error::Status::BadAccess});
  }

  /**
   * @brief Try to get a copy of the node id with the specified key, or return
   * the provided default value
   * @tparam TDefault type of the default value, must be convertible to uuid
   * @param key the key of the node id to find
   * @param default_value the default value to return if the key is not found
   * @return the associated node id if the key it exists, otherwise the provided
   * default value
   */
  template <typename TDefault>
  [[nodiscard]] auto GetOr(const KeyType& key, TDefault&& default_value) const {
    if (auto iter = m_key_id_mapping.find(key);
        iter != m_key_id_mapping.end()) {
      return iter->second;
    }
    return static_cast<MappedType>(std::forward<TDefault>(default_value));
  }

  /**
   * @brief Erase all node ids from this ObjectNodeType
   */
  void Clear() noexcept { m_key_id_mapping.clear(); }

  /**
   * @brief Insert value if the container doesn't already contain an element
   * with an equivalent key
   * @param value TODO
   * @return
   */
  std::pair<Iterator, bool> Insert(const ValueType& value) {
    return m_key_id_mapping.insert(value);
  }

  /**
   * @brief
   * @param value TODO
   * @return
   */
  std::pair<Iterator, bool> Insert(ValueType&& value) {
    return m_key_id_mapping.insert(value);
  }

  /**
   * @brief
   * @param value TODO
   * @return
   */
  Iterator Insert(ConstIterator hint, const ValueType& value) {
    return m_key_id_mapping.insert(hint, value);
  }

  /**
   * @brief
   * @param value TODO
   * @return
   */
  Iterator Insert(ConstIterator hint, ValueType&& value) {
    return m_key_id_mapping.insert(hint, value);
  }

  /**
   * @brief TODO
   * @tparam TConvertibleToValueType
   * @param value
   * @return
   */
  template <typename TConvertibleToValueType>
  std::pair<Iterator, bool> Insert(TConvertibleToValueType&& value) {
    return m_key_id_mapping.insert(
        std::forward<TConvertibleToValueType>(value));
  }

  /**
   * @brief TODO
   * @tparam TConvertibleToValueType
   * @param hint
   * @param value
   * @return
   */
  template <typename TConvertibleToValueType>
  Iterator Insert(ConstIterator hint, TConvertibleToValueType&& value) {
    return m_key_id_mapping.insert(
        std::forward<TConvertibleToValueType>(hint, value));
  }

  /**
   * @brief TODO
   * @param init_list
   */
  void Insert(std::initializer_list<ValueType> init_list) {
    m_key_id_mapping.insert(init_list);
  }

  /**
   * @brief TODO
   * @tparam TValue
   * @param key
   * @param obj
   * @return
   */
  template <typename TValue>
  std::pair<Iterator, bool> InsertOrAssign(const KeyType& key, TValue&& obj) {
    return m_key_id_mapping.insert_or_assign(key, std::forward<TValue>(obj));
  }

  /**
   * @brief TODO
   * @tparam TValue
   * @param key
   * @param obj
   * @return
   */
  template <typename TValue>
  std::pair<Iterator, bool> InsertOrAssign(KeyType&& key, TValue&& obj) {
    return m_key_id_mapping.insert_or_assign(key, std::forward<TValue>(obj));
  }

  /**
   * @brief  TODO
   * @tparam TValue
   * @param hint
   * @param key
   * @param obj
   * @return
   */
  template <typename TValue>
  Iterator InsertOrAssign(ConstIterator hint, const KeyType& key,
                          TValue&& obj) {
    return m_key_id_mapping.insert_or_assign(hint, key,
                                             std::forward<TValue>(obj));
  }

  /**
   * @brief  TODO
   * @tparam TValue
   * @param hint
   * @param key
   * @param obj
   * @return
   */
  template <typename TValue>
  Iterator InsertOrAssign(ConstIterator hint, KeyType&& key, TValue&& obj) {
    return m_key_id_mapping.insert_or_assign(hint, key,
                                             std::forward<TValue>(obj));
  }

  /**
   * @brief  TODO
   * @tparam TArgs
   * @param args
   * @return
   */
  template <typename... TArgs>
  std::pair<Iterator, bool> Emplace(TArgs&&... args) {
    return m_key_id_mapping.emplace(std::forward<TArgs>(args)...);
  }

  /**
   * @brief TODO
   * @tparam TArgs
   * @param hint
   * @param args
   * @return
   */
  template <typename... TArgs>
  Iterator EmplaceHint(ConstIterator hint, TArgs&&... args) {
    return m_key_id_mapping.emplace_hint(std::forward<TArgs>(args)...);
  }

  /**
   * @brief TODO
   * @tparam TArgs
   * @param key
   * @param args
   * @return
   */
  template <typename... TArgs>
  std::pair<Iterator, bool> TryEmplace(const KeyType& key, TArgs&&... args) {
    return m_key_id_mapping.try_emplace(key, std::forward<TArgs>(args)...);
  }

  /**
   * @brief TODO
   * @tparam TArgs
   * @param key
   * @param args
   * @return
   */
  template <typename... TArgs>
  std::pair<Iterator, bool> TryEmplace(KeyType&& key, TArgs&&... args) {
    return m_key_id_mapping.try_emplace(key, std::forward<TArgs>(args)...);
  }

  /**
   * @brief TODO
   * @tparam TArgs
   * @param hint
   * @param key
   * @param args
   * @return
   */
  template <typename... TArgs>
  Iterator TryEmplace(ConstIterator hint, const KeyType& key, TArgs&&... args) {
    return m_key_id_mapping.try_emplace(hint, key,
                                        std::forward<TArgs>(args)...);
  }

  /**
   * @brief TODO
   * @tparam TArgs
   * @param hint
   * @param key
   * @param args
   * @return
   */
  template <typename... TArgs>
  Iterator TryEmplace(ConstIterator hint, KeyType&& key, TArgs&&... args) {
    return m_key_id_mapping.try_emplace(hint, key,
                                        std::forward<TArgs>(args)...);
  }

  /**
   * @brief TODO
   * @param pos
   * @return
   */
  Iterator Erase(Iterator pos) {
    return m_key_id_mapping.erase(pos);
  }

  /**
   * @brief TODO
   * @param pos
   * @return
   */
  Iterator Erase(ConstIterator pos) {
    return m_key_id_mapping.erase(pos);
  }

  /**
   * @brief TODO
   * @param first
   * @param last
   * @return
   */
  Iterator Erase(ConstIterator first, ConstIterator last) {
    return m_key_id_mapping.erase(first, last);
  }

  /**
   * @brief TODO
   * @param key
   * @return
   */
  SizeType Erase(const KeyType& key) {
    return m_key_id_mapping.erase(key);
  }

  // TODO: BEGIN MONADIC OPERATIONS
  // TODO: END MONADIC OPERATIONS

  /**
   * @brief Check if there is a key equivalent to the provided key in this
   * ObjectNodeType
   * @param key key value of the node id to search for
   * @return true if there is such a node id, otherwise false
   */
  [[nodiscard]] auto Contains(const KeyType& key) const -> bool {
    return m_key_id_mapping.contains(key);
  }

  /**
   * @brief Returns the number of children in this ObjectNodeType
   * @return the number of children in this ObjectNodeType
   */
  [[nodiscard]] auto Size() const noexcept -> SizeType {
    return m_key_id_mapping.size();
  }

  /**
   * @brief Check if this ObjectNodeType is empty
   * @return true if empty, otherwise false
   */
  [[nodiscard]] auto Empty() const noexcept -> bool {
    return m_key_id_mapping.empty();
  }

  // TODO: BEGIN ALGORITHMS
  /**
   * @brief Find a node id with key equivalent to the provided key
   * @param key key value of the node id to search for
   * @return An iterator to the requested node id. If no such node id is found,
   * past-the-end (see end()) iterator is returned.
   */
  [[nodiscard]] auto Find(const KeyType& key) -> Iterator {
    return m_key_id_mapping.find(key);
  }

  /**
   * @brief Find a node id with key equivalent to the provided key
   * @param key key value of the node id to search for
   * @return An iterator to the requested node id. If no such node id is found,
   * past-the-end (see end()) iterator is returned.
   */
  [[nodiscard]] auto Find(const KeyType& key) const -> ConstIterator {
    return m_key_id_mapping.find(key);
  }
  // TODO: END ALGORITHMS

  // TODO: BEGIN INSERTIONS
  // TODO: END INSERTIONS

  // TODO: BEGIN ITERATION
  // TODO: END ITERATION

  // TODO: BEGIN COMPARISON
  // TODO: END COMPARISON
private:
  MapType m_key_id_mapping;
};

}  // namespace mguid

#endif  // DATATREE_OBJECT_NODE_TYPE_HPP
