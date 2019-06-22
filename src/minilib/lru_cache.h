#ifndef MINILIB_LRU_CACHE_H
#define MINILIB_LRU_CACHE_H

#include <list>
#include <unordered_map>

namespace minilib {

template <typename K, typename V>
class LruCache {
public:
  typedef K key_type;
  typedef V value_type;
  typedef std::pair<K, V> pair_type;

  explicit LruCache(size_t capacity) : capacity_(capacity) {
  }

  size_t size() const { return map_.size(); }
  size_t capacity() const { return capacity_; }

  void put(const key_type& key, const value_type& val) {
    auto it = map_.find(key);
    if (it == map_.end()) {
      if (map_.size() == capacity_) {
        map_.erase(list_.back().first);
        list_.pop_back();
      }
      list_.push_front({key, val});
      map_[key] = list_.begin();
    } else {
      *(it->second) = {key, val};
      list_.splice(list_.begin(), list_, it->second);
    }
  }

  bool get(const key_type& key, value_type& val) {
    auto it = map_.find(key);
    if (it == map_.end()) {
      return false;
    }

    val = it->second->second;
    list_.splice(list_.begin(), list_, it->second);
    return true;
  }

private:
  typedef std::list<pair_type> list_type;
  typedef typename list_type::iterator list_iterator;
  typedef std::unordered_map<key_type, list_iterator> map_type;

  size_t capacity_;
  list_type list_;
  map_type map_;
};

} // namespace minilib

#endif // MINILIB_LRU_CACHE_H
