#ifndef MINILIB_PRIORITY_QUEUE_H
#define MINILIB_PRIORITY_QUEUE_H

#include <functional>
#include <vector>

template <typename T, typename Compare = std::less<T>>
class priority_queue {
 public:
  priority_queue();
  ~priority_queue();

  void push(const T& v);
  void push(T&& v);
  void pop();
  const T& top() const { return arr_.front(); }
  size_t size() const { return arr_.size(); }
  size_t empty() const { return arr_.empty(); }

 private:
  void sift_down(size_t root);
  void sift_up(size_t root);

  size_t parent(size_t i) const { return i == 0 ? 0 : (i - 1) / 2; }
  size_t left_child(size_t i) const { return i * 2 + 1; }
  size_t right_child(size_t i) const { return i * 2 + 2; }

  std::vector<T> arr_;
  Compare cmp_;
};

template <typename T, typename Compare>
priority_queue<T, Compare>::priority_queue() {}

template <typename T, typename Compare>
priority_queue<T, Compare>::~priority_queue() {}

template <typename T, typename Compare>
void priority_queue<T, Compare>::push(const T& v) {
  arr_.push_back(v);
  sift_up(arr_.size() - 1);
}

template <typename T, typename Compare>
void priority_queue<T, Compare>::push(T&& v) {
  arr_.push_back(std::move(v));
  sift_up(arr_.size() - 1);
}

template <typename T, typename Compare>
void priority_queue<T, Compare>::pop() {
  arr_[0] = arr_.back();
  arr_.pop_back();
  if (!arr_.empty()) {
    sift_down(0);
  }
}

template <typename T, typename Compare>
void priority_queue<T, Compare>::sift_down(size_t root) {
  while (root < arr_.size()) {
    size_t l = left_child(root);
    size_t r = right_child(root);
    size_t s = root;
    if (l < arr_.size() && !cmp_(arr_[l], arr_[root])) {
      s = l;
    }
    if (r < arr_.size() && !cmp_(arr_[r], arr_[s])) {
      s = r;
    }
    if (root == s) {
      break;
    }
    std::swap(arr_[root], arr_[s]);
    root = s;
  }
}

template <typename T, typename Compare>
void priority_queue<T, Compare>::sift_up(size_t root) {
  while (root > 0) {
    size_t p = parent(root);
    if (p >= 0 && cmp_(arr_[p], arr_[root])) {
      std::swap(arr_[root], arr_[p]);
      root = p;
    } else {
      break;
    }
  }
}

#endif  // MINILIB_PRIORITY_QUEUE_H
