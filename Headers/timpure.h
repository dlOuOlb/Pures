#ifndef _INC_TIMPURE
#define _INC_TIMPURE "Date:2019.11.22"
/*------------------------------------------------------------------*/
/*	TimPure provides some time representing functions.				*/
/*																	*/
/*	Written by Ranny Clover											*/
/*	http://github.com/dlOuOlb/Pures/								*/
/*------------------------------------------------------------------*/

#include <time.h>

typedef const struct
{
	//TimPure : Calendar Time Value Functions
	const struct
	{
		//TimPure : Get the current calendar time value.
		//＊It might be the number of seconds since 1970.01.01 00:00:00.
		time_t(*const Now_)(void);
		//TimPure : Convert from struct tm to time_t.
		time_t(*const Obj_)(const struct tm TimeObject);
	}
	Val;

	//TimPure : Calendar Time Object Functions
	//＊Mode 0 : Coordinated Universal Time (UTC)
	//　Mode 1 : Local Time
	const struct
	{
		//TimPure : Get the current calendar time object.
		struct tm(*const Now_)(const _Bool Mode);
		//TimPure : Convert from time_t to struct tm.
		struct tm(*const Val_)(const time_t TimeValue,const _Bool Mode);
	}
	Obj;

	//TimPure : Textual Representation Functions
	//＊Required Text size is 26 bytes for the following format:
	//　Www Mmm dd hh:mm:ss yyyy\n\0
	//＊Return value is defined under "TimP.Bool".
	const struct
	{
		//TimPure : Convert the given calendar time value to a textual representation.
		_Bool(*const Val_)(char *const Text,const time_t TimeValue);
		//TimPure : Convert the given calendar time object to a textual representation.
		_Bool(*const Obj_)(char *const Text,const struct tm TimeObject);
	}
	Text;

	//TimPure : Library Version - "Date:yyyy.mm.dd"
	const char *const Version;

	//TimPure : Boolean Return Values
	const struct
	{
		const _Bool Success;	//TimPure : No problem.
		const _Bool Failure;	//TimPure : Something wrong.
	}
	Bool;
}
TIMPACK;	//TimPure : Library Pack Structure

//TimPure : Library Pack Object
extern TIMPACK TimP;
//TimPure : Indirect access to the library pack object.
extern TIMPACK *TimP_(void);
#endif
