/**
 * Copyright (c) 2024 Matthew Guidry
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 *
 * @brief Value type declarations and concepts
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#ifndef DATATREE_VALUE_TYPES_HPP
#define DATATREE_VALUE_TYPES_HPP

#include <string>
#include <type_traits>
#include <variant>

#include "datatree/node_types/detail/null_type.hpp"
#include "datatree/node_types/detail/number_type.hpp"

namespace mguid {

using BoolType = bool;

using StringType = std::string;
//    NumberType
//    NullType

/**
 * @brief A type satisfies this concept if it is the same as bool without
 * cvref qualifiers
 * @tparam TType type to constrain
 */
template <typename TType>
concept SatisfiesBoolType = std::same_as<std::remove_cvref_t<TType>, bool>;

/**
 * @brief A type satisfies this concept if it is the convertible to
 * std::string without cvref qualifiers
 * @tparam TType type to constrain
 */
template <typename TType>
concept SatisfiesStringType =
    !std::same_as<std::remove_cvref_t<TType>, nullptr_t> &&
    std::convertible_to<std::remove_cvref_t<TType>, std::string>;

/**
 * @brief A type satisfies this concept if it satisfies AllowedNumericType
 * or whose underlying type is a NumberType
 * @tparam TType type to constrain
 */
template <typename TType>
concept SatisfiesNumberType =
    detail::AllowedNumericType<TType> ||
    std::same_as<std::remove_cvref_t<TType>, NumberType>;

/**
 * @brief A type satisfies this concept if it is the same as NullType without
 * cvref qualifiers
 * @tparam TType type to constrain
 */
template <typename TType>
concept SatisfiesNullType = std::same_as<std::remove_cvref_t<TType>, NullType>;

/**
 * @brief A variant type of allowed value node value types
 */
using VariantValueType =
    std::variant<NullType, BoolType, NumberType, StringType>;

using StringKeyType = std::string;
using IntegerKeyType = std::size_t;

/**
 * @brief Key type to use to access paths, string for maps or int for arrays
 *
 * For example, if I had a json object `j`:
 *
 * ```
 * {
 *   "key1" :
 *   {
 *     "key2" : [ ... ]
 *   }
 * }
 * ```
 *
 * ```
 *         j["key1"]["key2"][0];
 *         ___|        |    |___________
 *        |            |               |
 * StringKeyType  StringKeyType  IntegerKeyType
 * ```
 *
 * The same applies for this DataTree
 */
struct KeyType : std::variant<StringKeyType, IntegerKeyType> {
  using BaseType = std::variant<StringKeyType, IntegerKeyType>;

  KeyType() = default;
  KeyType(const KeyType&) = default;
  KeyType(KeyType&&) = default;
  KeyType& operator=(const KeyType&) = default;
  KeyType& operator=(KeyType&&) = default;

  KeyType(const std::string& key) : BaseType{key} { }
  KeyType(std::string&& key) : BaseType{std::move(key)} {}

  KeyType(const char* key) : BaseType{key} { }

  KeyType(const std::size_t& idx) : BaseType{idx} { }
  KeyType(std::size_t&& idx) : BaseType{idx} {}

  /**
   * @brief Visit a value node type with a visitor overload set
   * @tparam TCallables set of non final callable types
   * @param callables set of non final callables
   * @return the common return type of all callables provided
   */
  template <typename... TCallables>
  decltype(auto) Visit(TCallables&&... callables) {
    auto overload_set = Overload{std::forward<TCallables>(callables)...};
    return std::visit(overload_set, *this);
  }

  /**
   * @brief Visit a value node type with a visitor overload set
   * @tparam TCallables set of non final callable types
   * @param callables set of non final callables
   * @return the common return type of all callables provided
   */
  template <typename... TCallables>
  decltype(auto) Visit(TCallables&&... callables) const {
    auto overload_set = Overload{std::forward<TCallables>(callables)...};
    return std::visit(overload_set, *this);
  }
};

namespace key_literals {
/**
 * @brief UDL to create a KeyType from an index
 * @param idx an index
 * @return a KeyType created from an index
 */
inline KeyType operator""_k(unsigned long long idx) { return KeyType{idx}; }

/**
 * @brief Helper for string literal KeyType UDL
 * @tparam NSize size of string literal
 */
template <std::size_t NSize>
struct KeyTypeStringLiteralHelper {
  char data[NSize]{};
  /**
   * @brief Construct a KeyTypeStringLiteralHelper from a string literal
   * @param str a string literal
   */
  constexpr KeyTypeStringLiteralHelper(const char (&str)[NSize]) {
    std::ranges::copy(str, data);
  }
};

/**
 * @brief UDL to create a KeyType from a string literal
 * @param idx an index
 * @return a KeyType created from a string literal
 */
template <KeyTypeStringLiteralHelper TLiteralStrKey>
KeyType operator""_k() {
  return KeyType{TLiteralStrKey.data};
}
}  // namespace key_literals

