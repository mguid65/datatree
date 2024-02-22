/**
 * @brief Declarations for datatree
 * @author Matthew Guidry(github: mguid65)
 * @date 2024-02-04
 */

#ifndef DATATREE_DATATREE_HPP
#define DATATREE_DATATREE_HPP

#include <array>
#include <iostream>
#include <sstream>

#include "datatree/common.hpp"
#include "datatree/tree_node.hpp"

namespace mguid {

inline std::string PrettifyJson(const std::string& json,
                                std::size_t tab_width = 2) {
  std::size_t indent{0};
  std::string result;

  auto append_indent = [&]() { result.append(indent * tab_width, ' '); };

  for (const auto& ch : json) {
    switch (ch) {
      case '{':
        [[fallthrough]];
      case '[': {
        indent += 1;
        result += ch;
        result += '\n';
        append_indent();
        break;
      }
      case '}':
        [[fallthrough]];
      case ']': {
        indent -= 1;
        result += '\n';
        append_indent();
        result += ch;
        break;
      }
      case ',': {
        result += ch;
        result += '\n';
        append_indent();
        break;
      }
      default:
        result += ch;
    }
  }

  return result;
}

class DataTree {
  using MapType = std::unordered_map<uuid, TreeNode>;

public:
  /**
   * @brief
   */
  enum class VisitOrder : std::uint8_t { PreOrder, PostOrder };

  /**
   * @brief
   */
  DataTree() = default;

  /**
   * @brief Explicit defaults for copy/move construction/assignment
   */
  DataTree(const DataTree&) = default;
  DataTree(DataTree&&) noexcept = default;
  DataTree& operator=(const DataTree&) = default;
  DataTree& operator=(DataTree&&) noexcept = default;

  /**
   * @brief Set a node in the data tree
   *
   * The path will be created if it does not exist
   *
   * If other nodes with the wrong type exist along the path, they will be
   * destroyed.
   *
   * @tparam NLength path length
   * @param path path to node
   * @param node a valid node type
   */
  template <std::size_t NLength>
  void Set(const Path<NLength>& path,
           [[maybe_unused]] ValidNodeType auto&& node) {
    if constexpr (NLength == 0) {
      m_nodes.at(uuid{}).Set(node);
    } else {
      const auto& items = path.Items();
      // Begin with root: nil uuid
      uuid current_parent_id{};
      std::invoke(
          [this, &items, &current_parent_id]<std::size_t... NIdxs>(
              std::index_sequence<NIdxs...>) {
            (
                [this, &items, &current_parent_id]() {
                  // Get or init node at `current_parent_id`
                  auto& parent = m_nodes[current_parent_id];
                  // check if path item is key or value
                  auto& item = items[NIdxs];
                  switch (item.index()) {
                    case 0: {
                      const auto& key = std::get<StringKeyType>(item);
                      if (!parent.HasObject()) {
                        if (parent.HasArray()) {
                          DeleteSubtree(current_parent_id, true);
                        }
                        parent.Reset<NodeTypeTag::Object>();
                      }
                      auto& object = parent.GetObject();
                      auto result = object.InsertOrAssign(key, RandomUUID());
                      current_parent_id = std::get<0>(result)->second;
                      break;
                    }
                    case 1: {
                      const auto& idx = std::get<IntegerKeyType>(item);
                      if (!parent.HasArray()) {
                        if (parent.HasObject()) {
                          DeleteSubtree(current_parent_id, true);
                        }
                        parent.Reset<NodeTypeTag::Array>();
                      }
                      auto& array = parent.GetArray();
                      const auto previous_size = array.Size();
                      if (previous_size < idx + 1) {
                        array.Resize(idx + 1);
                        [[maybe_unused]] const auto capacity = array.Capacity();
                        const auto new_size = array.Size();
                        for (auto new_idx{previous_size}; new_idx < new_size;
                             ++new_idx) {
                          array.Set(new_idx, RandomUUID());
                          m_nodes.emplace(array.Get(new_idx).value(),
                                          TreeNode{ValueNodeType{}});
                        }
                      }
                      current_parent_id = array.Get(idx).value();
                      break;
                    }
                    default: {
                      Unreachable();
                    }
                  }
                }(),
                ...);
          },
          std::make_index_sequence<NLength>{});
      auto& last = m_nodes[current_parent_id];
      last.Set(node);
    }
  }

