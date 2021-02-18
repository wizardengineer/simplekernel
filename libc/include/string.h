#ifndef _STRING_H
#define _STRING_H 1
 
#include <sys/cdefs.h>
 
#include <stddef.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
int memcmp(const void*, const void*, size_t);

void* memcpy(void* __restrict, const void* __restrict, size_t);

void* memmove(void*, const void*, size_t);

void* memset(void*, int, size_t);

size_t strlen(const char*);

int isdigit(int c);

long atol(const char *s);

long atoi(const char *s);

const char* ltoi(long in);

char *strcpy(char *dest, const char *src);

void itoa(char *buf, unsigned long int n, int base);

#ifdef __cplusplus
}
#endif
 
#endif
