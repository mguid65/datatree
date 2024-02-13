/**
 * @brief Declarations for array node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-12
 */

#ifndef DATATREE_ARRAY_NODE_TYPE_HPP
#define DATATREE_ARRAY_NODE_TYPE_HPP

#include <vector>

#include "datatree/common.hpp"
#include "datatree/error/error_type.hpp"

namespace mguid {

/**
 * @brief A class that represents an Array Node Type
 */
class ArrayNodeType {
public:
  using ArrayType = std::vector<mguid::uuid>;
  using ValueType = ArrayType::value_type;
  using SizeType = ArrayType::size_type;
  using Iterator = ArrayType::iterator;
  using ConstIterator = ArrayType::const_iterator;
  using ReverseIterator = ArrayType::reverse_iterator;
  using ConstReverseIterator = ArrayType::const_reverse_iterator;

  /**
   * @brief Default construct an ArrayNodeType
   */
  ArrayNodeType() noexcept(noexcept(ArrayType())) = default;

  /**
   * @brief Explicit defaults for copy/move construction/assignment
   */
  ArrayNodeType(const ArrayNodeType&) = default;
  ArrayNodeType(ArrayNodeType&&) noexcept = default;
  ArrayNodeType& operator=(const ArrayNodeType&) = default;
  ArrayNodeType& operator=(ArrayNodeType&&) noexcept = default;

  /**
   * @brief Construct from an initializer list of uuids
   * @param init_list an initializer list of uuids
   */
  ArrayNodeType(std::initializer_list<mguid::uuid> init_list)
      : m_array{init_list} {}

  /**
   * @brief Assign an initializer list of uuids to this
   * @param init_list an initializer list of uuids
   * @return reference to this
   */
  ArrayNodeType& operator=(std::initializer_list<mguid::uuid> init_list) {
    m_array = init_list;
    return *this;
  }

  /**
   * @brief Access the specified element with bounds checking
   * @param pos position of the element to return
   * @return copy of the element at pos or Error
   */
  [[nodiscard]] auto Get(SizeType pos) const -> expected<ValueType, Error> {
    if (ValidIndex(pos)) { return m_array[pos]; }
    return make_unexpected(Error{.category = Error::Category::OutOfRange});
  }

  /**
   * @brief Set the specified element with bounds checking
   * @param pos position of the element to return
   * @return
   */
  auto Set(SizeType pos, const ValueType& value) -> expected<void, Error> {
    if (ValidIndex(pos)) {
      m_array[pos] = value;
      return {};
    }
    return make_unexpected(Error{.category = Error::Category::OutOfRange});
  }

  /**
   * @brief Set the specified element with bounds checking
   * @param pos position of the element to return
   * @return copy of the element at pos or Error
   */
  auto Set(SizeType pos, ValueType&& value) -> expected<void, Error> {
    if (ValidIndex(pos)) {
      m_array[pos] = value;
      return {};
    }
    return make_unexpected(Error{.category = Error::Category::OutOfRange});
  }

  /**
   * @brief Get the element at the front of this ArrayNodeType
   * @return the element at the front of this ArrayNodeType
   */
  [[nodiscard]] auto Front() const -> expected<ValueType, Error> {
    if (Empty()) {
      return make_unexpected(Error{.category = Error::Category::OutOfRange});
    }
    return m_array.front();
  }

  /**
   * @brief Get the element at the Back of this ArrayNodeType
   * @return the element at the Back of this ArrayNodeType
   */
  [[nodiscard]] auto Back() const -> expected<ValueType, Error> {
    if (Empty()) {
      return make_unexpected(Error{.category = Error::Category::OutOfRange});
    }
    return m_array.front();
  }

  /**
   * @brief Check if this ArrayNodeType is empty
   * @return true if empty, otherwise false
   */
  [[nodiscard]] auto Empty() const -> bool { return m_array.empty(); }

  /**
   * @brief Get the number of elements in this ArrayNodeType
   * @return the number of elements in this ArrayNodeType
   */
  [[nodiscard]] auto Size() const -> SizeType { return m_array.size(); }

  /**
   * @brief Resizes the container to contain count elements
   *
   * Does nothing if count == Size().
   * If the current size is greater than count, the container is reduced to its
   * first count elements. If the current size is less than count additional
   * default-inserted elements are appended.
   *
   * @param count new size of the container
   */
  void Resize(SizeType count) { m_array.resize(count); }

  /**
   * @brief Requests the removal of unused capacity.
   */
  void ShrinkToFit() { m_array.shrink_to_fit(); }

  /**
   * @brief Erases all elements from the container.
   */
  void Clear() noexcept { m_array.clear(); }