  template <bool TPretty = false>
  void Print() {
    // Use this to determine if we need a comma
    std::vector<std::size_t> level_stack{[&]() {
      return RootNode().Visit(
          [&](const ObjectNodeType& obj) { return obj.Size(); },
          [&](const ArrayNodeType& arr) { return arr.Size(); },
          [&](const ValueNodeType&) { return std::size_t{0}; });
    }()};
    std::stringstream ss;
    auto visitor = VisitSubTree{
        [&](const auto& kv, const std::optional<KeyType>& key_or_idx) {
          if (key_or_idx.has_value()) {
            std::visit(Overload{[&](const StringKeyType& key) {
                                  ss << "\"" << key << "\" : ";
                                },
                                [&](auto&&) {}},
                       key_or_idx.value());
          }
          kv.second.Visit(
              [&](const ObjectNodeType& obj) {
                level_stack.push_back(obj.Size());
                ss << "{";
              },
              [&](const ArrayNodeType& arr) {
                level_stack.push_back(arr.Size());
                ss << "[";
              },
              [&](auto&&) {});
        },
        [&](const auto& kv) {
          kv.second.Visit(
              [&](const ObjectNodeType&) {
                ss << "}";
                level_stack.pop_back();
                level_stack.back()--;
                if (level_stack.back() != 0) { ss << ","; }
              },
              [&](const ArrayNodeType&) {
                ss << "]";
                level_stack.pop_back();
                level_stack.back()--;
                if (level_stack.back() != 0) { ss << ","; }
              },
              [&](const ValueNodeType& node) {
                node.Visit(
                    [&](const NullType& val) { ss << val; },
                    [&](const BoolType& val) {
                      constexpr auto boolalpha = [](bool value) {
                        if (value) { return "true"; }
                        return "false";
                      };
                      ss << boolalpha(val);
                    },
                    [&](const NumberType& val) {
                      val.Visit([&](auto&& value) { ss << value; });
                    },
                    [&](const StringType& val) { ss << "\"" << val << "\""; });
                level_stack.back()--;
                if (level_stack.back() != 0) { ss << ","; }
              });
        }};

    visitor(*this);
    if constexpr (TPretty) {
      std::cout << PrettifyJson(ss.str()) << '\n';
    } else {
      std::cout << ss.str() << '\n';
    }
  }

  /**
   * @brief
   * @param items
   * @param node
   */
  void Set(std::initializer_list<KeyType> items,
           [[maybe_unused]] ValidNodeType auto&& node) {
    if (items.size() == 0) {
      m_nodes.at(uuid{}).Set(node);
    } else {
      // Begin with root: nil uuid
      uuid current_parent_id{};
      for (const auto& item : items) {
        auto& parent = m_nodes[current_parent_id];
        switch (item.index()) {
          case 0: {
            const auto& key = std::get<StringKeyType>(item);
            if (!parent.HasObject()) {
              if (parent.HasArray()) { DeleteSubtree(current_parent_id, true); }
              parent.Reset<NodeTypeTag::Object>();
            }
            auto& object = parent.GetObject();
            auto result = object.InsertOrAssign(key, RandomUUID());
            current_parent_id = std::get<0>(result)->second;
            break;
          }
          case 1: {
            const auto& idx = std::get<IntegerKeyType>(item);
            if (!parent.HasArray()) {
              if (parent.HasObject()) {
                DeleteSubtree(current_parent_id, true);
              }
              parent.Reset<NodeTypeTag::Array>();
            }
            auto& array = parent.GetArray();
            const auto previous_size = array.Size();
            if (previous_size < idx + 1) {
              array.Resize(idx + 1);
              [[maybe_unused]] const auto capacity = array.Capacity();
              const auto new_size = array.Size();
              for (auto new_idx{previous_size}; new_idx < new_size; ++new_idx) {
                array.Set(new_idx, RandomUUID());
                m_nodes.emplace(array.Get(new_idx).value(), TreeNode{});
              }
            }
            current_parent_id = array.Get(idx).value();
            break;
          }
          default: {
            Unreachable();
          }
        }
      }
      auto& last = m_nodes[current_parent_id];
      last.Set(node);
    }
  }

  template <std::size_t NLength>
  auto Get(const Path<NLength>& path) -> expected<TreeNode, Error> {
    for ([[maybe_unused]] auto& path_item : path.Items()) {}
    return make_unexpected(Error{.category = Error::Category::KeyError});
  }

  auto Get(std::initializer_list<KeyType> path) -> expected<TreeNode, Error> {
    for ([[maybe_unused]] auto& path_item : path) {}
    return make_unexpected(Error{.category = Error::Category::KeyError});
  }

private:
  /**
   * @brief Get reference to the root node
   * @return reference to the root node
   */
  TreeNode& RootNode() { return m_nodes.at(uuid{}); }

  /**
   * @brief Get reference to the root node
   * @return reference to the root node
   */
  const TreeNode& RootNode() const { return m_nodes.at(uuid{}); }

  /**
   * @brief
   * @return
   */
  TreeNode& At(uuid id) { return m_nodes.at(id); }

  /**
   * @brief
   * @return
   */
  const TreeNode& At(uuid id) const { return m_nodes.at(id); }

  /**
   * @brief
   * @tparam TCallable
   * @tparam TOrder
   */
  template <typename TPreOrderCallable, typename TPostOrderCallable,
            bool TPreOrderVisitKey = std::is_invocable_v<
                TPreOrderCallable, MapType::value_type, std::optional<KeyType>>,
            bool TPostOrderVisitKey =
                std::is_invocable_v<TPostOrderCallable, MapType::value_type,
                                    std::optional<KeyType>>>
    requires(std::is_invocable_v<TPreOrderCallable, MapType::value_type,
                                 std::optional<KeyType>> ||
             std::is_invocable_v<TPreOrderCallable, MapType::value_type>) &&
            (std::is_invocable_v<TPostOrderCallable, MapType::value_type,
                                 std::optional<KeyType>> ||
             std::is_invocable_v<TPostOrderCallable, MapType::value_type>)
  struct VisitSubTree {
    /**
     * @brief
     * @param callable
     */
    VisitSubTree(TPreOrderCallable&& pre_order, TPostOrderCallable&& post_order)
        : m_preorder_callable{std::forward<TPreOrderCallable>(pre_order)},
          m_postorder_callable{std::forward<TPostOrderCallable>(post_order)} {}

