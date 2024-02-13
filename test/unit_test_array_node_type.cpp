/**
 * @brief Tests for array node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <iostream>
#include <type_traits>
#include <vector>

#include <catch2/catch_all.hpp>

#include <datatree/node_types/array_node_type.hpp>

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
                                    std::initializer_list<mguid::uuid>>);
    REQUIRE(std::is_constructible_v<const mguid::ArrayNodeType,
                                    std::initializer_list<mguid::uuid>>);
  }
  SECTION("Initializer List Assignment") {
    REQUIRE(std::is_assignable_v<mguid::ArrayNodeType,
                                 std::initializer_list<mguid::uuid>>);
  }
}

TEST_CASE("Array Node Type Get") {
  SECTION("Get Invalid Index Empty") {
    mguid::ArrayNodeType ant1;
    auto result = ant1.Get(0);
    REQUIRE(result.has_exception<mguid::Error>());
    REQUIRE(result.error().category == mguid::Error::Category::OutOfRange);
  }
  SECTION("Get Not Empty") {
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    auto result1 = ant1.Get(0);
    auto result2 = ant1.Get(1);
    auto result3 = ant1.Get(2);
    auto result4 = ant1.Get(3);

    REQUIRE(result1.has_value());
    REQUIRE(result2.has_value());
    REQUIRE(result3.has_value());
    REQUIRE(result4.has_value());
  }
  SECTION("Get Invalid Index Not Empty") {
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    auto result = ant1.Get(4);
    REQUIRE(result.has_exception<mguid::Error>());
    REQUIRE(result.error().category == mguid::Error::Category::OutOfRange);
  }
}

TEST_CASE("Array Node Type Set") {
  SECTION("Set Valid Index const &") {
    auto test_id =
        mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    REQUIRE_FALSE(ant1.Set(0, test_id.value()).has_exception<mguid::Error>());
    REQUIRE_FALSE(ant1.Set(1, test_id.value()).has_exception<mguid::Error>());
    REQUIRE_FALSE(ant1.Set(2, test_id.value()).has_exception<mguid::Error>());
    REQUIRE_FALSE(ant1.Set(3, test_id.value()).has_exception<mguid::Error>());
  }
  SECTION("Set Invalid Index const &") {
    auto test_id =
        mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d");
    mguid::ArrayNodeType ant1{{}, {}, {}, {}};
    REQUIRE(ant1.Set(4, test_id.value()).has_exception<mguid::Error>());
  }
}

TEST_CASE("Array Node Type Front") {
  auto test_id_1 =
      mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d").value();
  auto test_id_2 =
      mguid::uuid::from_string("fc64a15a-03ae-4c46-bd13-6fb249a2cf54").value();
  SECTION("Front Has Elements") {
    mguid::ArrayNodeType ant1{test_id_1, test_id_2};
    auto result = ant1.Front();
    REQUIRE(result.has_value());
    REQUIRE(result.value() == test_id_1);
  }
  SECTION("Front Empty") {
    mguid::ArrayNodeType ant1;
    REQUIRE(ant1.Front().has_exception<mguid::Error>());
  }
}

TEST_CASE("Array Node Type Back") {
  auto test_id_1 =
      mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d").value();
  auto test_id_2 =
      mguid::uuid::from_string("fc64a15a-03ae-4c46-bd13-6fb249a2cf54").value();
  SECTION("Back Has Elements") {
    mguid::ArrayNodeType ant1{test_id_1, test_id_2};
    auto result = ant1.Back();
    REQUIRE(result.value() == test_id_2);
  }
  SECTION("Back Empty") {
    mguid::ArrayNodeType ant1;
    REQUIRE(ant1.Back().has_exception<mguid::Error>());
  }
}

TEST_CASE("Array Node Type Empty") {
  SECTION("Empty") {
    mguid::ArrayNodeType ant1;
    REQUIRE(ant1.Empty());
  }
  SECTION("Not Empty") {
    mguid::ArrayNodeType ant1{mguid::uuid{}};
    REQUIRE_FALSE(ant1.Empty());
  }
}

TEST_CASE("Array Node Type Size") {
  SECTION("Empty") {
    mguid::ArrayNodeType ant1;
    REQUIRE(ant1.Size() == 0);
  }
  SECTION("Size 3") {
    mguid::ArrayNodeType ant1{mguid::uuid{}, mguid::uuid{}, mguid::uuid{}};
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
    mguid::ArrayNodeType ant1{mguid::uuid{}, mguid::uuid{}, mguid::uuid{}};
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
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.Begin(), test_id_1);
      auto expected_pos = ant1.Begin();
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_id_1);
    }
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.End(), test_id_1);
      auto expected_pos = ant1.Begin();
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_id_1);
    }
  }
  SECTION("Insert const & Not Empty") {
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();

      mguid::ArrayNodeType ant1{mguid::uuid{}};
      auto iter = ant1.Insert(ant1.End(), test_id_1);
      auto expected_pos = std::next(ant1.Begin());
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_id_1);
    }
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();

      mguid::ArrayNodeType ant1{mguid::uuid{}};
      auto iter = ant1.Insert(ant1.Begin(), test_id_1);
      auto expected_pos = ant1.Begin();
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_id_1);
    }
  }
  SECTION("Insert Count const & Empty") {
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.End(), 2, test_id_1);
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_id_1);
      ++iter;
      REQUIRE(*iter == test_id_1);
    }
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.Begin(), 2, test_id_1);
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_id_1);
      ++iter;
      REQUIRE(*iter == test_id_1);
    }
  }
  SECTION("Insert Count const & Not Empty") {
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();

      mguid::ArrayNodeType ant1{mguid::uuid{}};
      auto iter = ant1.Insert(ant1.End(), 2, test_id_1);
      auto expected_pos_1 = std::next(ant1.Begin());
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_id_1);
      ++iter;
      REQUIRE(*iter == test_id_1);
    }
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();

      mguid::ArrayNodeType ant1{mguid::uuid{}};
      auto iter = ant1.Insert(ant1.Begin(), 2, test_id_1);
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_id_1);
      ++iter;
      REQUIRE(*iter == test_id_1);
    }
  }
  SECTION("Insert Range Empty") {
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();
      auto test_id_2 =
          mguid::uuid::from_string("fc64a15a-03ae-4c46-bd13-6fb249a2cf54")
              .value();

      const std::vector<mguid::uuid> init{test_id_1, test_id_2};

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.End(), init.begin(), init.end());
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_id_1);
      ++iter;
      REQUIRE(*iter == test_id_2);
    }
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();
      auto test_id_2 =
          mguid::uuid::from_string("fc64a15a-03ae-4c46-bd13-6fb249a2cf54")
              .value();

      const std::vector<mguid::uuid> init{test_id_1, test_id_2};

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.Begin(), init.begin(), init.end());
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_id_1);
      ++iter;
      REQUIRE(*iter == test_id_2);
    }
  }
  SECTION("Insert Range Not Empty") {
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();
      auto test_id_2 =
          mguid::uuid::from_string("fc64a15a-03ae-4c46-bd13-6fb249a2cf54")
              .value();

      const std::vector<mguid::uuid> init{test_id_1, test_id_2};

      mguid::ArrayNodeType ant1{mguid::uuid{}};
      auto iter = ant1.Insert(ant1.End(), init.begin(), init.end());
      auto expected_pos_1 = std::next(ant1.Begin());
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_id_1);
      ++iter;
      REQUIRE(*iter == test_id_2);
    }
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();
      auto test_id_2 =
          mguid::uuid::from_string("fc64a15a-03ae-4c46-bd13-6fb249a2cf54")
              .value();

      const std::vector<mguid::uuid> init{test_id_1, test_id_2};

      mguid::ArrayNodeType ant1{mguid::uuid{}};
      auto iter = ant1.Insert(ant1.Begin(), init.begin(), init.end());
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_id_1);
      ++iter;
      REQUIRE(*iter == test_id_2);
    }
  }
  SECTION("Insert Initializer List Empty") {
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();
      auto test_id_2 =
          mguid::uuid::from_string("fc64a15a-03ae-4c46-bd13-6fb249a2cf54")
              .value();

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.End(), {test_id_1, test_id_2});
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_id_1);
      ++iter;
      REQUIRE(*iter == test_id_2);
    }
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();
      auto test_id_2 =
          mguid::uuid::from_string("fc64a15a-03ae-4c46-bd13-6fb249a2cf54")
              .value();

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Insert(ant1.Begin(), {test_id_1, test_id_2});
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_id_1);
      ++iter;
      REQUIRE(*iter == test_id_2);
    }
  }
  SECTION("Insert Initializer List Not Empty") {
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();
      auto test_id_2 =
          mguid::uuid::from_string("fc64a15a-03ae-4c46-bd13-6fb249a2cf54")
              .value();

      mguid::ArrayNodeType ant1{mguid::uuid{}};
      auto iter = ant1.Insert(ant1.End(), {test_id_1, test_id_2});
      auto expected_pos_1 = std::next(ant1.Begin());
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_id_1);
      ++iter;
      REQUIRE(*iter == test_id_2);
    }
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();
      auto test_id_2 =
          mguid::uuid::from_string("fc64a15a-03ae-4c46-bd13-6fb249a2cf54")
              .value();

      mguid::ArrayNodeType ant1{mguid::uuid{}};
      auto iter = ant1.Insert(ant1.Begin(), {test_id_1, test_id_2});
      auto expected_pos_1 = ant1.Begin();
      REQUIRE(iter == expected_pos_1);
      REQUIRE(*iter == test_id_1);
      ++iter;
      REQUIRE(*iter == test_id_2);
    }
  }
}

TEST_CASE("Array Node Type Emplace") {
  SECTION("Emplace const & Empty") {
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Emplace(ant1.Begin(), test_id_1);
      auto expected_pos = ant1.Begin();
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_id_1);
    }
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();

      mguid::ArrayNodeType ant1;
      auto iter = ant1.Emplace(ant1.End(), test_id_1);
      auto expected_pos = ant1.Begin();
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_id_1);
    }
  }
  SECTION("Emplace const & Not Empty") {
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();

      mguid::ArrayNodeType ant1{mguid::uuid{}};
      auto iter = ant1.Emplace(ant1.End(), test_id_1);
      auto expected_pos = std::next(ant1.Begin());
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_id_1);
    }
    {
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();

      mguid::ArrayNodeType ant1{mguid::uuid{}};
      auto iter = ant1.Emplace(ant1.Begin(), test_id_1);
      auto expected_pos = ant1.Begin();
      REQUIRE(iter == expected_pos);
      REQUIRE(*iter == test_id_1);
    }
  }
}

TEST_CASE("Array Node Type Erase") {
  SECTION("Erase Pos") {
    {
      mguid::ArrayNodeType ant1{mguid::uuid{}};
      auto iter = ant1.Erase(ant1.Begin());
      REQUIRE(iter == ant1.End());
      REQUIRE(ant1.Empty());
    }
    {
      mguid::ArrayNodeType ant1{mguid::uuid{}, mguid::uuid{}, mguid::uuid{}};
      auto iter = ant1.Erase(ant1.Begin());
      REQUIRE(iter == ant1.Begin());
      REQUIRE(ant1.Size() == 2);
    }
  }
  SECTION("Erase Range") {
    {
      mguid::ArrayNodeType ant1{mguid::uuid{}};
      auto iter = ant1.Erase(ant1.Begin(), ant1.End());
      REQUIRE(iter == ant1.End());
      REQUIRE(ant1.Empty());
    }
    {
      mguid::ArrayNodeType ant1{mguid::uuid{}, mguid::uuid{}, mguid::uuid{}};
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
    ant1.PushBack(mguid::uuid{});
    REQUIRE(ant1.Size() == 2);
  }
}
TEST_CASE("Array Node Type Emplace Back") {
  SECTION("Emplace Back") {
    mguid::ArrayNodeType ant1;
    ant1.EmplaceBack(mguid::uuid{});
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
      auto test_id_1 =
          mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
              .value();
      mguid::ArrayNodeType ant1{mguid::uuid{}, test_id_1};
      ant1.PopBack();
      REQUIRE(ant1.Back().value().is_nil());
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
    auto test_id_1 =
        mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
            .value();

    mguid::ArrayNodeType ant1{test_id_1};
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
  SECTION("Ordering") {
    auto test_id_1 =
        mguid::uuid::from_string("087704fb-54bd-4b5e-a323-2f954d7aae9d")
            .value();
    auto test_id_2 =
        mguid::uuid::from_string("fc64a15a-03ae-4c46-bd13-6fb249a2cf54")
            .value();
    mguid::ArrayNodeType ant1;
    mguid::ArrayNodeType ant2{{}};
    mguid::ArrayNodeType ant3{test_id_1};
    mguid::ArrayNodeType ant4{test_id_2};
    mguid::ArrayNodeType ant5{{}, {}};
    mguid::ArrayNodeType ant6{test_id_2, test_id_1};
    mguid::ArrayNodeType ant7{test_id_1, test_id_2};

    REQUIRE(ant2 > ant1);
    REQUIRE(ant3 > ant2);
    REQUIRE(ant4 > ant3);
    REQUIRE(ant4 > ant5);
    REQUIRE(ant6 > ant5);
    REQUIRE(ant6 > ant7);
    REQUIRE(ant7 > ant5);

    REQUIRE(ant1 < ant2);
    REQUIRE(ant2 < ant3);
    REQUIRE(ant3 < ant4);
    REQUIRE(ant5 < ant4);
    REQUIRE(ant5 < ant6);
    REQUIRE(ant7 < ant6);
    REQUIRE(ant5 < ant7);

    REQUIRE(ant2 >= ant2);
    REQUIRE(ant2 >= ant1);
    REQUIRE(ant3 >= ant2);
    REQUIRE(ant4 >= ant3);
    REQUIRE(ant4 >= ant5);
    REQUIRE(ant6 >= ant5);
    REQUIRE(ant6 >= ant7);
    REQUIRE(ant7 >= ant5);

    REQUIRE(ant2 <= ant2);
    REQUIRE(ant1 <= ant2);
    REQUIRE(ant2 <= ant3);
    REQUIRE(ant3 <= ant4);
    REQUIRE(ant5 <= ant4);
    REQUIRE(ant5 <= ant6);
    REQUIRE(ant7 <= ant6);
    REQUIRE(ant5 <= ant7);

    REQUIRE(ant2 <=> ant2 == std::strong_ordering::equal);
    REQUIRE(ant1 <=> ant2 == std::strong_ordering::less);
    REQUIRE(ant2 <=> ant3 == std::strong_ordering::less);
    REQUIRE(ant3 <=> ant4 == std::strong_ordering::less);
    REQUIRE(ant5 <=> ant4 == std::strong_ordering::less);
    REQUIRE(ant5 <=> ant6 == std::strong_ordering::less);
    REQUIRE(ant7 <=> ant6 == std::strong_ordering::less);
    REQUIRE(ant5 <=> ant7 == std::strong_ordering::less);

    REQUIRE(ant2 <=> ant1 == std::strong_ordering::greater);
    REQUIRE(ant3 <=> ant2 == std::strong_ordering::greater);
    REQUIRE(ant4 <=> ant3 == std::strong_ordering::greater);
    REQUIRE(ant4 <=> ant5 == std::strong_ordering::greater);
    REQUIRE(ant6 <=> ant5 == std::strong_ordering::greater);
    REQUIRE(ant6 <=> ant7 == std::strong_ordering::greater);
    REQUIRE(ant7 <=> ant5 == std::strong_ordering::greater);
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
  SECTION("Begin") {
    mguid::ArrayNodeType ant1;
    auto iter1 = ant1.Begin();
    auto iter2 = ant1.Begin();
    auto iter3 = ant1.begin();
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
  SECTION("End") {
    mguid::ArrayNodeType ant1;
    auto iter1 = ant1.End();
    auto iter2 = ant1.End();
    auto iter3 = ant1.end();
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
  SECTION("RBegin") {
    mguid::ArrayNodeType ant1;
    auto iter1 = ant1.RBegin();
    auto iter2 = ant1.RBegin();
    auto iter3 = ant1.rbegin();
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
  SECTION("REnd") {
    mguid::ArrayNodeType ant1;
    auto iter1 = ant1.REnd();
    auto iter2 = ant1.REnd();
    auto iter3 = ant1.rend();
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