/**
 * @brief Tests for array node type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

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
  // TODO
}
TEST_CASE("Array Node Type Emplace") {
  // TODO
}
TEST_CASE("Array Node Type Erase") {
  // TODO
}
TEST_CASE("Array Node Type Push Back") {
  // TODO
}
TEST_CASE("Array Node Type Emplace Back") {
  // TODO
}
TEST_CASE("Array Node Type Pop Back") {
  // TODO
}
TEST_CASE("Array Node Type Pop Comparison") {
  // TODO
}
TEST_CASE("Array Node Type Iterators") {
  // TODO
}