/* Undefine (also defined in libc-symbols.h).  */
#undef __attribute_copy__
#if __GNUC_PREREQ (9, 0)
/* Copies attributes from the declaration or type referenced by
   the argument.  */
# define __attribute_copy__(arg) __attribute__ ((__copy__ (arg)))
#else
# define __attribute_copy__(arg)
#endif
#if (!defined _Static_assert && !defined __cplusplus \
     && (defined __STDC_VERSION__ ? __STDC_VERSION__ : 0) < 201112 \
     && (!__GNUC_PREREQ (4, 6) || defined __STRICT_ANSI__))
# define _Static_assert(expr, diagnostic) \
    extern int (*__Static_assert_function (void)) \
      [!!sizeof (struct { int __error_if_negative: (expr) ? 2 : -1; })]
#endif
#include <bits/wordsize.h>
#include <bits/long-double.h>
#if defined __LONG_DOUBLE_MATH_OPTIONAL && defined __NO_LONG_DOUBLE_MATH
# define __LDBL_COMPAT 1
# ifdef __REDIRECT
#  define __LDBL_REDIR1(name, proto, alias) __REDIRECT (name, proto, alias)
#  define __LDBL_REDIR(name, proto) \
  __LDBL_REDIR1 (name, proto, __nldbl_##name)
#  define __LDBL_REDIR1_NTH(name, proto, alias) __REDIRECT_NTH (name, proto, alias)
#  define __LDBL_REDIR_NTH(name, proto) \
  __LDBL_REDIR1_NTH (name, proto, __nldbl_##name)
#  define __LDBL_REDIR1_DECL(name, alias) \
  extern __typeof (name) name __asm (__ASMNAME (#alias));
#  define __LDBL_REDIR_DECL(name) \
  extern __typeof (name) name __asm (__ASMNAME ("__nldbl_" #name));
#  define __REDIRECT_LDBL(name, proto, alias) \
  __LDBL_REDIR1 (name, proto, __nldbl_##alias)
#  define __REDIRECT_NTH_LDBL(name, proto, alias) \
  __LDBL_REDIR1_NTH (name, proto, __nldbl_##alias)
# endif
#endif
#if !defined __LDBL_COMPAT || !defined __REDIRECT
# define __LDBL_REDIR1(name, proto, alias) name proto
# define __LDBL_REDIR(name, proto) name proto
# define __LDBL_REDIR1_NTH(name, proto, alias) name proto __THROW
# define __LDBL_REDIR_NTH(name, proto) name proto __THROW
# define __LDBL_REDIR_DECL(name)
# ifdef __REDIRECT
#  define __REDIRECT_LDBL(name, proto, alias) __REDIRECT (name, proto, alias)
#  define __REDIRECT_NTH_LDBL(name, proto, alias) \
  __REDIRECT_NTH (name, proto, alias)
# endif
#endif
/* __glibc_macro_warning (MESSAGE) issues warning MESSAGE.  This is
   intended for use in preprocessor macros.
   Note: MESSAGE must be a _single_ string; concatenation of string
   literals is not supported.  */
#if __GNUC_PREREQ (4,8) || __glibc_clang_prereq (3,5)
# define __glibc_macro_warning1(message) _Pragma (#message)
# define __glibc_macro_warning(message) \
  __glibc_macro_warning1 (GCC warning message)
#else
# define __glibc_macro_warning(msg)
#endif
/* Generic selection (ISO C11) is a C-only feature, available in GCC
   since version 4.9.  Previous versions do not provide generic
   selection, even though they might set __STDC_VERSION__ to 201112L,
   when in -std=c11 mode.  Thus, we must check for !defined __GNUC__
   when testing __STDC_VERSION__ for generic selection support.
   On the other hand, Clang also defines __GNUC__, so a clang-specific
   check is required to enable the use of generic selection.  */
#if !defined __cplusplus \
    && (__GNUC_PREREQ (4, 9) \
        || __glibc_clang_has_extension (c_generic_selections) \
        || (!defined __GNUC__ && defined __STDC_VERSION__ \
            && __STDC_VERSION__ >= 201112L))
# define __HAVE_GENERIC_SELECTION 1
#else
# define __HAVE_GENERIC_SELECTION 0
#endif
#endif         /* sys/cdefs.h */

