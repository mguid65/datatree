/**
 * @brief Declarations for datatree
 * @author Matthew Guidry(github: mguid65)
 * @date 2024-02-04
 */

#ifndef DATATREE_DATATREE_HPP
#define DATATREE_DATATREE_HPP

#include "datatree/common.hpp"
#include "datatree/tree_node.hpp"

namespace mguid {

class DataTree {
  using MapType = std::unordered_map<uuid, TreeNode>;

public:
  DataTree() { m_nodes.emplace(m_root_id, TreeNode{ObjectNodeType{}}); }

  /**
   * @brief Explicit defaults for copy/move construction/assignment
   */
  DataTree(const DataTree&) = default;
  DataTree(DataTree&&) noexcept = default;
  DataTree& operator=(const DataTree&) = default;
  DataTree& operator=(DataTree&&) noexcept = default;

  template <std::size_t NLength>
  void Set(const Path<NLength>& path,
           [[maybe_unused]] ValidNodeType auto&& node) {
    for ([[maybe_unused]] auto& path_item : path.Items()) {}
  }

  void Set(std::initializer_list<KeyType> path,
           [[maybe_unused]] ValidNodeType auto&& node) {
    for ([[maybe_unused]] auto& path_item : path) {}
  }

  template <std::size_t NLength>
  auto Get(const Path<NLength>& path) -> expected<TreeNode, Error> {
    for ([[maybe_unused]] auto& path_item : path.Items()) {}
    return make_unexpected(Error{.category = Error::Category::KeyError});
  }

  auto Get(std::initializer_list<KeyType> path)  -> expected<TreeNode, Error>{
    for ([[maybe_unused]] auto& path_item : path) {}
    return make_unexpected(Error{.category = Error::Category::KeyError});
  }
private:
  uuid m_root_id{RandomUUID()};
  MapType m_nodes;
};

}  // namespace mguid

#endif  // DATATREE_DATATREE_HPP
