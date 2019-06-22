#ifndef MINILIB_BLOCKING_QUEUE_H
#define MINILIB_BLOCKING_QUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>

namespace minilib {

// blocking_queue是一个固定大小的阻塞队列，
// push时，如果已满，则使用条件变量阻塞等待
// pop时，如果已空，则使用条件变量阻塞等待
template <typename T>
class blocking_queue {
 public:
  typedef T type;
  explicit blocking_queue(size_t size) : size_(size) {}
  ~blocking_queue() {}

  void pop(type& v) {
    // 需要使用unique_lock，因为在wait时先会原子的unlock，若满足条件则重新lock
    std::unique_lock<std::mutex> lk(cv_m_);
    while (queue_.empty()) {
      cv_.wait(lk);
    }
    v = std::move(queue_.front());
    queue_.pop();

    cv_.notify_one();
  }

  void push(const type& v) {
    std::unique_lock<std::mutex> lk(cv_m_);
    while (queue_.size() >= size_) {
      cv_.wait(lk);
    }
    queue_.push(v);

    cv_.notify_one();
  }

  void push(type&& v) {
    std::unique_lock<std::mutex> lk(cv_m_);
    while (queue_.size() >= size_) {
      cv_.wait(lk);
    }
    queue_.push(std::move(v));

    cv_.notify_one();
  }

 private:
  blocking_queue(const blocking_queue&) = delete;
  blocking_queue& operator=(const blocking_queue&) = delete;

  size_t size_;
  std::queue<type> queue_;
  std::mutex cv_m_;
  std::condition_variable cv_;
};

}  // namespace minilib

#endif  // MINILIB_BLOCKING_QUEUE_H
