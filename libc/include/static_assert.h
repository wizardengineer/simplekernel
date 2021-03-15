/* simple implementation of static assert */
#ifndef __static_assert
#define __static_assert

#include <features.h>
#include <stdio.h>

#define static_assert(EXPR, MSG) ((EXPR) ? 0 : printf(MSG))



#endif // __static_assert
