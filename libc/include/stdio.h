#ifndef _STDIO_H
#define _STDIO_H 1
 
#include <sys/cdefs.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
 
#define EOF (-1)
 
#ifdef __cplusplus
extern "C" {
#endif
 
void printf(const char* format, ...);
void putchar(char c);
int puts(const char*);
void __vsprintf_internal(char *str, void (*putchar)(char),
                         const char* restrict format, uint32_t *pos,
                         va_list arg);
void __vsprintf_w(char * str, void (*putchar)(char), const char * format, va_list arg);

#ifdef __cplusplus
}
#endif
 
#endif
