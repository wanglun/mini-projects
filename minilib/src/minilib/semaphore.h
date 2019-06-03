#ifndef MINILIB_SEMAPHORE_H
#define MINILIB_SEMAPHORE_H

#include <mutex>
#include <condition_variable>

namespace minilib {

class Semaphore {
public:
  // unlock
  void notify() {
    std::lock_guard<std::mutex> lk(m_);
    ++count_;
    cv_.notify_one();
  }

  // lock
  void wait() {
    std::unique_lock<std::mutex> lk(m_);
    // equals to:
    // while (count_ == 0) {
    //   cv_.wait(lk);
    // }
    cv_.wait(lk, [this]{ return count_ > 0; });
    --count_;
  }

  // try to lock
  bool try_wait() {
    std::lock_guard<std::mutex> lk(m_);
    if (count_ > 0) {
      --count_;
      return true;
    }
    return false;
  }
private:
  std::mutex m_;
  std::condition_variable cv_;
  size_t count_ = 0;
};

} // namespace minilib

#endif // MINILIB_SEMAPHORE_H
