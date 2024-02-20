/**
 * @brief Declarations for datatree
 * @author Matthew Guidry(github: mguid65)
 * @date 2024-02-04
 */

#ifndef DATATREE_DATATREE_HPP
#define DATATREE_DATATREE_HPP

#include <array>
#include <iostream>

#include "datatree/common.hpp"
#include "datatree/tree_node.hpp"

namespace mguid {

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
   * @brief
   * @tparam NLength
   * @param path
   * @param node
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
      for (const auto& item : items) {
        auto& parent = m_nodes[current_parent_id];
        if (auto* key_ptr = std::get_if<StringKeyType>(&item);
            key_ptr != nullptr) {
          auto& key = *key_ptr;
          if (!parent.HasObject()) {
            if (parent.HasArray()) { DeleteSubtree(current_parent_id, true); }
            parent.Reset<NodeTypeTag::Object>();
          }
          auto& object = parent.GetObject();
          auto result = object.InsertOrAssign(key, RandomUUID());
          current_parent_id = std::get<0>(result)->second;
        } else {
          auto idx = std::get<IntegerKeyType>(item);
          if (!parent.HasArray()) {
            if (parent.HasObject()) { DeleteSubtree(current_parent_id, true); }
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
        }
      }
      auto& last = m_nodes[current_parent_id];
      last.Set(node);
    }
  }

  void Dump() {
    auto visitor = VisitSubTree{[](const auto& kv) {
      kv.second.Visit(
          [](const ObjectNodeType& node) {
            std::cout << "Object Node: Size=" << node.Size() << '\n';
          },
          [](const ArrayNodeType& node) {
            std::cout << "Array Node: Size=" << node.Size() << '\n';
          },
          [](const ValueNodeType& node) {
            std::cout << "Value Node: Value=";
            node.Visit([](const NullType&) { std::cout << "Null" << '\n'; },
                       [](const BoolType& val) {
                         constexpr auto boolalpha = [](bool value) {
                           if (value) { return "True"; }
                           return "False";
                         };
                         std::cout << boolalpha(val) << '\n';
                       },
                       [](const NumberType& val) {
                         val.Visit([](auto&& value) {
                           std::cout << value << '\n';
                         });
                       },
                       [](const StringType& val) {
                         std::cout << "\"" << val << "\"" << '\n';
                       });
          });
    }};

    visitor(*this);
  }

  //  void Set(std::initializer_list<KeyType> path,
  //           [[maybe_unused]] ValidNodeType auto&& node) {
  //    if (path.size() == 0) {
  //      m_nodes.at(uuid{}).Set(node);
  //    } else {
  //      for ([[maybe_unused]] auto& path_item : path) {}
  //    }
  //  }

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
  template <typename TCallable, VisitOrder TOrder = VisitOrder::PreOrder>
  struct VisitSubTree {
    /**
     * @brief
     * @param callable
     */
    VisitSubTree(TCallable&& callable)
        : m_callable{std::forward<TCallable>(callable)} {}

    /**
     * @brief
     * @param dt
     * @param start_id
     */
    void operator()(DataTree& dt, uuid start_id = uuid{}) {
      VisitInner(dt, start_id);
    }

    /**
     * @brief
     * @param dt
     * @param start_id
     */
    void operator()(const DataTree& dt, uuid start_id = uuid{}) const {
      VisitInner(dt, start_id);
    }

  private:
    /**
     * @brief
     * @param dt
     * @param current_id
     */
    void VisitInner(DataTree& dt, uuid current_id) {
      auto iter = dt.m_nodes.find(current_id);
      if constexpr (TOrder == VisitOrder::PreOrder) { m_callable(*iter); }
      switch (dt.At(current_id).Tag()) {
        case NodeTypeTag::Object: {
          auto& node = iter->second.GetObject();
          for (const auto& kv : node) { VisitInner(dt, kv.second); }
          break;
        }
        case NodeTypeTag::Array: {
          auto& node = iter->second.GetArray();
          for (const auto& id : node) { VisitInner(dt, id); }
          break;
        }
        case NodeTypeTag::Value: {
          break;
        }
      }
      if constexpr (TOrder == VisitOrder::PostOrder) { m_callable(*iter); }
    }
    /**
     * @brief
     * @param dt
     * @param current_id
     */
    void VisitInner(const DataTree& dt, uuid current_id) const {
      auto iter = dt.m_nodes.find(current_id);
      if constexpr (TOrder == VisitOrder::PreOrder) { m_callable(*iter); }
      switch (dt.At(current_id).Tag()) {
        case NodeTypeTag::Object: {
          auto& node = iter->second.GetObject();
          for (const auto& kv : node) { VisitInner(dt, kv.second); }
          break;
        }
        case NodeTypeTag::Array: {
          auto& node = iter->second.GetArray();
          for (const auto& id : node) { VisitInner(dt, id); }
          break;
        }
        case NodeTypeTag::Value: {
          break;
        }
      }
      if constexpr (TOrder == VisitOrder::PostOrder) { m_callable(*iter); }
    }
    TCallable m_callable;
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

    auto visitor = VisitSubTree{[&result, &parent](const auto& kv) {
      if (kv.first != parent) { result.push_back(kv.first); }
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