/**
 * @brief Determine the first type in the type list that is convertible to TType
 * @tparam TType type to check against list
 * @tparam TFirst first type in list
 * @tparam TOther the rest of the type list
 */
template <typename TType, typename TFirst, typename... TOther>
struct PickFirstConvertible {
private:
  using rhs_chain_type = typename PickFirstConvertible<TType, TOther...>::type;

public:
  using type =
      typename std::conditional<std::is_convertible<TType, TFirst>::value,
                                TFirst, rhs_chain_type>::type;
};

/**
 * @brief Determine the first type in the type list that is convertible to TType
 * @tparam TType type to check against list
 * @tparam TFirst first type in list
 */
template <typename TType, typename TFirst>
struct PickFirstConvertible<TType, TFirst> {
  using type = std::conditional<std::is_convertible<TType, TFirst>::value,
                                TFirst, void>::type;
};

/**
 * @brief Represents a path to a node in the data tree
 * @tparam NLength path length
 */
template <std::size_t NLength>
struct Path {
  /**
   * @brief Construct a Path from variadic path items
   * @tparam TArgs path item types
   * @param path_items path items
   */
  template <typename... TArgs>
  Path(TArgs&&... path_items)
      : items{{static_cast<typename PickFirstConvertible<
            TArgs, StringKeyType, IntegerKeyType>::type>(path_items)...}} {}

  /**
   * @brief TryGet array of KeyType path items
   * @return array of KeyType path items
   */
  [[nodiscard]] const std::array<KeyType, NLength>& Items() const {
    return items;
  }

private:
  std::array<KeyType, NLength> items;
};

/**
 * @brief Requires that a type has a subscript operator that accepts std::size_t
 * @tparam TContainer some container type
 */
template <typename TContainer>
concept IntegerIndexable = requires(TContainer container, std::size_t idx) {
  { container[idx] };
};

/**
 * @brief Compile time for loop for a container with an integer subscript
 * operator
 * @tparam NCount Number of iterations
 * @tparam TContainer Type of container with an integer subscript operator
 * @tparam TFunc Type of function to apply at each "iteration"
 * @param container container with a integer subscript operator
 * @param func function to apply at each "iteration"
 */
template <std::size_t NCount, IntegerIndexable TContainer, typename TFunc>
  requires std::invocable<TFunc, decltype(std::declval<TContainer>()[0])>
constexpr void For(TContainer&& container, TFunc&& func) noexcept(
    std::is_nothrow_invocable_v<TFunc,
                                decltype(std::declval<TContainer>()[0])>) {
  constexpr auto ForImpl =
      []<std::size_t... NIdxs>(
          std::add_lvalue_reference_t<std::remove_reference_t<TContainer>>
              container_inner,
          std::add_lvalue_reference_t<std::remove_reference_t<TFunc>>
              func_inner,
          std::index_sequence<NIdxs...>) {
        (std::invoke(func_inner, container_inner[NIdxs]), ...);
      };
  ForImpl(std::forward<TContainer>(container), std::forward<TFunc>(func),
          std::make_index_sequence<NCount>{});
}

/**
 * @brief Ostream overload to print a Path
 * @tparam NLength path length
 * @param os reference to some ostream object
 * @param path a path object
 * @return reference to ostream
 */
template <std::size_t NLength>
std::ostream& operator<<(std::ostream& os, const Path<NLength>& path) {
  For<NLength>(path.Items(), [&os](auto&& arg) {
    std::visit(Overload{[&os](const StringKeyType& key_or_idx) {
                          os << "[\"" << key_or_idx << "\"]";
                        },
                        [&os](const IntegerKeyType& key_or_idx) {
                          os << "[" << key_or_idx << "]";
                        }},
               KeyType{arg});
  });
  return os << std::endl;
}

/**
 * @brief Deduction guide to create a path from key path parameters
 */
template <typename... TArgs>
Path(TArgs...) -> Path<sizeof...(TArgs)>;

/**
 * @brief A type satisfies this concept if it satisfies one of the value node
 * value type concepts
 *
 * What a name
 *
 * @tparam TType type to constrain
 */
template <typename TType>
concept ValidValueNodeTypeValueType =
    SatisfiesBoolType<TType> || SatisfiesStringType<TType> ||
    SatisfiesNumberType<TType> || SatisfiesNullType<TType>;

}  // namespace mguid

#endif  // DATATREE_VALUE_TYPES_HPP
