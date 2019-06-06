#include <gtest/gtest.h>

#include "minilib/sort.h"

namespace minilib {

TEST(sort, shell_sort_vector) {
  std::vector<int> vec{4, 2, 5, 10, 3, 2, 20};
  std::vector<int> expect_vec{2, 2, 3, 4, 5, 10, 20};

  shell_sort(vec);
  EXPECT_EQ(expect_vec, vec);

  vec = {-1, -2, 10, -4, 15, 0};
  expect_vec = {-4, -2, -1, 0, 10, 15};
  shell_sort(vec);
  EXPECT_EQ(expect_vec, vec);
}

TEST(sort, quick_sort_vector) {
  std::vector<int> vec{4, 2, 5, 10, 3, 2, 20};
  std::vector<int> expect_vec{2, 2, 3, 4, 5, 10, 20};

  quick_sort(vec, 0, vec.size() - 1);
  EXPECT_EQ(expect_vec, vec);

  vec = {-1, -2, 10, -4, 15, 0};
  expect_vec = {-4, -2, -1, 0, 10, 15};
  quick_sort(vec, 0, vec.size() - 1);
  EXPECT_EQ(expect_vec, vec);
}

TEST(sort, merge_sort_vector) {
  std::vector<int> vec{4, 2, 5, 10, 3, 2, 20};
  std::vector<int> expect_vec{2, 2, 3, 4, 5, 10, 20};

  vec = merge_sort(vec, 0, vec.size() - 1);
  EXPECT_EQ(expect_vec, vec);

  vec = {-1, -2, 10, -4, 15, 0};
  expect_vec = {-4, -2, -1, 0, 10, 15};
  vec = merge_sort(vec, 0, vec.size() - 1);
  EXPECT_EQ(expect_vec, vec);
}

TEST(sort, heap_sort_vector) {
  std::vector<int> vec{4, 2, 5, 10, 3, 2, 20};
  std::vector<int> expect_vec{2, 2, 3, 4, 5, 10, 20};

  heap_sort(vec);
  EXPECT_EQ(expect_vec, vec);

  vec = {-1, -2, 10, -4, 15, 0};
  expect_vec = {-4, -2, -1, 0, 10, 15};
  heap_sort(vec);
  EXPECT_EQ(expect_vec, vec);
}

}  // namespace minilib
