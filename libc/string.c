#include <string.h>
#include <stddef.h>

// string length
size_t strlen(const char* str)
{
  int len = 0;
  while(str[len]) { len++; }
  return len;
}