  /**
   * @brief Inserts elements at the specified location in the container.
   * @param pos	iterator before which the content will be inserted
   * @param value element value to insert
   * @return Iterator pointing to the inserted value
   */
  auto Insert(ConstIterator pos, const ValueType& value) -> Iterator {
    return m_array.insert(pos, value);
  }

  /**
   * @brief Inserts elements at the specified location in the container.
   * @param pos	iterator before which the content will be inserted
   * @param value element value to insert
   * @return Iterator pointing to the inserted value
   */
  auto Insert(ConstIterator pos, ValueType&& value) -> Iterator {
    return m_array.insert(pos, value);
  }

  /**
   * @brief Inserts count copies of the value before pos
   * @param pos	iterator before which the content will be inserted
   * @param count number of elements to insert
   * @param value element value to insert
   * @return Iterator pointing to the first element inserted, or pos if count ==
   * 0.
   */
  auto Insert(ConstIterator pos, SizeType count, const ValueType& value)
      -> Iterator {
    return m_array.insert(pos, count, value);
  }

  /**
   * @brief Inserts elements from range [first, last) before pos
   * @tparam TInputIt range iterator type
   * @param pos iterator before which the content will be inserted
   * @param first the beginning of the range of elements to insert
   * @param last the end of the range of elements to insert
   * @return Iterator pointing to the first element inserted, or pos if first ==
   * last
   */
  template <typename TInputIt>
  auto Insert(ConstIterator pos, TInputIt first, TInputIt last) -> Iterator {
    return m_array.insert(pos, first, last);
  }

  /**
   * @brief Inserts elements from initializer list init_list before pos
   * @param pos iterator before which the content will be inserted
   * @param init_list initializer list to insert the values from
   * @return Iterator pointing to the first element inserted, or pos if
   * init_list is empty.
   */
  auto Insert(ConstIterator pos, std::initializer_list<ValueType> init_list)
      -> Iterator {
    return m_array.insert(pos, init_list);
  }

  /**
   * @brief Inserts a new element into the container directly before pos
   * @tparam TArgs types of arguments to forward to the constructor of the
   * element
   * @param pos iterator before which the new element will be constructed
   * @param args arguments to forward to the constructor of the element
   * @return Iterator pointing to the emplaced element.
   */
  template <typename... TArgs>
  auto Emplace(ConstIterator pos, TArgs&&... args) -> Iterator {
    return m_array.emplace(pos, std::forward<TArgs>(args)...);
  }

  /**
   * @brief Remove the element at pos from the container
   * @param pos iterator to the element to remove
   * @return Iterator following the last removed element. If pos refers to the
   * last element, then the end() iterator is returned.
   */
  auto Erase(ConstIterator pos) -> Iterator { return m_array.erase(pos); }

  /**
   * @brief Remove the elements in the range [first, last) from the container
   * @param first iterator to the beginning of the range to remove
   * @param last iterator to the end of the range to remove
   * @return Iterator following the last removed element. If last == end() prior
   * to removal, then the updated end() iterator is returned. If [first, last)
   * is an empty range, then last is returned.
   */
  auto Erase(ConstIterator first, ConstIterator last) -> Iterator {
    return m_array.erase(first, last);
  }

  /**
   * @brief Appends the given element value to the end of the container.
   *
   * The new element is initialized as a copy of value.
   *
   * @param value the value of the element to append
   */
  void PushBack(const ValueType& value) { m_array.push_back(value); }

  /**
   * @brief Appends the given element value to the end of the container.
   *
   * value is moved into the new element.
   *
   * @param value the value of the element to append
   */
  void PushBack(ValueType&& value) { m_array.push_back(value); }

  /**
   * @brief Appends a new element to the end of the container.
   *
   * The element is constructed through std::allocator_traits::construct, which
   * typically uses placement-new to construct the element in-place at the
   * location provided by the container. The arguments args... are forwarded to
   * the constructor as std::forward<TArgs>(args)....
   *
   * @tparam TArgs types of arguments to forward to the constructor of the
   * element
   * @param args arguments to forward to the constructor of the element
   */
  template <typename... TArgs>
  void EmplaceBack(TArgs&&... args) {
    m_array.emplace_back(std::forward<TArgs>(args)...);
  }

  /**
   * @brief Removes the last element of the container.
   */
  void PopBack() { m_array.pop_back(); }

  /**
   * @brief Compares the contents of two ArrayNodeTypes.
   *
   * Compares the contents of this and other lexicographically.
   *
   * @return The relative order of the first pair of non-equivalent elements in
   * this and other if there are such elements, *this.Size() <=> other.Size()
   * otherwise.
   */
  [[nodiscard]] auto operator<=>(const ArrayNodeType&) const
      -> std::weak_ordering = default;

