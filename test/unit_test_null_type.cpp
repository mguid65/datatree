/**
 * @brief Tests for null value type
 * @author Matthew Guidry (github: mguid65)
 * @date 2024-02-05
 */

#include <catch2/catch_all.hpp>

#include <datatree/node_types/detail/null_type.hpp>
#include <type_traits>

TEST_CASE("Null Type Traits") {
  SECTION("Trivially Default Constructible") {
    REQUIRE(std::is_trivially_default_constructible_v<mguid::NullType>);
  }
  SECTION("Trivially Copy Constructible") {
    REQUIRE(std::is_trivially_copy_constructible_v<mguid::NullType>);
  }
  SECTION("Trivially Copy Assignable") {
    REQUIRE(std::is_trivially_copy_assignable_v<mguid::NullType>);
  }
  SECTION("Trivially Destructible") {
    REQUIRE(std::is_trivially_destructible_v<mguid::NullType>);
  }
  SECTION("Constexpr Constructible") {
    constexpr mguid::NullType nt;
    ((void) nt);
  }
}

TEST_CASE("Null Type Comparisons") {
  SECTION("Comparisons") {
    constexpr mguid::NullType nt1;
    constexpr mguid::NullType nt2;

    // Comparisons are correct and noexcept
    REQUIRE((nt1 == nt2));
    REQUIRE(noexcept((nt1 == nt2)));

    REQUIRE((nt2 == nt1));
    REQUIRE(noexcept((nt2 == nt1)));

    REQUIRE(!(nt1 != nt2));
    REQUIRE(noexcept(!(nt1 != nt2)));

    REQUIRE(!(nt2 != nt1));
    REQUIRE(noexcept(!(nt2 != nt1)));

    REQUIRE(!(nt1  < nt2));
    REQUIRE(noexcept(!(nt1  < nt2)));

    REQUIRE(!(nt2  < nt1));
    REQUIRE(noexcept(!(nt2  < nt1)));

    REQUIRE((nt1 <= nt2));
    REQUIRE(noexcept((nt1 <= nt2)));

    REQUIRE((nt2 <= nt1));
    REQUIRE(noexcept((nt2 <= nt1)));

    REQUIRE(!(nt1  > nt2));
    REQUIRE(noexcept(!(nt1  > nt2)));

    REQUIRE(!(nt2  > nt1));
    REQUIRE(noexcept(!(nt2  > nt1)));

    REQUIRE((nt1 >= nt2));
    REQUIRE(noexcept((nt1 >= nt2)));

    REQUIRE((nt2 >= nt1));
    REQUIRE(noexcept((nt2 >= nt1)));

    // Ordered comparison is correct and noexcept

    REQUIRE(nt1 <=> nt2 == std::strong_ordering::equal);
    REQUIRE(noexcept(nt1 <=> nt2));
  }
}

TEST_CASE("Null Type Hash") {
  using hash_type = std::hash<mguid::NullType>;
  const auto hsh = hash_type{};

  mguid::NullType nt1;
  const mguid::NullType nt2;

  REQUIRE(hsh(nt1) == hsh(nt1));
  REQUIRE(hsh(nt2) == hsh(nt2));
  REQUIRE(hsh(nt1) == hsh(nt2));

  REQUIRE(std::is_same_v<decltype(hsh(nt1)), std::size_t>);
  REQUIRE(noexcept(hsh(nt1)));
  REQUIRE(std::is_copy_constructible_v<hash_type>);
}