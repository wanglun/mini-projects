#include <memory>
#include <gtest/gtest.h>

#include "minilib/lru_cache.h"

namespace minilib {

TEST(lru_cache, basic) {
  LruCache<int, int> lru_cache(2);
  int val;
  EXPECT_FALSE(lru_cache.get(10, val));

  lru_cache.put(1, 1);
  lru_cache.put(2, 2);
  EXPECT_EQ(2, lru_cache.size());
  EXPECT_TRUE(lru_cache.get(1, val));
  EXPECT_EQ(1, val);
  // refresh 2
  EXPECT_TRUE(lru_cache.get(2, val));
  EXPECT_EQ(2, val);
  // re get 2
  EXPECT_TRUE(lru_cache.get(2, val));
  EXPECT_EQ(2, val);
  EXPECT_FALSE(lru_cache.get(3, val));

  // will erase {1, 1}
  lru_cache.put(3, 3);
  EXPECT_EQ(2, lru_cache.size());
  EXPECT_TRUE(lru_cache.get(2, val));
  EXPECT_EQ(2, val);
  EXPECT_FALSE(lru_cache.get(1, val));
  EXPECT_TRUE(lru_cache.get(3, val));
  EXPECT_EQ(3, val);
}

TEST(lru_cache, shared_ptr) {
  typedef std::shared_ptr<int> val_type;
  LruCache<int, val_type> lru_cache(2);
  val_type val;
  EXPECT_FALSE(lru_cache.get(10, val));

  lru_cache.put(1, val_type(new int(1)));
  lru_cache.put(2, val_type(new int(2)));
  EXPECT_EQ(2, lru_cache.size());
  EXPECT_TRUE(lru_cache.get(1, val));
  EXPECT_EQ(1, *val.get());
  // refresh 2
  EXPECT_TRUE(lru_cache.get(2, val));
  EXPECT_EQ(2, *val.get());
  // re get 2
  EXPECT_TRUE(lru_cache.get(2, val));
  EXPECT_EQ(2, *val.get());
  EXPECT_FALSE(lru_cache.get(3, val));

  // will erase {1, 1}
  lru_cache.put(3, val_type(new int(3)));
  EXPECT_EQ(2, lru_cache.size());
  EXPECT_TRUE(lru_cache.get(2, val));
  EXPECT_EQ(2, *val.get());
  EXPECT_FALSE(lru_cache.get(1, val));
  EXPECT_TRUE(lru_cache.get(3, val));
  EXPECT_EQ(3, *val.get());
}

}  // namespace minilib
