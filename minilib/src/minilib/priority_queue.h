#include <vector>

template <typename T>
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
  void heapify();
  void sift_down(size_t root);
  void sift_up(size_t root);

  size_t parent(size_t i) const { return i == 0 ? 0 : (i - 1) / 2; }
  size_t left_child(size_t i) const { return i * 2 + 1; }
  size_t right_child(size_t i) const { return i * 2 + 2; }

  std::vector<T> arr_;
};

template <typename T>
priority_queue<T>::priority_queue() {}

template <typename T>
priority_queue<T>::~priority_queue() {}

template <typename T>
void priority_queue<T>::push(const T& v) {
  arr_.push_back(v);
  sift_up(arr_.size() - 1);
}

template <typename T>
void priority_queue<T>::push(T&& v) {
  arr_.push_back(std::move(v));
  sift_up(arr_.size() - 1);
}

template <typename T>
void priority_queue<T>::pop() {
  arr_[0] = arr_.back();
  arr_.pop_back();
  if (!arr_.empty()) {
    sift_down(0);
  }
}

template <typename T>
void priority_queue<T>::heapify() {}

template <typename T>
void priority_queue<T>::sift_down(size_t root) {
  while (root < arr_.size()) {
    size_t l = left_child(root);
    size_t r = right_child(root);
    size_t s = root;
    if (l < arr_.size() && arr_[l] > arr_[root]) {
      s = l;
    }
    if (r < arr_.size() && arr_[r] > arr_[s]) {
      s = r;
    }
    if (root == s) {
      break;
    }
    std::swap(arr_[root], arr_[s]);
    root = s;
  }
}

template <typename T>
void priority_queue<T>::sift_up(size_t root) {
  while (root > 0) {
    size_t p = parent(root);
    if (p >= 0 && arr_[p] < arr_[root]) {
      std::swap(arr_[root], arr_[p]);
      root = p;
    } else {
      break;
    }
  }
}
