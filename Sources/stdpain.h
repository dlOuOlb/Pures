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
#include <limits.h>
#include <locale.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>
#include <wchar.h>

#define _SUCCESS_ ((_Bool)(1))
#define _FAILURE_ ((_Bool)(0))

_Static_assert(sizeof(void*)==sizeof(uintptr_t),"sizeof(void*) != sizeof(uintptr_t)");
_Static_assert(((void*)(NULL))==((void*)((uintptr_t)(0))),"NULL != 0");
_Static_assert(((uintptr_t)(0))==((uintptr_t)((void*)(NULL))),"0 != NULL");

static _Bool _StdP_Fine_Zero_(register unsigned int E)
{
	(void)(_StdP_Fine_Zero_);
	const unsigned int S=(sizeof(int)*CHAR_BIT)-1;
	const _Bool T[2]={[0]=_SUCCESS_,[1]=_FAILURE_};

	E|=0-E;
	E>>=S;

	return T[E];
}
static _Bool _StdP_Fine_MSB0_(register unsigned int E)
{
	(void)(_StdP_Fine_MSB0_);
	const unsigned int S=(sizeof(int)*CHAR_BIT)-1;
	const _Bool T[2]={[0]=_SUCCESS_,[1]=_FAILURE_};

	E>>=S;

	return T[E];
}
static _Bool _StdP_Fine_Some_(const void *const P)
{
	(void)(_StdP_Fine_Some_);
	const uintptr_t S=(sizeof(void*)*CHAR_BIT)-1;
	const _Bool T[2]={[0]=_FAILURE_,[1]=_SUCCESS_};

	register uintptr_t E=(uintptr_t)(P);

	E|=0-E;
	E>>=S;

	return T[E];
}

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
