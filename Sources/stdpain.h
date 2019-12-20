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