  /**
   * @brief Equality compare the contents of two ArrayNodeTypes.
   *
   * Checks if the contents of this and other are equal, that is, they have the
   * same number of elements and each element in this compares equal with the
   * element in other at the same position.
   *
   * @return true if the contents of the ArrayNodeTypes are equal, false
   * otherwise.
   */
  [[nodiscard]] auto operator==(const ArrayNodeType&) const -> bool = default;

  /**
   * @brief Returns an iterator to the first element of the ArrayNodeType.
   * @return an iterator to the first element of the ArrayNodeType.
   */
  [[nodiscard]] auto Begin() noexcept -> Iterator { return m_array.begin(); }

  /**
   * @brief Returns an iterator to the first element of the ArrayNodeType.
   * @return an iterator to the first element of the ArrayNodeType.
   */
  [[nodiscard]] auto Begin() const noexcept -> ConstIterator {
    return m_array.begin();
  }

  /**
   * @brief Returns an iterator to the first element of the ArrayNodeType.
   * @return an iterator to the first element of the ArrayNodeType.
   */
  [[nodiscard]] auto CBegin() const noexcept -> ConstIterator {
    return m_array.cbegin();
  }

  /**
   * @brief Returns an iterator to the element following the last element of the
   * ArrayNodeType.
   * @return an iterator to the element following the last element of the
   * ArrayNodeType.
   */
  [[nodiscard]] auto End() noexcept -> Iterator { return m_array.end(); }

  /**
   * @brief Returns an iterator to the element following the last element of the
   * ArrayNodeType.
   * @return an iterator to the element following the last element of the
   * ArrayNodeType.
   */
  [[nodiscard]] auto End() const noexcept -> ConstIterator {
    return m_array.end();
  }

  /**
   * @brief Returns an iterator to the element following the last element of the
   * ArrayNodeType.
   * @return an iterator to the element following the last element of the
   * ArrayNodeType.
   */
  [[nodiscard]] auto CEnd() const noexcept -> ConstIterator {
    return m_array.cend();
  }

  /**
   * @brief Returns a reverse iterator to the first element of the reversed
   * ArrayNodeType. It corresponds to the last element of the non-reversed
   * ArrayNodeType. If the ArrayNodeType is empty, the returned iterator is
   * equal to REnd().
   * @return a reverse iterator to the first element of the reversed
   * ArrayNodeType.
   */
  [[nodiscard]] auto RBegin() noexcept -> ReverseIterator {
    return m_array.rbegin();
  }

  /**
   * @brief Returns a reverse iterator to the first element of the reversed
   * ArrayNodeType. It corresponds to the last element of the non-reversed
   * ArrayNodeType. If the ArrayNodeType is empty, the returned iterator is
   * equal to REnd().
   * @return a reverse iterator to the first element of the reversed
   * ArrayNodeType.
   */
  [[nodiscard]] auto RBegin() const noexcept -> ConstReverseIterator {
    return m_array.rbegin();
  }

  /**
   * @brief Returns a reverse iterator to the first element of the reversed
   * ArrayNodeType. It corresponds to the last element of the non-reversed
   * ArrayNodeType. If the ArrayNodeType is empty, the returned iterator is
   * equal to REnd().
   * @return a reverse iterator to the first element of the reversed
   * ArrayNodeType.
   */
  [[nodiscard]] auto CRBegin() const noexcept -> ConstReverseIterator {
    return m_array.crbegin();
  }

  /**
   * @brief Returns a reverse iterator to the element following the last element
   * of the reversed ArrayNodeType. It corresponds to the element preceding the
   * first element of the non-reversed ArrayNodeType. This element acts as a
   * placeholder, attempting to access it results in undefined behavior.
   * @return a reverse iterator to the element following the last element of the
   * reversed ArrayNodeType.
   */
  [[nodiscard]] auto REnd() noexcept -> ReverseIterator {
    return m_array.rend();
  }

  /**
   * @brief Returns a reverse iterator to the element following the last element
   * of the reversed ArrayNodeType. It corresponds to the element preceding the
   * first element of the non-reversed ArrayNodeType. This element acts as a
   * placeholder, attempting to access it results in undefined behavior.
   * @return a reverse iterator to the element following the last element of the
   * reversed ArrayNodeType.
   */
  [[nodiscard]] auto REnd() const noexcept -> ConstReverseIterator {
    return m_array.rend();
  }

  /**
   * @brief Returns a reverse iterator to the element following the last element
   * of the reversed ArrayNodeType. It corresponds to the element preceding the
   * first element of the non-reversed ArrayNodeType. This element acts as a
   * placeholder, attempting to access it results in undefined behavior.
   * @return a reverse iterator to the element following the last element of the
   * reversed ArrayNodeType.
   */
  [[nodiscard]] auto CREnd() const noexcept -> ConstReverseIterator {
    return m_array.crend();
  }

