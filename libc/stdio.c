#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <kernel/tty.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#pragma GCC diagnostic ignored "-Wunused-variable"

/* Minimum and maximum values a `signed int' can hold. */ 
#   ifndef __INT_MAX__
#    define __INT_MAX__ 2147483647
#   endif
#   undef INT_MIN
#   define INT_MIN (-INT_MAX-1)
#   undef INT_MAX
#   define INT_MAX __INT_MAX__


static int is_format_letter(char c) 
{
    return c == 'c' ||  c == 'd' || c == 'i' || c == 'e' 
                    ||  c == 'E' || c == 'f' || c == 'g' 
                    ||  c == 'G' || c == 'o' || c == 's' 
                    ||  c == 'u' || c == 'x' || c == 'X' 
                    ||  c == 'p' || c == 'n';
}


void putchar(char c) { terminal_putchar(c); }

/* __vsprintf_internal wrapper */
void __vsprintf_w(char * str, void (*putchar)(char), const char * format, va_list arg) 
{
  uint32_t pos = 0;
  __vsprintf_internal(str, putchar, format, &pos, arg);
}

void __vsprintf_internal(char *str, void (*putchar)(char),
                         const char* restrict format, uint32_t *pos,
                         va_list arg)
{
  char c = ' ';
  int sign = 0, 
      ival = 0, 
      base = 0;

  char     buffer[512];
  char     width_str[10];
  uint32_t uval = 0;
  uint32_t size = 8;
  uint32_t i = 0;
  
  int size_override = 0;
  memset(buffer, 0, 512);
  
  //if(format == NULL) { invoke_str_constraint("format is null\n"); return; }
  //if(putchar == NULL) { invoke_str_constraint("function ptr is null\n"); return; }
  while((c = *format++) != 0) {

    if(c == '%')
    {
      c = *format++;
      switch(c) {
        // will handle printf("%08x", 0xaa)
        case '0':
          size_override = 1;
          // gets the number between 0 and x/d/p, e.g 8 in 08x
          c = *format;
          while(!is_format_letter(c)) 
          {
            width_str[i++] = c;
            format++;
            c = *format;
          }
          width_str[i] = 0;
          format++;
          // convert to a number
          size = atoi(width_str);
        case 'd':
        case 'u':
        case 'x':
        case 'p':
          base = (c == 'd' || c == 'u' ? 10 : 16);
          
          uval = ival = va_arg(arg, int);
          if(c == 'd' && ival < 0)
          {
            sign = 1;
            uval = -ival;
          }
          itoa(buffer, uval, base);
          uint32_t len = strlen(buffer);

          // if width wasn't specify
          if(!size_override)  { size = len; }
          if((c == 'x' || c == 'p' || c == 'd') && len < size)
          {
            for(i = 0; i < len; i++) {
              buffer[size - 1 - i] = buffer[len - 1 - i];
            }
            for(i = 0; i < size - len; i++) {
              buffer[i] = '0';
            }
          }
          if(c == 'd' && sign)
          {
            if(str) {
              *(str + *pos) = '-';
              *pos = *pos + 1;
            } else { (*putchar)('-'); }
          } 
          if(str)
          {
            strcpy(str + *pos, buffer);
            *pos = *pos + strlen(buffer);
          }
          else
          {
            char *t = buffer;
            while(*t) 
            {
              putchar(*t);
              t++;
            }
          } break;
        case 'c':
          if(str)
          {
            *(str + *pos) = (char)va_arg(arg, int);
            *pos = *pos + 1;
          } else { (*putchar)((char)va_arg(arg, int)); }
          break;
        case 's':
          if(str)
          {
            const char *t = va_arg(arg, const char*);
            strcpy(str + (*pos), t);
            *pos = *pos + strlen(t);
          }
          else
          {
            size_t len = strlen(format);
            const char *t = va_arg(arg, const char*);
            while(*t)
            {
              putchar(*t);
              t++;
            }
          } break;

        default:
          break;
      }
      continue;
    }
    if(str) 
    {
      *(str + *pos) = c;
      *pos = *pos + 1;
    } else { (*putchar)(c); }
  }
}

void printf(const char* format, ...) {
  va_list parameters;
  va_start(parameters, format);
  __vsprintf_w(NULL, putchar, format, parameters);
  va_end(parameters);
}

#pragma GCC diagnostic pop


