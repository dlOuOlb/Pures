#ifndef xSTDPAIN_SRC_
#define xSTDPAIN_SRC_

#if(defined(__STDC__)&&(__STDC__))

#if(defined(__STDC_VERSION__)&&(__STDC_VERSION__>=201710L))

//#if(defined(__STDC_VERSION_STDINT_H__)&&(__STDC_VERSION_STDINT_H__>=yyyymmL))

//#if(defined(__STDC_VERSION_STDLIB_H__)&&(__STDC_VERSION_STDLIB_H__>=yyyymmL))

//#if(defined(__STDC_VERSION_TIME_H__)&&(__STDC_VERSION_TIME_H__>=yyyymmL))

#if(defined(__STDC_LIB_EXT1__)&&(__STDC_LIB_EXT1__>=201112L))

#if(defined(__STDC_NO_THREADS__)&&(__STDC_NO_THREADS__))
#error The implementation does not support multithreading.
#else

_Static_assert((sizeof(void*)&(sizeof(void*)-1))==0,"sizeof(void*) != 1<<N");
_Static_assert(sizeof(void*)==sizeof(union xstdp_u*),"sizeof(void*) != sizeof(union*)");
_Static_assert(sizeof(void*)==sizeof(struct xstdp_s*),"sizeof(void*) != sizeof(struct*)");

_Static_assert((sizeof(void(*)(void))&(sizeof(void(*)(void))-1))==0,"sizeof(void(*)(void)) != 1<<N");
_Static_assert(sizeof(void(*)(void))==sizeof(union xstdp_u(*)(struct xstdp_s)),"sizeof(void(*)(void)) != sizeof(union(*)(struct))");

#define __STDC_WANT_LIB_EXT1__ (1)

#include <errno.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>

#endif

#else
#error The implementation does not support the C11 bounds-checking interfaces.
#endif

//#else
//#error The implementation does not support the standard C2x <time.h>.
//#endif

//#else
//#error The implementation does not support the standard C2x <stdlib.h>.
//#endif

//#else
//#error The implementation does not support the standard C2x <stdint.h>.
//#endif

#else
#error The implementation does not support the standard C18.
#endif

#else
#error The implementation does not conform to the standard C.
#endif

#endif