  /**
   * @brief Returns an iterator to the first element of the ArrayNodeType.
   * @return an iterator to the first element of the ArrayNodeType.
   */
  [[nodiscard]] auto begin() noexcept -> Iterator { return Begin(); }

  /**
   * @brief Returns an iterator to the first element of the ArrayNodeType.
   * @return an iterator to the first element of the ArrayNodeType.
   */
  [[nodiscard]] auto begin() const noexcept -> ConstIterator { return Begin(); }

  /**
   * @brief Returns an iterator to the first element of the ArrayNodeType.
   * @return an iterator to the first element of the ArrayNodeType.
   */
  [[nodiscard]] auto cbegin() const noexcept -> ConstIterator {
    return CBegin();
  }

  /**
   * @brief Returns an iterator to the element following the last element of the
   * ArrayNodeType.
   * @return an iterator to the element following the last element of the
   * ArrayNodeType.
   */
  [[nodiscard]] auto end() noexcept -> Iterator { return End(); }

  /**
   * @brief Returns an iterator to the element following the last element of the
   * ArrayNodeType.
   * @return an iterator to the element following the last element of the
   * ArrayNodeType.
   */
  [[nodiscard]] auto end() const noexcept -> ConstIterator { return End(); }

  /**
   * @brief Returns an iterator to the element following the last element of the
   * ArrayNodeType.
   * @return an iterator to the element following the last element of the
   * ArrayNodeType.
   */
  [[nodiscard]] auto cend() const noexcept -> ConstIterator { return CEnd(); }

  /**
   * @brief Returns a reverse iterator to the first element of the reversed
   * ArrayNodeType. It corresponds to the last element of the non-reversed
   * ArrayNodeType. If the ArrayNodeType is empty, the returned iterator is
   * equal to REnd().
   * @return a reverse iterator to the first element of the reversed
   * ArrayNodeType.
   */
  [[nodiscard]] auto rbegin() noexcept -> ReverseIterator { return RBegin(); }

  /**
   * @brief Returns a reverse iterator to the first element of the reversed
   * ArrayNodeType. It corresponds to the last element of the non-reversed
   * ArrayNodeType. If the ArrayNodeType is empty, the returned iterator is
   * equal to REnd().
   * @return a reverse iterator to the first element of the reversed
   * ArrayNodeType.
   */
  [[nodiscard]] auto rbegin() const noexcept -> ConstReverseIterator {
    return RBegin();
  }

  /**
   * @brief Returns a reverse iterator to the first element of the reversed
   * ArrayNodeType. It corresponds to the last element of the non-reversed
   * ArrayNodeType. If the ArrayNodeType is empty, the returned iterator is
   * equal to REnd().
   * @return a reverse iterator to the first element of the reversed
   * ArrayNodeType.
   */
  [[nodiscard]] auto crbegin() const noexcept -> ConstReverseIterator {
    return CRBegin();
  }

  /**
   * @brief Returns a reverse iterator to the element following the last element
   * of the reversed ArrayNodeType. It corresponds to the element preceding the
   * first element of the non-reversed ArrayNodeType. This element acts as a
   * placeholder, attempting to access it results in undefined behavior.
   * @return a reverse iterator to the element following the last element of the
   * reversed ArrayNodeType.
   */
  [[nodiscard]] auto rend() noexcept -> ReverseIterator { return REnd(); }

  /**
   * @brief Returns a reverse iterator to the element following the last element
   * of the reversed ArrayNodeType. It corresponds to the element preceding the
   * first element of the non-reversed ArrayNodeType. This element acts as a
   * placeholder, attempting to access it results in undefined behavior.
   * @return a reverse iterator to the element following the last element of the
   * reversed ArrayNodeType.
   */
  [[nodiscard]] auto rend() const noexcept -> ConstReverseIterator {
    return REnd();
  }

  /**
   * @brief Returns a reverse iterator to the element following the last element
   * of the reversed ArrayNodeType. It corresponds to the element preceding the
   * first element of the non-reversed ArrayNodeType. This element acts as a
   * placeholder, attempting to access it results in undefined behavior.
   * @return a reverse iterator to the element following the last element of the
   * reversed ArrayNodeType.
   */
  [[nodiscard]] auto crend() const noexcept -> ConstReverseIterator {
    return CREnd();
  }

private:
  /**
   * @brief Check if an index is valid
   * @param pos position of index to validate
   * @return true if the index is in bounds; otherwise false
   */
  [[nodiscard]] bool ValidIndex(SizeType pos) const {
    return pos < m_array.size();
  }

  ArrayType m_array;
};

}  // namespace mguid

#endif  // DATATREE_ARRAY_NODE_TYPE_HPP
