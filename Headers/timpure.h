/*------------------------------------------------------------------*/
/*	TimPure provides some time representing functions.				*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Pures/					2019.09.19	*/
/*------------------------------------------------------------------*/

#ifndef _INC_TIMPURE
#define _INC_TIMPURE

#include <time.h>

typedef struct tm timp_tm;			//TimPure : Calendar Time Variable
typedef const struct tm TIMP_TM;	//TimPure : Calendar Time Constant

//TimPure : Library Pack Structure
struct _timpack
{
	//TimPure : Calendar Time Value Functions
	const struct
	{
		//TimPure : Get the current calendar time value.
		//＊It might be the number of seconds since 1970.01.01 00:00:00.
		time_t(*const Now_)(void);
		//TimPure : Cast from timp_tm to time_t
		time_t(*const Obj_)(TIMP_TM TimeObject);
	}
	Val;

	//TimPure : Calendar Time Object Functions
	const struct
	{
		//TimPure : Get the current calendar time object.
		//＊Mode 0 : Coordinated Universal Time (UTC)
		//　Mode 1 : Local Time
		timp_tm(*const Now_)(const _Bool Mode);
		//TimPure : Cast from time_t to timp_tm
		//＊Mode 0 : Coordinated Universal Time (UTC)
		//　Mode 1 : Local Time
		timp_tm(*const Val_)(const time_t TimeValue,const _Bool Mode);
	}
	Obj;

	//TimPure : Textual Representation Functions
	//＊Return value is defined under "TimP.Bool".
	const struct
	{
		//TimPure : Convert the given calendar time value to a textual representation.
		//＊Required Text size is 26 bytes for the following format:
		//　Www Mmm dd hh:mm:ss yyyy\n\0
		_Bool(*const Val_)(char Text[26],const time_t TimeValue);
		//TimPure : Convert the given calendar time object to a textual representation.
		//＊Required Text size is 26 bytes for the following format:
		//　Www Mmm dd hh:mm:ss yyyy\n\0
		_Bool(*const Obj_)(char Text[26],TIMP_TM TimeValue);
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
};
typedef struct _timpack timpack;		//TimPure : Library Pack Variable (Prohibited)
typedef const struct _timpack TIMPACK;	//TimPure : Library Pack Constant

//TimPure : Library Pack Object
extern TIMPACK TimP;
//TimPure : Indirect access to the library pack object.
extern TIMPACK *TimP_(void);
#endif
