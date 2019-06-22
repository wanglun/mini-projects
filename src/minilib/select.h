#ifndef MINILIB_SELECT_H
#define MINILIB_SELECT_H

#include <algorithm>
#include <vector>

namespace minilib {

// T: avg O(n) best O(n) worst O(n^2)
// low <= k <= high
template <typename T>
T quick_select(std::vector<T>& vec, size_t k, size_t low, size_t high) {
  if (low == high) {
    return vec[low];
  }

  size_t pivot = low;
  size_t slow = pivot;
  size_t fast = pivot + 1;

  // partition
  for (; fast <= high; ++fast) {
    if (vec[fast] <= vec[pivot]) {
      ++slow;
      std::swap(vec[slow], vec[fast]);
    }
  }
  std::swap(vec[pivot], vec[slow]);

  if (k == slow) {
    return vec[slow];
  } else if (k < slow) {
    return quick_select(vec, k, low, slow - 1);
  } else {
    return quick_select(vec, k, slow + 1, high);
  }
}

} // namespace minilib

#endif // MINILIB_SELECT_H