    /**
     * @brief
     * @param dt
     * @param start_id
     */
    void operator()(DataTree& dt, uuid start_id = uuid{}) {
      VisitInner(dt, start_id, std::nullopt);
    }

    /**
     * @brief
     * @param dt
     * @param start_id
     */
    void operator()(const DataTree& dt, uuid start_id = uuid{}) const {
      VisitInner(dt, start_id, std::nullopt);
    }

  private:
    /**
     * @brief
     *
     * PRECONDITIONS:
     *     1. `current_id` must exist within `dt`
     *
     * @param dt
     * @param current_id
     */
    void VisitInner(DataTree& dt, uuid current_id,
                    const std::optional<KeyType>& key_or_idx) {
      auto iter = dt.m_nodes.find(current_id);
      if constexpr (TPreOrderVisitKey) {
        std::invoke(m_preorder_callable, *iter, key_or_idx);
      } else {
        std::invoke(m_preorder_callable, *iter);
      }
      switch (dt.At(current_id).Tag()) {
        case NodeTypeTag::Object: {
          auto& node = iter->second.GetObject();
          for (const auto& [key, value] : node) { VisitInner(dt, value, key); }
          break;
        }
        case NodeTypeTag::Array: {
          auto& node = iter->second.GetArray();
          for (std::size_t idx{0}; const auto& id : node) {
            VisitInner(dt, id, idx);
            ++idx;
          }
          break;
        }
        case NodeTypeTag::Value:
          break;
      }
      if constexpr (TPostOrderVisitKey) {
        std::invoke(m_postorder_callable, *iter, key_or_idx);
      } else {
        std::invoke(m_postorder_callable, *iter);
      }
    }

    /**
     * @brief
     *
     * PRECONDITIONS:
     *     1. `current_id` must exist within `dt`
     *
     * @param dt
     * @param current_id
     */
    void VisitInner(const DataTree& dt, uuid current_id,
                    std::optional<KeyType> key_or_idx) const {
      auto iter = dt.m_nodes.find(current_id);
      if constexpr (TPreOrderVisitKey) {
        std::invoke(m_preorder_callable, *iter, key_or_idx);
      } else {
        std::invoke(m_preorder_callable, *iter);
      }
      switch (dt.At(current_id).Tag()) {
        case NodeTypeTag::Object: {
          auto& node = iter->second.GetObject();
          for (const auto& [key, value] : node) { VisitInner(dt, value, key); }
          break;
        }
        case NodeTypeTag::Array: {
          auto& node = iter->second.GetArray();
          for (std::size_t idx{0}; const auto& id : node) {
            VisitInner(dt, id, idx);
            ++idx;
          }
          break;
        }
        case NodeTypeTag::Value:
          break;
      }
      if constexpr (TPostOrderVisitKey) {
        std::invoke(m_postorder_callable, *iter, key_or_idx);
      } else {
        std::invoke(m_postorder_callable, *iter);
      }
    }

    TPreOrderCallable m_preorder_callable;
    TPostOrderCallable m_postorder_callable;
  };

  /**
   * @brief
   * @tparam TFunc
   * @param ids
   * @param func
   */
  template <typename TFunc>
  void Apply(const std::vector<uuid>& ids, TFunc&& func) {
    std::for_each(ids.begin(), ids.end(), std::forward<TFunc>(func));
  }

  /**
   * @brief
   * @param parent
   * @return
   */
  [[nodiscard]] std::vector<uuid> ChildrenOf(uuid parent) const {
    if (m_nodes.find(parent) == m_nodes.end()) { return {}; }
    std::vector<uuid> result;

    auto visitor = VisitSubTree{[](auto) {},
                                [&result, &parent](const auto& kv) {
                                  if (kv.first != parent) {
                                    result.push_back(kv.first);
                                  }
                                }};

    visitor(*this, parent);

    return result;
  }

  /**
   * @brief
   * @param parent
   */
  void DeleteSubtree(uuid parent, bool exclude_parent = false) {
    // If the requested parent node id is not in the map, return
    if (m_nodes.find(parent) == m_nodes.end()) { return; }
    // Find all children of parent and erase them
    if (!exclude_parent) { m_nodes.erase(parent); }
    const auto children = ChildrenOf(parent);
    Apply(children, [this](uuid id) { m_nodes.erase(id); });
  }

  MapType m_nodes{{uuid{}, TreeNode{ObjectNodeType{}}}};
};

}  // namespace mguid

#endif  // DATATREE_DATATREE_HPP
