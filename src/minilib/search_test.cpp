#include <gtest/gtest.h>

#include "minilib/search.h"

namespace minilib {

TEST(search, binary_search) {
  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(3, binary_search(vec, 10));
  }

  {
    std::vector<int> vec{-1, 0, 13, 13, 13, 13, 13, 13, 20};
    EXPECT_EQ(2, binary_search(vec, 13));
  }

  {
    std::vector<int> vec{-1, 0, 2, 3, 13, 13, 20};
    EXPECT_EQ(4, binary_search(vec, 13));
  }

  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(6, binary_search(vec, 20));
  }

  {
    std::vector<int> vec{};
    EXPECT_EQ(-1, binary_search(vec, 20));
  }

  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(-1, binary_search(vec, 3));
  }
}

TEST(search, lower_bound) {
  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(3, lower_bound(vec, 10));
  }

  {
    std::vector<int> vec{-1, 0, 13, 13, 13, 13, 13, 13, 20};
    EXPECT_EQ(2, lower_bound(vec, 13));
  }

  {
    std::vector<int> vec{-1, 0, 2, 3, 13, 13, 20};
    EXPECT_EQ(4, lower_bound(vec, 13));
  }

  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(6, lower_bound(vec, 20));
  }

  {
    std::vector<int> vec{};
    EXPECT_EQ(0, lower_bound(vec, 20));
  }

  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(2, lower_bound(vec, 3));
  }

  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(7, lower_bound(vec, 30));
  }

  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(0, lower_bound(vec, -2));
  }
}

TEST(search, upper_bound) {
  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(4, upper_bound(vec, 10));
  }

  {
    std::vector<int> vec{-1, 0, 13, 13, 13, 13, 13, 13, 20};
    EXPECT_EQ(8, upper_bound(vec, 13));
  }

  {
    std::vector<int> vec{-1, 0, 2, 3, 13, 13, 20};
    EXPECT_EQ(6, upper_bound(vec, 13));
  }

  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(7, upper_bound(vec, 20));
  }

  {
    std::vector<int> vec{};
    EXPECT_EQ(0, upper_bound(vec, 20));
  }

  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(2, upper_bound(vec, 3));
  }

  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(7, upper_bound(vec, 30));
  }

  {
    std::vector<int> vec{-1, 2, 5, 10, 13, 13, 20};
    EXPECT_EQ(0, upper_bound(vec, -2));
  }
}

}  // namespace minilib
