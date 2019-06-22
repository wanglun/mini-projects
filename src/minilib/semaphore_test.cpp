#include <thread>
#include <gtest/gtest.h>

#include "minilib/semaphore.h"

namespace minilib {

TEST(semaphore, basic) {
  Semaphore sem;

  ASSERT_FALSE(sem.try_wait());

  std::thread th_notify(
      [](Semaphore& s) {
        for (int i = 0; i < 4; ++i) {
          s.notify();
        }
      }, std::ref(sem));
  std::thread th_wait(
      [](Semaphore& s) {
        for (int i = 0; i < 4; ++i) {
          s.wait();
        }
      }, std::ref(sem));
  th_notify.join();
  th_wait.join();
}

} // namespace minilib
