#include "minilib/cstring.h"

namespace minilib {

void* memmove(void* dest, const void* src, size_t n) {
  if (!dest || !src) {
    return nullptr;
  }

  const char* s = static_cast<const char*>(src);
  char* d = static_cast<char*>(dest);
  if (dest <= src) {
    while (n > 0) {
      --n;
      *d++ = *s++;
    }
  } else {
    while (n > 0) {
      --n;
      *(d + n) = *(s + n);
    }
  }
  return dest;
}

} // namespace minilib
