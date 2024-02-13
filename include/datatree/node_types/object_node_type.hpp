/**
 * @brief Declarations for object node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_OBJECT_NODE_TYPE_HPP
#define DATATREE_OBJECT_NODE_TYPE_HPP

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

/**
 * @brief Map like class that defines an object like node with children
 *
 * Most of the functions here just forward to the underlying map
 */
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
   * @brief Construct an ObjectNodeType from an initializer list of ValueType
   * @param init_list an initializer list of ValueType
   */
  ObjectNodeType(std::initializer_list<ValueType> init_list)
      : m_key_id_mapping{init_list} {}

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
    return make_unexpected(Error{.category = Error::Category::KeyError});
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
  [[nodiscard]] auto GetOr(const KeyType& key, TDefault&& default_value) const
      -> expected<MappedType, Error> {
    if (auto iter = m_key_id_mapping.find(key);
        iter != m_key_id_mapping.end()) {
      return iter->second;
    }
    return static_cast<MappedType>(std::forward<TDefault>(default_value));
  }

  /**
   * @brief Erase all elements from this ObjectNodeType
   */
  void Clear() noexcept { m_key_id_mapping.clear(); }

  /**
   * @brief Insert value if the container doesn't already contain an element
   * with an equivalent key
   * @param value value to insert
   * @return A std::pair consisting of an Iterator to the inserted value (or
   * to the element that prevented the insertion) and a bool denoting whether
   * the insertion took place (true if insertion happened, false if it did not).
   */
  std::pair<Iterator, bool> Insert(const ValueType& value) {
    return m_key_id_mapping.insert(value);
  }

  /**
   * @brief Insert value if the container doesn't already contain an element
   * with an equivalent key
   * @param value value to insert
   * @return A std::pair consisting of an Iterator to the inserted value (or
   * to the element that prevented the insertion) and a bool denoting whether
   * the insertion took place (true if insertion happened, false if it did not).
   */
  std::pair<Iterator, bool> Insert(ValueType&& value) {
    return m_key_id_mapping.insert(value);
  }

  /**
   * @brief Insert value if the container doesn't already contain an element
   * with an equivalent key
   *
   * This overload is equivalent to
   * Emplace(std::forward<TConvertibleToValueType>(value)) and only participates
   * in overload resolution if std::is_constructible_v<ValueType,
   * TConvertibleToValueType&&> == true.
   *
   * @tparam TConvertibleToValueType type of value to insert
   * @param value value to insert
   * @return A std::pair consisting of an Iterator to the inserted value (or
   * to the element that prevented the insertion) and a bool denoting whether
   * the insertion took place (true if insertion happened, false if it did not).
   */
  template <typename TConvertibleToValueType>
  std::pair<Iterator, bool> Insert(TConvertibleToValueType&& value) {
    return m_key_id_mapping.insert(
        std::forward<TConvertibleToValueType>(value));
  }

  /**
   * @brief Inserts value, using hint as a non-binding suggestion to where the
   * search should start.
   * @param value value to insert
   * @return An iterator to the inserted value, or to the value that
   * prevented the insertion.
   */
  Iterator InsertHint(ConstIterator hint, const ValueType& value) {
    return m_key_id_mapping.insert(hint, value);
  }

  /**
   * @brief Inserts value, using hint as a non-binding suggestion to where the
   * search should start.
   * @param value value to insert
   * @return An iterator to the inserted value, or to the value that
   * prevented the insertion.
   */
  Iterator InsertHint(ConstIterator hint, ValueType&& value) {
    return m_key_id_mapping.insert(hint, value);
  }

  /**
   * @brief Inserts value, using hint as a non-binding suggestion to where the
   * search should start.
   *
   * This overload is equivalent to
   * EmplaceHint(hint, std::forward<TConvertibleToValueType>(value)) and only
   * participates in overload resolution if std::is_constructible_v<ValueType,
   * TConvertibleToValueType&&> == true.
   *
   * @tparam TConvertibleToValueType type of value to insert
   *
   * @param value value to insert
   * @return An iterator to the inserted value, or to the value that
   * prevented the insertion.
   */
  template <typename TConvertibleToValueType>
  Iterator InsertHint(ConstIterator hint, TConvertibleToValueType&& value) {
    return m_key_id_mapping.insert(hint, value);
  }

  /**
   * @brief Inserts elements from initializer list init_list.
   *
   * If multiple elements in
   * the range have keys that compare equivalent, it is unspecified which
   * element is inserted
   *
   * @param init_list initializer list to insert the values from
   */
  void Insert(std::initializer_list<ValueType> init_list) {
    m_key_id_mapping.insert(init_list);
  }

  /**
   * @brief Insert a new element or assign to an existing element if found
   *
   * If a key equivalent to key already exists in the container, assigns
   * std::forward<TValue>(obj) to the MappedType corresponding to the key key.
   * If the key does not exist, inserts the new value as if by Insert,
   * constructing it from ValueType(key, std::forward<TValue>(obj)).
   *
   * @tparam TValue type of value to insert
   * @param key the key used both to look up and to insert if not found
   * @param obj the value to insert or assign
   * @return The bool component is true if the insertion took place and false if
   * the assignment took place. The iterator component is pointing at the
   * element that was inserted or updated.
   */
  template <typename TValue>
  std::pair<Iterator, bool> InsertOrAssign(const KeyType& key, TValue&& obj) {
    return m_key_id_mapping.insert_or_assign(key, std::forward<TValue>(obj));
  }

  /**
   * @brief Insert a new element or assign to an existing element if found
   *
   * If a key equivalent to key already exists in the container, assigns
   * std::forward<TValue>(obj) to the MappedType corresponding to the key key.
   * If the key does not exist, inserts the new value as if by Insert,
   * constructing it from ValueType(std::move(key), std::forward<TValue>(obj)).
   *
   * @tparam TValue type of value to insert
   * @param key the key used both to look up and to insert if not found
   * @param obj the value to insert or assign
   * @return The bool component is true if the insertion took place and false if
   * the assignment took place. The iterator component is pointing at the
   * element that was inserted or updated.
   */
  template <typename TValue>
  std::pair<Iterator, bool> InsertOrAssign(KeyType&& key, TValue&& obj) {
    return m_key_id_mapping.insert_or_assign(key, std::forward<TValue>(obj));
  }

  /**
   * @brief Insert a new element or assign to an existing element if found
   *
   * If a key equivalent to key already exists in the container, assigns
   * std::forward<TValue>(obj) to the MappedType corresponding to the key key.
   * If the key does not exist, constructs an object u of ValueType with
   * std::forward<KeyType>(key), std::forward<TValue>(obj)), then inserts u into
   * the underlying unordered_map. If hash_function()(u.first) !=
   * hash_function()(k) || contains(u.first) is true, the behavior is undefined.
   * The ValueType must be EmplaceConstructible into the underlying
   * unordered_map from std::forward<KeyType>(key), std::forward<TValue>(obj).
   * This overload participates in overload resolution only if
   * Hash::is_transparent and KeyEqual::is_transparent are valid and each
   * denotes a type. This assumes that such Hash is callable with both KeyType
   * and Key type, and that the KeyEqual is transparent, which, together, allows
   * calling this function without constructing an instance of Key.
   *
   * @tparam TValue type of value to insert
   * @param hint iterator to the position before which the new element will be
   * inserted
   * @param key the key used both to look up and to insert if not found
   * @param obj the value to insert or assign
   * @return The bool component is true if the insertion took place and false if
   * the assignment took place. The iterator component is pointing at the
   * element that was inserted or updated.
   */
  template <typename TValue>
  Iterator InsertOrAssignHint(ConstIterator hint, const KeyType& key,
                              TValue&& obj) {
    return m_key_id_mapping.insert_or_assign(hint, key,
                                             std::forward<TValue>(obj));
  }

  /**
   * @brief Insert a new element or assign to an existing element if found
   *
   * If a key equivalent to key already exists in the container, assigns
   * std::forward<TValue>(obj) to the MappedType corresponding to the key key.
   * If the key does not exist, constructs an object u of ValueType with
   * std::forward<KeyType>(key), std::forward<TValue>(obj)), then inserts u into
   * the underlying unordered_map. If hash_function()(u.first) !=
   * hash_function()(k) || contains(u.first) is true, the behavior is undefined.
   * The ValueType must be EmplaceConstructible into the underlying
   * unordered_map from std::forward<KeyType>(key), std::forward<TValue>(obj).
   * This overload participates in overload resolution only if
   * Hash::is_transparent and KeyEqual::is_transparent are valid and each
   * denotes a type. This assumes that such Hash is callable with both KeyType
   * and Key type, and that the KeyEqual is transparent, which, together, allows
   * calling this function without constructing an instance of Key.
   *
   * @tparam TValue type of value to insert
   * @param hint iterator to the position before which the new element will be
   * inserted
   * @param key the key used both to look up and to insert if not found
   * @param obj the value to insert or assign
   * @return The bool component is true if the insertion took place and false if
   * the assignment took place. The iterator component is pointing at the
   * element that was inserted or updated.
   */
  template <typename TValue>
  Iterator InsertOrAssignHint(ConstIterator hint, KeyType&& key, TValue&& obj) {
    return m_key_id_mapping.insert_or_assign(hint, key,
                                             std::forward<TValue>(obj));
  }

  /**
   * @brief Inserts a new element into the container constructed in-place with
   * the given args if there is no element with the key in the container.
   * @tparam TArgs type of arguments to forward
   * @param args arguments to forward to the constructor of the element
   * @return Returns a pair consisting of an iterator to the inserted element,
   * or the already-existing element if no insertion happened, and a bool
   * denoting whether the insertion took place (true if insertion happened,
   * false if it did not).
   */
  template <typename... TArgs>
  std::pair<Iterator, bool> Emplace(TArgs&&... args) {
    return m_key_id_mapping.emplace(std::forward<TArgs>(args)...);
  }

  /**
   * @brief Inserts a new element into the container, using hint as a suggestion
   * where the element should go.
   * @tparam TArgs type of arguments to forward
   * @param hint iterator, used as a suggestion as to where to insert the new
   * element
   * @param args arguments to forward to the constructor of the element
   * @return Returns an iterator to the newly inserted element. If the insertion
   * failed because the element already exists, returns an iterator to the
   * already existing element with the equivalent key.
   */
  template <typename... TArgs>
  Iterator EmplaceHint(ConstIterator hint, TArgs&&... args) {
    return m_key_id_mapping.emplace_hint(hint, std::forward<TArgs>(args)...);
  }

  /**
   * @brief If a key equivalent to key already exists in the container, does
   * nothing. Otherwise, inserts a new element into the container with key k and
   * value constructed with args.
   *
   * In such case that the key does not exist in the container:
   *
   * Behaves like Emplace except that the element is constructed as
   * value_type(std::piecewise_construct,
   *            std::forward_as_tuple(k),
   *            std::forward_as_tuple(std::forward<Args>(args)...))
   *
   * @tparam TArgs type of arguments to forward
   * @param key the key used both to look up and to insert if not found
   * @param args arguments to forward to the constructor of the element
   * @return The bool component is true if the insertion took place and false if
   * the assignment took place. The iterator component is pointing at the
   * element that was inserted or updated.
   */
  template <typename... TArgs>
  std::pair<Iterator, bool> TryEmplace(const KeyType& key, TArgs&&... args) {
    return m_key_id_mapping.try_emplace(key, std::forward<TArgs>(args)...);
  }

  /**
   * @brief If a key equivalent to key already exists in the container, does
   * nothing. Otherwise, inserts a new element into the container with key k and
   * value constructed with args.
   *
   * In such case that the key does not exist in the container:
   *
   * Behaves like emplace except that the element is constructed as
   * value_type(std::piecewise_construct,
   *            std::forward_as_tuple(std::move(k)),
   *            std::forward_as_tuple(std::forward<Args>(args)...))
   *
   * @tparam TArgs type of arguments to forward
   * @param key the key used both to look up and to insert if not found
   * @param args arguments to forward to the constructor of the element
   * @return The bool component is true if the insertion took place and false if
   * the assignment took place. The iterator component is pointing at the
   * element that was inserted or updated.
   */
  template <typename... TArgs>
  std::pair<Iterator, bool> TryEmplace(KeyType&& key, TArgs&&... args) {
    return m_key_id_mapping.try_emplace(key, std::forward<TArgs>(args)...);
  }

  /**
   * @brief If a key equivalent to key already exists in the container, does
   * nothing. Otherwise, inserts a new element into the container with key k and
   * value constructed with args.
   *
   * In such case that the key does not exist in the container:
   *
   * Behaves like EmplaceHint except that the element is constructed as
   * value_type(std::piecewise_construct,
   *            std::forward_as_tuple(k),
   *            std::forward_as_tuple(std::forward<Args>(args)...))
   *
   * @tparam TArgs type of arguments to forward
   * @param hint iterator to the position before which the new element will be
   * inserted
   * @param key the key used both to look up and to insert if not found
   * @param args arguments to forward to the constructor of the element
   * @return The bool component is true if the insertion took place and false if
   * the assignment took place. The iterator component is pointing at the
   * element that was inserted or updated.
   */
  template <typename... TArgs>
  Iterator TryEmplaceHint(ConstIterator hint, const KeyType& key,
                          TArgs&&... args) {
    return m_key_id_mapping.try_emplace(hint, key,
                                        std::forward<TArgs>(args)...);
  }

  /**
   * @brief If a key equivalent to key already exists in the container, does
   * nothing. Otherwise, inserts a new element into the container with key k and
   * value constructed with args.
   *
   * In such case that the key does not exist in the container:
   *
   * Behaves like EmplaceHint except that the element is constructed as
   * value_type(std::piecewise_construct,
   *            std::forward_as_tuple(std::move(k)),
   *            std::forward_as_tuple(std::forward<Args>(args)...))
   *
   * @tparam TArgs type of arguments to forward
   * @param hint iterator to the position before which the new element will be
   * inserted
   * @param key the key used both to look up and to insert if not found
   * @param args arguments to forward to the constructor of the element
   * @return The bool component is true if the insertion took place and false if
   * the assignment took place. The iterator component is pointing at the
   * element that was inserted or updated.
   */
  template <typename... TArgs>
  Iterator TryEmplaceHint(ConstIterator hint, KeyType&& key, TArgs&&... args) {
    return m_key_id_mapping.try_emplace(hint, key,
                                        std::forward<TArgs>(args)...);
  }

  // Note: I haven't exposed the ranged erase:
  // Iterator Erase(ConstIterator first, ConstIterator last);
  // because I don't like it.
  // Since unordered_map is *unordered* it is unpredictable what is within the
  // range. It is hard to see how this could be useful.

  /**
   * @brief Removes the element at pos
   * @param pos iterator to the element to remove
   * @return Iterator following the last removed element.
   */
  Iterator Erase(Iterator pos) { return m_key_id_mapping.erase(pos); }

  /**
   * @brief Removes the element at pos
   * @param pos iterator to the element to remove
   * @return Iterator following the last removed element.
   */
  Iterator Erase(ConstIterator pos) { return m_key_id_mapping.erase(pos); }

  /**
   * @brief Removes the element (if one exists) with the key equivalent to key.
   * @param key key value of the elements to remove
   * @return Number of elements removed (0 or 1).
   */
  SizeType Erase(const KeyType& key) { return m_key_id_mapping.erase(key); }

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

  /**
   * @brief Get an iterator to the first element of the underlying map.
   * @return Iterator to the first element.
   */
  [[nodiscard]] Iterator Begin() noexcept { return m_key_id_mapping.begin(); }

  /**
   * @brief Get an iterator to the first element of the underlying map.
   * @return Iterator to the first element.
   */
  [[nodiscard]] ConstIterator Begin() const noexcept {
    return m_key_id_mapping.begin();
  }

  /**
   * @brief Get an iterator to the first element of the underlying map.
   * @return Iterator to the first element.
   */
  [[nodiscard]] ConstIterator CBegin() const noexcept {
    return m_key_id_mapping.cbegin();
  }

  /**
   * @brief Get an iterator to the first element of the underlying map.
   * @return Iterator to the first element.
   */
  [[nodiscard]] Iterator begin() noexcept { return Begin(); }

  /**
   * @brief Get an iterator to the first element of the underlying map.
   * @return Iterator to the first element.
   */
  [[nodiscard]] ConstIterator begin() const noexcept { return Begin(); }

  /**
   * @brief Get an iterator to the first element of the underlying map.
   * @return Iterator to the first element.
   */
  [[nodiscard]] ConstIterator cbegin() const noexcept { return CBegin(); }

  /**
   * @brief Get an iterator to the element following the last element of the
   * unordered_map.
   * @return Iterator to the element following the last element.
   */
  [[nodiscard]] Iterator End() noexcept { return m_key_id_mapping.end(); }

  /**
   * @brief Get an iterator to the element following the last element of the
   * unordered_map.
   * @return Iterator to the element following the last element.
   */
  [[nodiscard]] ConstIterator End() const noexcept {
    return m_key_id_mapping.end();
  }

  /**
   * @brief Get an iterator to the element following the last element of the
   * unordered_map.
   * @return Iterator to the element following the last element.
   */
  [[nodiscard]] ConstIterator CEnd() const noexcept {
    return m_key_id_mapping.cend();
  }

  /**
   * @brief Get an iterator to the element following the last element of the
   * unordered_map.
   * @return Iterator to the element following the last element.
   */
  [[nodiscard]] Iterator end() noexcept { return End(); }

  /**
   * @brief Get an iterator to the element following the last element of the
   * unordered_map.
   * @return Iterator to the element following the last element.
   */
  [[nodiscard]] ConstIterator end() const noexcept { return End(); }

  /**
   * @brief Get an iterator to the element following the last element of the
   * unordered_map.
   * @return Iterator to the element following the last element.
   */
  [[nodiscard]] ConstIterator cend() const noexcept { return CEnd(); }

  /**
   * @brief Compares the contents of two ObjectNodeTypes.
   * @param other ObjectNodeType to compare against
   * @return true if the contents of the containers are equal, false otherwise.
   */
  [[nodiscard]] bool operator==(const ObjectNodeType& other) const = default;

private:
  MapType m_key_id_mapping;
};

}  // namespace mguid

#endif  // DATATREE_OBJECT_NODE_TYPE_HPP
