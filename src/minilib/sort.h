#ifndef MINILIB_SORT_H
#define MINILIB_SORT_H

#include <algorithm>
#include <vector>

namespace minilib {

template <typename T>
void shell_sort(std::vector<T>& vec) {
  size_t h = 1;
  while (h < vec.size() / 3) {
    h = 3 * h + 1;
  }

  while (h >= 1) {
    for (size_t i = h; i < vec.size(); ++i) {
      for (size_t j = i; j >= h && vec[j] < vec[j - h]; j -= h) {
        std::swap(vec[j], vec[j - h]);
      }
    }
    h = h / 3;
  }
}

template <typename T>
void quick_sort(std::vector<T>& arr, size_t low, size_t high) {
  if (low >= high) {
    return;
  }

  size_t pivot = low;
  size_t slow = pivot;
  size_t fast = pivot + 1;
  for (; fast <= high; ++fast) {
    if (arr[fast] <= arr[pivot]) {
      ++slow;
      std::swap(arr[fast], arr[slow]);
    }
  }
  std::swap(arr[pivot], arr[slow]);

  if (slow > 0) {
    quick_sort(arr, low, slow - 1);
  }
  quick_sort(arr, slow + 1, high);
}

template <typename T>
std::vector<T> merge_sort(const std::vector<T>& vec, size_t low, size_t high) {
  if (low == high) {
    return {vec[low]};
  }
  if (low > high) {
    return {};
  }

  std::vector<T> ret;

  size_t mid = low + (high - low) / 2;
  auto left_vec = merge_sort(vec, low, mid);
  auto right_vec = merge_sort(vec, mid + 1, high);
  size_t i = 0;
  size_t j = 0;
  while (i < left_vec.size() && j < right_vec.size()) {
    if (left_vec[i] <= right_vec[j]) {
      ret.push_back(left_vec[i]);
      ++i;
    } else {
      ret.push_back(right_vec[j]);
      ++j;
    }
  }
  for (; i < left_vec.size(); ++i) {
    ret.push_back(left_vec[i]);
  }
  for (; j < right_vec.size(); ++j) {
    ret.push_back(right_vec[j]);
  }

  return std::move(ret);
}

// left = root * 2 + 1
// right = root * 2 + 2
// root = (child - 1) / 2
// node_end = size / 2 - 1
template <typename T>
void heap_sort_sift_down(std::vector<T>& vec, size_t size, size_t i) {
  while (i < size) {
    size_t left = i * 2 + 1;
    size_t right = i * 2 + 2;
    size_t tmp = i;
    if (left < size && vec[tmp] > vec[left]) {
      tmp = left;
    }
    if (right < size && vec[tmp] > vec[right]) {
      tmp = right;
    }
    if (i == tmp) {
      break;
    }
    std::swap(vec[i], vec[tmp]);
    i = tmp;
  }
}

template <typename T>
void heap_sort(std::vector<T>& vec) {
  // build heap
  size_t node_end = vec.size() / 2 - 1;
  for (size_t i = 0; i <= node_end; ++i) {
    // sift_down
    heap_sort_sift_down(vec, vec.size(), node_end - i);
  }

  // sort
  for (size_t i = 0 ; i < vec.size(); ++i) {
    std::swap(vec[0], vec[vec.size() - i - 1]);
    // sift_down
    heap_sort_sift_down(vec, vec.size() - i - 1, 0);
  }

  // reverse
  for (size_t i = 0, j = vec.size() - 1; i < j; ++i, --j) {
    std::swap(vec[i], vec[j]);
  }
}

} // namespace minilib

#endif // MINILIB_SORT_H
