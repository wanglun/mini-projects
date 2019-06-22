#include <gtest/gtest.h>
#include <string>

#include "minilib/blocking_queue.h"

namespace minilib {

TEST(cstring, memmove_dest_lg_src) {
  std::string s("abcdefg");
  const char* src = s.c_str();
  char* dest = const_cast<char*>(src) + 2;
  char* res = static_cast<char*>(memmove(dest, src, 3));
  ASSERT_EQ(dest, res);
  ASSERT_EQ("abc", std::string(dest, 3));
}

TEST(cstring, memmove_dest_le_src) {
  std::string s("abcdefg");
  const char* src = s.c_str() + 2;
  char* dest = const_cast<char*>(src);
  char* res = static_cast<char*>(memmove(dest, src, 3));
  ASSERT_EQ(dest, res);
  ASSERT_EQ("cde", std::string(dest, 3));
}

}
