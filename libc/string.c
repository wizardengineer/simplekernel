#include <string.h>
#include <stddef.h>

// string length
size_t strlen(const char* str)
{
  int len = 0;
  while(str[len]) { len++; }
  return len;
}

// memory move
void* memmove(void* dstptr, const void* srcptr, size_t size)
{
  unsigned char* dst = (unsigned char*) dstptr;
  const unsigned char* src = (const unsigned char*) srcptr;
  if (dst < src) {
    for (size_t i = 0; i < size; i++) { dst[i] = src[i]; }
  } 
  else {
    for (size_t i = size; i != 0; i--) { dst[i-1] = src[i-1]; }
  }
  return dstptr;
}

// memcpy and memset
//

void *memset (void *dest, int val, size_t len)
{
  unsigned char *ptr = dest;
  while (len-- > 0)
    *ptr++ = val;
  return dest;
}

void *memcpy (void *dest, const void *src, size_t len)
{
  char *d = dest;
  const char *s = src;
  while (len--)
    *d++ = *s++;
  return dest;
}

