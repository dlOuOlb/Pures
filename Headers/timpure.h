#ifndef _INC_TIMPURE
#define _INC_TIMPURE "TimP:2019.12.20"
/*------------------------------------------------------------------+
|	TimPure provides some time representing functions.				|
|																	|
|	Written by Ranny Clover											|
|	http://github.com/dlOuOlb/Pures/blob/master/Headers/timpure.h	|
+-------------------------------------------------------------------+
|	[!] Non-Standard Assumptions:									|
|																	|
|	- All data pointers have the same size, a power of 2.			|
|	- All function pointers have the same size, a power of 2.		|
+-------------------------------------------------------------------+
|	[+] Pre-Header Definitions:										|
|																	|
|	#define _PURES_DLL_IMPORT_ __declspec(dllimport)				|
|	#define _TIMP_MACRO_DEFINE_										|
+-------------------------------------------------------------------+
|	[!] Note:														|
|																	|
|	Functions of this library do not take pointers but values, so	|
|	the interface mismatch such as type or call between the build	|
|	and the usage may cause an unintended behavior.					|
+------------------------------------------------------------------*/

#include <time.h>

//TimPure : Textual Representation for Time
typedef struct { char Text[32]; }timp_tx;typedef const timp_tx TIMP_TX;

//TimPure : Library Alignment Union
typedef const union { const size_t S;const void *const D;void(*const F_)(void); }TIMPACE;

//TimPure : Library Pack Structure
typedef const struct
#define _TimP_Align_(N) _Alignas((N)*sizeof(TIMPACE))
{
	//TimPure : Basic Time Utilities
	_TimP_Align_(8) const struct
	{
		//TimPure : Pointers to Some Constants
		_TimP_Align_(2) const struct
		{
			//TimPure : Library Version - "TimP:yyyy.mm.dd"
			_TimP_Align_(1) const char *const restrict Version;

			//TimPure : Type Sizes
			//＊Type size mismatch between the build and the usage
			//　is an obvious evidence to do not use this library.
			//＊But even if the type size is matched,
			//　its function ABI can be different,
			//　so a user should check this issue manually.
			_TimP_Align_(1) const struct _timpack_size
			{
				const size_t Size;		//TimPure : sizeof(size_t)
				const size_t Long;		//TimPure : sizeof(long)
				const size_t Double;	//TimPure : sizeof(double)
				const size_t Time;		//TimPure : sizeof(time_t)
				const size_t TM;		//TimPure : sizeof(struct tm)
				const size_t TimeSpec;	//TimPure : sizeof(struct timespec)
			}
			*const restrict Size;
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
		_TimP_Align_(2) const struct
		{
			//TimPure : Get the current calendar time object in UTC.
			_TimP_Align_(1) struct tm(*const Now_)(void);
			//TimPure : Convert from time_t to struct tm in UTC.
			//＊Return object is filled with (-1) for failure.
			_TimP_Align_(1) struct tm(*const Val_)(const time_t TimeValue);
		}
		Obj;

		//TimPure : Textual Representation Functions
		//＊Return text takes the form of
		//　"Www Mmm dd hh:mm:ss yyyy\n" for success, "" for failure.
		_TimP_Align_(2) const struct
		{
			//TimPure : Convert the given calendar time value to a textual representation.
			_TimP_Align_(1) timp_tx(*const Val_)(const time_t TimeValue);
			//TimPure : Convert the given calendar time object to a textual representation.
			_TimP_Align_(1) timp_tx(*const Obj_)(const struct tm TimeObject);
		}
		Text;
	};

	//TimPure : Time Specification Functions
	//＊Note that their behaviors depend on the type 'time_t',
	//　i.e. invalid for negative values unless 'time_t' is signed.
	_TimP_Align_(8) const struct _timpack_spec
	{
		//TimPure : Time Specification Arithmetics
		_TimP_Align_(4) const struct
		{
			//TimPure : Calculate ( A + B ).
			_TimP_Align_(1) struct timespec(*const Add_)(const struct timespec A,const struct timespec B);
			//TimPure : Calculate ( A - B ).
			_TimP_Align_(1) struct timespec(*const Sub_)(const struct timespec A,const struct timespec B);
			//TimPure : Calculate ( A * C ).
			_TimP_Align_(1) struct timespec(*const Mul_)(const struct timespec A,const long C);
			//TimPure : Calculate ( A / C ).
			//＊The divisor C must not be zero.
			_TimP_Align_(1) struct timespec(*const Div_)(const struct timespec A,const long C);
		};

		//TimPure : Time Specification Utilities
		_TimP_Align_(4) const struct
		{
			//TimPure : Conversion from Time Specification to Double
			_TimP_Align_(1) double(*const Get_)(const struct timespec TimeSpec);
			//TimPure : Conversion from Double to Time Specification
			_TimP_Align_(1) struct timespec(*const Set_)(const double Double);
			//TimPure : Get the current calendar time specification in UTC.
			//＊Return object is { 0, -1 } for failure.
			_TimP_Align_(1) struct timespec(*const Now_)(void);
			//TimPure : Calculate ( Sum + ( Now_( ) - Mark ) ).
			_TimP_Align_(1) struct timespec(*const Sum_)(const struct timespec Sum,const struct timespec Mark);
		};
	}
	Spec;
}
#undef _TimP_Align_
TIMPACK;

#ifdef _PURES_DLL_IMPORT_
_PURES_DLL_IMPORT_
#endif

//TimPure : Library Pack Object
extern _Alignas(TIMPACK) TIMPACK TimP;
//TimPure : Indirect access to the library pack object. (&TimP)
extern TIMPACK *TimP_(void);

#ifdef _TIMP_MACRO_DEFINE_
//TimPure : Abbreviation of "TimP.Text.Val_" or "TimP.Text.Obj_".
#define TimP_Text_(Time) _Generic((Time),time_t:TimP.Text.Val_,struct tm:TimP.Text.Obj_)(Time)
//TimPure : Abbreviation of combined calls of "TimP.Val.Now_" and "TimP.Text.Val_".
#define TimP_Text_Val_Now_() TimP.Text.Val_(TimP.Val.Now_())
//TimPure : Abbreviation of combined calls of "TimP.Obj.Now_" and "TimP.Text.Obj_".
#define TimP_Text_Obj_Now_() TimP.Text.Obj_(TimP.Obj.Now_())
//TimPure : Abbreviation of a once-loop over "TimP.Spec.Now_" and "TimP.Spec.Sum_".
//＊Do not jump over the loop block, e.g. 'goto', 'break', and 'return'.
#define TimP_Spec_Run_Do_(TimeSpec) for(const struct timespec(_##TimeSpec##Mark)=TimP.Spec.Now_(),*(_##TimeSpec##Temp)=&(_##TimeSpec##Mark);(_##TimeSpec##Temp);(TimeSpec)=TimP.Spec.Sum_((TimeSpec),(_##TimeSpec##Mark)),(_##TimeSpec##Temp)=NULL)
#endif

#endif
