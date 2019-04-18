#include <gflags/gflags.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>

#include "minilib/priority_queue.h"

namespace minilib {

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
  for (int i : v) {
    os << i << " ";
  }
  return os;
}

TEST(priority_queue, max_heap) {
  priority_queue<int> h;
  std::vector<int> seq{3, 4, 1, 1, 10, 6};
  std::vector<int> h_built{10, 4, 6, 1, 3, 1};
  for (int v : seq) {
    h.push(v);
  }
  ASSERT_EQ(seq.size(), h.size());
  ASSERT_FALSE(h.empty());
  ASSERT_EQ(h_built, h.arr_);

  std::sort(seq.begin(), seq.end(), [](int i, int j) { return i > j; });
  size_t i = 0;
  for (; !h.empty(); ++i) {
    ASSERT_EQ(seq[i], h.top());
    h.pop();
  }
  ASSERT_EQ(seq.size(), i);
}

TEST(priority_queue, min_heap) {
  priority_queue<int, std::greater<int>> h;
  std::vector<int> seq{3, 4, 1, 1, 10, 6};
  std::vector<int> h_built{1, 1, 3, 4, 10, 6};
  for (int v : seq) {
    h.push(v);
  }
  ASSERT_EQ(seq.size(), h.size());
  ASSERT_FALSE(h.empty());
  ASSERT_EQ(h_built, h.arr_);

  std::sort(seq.begin(), seq.end());
  size_t i = 0;
  for (; !h.empty(); ++i) {
    ASSERT_EQ(seq[i], h.top());
    h.pop();
  }
  ASSERT_EQ(seq.size(), i);
}

TEST(priority_queue, sift_down) {
  priority_queue<int> h;
  h.arr_ = {1, 4, 6, 1, 3};
  h.sift_down(0);
  std::vector<int> target = {6, 4, 1, 1, 3};
  ASSERT_EQ(target, h.arr_);
}

TEST(priority_queue, sift_up) {
  priority_queue<int> h;
  h.arr_ = {6, 4, 5, 1, 3, 2, 7};
  h.sift_up(h.arr_.size() - 1);
  std::vector<int> target = {7, 4, 6, 1, 3, 2, 5};
  ASSERT_EQ(target, h.arr_);
}

}  // namespace minilib
