#include <gtest/gtest.h>

#include "minilib/select.h"

namespace minilib {

TEST(select, quick_select) {
  {
    std::vector<int> vec{4, 2, 5, 10, 3, 2, 20};
    EXPECT_EQ(4, quick_select(vec, 3, 0, vec.size() - 1));
  }
  {
    std::vector<int> vec{4, 2, 5, 10, 3, 2, 20};
    EXPECT_EQ(2, quick_select(vec, 0, 0, vec.size() - 1));
  }
  {
    std::vector<int> vec{4, 2, 5, 10, 3, 2, 20};
    EXPECT_EQ(20, quick_select(vec, 6, 0, vec.size() - 1));
  }
}

}  // namespace minilib
