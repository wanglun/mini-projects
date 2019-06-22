#include <gflags/gflags.h>
#include <gtest/gtest.h>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "minilib/blocking_queue.h"

namespace minilib {

TEST(blocking_queue, basic) {
  blocking_queue<int> q(3);
  std::thread th_push(
      [](blocking_queue<int>& q) {
        for (int i = 0; i < 4; ++i) {
          q.push(i);
          std::cout << "pushed:" << i << std::endl;
        }
      },
      std::ref(q));

  std::thread th_pop(
      [](blocking_queue<int>& q) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for (int i = 0; i < 2; ++i) {
          int val = 0;
          q.pop(val);
          std::cout << "poped:" << val << std::endl;
        }
      },
      std::ref(q));

  th_push.join();
  th_pop.join();
}

}  // namespace minilib
