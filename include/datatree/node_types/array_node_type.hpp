/**
 * @brief Declarations for array node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
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
   * @brief TODO
   * @param pos
   * @param value
   * @return
   */
  auto Insert(ConstIterator pos, const ValueType& value) -> Iterator {
    return m_array.insert(pos, value);
  }

  /**
   * @brief TODO
   * @param pos
   * @param value
   * @return
   */
  auto Insert(ConstIterator pos, ValueType&& value) -> Iterator {
    return m_array.insert(pos, value);
  }

  /**
   * @brief TODO
   * @param pos
   * @param count
   * @param value
   * @return
   */
  auto Insert(ConstIterator pos, SizeType count, const ValueType& value)
      -> Iterator {
    return m_array.insert(pos, count, value);
  }

  /**
   * @brief TODO
   * @tparam TInputIt
   * @param pos
   * @param first
   * @param last
   * @return
   */
  template <typename TInputIt>
  auto Insert(ConstIterator pos, TInputIt first, TInputIt last) -> Iterator {
    return m_array.insert(pos, first, last);
  }

  /**
   * @brief TODO
   * @param pos
   * @param init_list
   * @return
   */
  auto Insert(ConstIterator pos, std::initializer_list<ValueType> init_list)
      -> Iterator {
    return m_array.insert(pos, init_list);
  }

  /**
   * @brief TODO
   * @tparam TArgs
   * @param pos
   * @param args
   * @return
   */
  template <typename... TArgs>
  auto Emplace(ConstIterator pos, TArgs&&... args) -> Iterator {
    return m_array.emplace(pos, std::forward<TArgs>(args)...);
  }

  /**
   * @brief TODO
   * @param pos
   * @return
   */
  auto Erase(ConstIterator pos) -> Iterator { return m_array.erase(pos); }

  /**
   * @brief TODO
   * @param first
   * @param last
   * @return
   */
  auto Erase(ConstIterator first, ConstIterator last) -> Iterator {
    return m_array.erase(first, last);
  }

  /**
   * @brief TODO
   * @param value
   * @return
   */
  void PushBack(const ValueType& value) { m_array.push_back(value); }

  /**
   * @brief TODO
   * @param value
   * @return
   */
  void PushBack(ValueType&& value) { m_array.push_back(value); }

  /**
   * @brief TODO
   * @tparam TArgs
   * @param args
   * @return
   */
  template <typename... TArgs>
  void EmplaceBack(TArgs&&... args) {
    m_array.emplace_back(std::forward<TArgs>(args)...);
  }

  /**
   * @brief TODO
   * @return
   */
  void PopBack() { m_array.pop_back(); }

  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto operator<=>(const ArrayNodeType&) const
      -> std::weak_ordering = default;
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto operator==(const ArrayNodeType&) const -> bool = default;

  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto Begin() noexcept -> Iterator { return m_array.begin(); }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto Begin() const noexcept -> ConstIterator {
    return m_array.begin();
  }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto CBegin() const noexcept -> ConstIterator {
    return m_array.cbegin();
  }

  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto End() noexcept -> Iterator { return m_array.end(); }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto End() const noexcept -> ConstIterator {
    return m_array.end();
  }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto CEnd() const noexcept -> ConstIterator {
    return m_array.cend();
  }

  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto RBegin() noexcept -> ReverseIterator {
    return m_array.rbegin();
  }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto RBegin() const noexcept -> ConstReverseIterator {
    return m_array.rbegin();
  }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto CRBegin() const noexcept -> ConstReverseIterator {
    return m_array.crbegin();
  }

  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto REnd() noexcept -> ReverseIterator {
    return m_array.rend();
  }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto REnd() const noexcept -> ConstReverseIterator {
    return m_array.rend();
  }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto CREnd() const noexcept -> ConstReverseIterator {
    return m_array.crend();
  }

  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto begin() noexcept -> Iterator { return Begin(); }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto begin() const noexcept -> ConstIterator { return Begin(); }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto cbegin() const noexcept -> ConstIterator {
    return CBegin();
  }

  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto end() noexcept -> Iterator { return End(); }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto end() const noexcept -> ConstIterator { return End(); }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto cend() const noexcept -> ConstIterator { return CEnd(); }

  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto rbegin() noexcept -> ReverseIterator { return RBegin(); }

  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto rbegin() const noexcept -> ConstReverseIterator {
    return RBegin();
  }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto crbegin() const noexcept -> ConstReverseIterator {
    return CRBegin();
  }

  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto rend() noexcept -> ReverseIterator { return REnd(); }
  /**
   * @brief TODO
   * @return
   */
  [[nodiscard]] auto rend() const noexcept -> ConstReverseIterator {
    return REnd();
  }
  /**
   * @brief TODO
   * @return
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
