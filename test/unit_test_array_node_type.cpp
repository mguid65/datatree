/**
 * @brief Tests for array node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <span>
#include <type_traits>
#include <vector>

#include <catch2/catch_all.hpp>

#include <datatree/tree_node.hpp>

TEST_CASE("Array Node Type Constructor") {
  SECTION("Default Constructor") {
    REQUIRE(std::is_nothrow_default_constructible_v<mguid::ArrayNodeType>);
    REQUIRE(
        std::is_nothrow_default_constructible_v<const mguid::ArrayNodeType>);
  }
  SECTION("Copy Constructor") {
    REQUIRE(std::is_copy_constructible_v<mguid::ArrayNodeType>);
    REQUIRE(std::is_copy_constructible_v<const mguid::ArrayNodeType>);
  }
  SECTION("Move Constructor") {
    REQUIRE(std::is_nothrow_move_constructible_v<mguid::ArrayNodeType>);
    REQUIRE(std::is_nothrow_constructible_v<const mguid::ArrayNodeType,
                                            mguid::ArrayNodeType&&>);
  }
  SECTION("Copy Assignment") {
    REQUIRE(std::is_copy_assignable_v<mguid::ArrayNodeType>);
  }
  SECTION("Move Assignment") {
    REQUIRE(std::is_nothrow_move_assignable_v<mguid::ArrayNodeType>);
  }
  SECTION("Initializer List Constructor") {
    REQUIRE(std::is_constructible_v<mguid::ArrayNodeType,
                                    std::initializer_list<mguid::TreeNode>>);
    REQUIRE(std::is_constructible_v<const mguid::ArrayNodeType,
                                    std::initializer_list<mguid::TreeNode>>);
  }
  SECTION("Initializer List Assignment") {
    REQUIRE(std::is_assignable_v<mguid::ArrayNodeType,
                                 std::initializer_list<mguid::TreeNode>>);
  }
  SECTION("Size Initialization") {
    REQUIRE(std::is_constructible_v<mguid::ArrayNodeType,
                                    mguid::ArrayNodeType::SizeType>);
    REQUIRE(mguid::ArrayNodeType{mguid::ArrayNodeType::SizeType{64}}.Size() ==
            mguid::ArrayNodeType::SizeType{64});
  }
}

TEST_CASE("Array Node Type Try Get") {
  SECTION("Get Invalid Index Empty") {
    mguid::ArrayNodeType ant1;
    auto result = ant1.TryGet(0);
    REQUIRE_FALSE(result.has_value());
    REQUIRE(result.error().category == mguid::Error::Category::OutOfRange);
  }
  SECTION("Get Not Empty") {
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    auto result1 = ant1.TryGet(0);
    auto result2 = ant1.TryGet(1);
    auto result3 = ant1.TryGet(2);
    auto result4 = ant1.TryGet(3);

    REQUIRE(result1.has_value());
    REQUIRE(result2.has_value());
    REQUIRE(result3.has_value());
    REQUIRE(result4.has_value());
  }
  SECTION("Get Invalid Index Not Empty") {
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    auto result = ant1.TryGet(4);
    REQUIRE_FALSE(result.has_value());
    REQUIRE(result.error().category == mguid::Error::Category::OutOfRange);
  }
}

TEST_CASE("Array Node Type Operator []") {
  SECTION("Get Non-Existent Index Empty") {
    mguid::ArrayNodeType ant1;
    REQUIRE(ant1.Empty());
    const auto& result = ant1[0];
    REQUIRE(ant1.Size() == 1);
    REQUIRE(result.HasValue());
  }
  SECTION("Get Not Empty") {
    {
      mguid::ArrayNodeType ant1{{}, {}, {}, {}};
      REQUIRE(ant1.Size() == 4);

      const auto& result1 = ant1[0];
      const auto& result2 = ant1[1];
      const auto& result3 = ant1[2];
      const auto& result4 = ant1[3];
      REQUIRE(ant1.Size() == 4);

      REQUIRE(result1.HasObject());
      REQUIRE(result2.HasObject());
      REQUIRE(result3.HasObject());
      REQUIRE(result4.HasObject());
    }
    {
      const mguid::ArrayNodeType ant1{{}, {}, {}, {}};
      REQUIRE(ant1.Size() == 4);

      const auto& result1 = ant1[0];
      const auto& result2 = ant1[1];
      const auto& result3 = ant1[2];
      const auto& result4 = ant1[3];
      REQUIRE(ant1.Size() == 4);

      REQUIRE(result1.HasObject());
      REQUIRE(result2.HasObject());
      REQUIRE(result3.HasObject());
      REQUIRE(result4.HasObject());
    }
  }
  SECTION("Get Non-Existent Index Index Not Empty") {
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    REQUIRE(ant1.Size() == 4);
    const auto& result = ant1[4];
    REQUIRE(ant1.Size() == 5);
    REQUIRE(result.HasValue());
  }
}

TEST_CASE("Array Node Type At") {
  SECTION("Get Non-Existent Index Empty") {
    mguid::ArrayNodeType ant1;
    REQUIRE(ant1.Empty());
    REQUIRE_THROWS(ant1.At(0));
  }
  SECTION("Get Not Empty") {
    {
      mguid::ArrayNodeType ant1{{}, {}, {}, {}};
      REQUIRE(ant1.Size() == 4);

      const auto& result1 = ant1.At(0);
      const auto& result2 = ant1.At(1);
      const auto& result3 = ant1.At(2);
      const auto& result4 = ant1.At(3);
      REQUIRE(ant1.Size() == 4);

      REQUIRE(result1.HasObject());
      REQUIRE(result2.HasObject());
      REQUIRE(result3.HasObject());
      REQUIRE(result4.HasObject());
    }
    {
      const mguid::ArrayNodeType ant1{{}, {}, {}, {}};
      REQUIRE(ant1.Size() == 4);

      const auto& result1 = ant1.At(0);
      const auto& result2 = ant1.At(1);
      const auto& result3 = ant1.At(2);
      const auto& result4 = ant1.At(3);
      REQUIRE(ant1.Size() == 4);

      REQUIRE(result1.HasObject());
      REQUIRE(result2.HasObject());
      REQUIRE(result3.HasObject());
      REQUIRE(result4.HasObject());
    }
  }
  SECTION("Get Non-Existent Index Index Not Empty") {
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    REQUIRE_THROWS(ant1.At(4));
  }
}

TEST_CASE("Array Node Type Try Set") {
  SECTION("Set Valid Index") {
    auto test_node = mguid::TreeNode{};
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    REQUIRE(ant1.TrySet(0, test_node).has_value());
    REQUIRE(ant1.TrySet(1, test_node).has_value());
    REQUIRE(ant1.TrySet(2, test_node).has_value());
    // Clang-Tidy thinks there is a use-after-move here
    REQUIRE(ant1.TrySet(3, std::move(test_node)).has_value());
  }
  SECTION("Set Invalid Index") {
    mguid::ArrayNodeType ant1{mguid::TreeNode{}, mguid::TreeNode{},
                              mguid::TreeNode{}, mguid::TreeNode{}};
    auto result = ant1.TrySet(4, mguid::TreeNode{});
    REQUIRE_FALSE(result.has_value());
    REQUIRE(result.error().category == mguid::Error::Category::OutOfRange);
  }
}

TEST_CASE("Array Node Type Set") {
  SECTION("Set Valid Index") {
    auto test_node = mguid::TreeNode{};
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    ant1.Set(0, test_node);
    ant1.Set(1, test_node);
    ant1.Set(2, test_node);
    // The last one is a move
    ant1.Set(3, std::move(test_node));
    REQUIRE(ant1.Size() == 4);
  }
  SECTION("Set Non-Existent Index") {
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    ant1.Set(4, mguid::TreeNode{});
    REQUIRE(ant1.Size() == 5);
  }
}

TEST_CASE("Array Node Type Try Front") {
  auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};
  auto test_node_2 = mguid::TreeNode{mguid::ValueNodeType{2}};
  SECTION("TryFront Has Elements") {
    {
      mguid::ArrayNodeType ant1{test_node_1, test_node_2};
      auto result = ant1.TryFront();
      REQUIRE(result.has_value());
      REQUIRE(result.value() == test_node_1);
    }
    {
      const mguid::ArrayNodeType ant1{test_node_1, test_node_2};
      auto result = ant1.TryFront();
      REQUIRE(result.has_value());
      REQUIRE(result.value() == test_node_1);
    }
  }
  SECTION("TryFront Empty") {
    {
      mguid::ArrayNodeType ant1;
      REQUIRE_FALSE(ant1.TryFront().has_value());
    }
    {
      const mguid::ArrayNodeType ant1;
      REQUIRE_FALSE(ant1.TryFront().has_value());
    }
  }
}

TEST_CASE("Array Node Type Try Back") {
  auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};
  auto test_node_2 = mguid::TreeNode{mguid::ValueNodeType{2}};
  SECTION("TryBack Has Elements") {
    {
      mguid::ArrayNodeType ant1{test_node_1, test_node_2};
      auto result = ant1.TryBack();
      REQUIRE(result.value() == test_node_2);
    }
    {
      const mguid::ArrayNodeType ant1{test_node_1, test_node_2};
      auto result = ant1.TryBack();
      REQUIRE(result.value() == test_node_2);
    }
  }
  SECTION("TryBack Empty") {
    {
      mguid::ArrayNodeType ant1;
      REQUIRE_FALSE(ant1.TryBack().has_value());
    }
    {
      const mguid::ArrayNodeType ant1;
      REQUIRE_FALSE(ant1.TryBack().has_value());
    }
  }
}

TEST_CASE("Array Node Type Front") {
  auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};
  auto test_node_2 = mguid::TreeNode{mguid::ValueNodeType{2}};
  SECTION("Front Has Elements") {
    {
      mguid::ArrayNodeType ant1{test_node_1, test_node_2};
      REQUIRE(ant1.Front() == test_node_1);
    }
    {
      const mguid::ArrayNodeType ant1{test_node_1, test_node_2};
      REQUIRE(ant1.Front() == test_node_1);
    }
  }
}

TEST_CASE("Array Node Type Back") {
  auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};
  auto test_node_2 = mguid::TreeNode{mguid::ValueNodeType{2}};
  SECTION("Back Has Elements") {
    {
      mguid::ArrayNodeType ant1{test_node_1, test_node_2};
      REQUIRE(ant1.Back() == test_node_2);
    }
    {
      const mguid::ArrayNodeType ant1{test_node_1, test_node_2};
      REQUIRE(ant1.Back() == test_node_2);
    }
  }
}

TEST_CASE("Array Node Type Empty") {
  SECTION("Empty") {
    mguid::ArrayNodeType ant1;
    REQUIRE(ant1.Empty());
  }
  SECTION("Not Empty") {
    mguid::ArrayNodeType ant1{mguid::TreeNode{}};
    REQUIRE_FALSE(ant1.Empty());
  }
}

TEST_CASE("Array Node Type Size") {
  SECTION("Empty") {
    mguid::ArrayNodeType ant1;
    REQUIRE(ant1.Size() == 0);
  }
  SECTION("Size 3") {
    mguid::ArrayNodeType ant1{mguid::TreeNode{}, mguid::TreeNode{},
                              mguid::TreeNode{}};
    REQUIRE(ant1.Size() == 3);
  }
  SECTION("Size 1024") {
    mguid::ArrayNodeType ant1;
    for (auto i{0}; i < 1024; ++i) { ant1.PushBack({}); }
    REQUIRE(ant1.Size() == 1024);
  }
}

TEST_CASE("Array Node Type Resize") {
  mguid::ArrayNodeType ant1;
  REQUIRE(ant1.Size() == 0);
  ant1.Resize(1);
  REQUIRE(ant1.Size() == 1);
  ant1.Resize(1024);
  REQUIRE(ant1.Size() == 1024);
  ant1.Resize(1);
  REQUIRE(ant1.Size() == 1);
  ant1.Resize(0);
  REQUIRE(ant1.Size() == 0);
}

TEST_CASE("Array Node Type Resize With Value") {
  mguid::ArrayNodeType ant1;
  REQUIRE(ant1.Size() == 0);
  ant1.Resize(1, mguid::TreeNode{mguid::ValueNodeType{}});
  REQUIRE(ant1.At(0).HasValue());
  REQUIRE(ant1.Size() == 1);
  ant1.Resize(1024, mguid::TreeNode{mguid::ValueNodeType{}});
  REQUIRE(ant1.At(1).HasValue());
  REQUIRE(ant1.At(512).HasValue());
  REQUIRE(ant1.At(1023).HasValue());
  REQUIRE(ant1.Size() == 1024);
  ant1.Resize(1, mguid::TreeNode{mguid::ValueNodeType{}});
  REQUIRE(ant1.Size() == 1);
  ant1.Resize(0, mguid::TreeNode{mguid::ValueNodeType{}});
  REQUIRE(ant1.Size() == 0);
}

TEST_CASE("Array Node Type Reserve/Capacity/ShrinkToFit") {
  // Difficult to test accurately since some allocator implementation might
  // allocate some initial memory and vector implementations may have different
  // growth policies
  mguid::ArrayNodeType ant1;
  ant1.Reserve(1);
  REQUIRE(ant1.Capacity() >= 1);
  ant1.Reserve(1024);
  REQUIRE(ant1.Capacity() >= 1024);
  ant1.PushBack({});
  ant1.ShrinkToFit();
  REQUIRE(ant1.Capacity() >= 1);
}

TEST_CASE("Array Node Type Clear") {
  SECTION("Empty") {
    mguid::ArrayNodeType ant1;
    ant1.Clear();
    REQUIRE(ant1.Empty());
  }
  SECTION("3 Elements") {
    mguid::ArrayNodeType ant1{mguid::TreeNode{}, mguid::TreeNode{},
                              mguid::TreeNode{}};
    ant1.Clear();
    REQUIRE(ant1.Empty());
  }
  SECTION("1024 Elements") {
    mguid::ArrayNodeType ant1;
    for (auto i{0}; i < 1024; ++i) { ant1.PushBack({}); }
    ant1.Clear();
    REQUIRE(ant1.Empty());
  }
}

TEST_CASE("Array Node Type Insert") {
  SECTION("Insert const & Empty") {
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.Begin(), test_node_1);
      auto expected_pos = ant1.Begin();
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_node_1);
    }
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.End(), test_node_1);
      auto expected_pos = ant1.Begin();
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_node_1);
    }
  }
  SECTION("Insert const & Not Empty") {
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1{mguid::TreeNode{}};
      auto iter = ant1.Insert(ant1.End(), test_node_1);
      auto expected_pos = std::next(ant1.Begin());
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_node_1);
    }
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1{mguid::TreeNode{}};
      auto iter = ant1.Insert(ant1.Begin(), test_node_1);
      auto expected_pos = ant1.Begin();
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_node_1);
    }
  }
  SECTION("Insert Count const & Empty") {
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.End(), 2, test_node_1);
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_node_1);
      ++iter;
      REQUIRE(*iter == test_node_1);
    }
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.Begin(), 2, test_node_1);
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_node_1);
      ++iter;
      REQUIRE(*iter == test_node_1);
    }
  }
  SECTION("Insert Count const & Not Empty") {
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1{mguid::TreeNode{}};
      auto iter = ant1.Insert(ant1.End(), 2, test_node_1);
      auto expected_pos_1 = std::next(ant1.Begin());
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_node_1);
      ++iter;
      REQUIRE(*iter == test_node_1);
    }
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1{mguid::TreeNode{}};
      auto iter = ant1.Insert(ant1.Begin(), 2, test_node_1);
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_node_1);
      ++iter;
      REQUIRE(*iter == test_node_1);
    }
  }
  SECTION("Insert Range Empty") {
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};
      auto test_node_2 = mguid::TreeNode{mguid::ValueNodeType{2}};

      const std::vector<mguid::TreeNode> init{test_node_1, test_node_2};

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.End(), init.begin(), init.end());
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_node_1);
      ++iter;
      REQUIRE(*iter == test_node_2);
    }
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};
      auto test_node_2 = mguid::TreeNode{mguid::ValueNodeType{2}};

      const std::vector<mguid::TreeNode> init{test_node_1, test_node_2};

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.Begin(), init.begin(), init.end());
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_node_1);
      ++iter;
      REQUIRE(*iter == test_node_2);
    }
  }
  SECTION("Insert Range Not Empty") {
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};
      auto test_node_2 = mguid::TreeNode{mguid::ValueNodeType{2}};

      const std::vector<mguid::TreeNode> init{test_node_1, test_node_2};

      mguid::ArrayNodeType ant1{mguid::TreeNode{}};
      auto iter = ant1.Insert(ant1.End(), init.begin(), init.end());
      auto expected_pos_1 = std::next(ant1.Begin());
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_node_1);
      ++iter;
      REQUIRE(*iter == test_node_2);
    }
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};
      auto test_node_2 = mguid::TreeNode{mguid::ValueNodeType{2}};

      const std::vector<mguid::TreeNode> init{test_node_1, test_node_2};

      mguid::ArrayNodeType ant1{mguid::TreeNode{}};
      auto iter = ant1.Insert(ant1.Begin(), init.begin(), init.end());
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_node_1);
      ++iter;
      REQUIRE(*iter == test_node_2);
    }
  }
  SECTION("Insert Initializer List Empty") {
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};
      auto test_node_2 = mguid::TreeNode{mguid::ValueNodeType{2}};

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.End(), {test_node_1, test_node_2});
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_node_1);
      ++iter;
      REQUIRE(*iter == test_node_2);
    }
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};
      auto test_node_2 = mguid::TreeNode{mguid::ValueNodeType{2}};

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.Begin(), {test_node_1, test_node_2});
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_node_1);
      ++iter;
      REQUIRE(*iter == test_node_2);
    }
  }
  SECTION("Insert Initializer List Not Empty") {
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};
      auto test_node_2 = mguid::TreeNode{mguid::ValueNodeType{2}};

      mguid::ArrayNodeType ant1{mguid::TreeNode{}};
      auto iter = ant1.Insert(ant1.End(), {test_node_1, test_node_2});
      auto expected_pos_1 = std::next(ant1.Begin());
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_node_1);
      ++iter;
      REQUIRE(*iter == test_node_2);
    }
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};
      auto test_node_2 = mguid::TreeNode{mguid::ValueNodeType{2}};

      mguid::ArrayNodeType ant1{mguid::TreeNode{}};
      auto iter = ant1.Insert(ant1.Begin(), {test_node_1, test_node_2});
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_node_1);
      ++iter;
      REQUIRE(*iter == test_node_2);
    }
  }
}

TEST_CASE("Array Node Type Emplace") {
  SECTION("Emplace const & Empty") {
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Emplace(ant1.Begin(), test_node_1);
      auto expected_pos = ant1.Begin();
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_node_1);
    }
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Emplace(ant1.End(), test_node_1);
      auto expected_pos = ant1.Begin();
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_node_1);
    }
  }
  SECTION("Emplace const & Not Empty") {
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1{mguid::TreeNode{}};
      auto iter = ant1.Emplace(ant1.End(), test_node_1);
      auto expected_pos = std::next(ant1.Begin());
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_node_1);
    }
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1{mguid::TreeNode{}};
      auto iter = ant1.Emplace(ant1.Begin(), test_node_1);
      auto expected_pos = ant1.Begin();
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_node_1);
    }
  }
}

TEST_CASE("Array Node Type Erase") {
  SECTION("Erase Pos") {
    {
      mguid::ArrayNodeType ant1{mguid::TreeNode{}};
      auto iter = ant1.Erase(ant1.Begin());
      REQUIRE(iter == ant1.End());
      REQUIRE(ant1.Empty());
    }
    {
      mguid::ArrayNodeType ant1{mguid::TreeNode{}, mguid::TreeNode{},
                                mguid::TreeNode{}};
      auto iter = ant1.Erase(ant1.Begin());
      REQUIRE(iter == ant1.Begin());
      REQUIRE(ant1.Size() == 2);
    }
  }
  SECTION("Erase Range") {
    {
      mguid::ArrayNodeType ant1{mguid::TreeNode{}};
      auto iter = ant1.Erase(ant1.Begin(), ant1.End());
      REQUIRE(iter == ant1.End());
      REQUIRE(ant1.Empty());
    }
    {
      mguid::ArrayNodeType ant1{mguid::TreeNode{}, mguid::TreeNode{},
                                mguid::TreeNode{}};
      auto iter = ant1.Erase(ant1.Begin(), std::next(ant1.Begin()));
      REQUIRE(iter == ant1.Begin());
      REQUIRE(ant1.Size() == 2);
    }
  }
}
TEST_CASE("Array Node Type Push Back") {
  SECTION("Push Back") {
    mguid::ArrayNodeType ant1;
    ant1.PushBack({});
    ant1.PushBack(mguid::TreeNode{});
    REQUIRE(ant1.Size() == 2);
  }
}
TEST_CASE("Array Node Type Emplace Back") {
  SECTION("Emplace Back") {
    mguid::ArrayNodeType ant1;
    ant1.EmplaceBack(mguid::TreeNode{});
    REQUIRE(ant1.Size() == 1);
  }
}

TEST_CASE("Array Node Type Pop Back") {
  SECTION("Pop Back Empty") {
    mguid::ArrayNodeType ant1;
    ant1.PopBack();
    REQUIRE(ant1.Empty());
  }
  SECTION("Pop Back Not Empty") {
    {
      mguid::ArrayNodeType ant1{{}};
      REQUIRE(ant1.Size() == 1);
      ant1.PopBack();
      REQUIRE(ant1.Empty());
    }
    {
      auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

      mguid::ArrayNodeType ant1{mguid::TreeNode{}, test_node_1};
      ant1.PopBack();
      REQUIRE(ant1.TryBack().value().HasObject());
    }
  }
}

TEST_CASE("Array Node Type Comparison") {
  SECTION("Equality Both Empty") {
    mguid::ArrayNodeType ant1;
    mguid::ArrayNodeType ant2;
    REQUIRE(ant1 == ant2);
    REQUIRE_FALSE(ant1 != ant2);
  }
  SECTION("Equality One Empty") {
    mguid::ArrayNodeType ant1{{}};
    mguid::ArrayNodeType ant2;
    REQUIRE_FALSE(ant1 == ant2);
    REQUIRE(ant1 != ant2);
  }
  SECTION("Equality Both 1 Equal Item") {
    mguid::ArrayNodeType ant1{{}};
    mguid::ArrayNodeType ant2{{}};
    REQUIRE(ant1 == ant2);
    REQUIRE_FALSE(ant1 != ant2);
  }
  SECTION("Equality Both 1 Non-Equal Item") {
    auto test_node_1 = mguid::TreeNode{mguid::ValueNodeType{1}};

    mguid::ArrayNodeType ant1{test_node_1};
    mguid::ArrayNodeType ant2{{}};
    REQUIRE_FALSE(ant1 == ant2);
    REQUIRE(ant1 != ant2);
  }
  SECTION("Equality Many Items Equal") {
    mguid::ArrayNodeType ant1{{}};
    mguid::ArrayNodeType ant2{{}};
    for (auto i{0}; i < 1024; ++i) {
      ant1.PushBack({});
      ant2.PushBack({});
    }
    REQUIRE(ant1 == ant2);
    REQUIRE_FALSE(ant1 != ant2);
  }
}

TEST_CASE("Array Node Type Iterators") {
  SECTION("Begin") {
    mguid::ArrayNodeType ant1;
    auto iter1 = ant1.Begin();
    auto iter2 = ant1.Begin();
    auto iter3 = ant1.begin();
    REQUIRE(iter1 == iter2);
    REQUIRE(iter3 == iter2);
  }
  SECTION("Begin Const") {
    const mguid::ArrayNodeType ant1;
    const auto iter1 = ant1.Begin();
    const auto iter2 = ant1.Begin();
    const auto iter3 = ant1.begin();
    REQUIRE(iter1 == iter2);
    REQUIRE(iter3 == iter2);
  }
  SECTION("CBegin") {
    mguid::ArrayNodeType ant1;
    auto iter1 = ant1.CBegin();
    auto iter2 = ant1.CBegin();
    auto iter3 = ant1.cbegin();
    REQUIRE(iter1 == iter2);
    REQUIRE(iter3 == iter2);
  }
  SECTION("End") {
    mguid::ArrayNodeType ant1;
    auto iter1 = ant1.End();
    auto iter2 = ant1.End();
    auto iter3 = ant1.end();
    REQUIRE(iter1 == iter2);
    REQUIRE(iter3 == iter2);
  }
  SECTION("End Const") {
    const mguid::ArrayNodeType ant1;
    const auto iter1 = ant1.End();
    const auto iter2 = ant1.End();
    const auto iter3 = ant1.end();
    REQUIRE(iter1 == iter2);
    REQUIRE(iter3 == iter2);
  }
  SECTION("CEnd") {
    mguid::ArrayNodeType ant1;
    auto iter1 = ant1.CEnd();
    auto iter2 = ant1.CEnd();
    auto iter3 = ant1.cend();
    REQUIRE(iter1 == iter2);
    REQUIRE(iter3 == iter2);
  }
  SECTION("RBegin") {
    mguid::ArrayNodeType ant1;
    auto iter1 = ant1.RBegin();
    auto iter2 = ant1.RBegin();
    auto iter3 = ant1.rbegin();
    REQUIRE(iter1 == iter2);
    REQUIRE(iter3 == iter2);
  }
  SECTION("RBegin Const") {
    const mguid::ArrayNodeType ant1;
    const auto iter1 = ant1.RBegin();
    const auto iter2 = ant1.RBegin();
    const auto iter3 = ant1.rbegin();
    REQUIRE(iter1 == iter2);
    REQUIRE(iter3 == iter2);
  }
  SECTION("CRBegin") {
    mguid::ArrayNodeType ant1;
    auto iter1 = ant1.CRBegin();
    auto iter2 = ant1.CRBegin();
    auto iter3 = ant1.crbegin();
    REQUIRE(iter1 == iter2);
    REQUIRE(iter3 == iter2);
  }
  SECTION("REnd") {
    mguid::ArrayNodeType ant1;
    auto iter1 = ant1.REnd();
    auto iter2 = ant1.REnd();
    auto iter3 = ant1.rend();
    REQUIRE(iter1 == iter2);
    REQUIRE(iter3 == iter2);
  }
  SECTION("REnd Const") {
    const mguid::ArrayNodeType ant1;
    const auto iter1 = ant1.REnd();
    const auto iter2 = ant1.REnd();
    const auto iter3 = ant1.rend();
    REQUIRE(iter1 == iter2);
    REQUIRE(iter3 == iter2);
  }
  SECTION("CREnd") {
    mguid::ArrayNodeType ant1;
    auto iter1 = ant1.CREnd();
    auto iter2 = ant1.CREnd();
    auto iter3 = ant1.crend();
    REQUIRE(iter1 == iter2);
    REQUIRE(iter3 == iter2);
  }
}