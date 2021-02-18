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

int isdigit(int c)
{
  return (unsigned int)(c - '0') <= 9;
}

long atol(const char *s)
{
  unsigned long ret = 0;
  unsigned long d;
  int neg = 0;

  if (*s == '-') 
  {
    neg = 1; s++;
  }

  while (1) 
  {
    d = (*s++) - '0';
    if (d > 9) { break; }
    ret *= 10;
    ret += d;
  }

  return neg ? -ret : ret;
}

long atoi(const char *s) { return atol(s); }

const char *ltoa(long in)
{
  /* large enough for -9223372036854775808 */
  static char buffer[21];
  char       *pos = buffer + sizeof(buffer) - 1;
  int         neg = in < 0;
  unsigned long n = neg ? -in : in;
  *pos-- = '\0';
  do {
    *pos-- = '0' + n % 10;
    n /= 10;
    if (pos < buffer)
    return pos + 1;
  } while (n);

  if (neg) { *pos-- = '-'; }
  return pos + 1;
  
}

void itoa(char *buf, unsigned long int n, int base)
{
    unsigned long int tmp;
    int i, j;

    tmp = n;
    i = 0;

    do {
        tmp = n % base;
        buf[i++] = (tmp < 10) ? (tmp + '0') : (tmp + 'a' - 10);
    } while (n /= base);
    buf[i--] = 0;

    for (j = 0; j < i; j++, i--) {
        tmp = buf[j];
        buf[j] = buf[i];
        buf[i] = tmp;
    }
}

char *strcpy(char *dest, const char *src)
{
  char *tmp = dest;  
  while ((*dest++ = *src++) != '\0');
  return tmp;
}
