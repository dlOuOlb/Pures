#ifndef _INC_TIMPURE
#define _INC_TIMPURE "TimP:2019.11.29"
/*------------------------------------------------------------------*/
/*	TimPure provides some time representing functions.				*/
/*																	*/
/*	Written by Ranny Clover											*/
/*	http://github.com/dlOuOlb/Pures/								*/
/*------------------------------------------------------------------*/
/*	[!] Non-Standard Assumptions:									*/
/*																	*/
/*	- All data pointers have the same size, a power of 2.			*/
/*	- All function pointers have the same size, a power of 2.		*/
/*------------------------------------------------------------------*/
/*	DLL IMPORT EXAMPLE:												*/
/*																	*/
/*	#define _PURES_DLL_IMPORT_ __declspec(dllimport)				*/
/*	#include <timpure.h>											*/
/*------------------------------------------------------------------*/

#include <time.h>

//TimPure : Union for Library Alignment
typedef const union { const void *const D;void(*const F_)(void); }TIMPACE;

//TimPure : Library Pack Structure
typedef const struct
#define _TimP_Align_(N) _Alignas((N)*sizeof(TIMPACE))
{
	_TimP_Align_(2) const struct
	{
		//TimPure : Library Version - "TimP:yyyy.mm.dd"
		_TimP_Align_(1) const char *const Version;

		//TimPure : Boolean Return Values
		_TimP_Align_(1) const struct _timp_b2
		{
			const _Bool Success;	//TimPure : No problem.
			const _Bool Failure;	//TimPure : Something wrong.
		}
		*const Bool;
	};

	//TimPure : Calendar Time Value Functions
	_TimP_Align_(2) const struct
	{
		//TimPure : Get the current calendar time value.
		//＊It might be the number of seconds since 1970.01.01 00:00:00.
		_TimP_Align_(1) time_t(*const Now_)(void);
		//TimPure : Convert from struct tm to time_t.
		_TimP_Align_(1) time_t(*const Obj_)(const struct tm TimeObject);
	}
	Val;

	//TimPure : Calendar Time Object Functions
	//＊Mode 0 : Coordinated Universal Time (UTC)
	//　Mode 1 : Local Time
	_TimP_Align_(2) const struct
	{
		//TimPure : Get the current calendar time object.
		_TimP_Align_(1) struct tm(*const Now_)(const _Bool Mode);
		//TimPure : Convert from time_t to struct tm.
		_TimP_Align_(1) struct tm(*const Val_)(const time_t TimeValue,const _Bool Mode);
	}
	Obj;

	//TimPure : Textual Representation Functions
	//＊Required Text size is 26 bytes for the following format:
	//　Www Mmm dd hh:mm:ss yyyy\n\0
	//＊Return value is defined under "TimP.Bool".
	_TimP_Align_(2) const struct
	{
		//TimPure : Convert the given calendar time value to a textual representation.
		_TimP_Align_(1) _Bool(*const Val_)(char *const Text,const time_t TimeValue);
		//TimPure : Convert the given calendar time object to a textual representation.
		_TimP_Align_(1) _Bool(*const Obj_)(char *const Text,const struct tm TimeObject);
	}
	Text;
}
#undef _TimP_Align_
TIMPACK;

#ifdef _PURES_DLL_IMPORT_
_PURES_DLL_IMPORT_
#endif

//TimPure : Library Pack Object
extern _Alignas(sizeof(TIMPACE)<<3) TIMPACK TimP;
//TimPure : Indirect access to the library pack object.
extern TIMPACK *TimP_(void);
#endif
