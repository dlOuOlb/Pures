#ifndef xSRC_STDPAIN
#define xSRC_STDPAIN

#ifdef __STDC__

#if(__STDC__)

#ifdef __STDC_VERSION__

#if(__STDC_VERSION__<201710L)
#error The implementation does not satisfy the C18 Standard.
#else

//#ifdef __STDC_VERSION_STDINT_H__

//#if(__STDC_VERSION_STDINT_H__<yyyymmL)
//#error The implementation does not satisfy the C2x Standard <stdint.h>.
//#else

//#ifdef __STDC_VERSION_STDLIB_H__

//#if(__STDC_VERSION_STDLIB_H__<yyyymmL)
//#error The implementation does not satisfy the C2x Standard <stdlib.h>.
//#else

//#ifdef __STDC_VERSION_TIME_H__

//#if(__STDC_VERSION_TIME_H__<yyyymmL)
//#error The implementation does not satisfy the C2x Standard <time.h>.
//#else

#ifdef __STDC_NO_THREADS__
#error The implementation does not support <threads.h>.
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
#error The implementation does not support the C Library Extension 1.
#endif

#endif

//#endif

//#else
//#error The implementation does not specify the C Standard <time.h> version number.
//#endif

//#endif

//#else
//#error The implementation does not specify the C Standard <stdlib.h> version number.
//#endif

//#endif

//#else
//#error The implementation does not specify the C Standard <stdint.h> version number.
//#endif

#endif

#else
#error The implementation does not specify the C Standard version number.
#endif

#else
#error The implementation does not conform to the C Standard.
#endif

#else
#error The implementation does not conform to the C Standard.
#endif

#endif
