#ifndef _SRC_STDPAIN
#define _SRC_STDPAIN

#ifdef __STDC__

#if(__STDC__)

#ifdef __STDC_VERSION__

#if(__STDC_VERSION__<201710L)
#error The compiler does not satisfy the C18 Standard.
#else

#ifdef __STDC_NO_THREADS__
#error The compiler does not support the thread library.
#else

#ifdef __STDC_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ (1)

_Static_assert((sizeof(void*)&(sizeof(void*)-1))==0,"sizeof(void*) != 1<<N");
_Static_assert((sizeof(void(*)(void))&(sizeof(void(*)(void))-1))==0,"sizeof(void(*)(void)) != 1<<N");

#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>
#include <wchar.h>

#else
#error The compiler does not support the C Library Extension 1.
#endif

#endif

#endif

#else
#error The compiler does not specify the C Standard version number.
#endif

#else
#error The compiler does not conform to the C Standard.
#endif

#else
#error The compiler does not conform to the C Standard.
#endif

#endif
