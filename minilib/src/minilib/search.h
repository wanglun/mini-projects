#ifndef MINILIB_SEARCH_H
#define MINILIB_SEARCH_H

#include <vector>

namespace minilib {

// T: O(logn)
// return index when found, else return -1
// Note: return the smallest index when found more than 1 targets
template <typename T>
int binary_search(const std::vector<T>& vec, T target) {
  int low = 0;
  int high = vec.size() - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (vec[mid] >= target) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return (low < vec.size() && vec[low] == target) ? low : -1;
}

// T: O(logn)
template <typename T>
int lower_bound(const std::vector<T>& vec, T target) {
  int low = 0;
  int high = vec.size() - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (vec[mid] >= target) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return low;
}

// T: O(logn)
template <typename T>
int upper_bound(const std::vector<T>& vec, T target) {
  int low = 0;
  int high = vec.size() - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (vec[mid] > target) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return low;
}

} // namespace minilib

#endif // MINILIB_SEARCH_H
