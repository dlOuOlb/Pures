#ifndef oSTRPURE_INC_
#define oSTRPURE_INC_ "StrP:2020.01.29"
/*------------------------------------------------------------------+
|	StrPure provides some inflexible string handling functions.		|
|																	|
|	Written by Ranny Clover											|
|	http://github.com/dlOuOlb/Pures/blob/master/Headers/strpure.h	|
+-------------------------------------------------------------------+
|	[!] Non-Standard Assumptions:									|
|																	|
|	- All data pointers have the same size, a power of 2.			|
|	- All function pointers have the same size, a power of 2.		|
+-------------------------------------------------------------------+
|	[+] Optional Pre-Header Definitions:							|
|																	|
|	#define uPURES_DLL_IMPORT_ __declspec(dllimport)				|
|	#define uSTRP_MACRO_DEFINE_										|
|																	|
|	#define __STDC_WANT_LIB_EXT1__ (1)								|
+------------------------------------------------------------------*/

#include <stdio.h>

//StrPure : char [0x0010] Holder
typedef struct { char NC[0x0010]; } strp_nc_0x0010; typedef const strp_nc_0x0010 STRP_NC_0X0010;

//StrPure : char [0x0040] Holder
typedef struct { char NC[0x0040]; } strp_nc_0x0040; typedef const strp_nc_0x0040 STRP_NC_0X0040;

//StrPure : char [0x0100] Holder
typedef struct { char NC[0x0100]; } strp_nc_0x0100; typedef const strp_nc_0x0100 STRP_NC_0X0100;

//StrPure : char [0x0400] Holder
typedef struct { char NC[0x0400]; } strp_nc_0x0400; typedef const strp_nc_0x0400 STRP_NC_0X0400;

//StrPure : Latent Union for Library Alignment
typedef const union { const size_t S;const void *const X;void(*const X_)(void); } STRPACE;

//StrPure : Library Pack Structure
typedef const struct
#define xStrP_Align_(N) _Alignas((N)*sizeof(STRPACE))
{
	//StrPure : Pointers to Some Constants
	xStrP_Align_(4) const struct
	{
		//StrPure : Library Version - "StrP:yyyy.mm.dd"
		xStrP_Align_(1) const char *const restrict Version;

		//StrPure : Boolean Return Values
		xStrP_Align_(1) const struct ostrpack_bool
		{
			const _Bool Success;	//StrPure : (1) No problem.
			const _Bool Failure;	//StrPure : (0) Something is wrong.
		}
		*const restrict Bool;

		//StrPure : Error Numbers
		xStrP_Align_(1) const struct ostrpack_errno
		{
			const int Zero;		//StrPure : No error.
			const int Dom;		//StrPure : Mathematics argument out of domain of function.
			const int IlSeq;	//StrPure : Illegal byte sequence.
			const int Range;	//StrPure : Result too large.
		}
		*const restrict Errno;

		//StrPure : Locale Categories
		xStrP_Align_(1) const struct ostrpack_lc
		{
			const int All;		//StrPure : Entire C locale.
			const int Collate;	//StrPure : Collation category.
			const int CType;	//StrPure : Character classification category.
			const int Monetary;	//StrPure : Monetary formatting category.
			const int Numeric;	//StrPure : Numeric formatting category.
			const int Time;		//StrPure : Time formatting category.
		}
		*const restrict LC;
	};

	//StrPure : Locale Handling Functions
	xStrP_Align_(4) const struct
	{
		//StrPure : "C" Minimal Locale
		xStrP_Align_(1) const char *const restrict Default;
		//StrPure : "" User-Preferred Locale
		xStrP_Align_(1) const char *const restrict Environment;
		//StrPure : Get the current locale.
		//＊Allowed (Category) value is defined under "StrP.LC".
		//＊Return value is defined under "StrP.Bool".
		xStrP_Align_(1) /*[[nodiscard]]*/ _Bool(*const Get_)(const int Category,const size_t Size,char *const Buffer);
		//StrPure : Set as the specified locale.
		//＊Allowed (Category) value is defined under "StrP.LC".
		//＊Return value is defined under "StrP.Bool".
		xStrP_Align_(1) /*[[nodiscard]]*/ _Bool(*const Set_)(const int Category,const char *const Locale);
	}
	Locale;

	//StrPure : Null-terminated Native Narrow Character String Functions
	//＊(strp_nc_0x####*)'s capacity must not be smaller than char [0x####].
	//＊(STRP_NC_0X####*)'s capacity can be smaller than char [0x####],
	//　but the string must be null-terminated within that capacity.
	xStrP_Align_(4) const struct
	{
		//StrPure : String Cast Functions
		//＊Use "StrP_NC_Cast_" for type safety.
		//＊Truncation could occur.
		//＊Return value is defined under "StrP.Errno".
		xStrP_Align_(4) const struct
		{
			//StrPure : Cast to char [0x0010]
			//＊(Target) type is 'strp_nc_0x0010*'.
			xStrP_Align_(4) const struct xstrpack_nc_cast
			{
				//StrPure : Cast from char [0x0010]
				//＊(Source) type is 'STRP_NC_0X0010*'.
				xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0010_)(void *const restrict Target,const void *const restrict Source);
				//StrPure : Cast from char [0x0040]
				//＊(Source) type is 'STRP_NC_0X0040*'.
				xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0040_)(void *const restrict Target,const void *const restrict Source);
				//StrPure : Cast from char [0x0100]
				//＊(Source) type is 'STRP_NC_0X0100*'.
				xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0100_)(void *const restrict Target,const void *const restrict Source);
				//StrPure : Cast from char [0x0400]
				//＊(Source) type is 'STRP_NC_0X0400*'.
				xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0400_)(void *const restrict Target,const void *const restrict Source);
			}
			x0010;

			//StrPure : Cast to char [0x0040]
			//＊(Target) type is 'strp_nc_0x0040*'.
			xStrP_Align_(4) const struct xstrpack_nc_cast x0040;

			//StrPure : Cast to char [0x0100]
			//＊(Target) type is 'strp_nc_0x0100*'.
			xStrP_Align_(4) const struct xstrpack_nc_cast x0100;

			//StrPure : Cast to char [0x0400]
			//＊(Target) type is 'strp_nc_0x0400*'.
			xStrP_Align_(4) const struct xstrpack_nc_cast x0400;
		}
		Cast;

		//StrPure : Find Functions
		xStrP_Align_(4) const struct
		{
			//StrPure : Character Find Functions
			//＊Use "StrP_NC_Find_Char_" for type inference.
			//＊Mode 0 : Forward Search
			//　Mode 1 : Reverse Search
			//＊Return value is, if the character is found,
			//　then its index in the string, else the capacity of the buffer.
			xStrP_Align_(4) const struct
			{
				//StrPure : Find the character for char [0x0010]
				xStrP_Align_(1) size_t(*const x0010_)(STRP_NC_0X0010 *const String,const char Character,const _Bool Mode);
				//StrPure : Find the character for char [0x0040]
				xStrP_Align_(1) size_t(*const x0040_)(STRP_NC_0X0040 *const String,const char Character,const _Bool Mode);
				//StrPure : Find the character for char [0x0100]
				xStrP_Align_(1) size_t(*const x0100_)(STRP_NC_0X0100 *const String,const char Character,const _Bool Mode);
				//StrPure : Find the character for char [0x0400]
				xStrP_Align_(1) size_t(*const x0400_)(STRP_NC_0X0400 *const String,const char Character,const _Bool Mode);
			}
			Char;

			//StrPure : String Find Functions
			//＊Use "StrP_NC_Find_String_" for type inference.
			//＊Return value is, if the sub-string is found,
			//　then its offset in the string, else the capacity of the buffer.
			xStrP_Align_(4) const struct
			{
				//StrPure : Find the sub-string for char [0x0010]
				xStrP_Align_(1) size_t(*const x0010_)(STRP_NC_0X0010 *const String,STRP_NC_0X0010 *const SubString);
				//StrPure : Find the sub-string for char [0x0040]
				xStrP_Align_(1) size_t(*const x0040_)(STRP_NC_0X0040 *const String,STRP_NC_0X0040 *const SubString);
				//StrPure : Find the sub-string for char [0x0100]
				xStrP_Align_(1) size_t(*const x0100_)(STRP_NC_0X0100 *const String,STRP_NC_0X0100 *const SubString);
				//StrPure : Find the sub-string for char [0x0400]
				xStrP_Align_(1) size_t(*const x0400_)(STRP_NC_0X0400 *const String,STRP_NC_0X0400 *const SubString);
			}
			String;
		}
		Find;

		//StrPure : String Length Functions
		//＊Use "StrP_NC_Length_" for type inference.
		//＊Return value is, if a null character is found,
		//　then the length of the string, else the capacity of the buffer.
		xStrP_Align_(4) const struct
		{
			//StrPure : Length for char [0x0010]
			xStrP_Align_(1) size_t(*const x0010_)(STRP_NC_0X0010 *const String);
			//StrPure : Length for char [0x0040]
			xStrP_Align_(1) size_t(*const x0040_)(STRP_NC_0X0040 *const String);
			//StrPure : Length for char [0x0100]
			xStrP_Align_(1) size_t(*const x0100_)(STRP_NC_0X0100 *const String);
			//StrPure : Length for char [0x0400]
			xStrP_Align_(1) size_t(*const x0400_)(STRP_NC_0X0400 *const String);
		}
		Length;

		//StrPure : String Reset Functions
		//＊Use "StrP_NC_Reset_" for type inference.
		//＊Return value is defined under "StrP.Errno".
		xStrP_Align_(4) const struct
		{
			//StrPure : Reset for char [0x0010]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0010_)(strp_nc_0x0010 *const restrict String);
			//StrPure : Reset for char [0x0040]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0040_)(strp_nc_0x0040 *const restrict String);
			//StrPure : Reset for char [0x0100]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0100_)(strp_nc_0x0100 *const restrict String);
			//StrPure : Reset for char [0x0400]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0400_)(strp_nc_0x0400 *const restrict String);
		}
		Reset;

		//StrPure : String Copy Functions
		//＊Use "StrP_NC_Copy_" for type inference.
		//＊Return value is defined under "StrP.Errno".
		xStrP_Align_(4) const struct
		{
			//StrPure : Copy for char [0x0010]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0010_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0010 *const restrict Source);
			//StrPure : Copy for char [0x0040]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0040_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0040 *const restrict Source);
			//StrPure : Copy for char [0x0100]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0100_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0100 *const restrict Source);
			//StrPure : Copy for char [0x0400]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0400_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0400 *const restrict Source);
		}
		Copy;

		//StrPure : String Concatenation Functions
		//＊Use "StrP_NC_Conc_" for type inference.
		//＊Return value is defined under "StrP.Errno".
		xStrP_Align_(4) const struct
		{
			//StrPure : Concatenation for char [0x0010]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0010_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0010 *const restrict Source);
			//StrPure : Concatenation for char [0x0040]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0040_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0040 *const restrict Source);
			//StrPure : Concatenation for char [0x0100]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0100_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0100 *const restrict Source);
			//StrPure : Concatenation for char [0x0400]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0400_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0400 *const restrict Source);
		}
		Conc;

		//StrPure : String Crop Functions
		//＊Use "StrP_NC_Crop_" for type inference.
		//＊Return value is defined under "StrP.Errno".
		xStrP_Align_(4) const struct
		{
			//StrPure : Crop for char [0x0010]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0010_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0010 *const restrict Source,const size_t Offset,const size_t Length);
			//StrPure : Crop for char [0x0040]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0040_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0040 *const restrict Source,const size_t Offset,const size_t Length);
			//StrPure : Crop for char [0x0100]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0100_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0100 *const restrict Source,const size_t Offset,const size_t Length);
			//StrPure : Crop for char [0x0400]
			xStrP_Align_(1) /*[[nodiscard]]*/ int(*const x0400_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0400 *const restrict Source,const size_t Offset,const size_t Length);
		}
		Crop;

		//StrPure : String Comparison Functions
		//＊Use "StrP_NC_Comp_" for type inference.
		//＊Return value is,
		//　with the left one against the right one in lexicographical order,
		//　negative for 'before', zero for 'equal', or positive for 'after'.
		xStrP_Align_(4) const struct
		{
			//StrPure : Comparison for char [0x0010]
			xStrP_Align_(1) int(*const x0010_)(STRP_NC_0X0010 *const Left,STRP_NC_0X0010 *const Right);
			//StrPure : Comparison for char [0x0040]
			xStrP_Align_(1) int(*const x0040_)(STRP_NC_0X0040 *const Left,STRP_NC_0X0040 *const Right);
			//StrPure : Comparison for char [0x0100]
			xStrP_Align_(1) int(*const x0100_)(STRP_NC_0X0100 *const Left,STRP_NC_0X0100 *const Right);
			//StrPure : Comparison for char [0x0400]
			xStrP_Align_(1) int(*const x0400_)(STRP_NC_0X0400 *const Left,STRP_NC_0X0400 *const Right);
		}
		Comp;

		//StrPure : String Put Functions
		//＊Use "StrP_NC_Puts_" for type safety.
		//＊If (Stream) is NULL, then (stdout) is used.
		//＊Return value is defined under "StrP.Bool".
		xStrP_Align_(4) const struct
		{
			//StrPure : Put string for char [0x0010]
			//＊(String) type is 'STRP_NC_0X0010*'.
			xStrP_Align_(1) /*[[nodiscard]]*/ _Bool(*const x0010_)(FILE *const restrict Stream,const void *const restrict String);
			//StrPure : Put string for char [0x0040]
			//＊(String) type is 'STRP_NC_0X0040*'.
			xStrP_Align_(1) /*[[nodiscard]]*/ _Bool(*const x0040_)(FILE *const restrict Stream,const void *const restrict String);
			//StrPure : Put string for char [0x0100]
			//＊(String) type is 'STRP_NC_0X0100*'.
			xStrP_Align_(1) /*[[nodiscard]]*/ _Bool(*const x0100_)(FILE *const restrict Stream,const void *const restrict String);
			//StrPure : Put string for char [0x0400]
			//＊(String) type is 'STRP_NC_0X0400*'.
			xStrP_Align_(1) /*[[nodiscard]]*/ _Bool(*const x0400_)(FILE *const restrict Stream,const void *const restrict String);
		}
		Puts;

		//StrPure : String Get Functions
		//＊Use "StrP_NC_Gets_" for type inference.
		//＊If (Stream) is NULL, then (stdin) is used.
		//＊Return value is defined under "StrP.Bool".
		xStrP_Align_(4) const struct
		{
			//StrPure : Get string for char [0x0010]
			xStrP_Align_(1) /*[[nodiscard]]*/ _Bool(*const x0010_)(FILE *const restrict Stream,strp_nc_0x0010 *const restrict String);
			//StrPure : Get string for char [0x0040]
			xStrP_Align_(1) /*[[nodiscard]]*/ _Bool(*const x0040_)(FILE *const restrict Stream,strp_nc_0x0040 *const restrict String);
			//StrPure : Get string for char [0x0100]
			xStrP_Align_(1) /*[[nodiscard]]*/ _Bool(*const x0100_)(FILE *const restrict Stream,strp_nc_0x0100 *const restrict String);
			//StrPure : Get string for char [0x0400]
			xStrP_Align_(1) /*[[nodiscard]]*/ _Bool(*const x0400_)(FILE *const restrict Stream,strp_nc_0x0400 *const restrict String);
		}
		Gets;
	}
	NC;
}
#undef xStrP_Align_
STRPACK;

#ifdef uPURES_DLL_IMPORT_
uPURES_DLL_IMPORT_
#endif

//StrPure : Library Pack Object
extern STRPACK StrP,*StrP_(void);

#ifdef uSTRP_MACRO_DEFINE_

#if(1)
//StrPure : Nullify the first character of the narrow string.
//＊Return bool is true for success, false for failure.
#define StrP_NC_Null_(T) ((T)&&((xStrP_NC_Guard_T_(T)->NC[0]='\0')=='\0'))
//StrPure : Abbreviation of "StrP.NC.Cast.x####.x####_".
//＊Return flag is zero for success, non-zero for failure.
#define StrP_NC_Cast_(T,S)\
_Generic\
(\
	(T),\
		strp_nc_0x0010*:xStrP_NC_Generic_(Cast.x0010,S),\
		strp_nc_0x0040*:xStrP_NC_Generic_(Cast.x0040,S),\
		strp_nc_0x0100*:xStrP_NC_Generic_(Cast.x0100,S),\
		strp_nc_0x0400*:xStrP_NC_Generic_(Cast.x0400,S)\
)\
((T),(S))
//StrPure : Abbreviation of "StrP.NC.Find.Char.x####_".
//＊Return flag is zero for success, non-zero for failure.
#define StrP_NC_Find_Char_(String,Character,Mode) xStrP_NC_Generic_(Find.Char,String)((String),(Character),(Mode))
//StrPure : Abbreviation of "StrP.NC.Find.String.x####_".
//＊Return flag is zero for success, non-zero for failure.
#define StrP_NC_Find_String_(Str,SubStr) xStrP_NC_Generic_(Find.String,Str)((Str),(SubStr))
//StrPure : Abbreviation of "StrP.NC.Length.x####_".
//＊Return flag is zero for success, non-zero for failure.
#define StrP_NC_Length_(String) xStrP_NC_Generic_(Length,String)(String)
//StrPure : Abbreviation of "StrP.NC.Reset.x####_".
//＊Return flag is zero for success, non-zero for failure.
#define StrP_NC_Reset_(String) xStrP_NC_Generic_(Reset,String)(String)
//StrPure : Abbreviation of "StrP.NC.Copy.x####_".
//＊Return flag is zero for success, non-zero for failure.
#define StrP_NC_Copy_(Target,Source) xStrP_NC_Generic_(Copy,Target)((Target),(Source))
//StrPure : Abbreviation of "StrP.NC.Conc.x####_".
//＊Return flag is zero for success, non-zero for failure.
#define StrP_NC_Conc_(Target,Source) xStrP_NC_Generic_(Conc,Target)((Target),(Source))
//StrPure : Abbreviation of "StrP.NC.Crop.x####_".
//＊Return flag is zero for success, non-zero for failure.
#define StrP_NC_Crop_(Target,Source,Offset,Length) xStrP_NC_Generic_(Crop,Target)((Target),(Source),(Offset),(Length))
//StrPure : Abbreviation of "StrP.NC.Comp.x####_".
//＊Return flag is zero for success, non-zero for failure.
#define StrP_NC_Comp_(Left,Right) xStrP_NC_Generic_(Comp,Left)((Left),(Right))
//StrPure : Abbreviation of "StrP.NC.Puts.x####_".
//＊Return bool is true for success, false for failure.
#define StrP_NC_Puts_(Stream,String) xStrP_NC_Generic_(Puts,String)((Stream),(String))
//StrPure : Abbreviation of "StrP.NC.Gets.x####_".
//＊Return bool is true for success, false for failure.
#define StrP_NC_Gets_(Stream,String) xStrP_NC_Generic_(Gets,String)((Stream),(String))
#endif

#if(defined(__STDC_WANT_LIB_EXT1__)&&(__STDC_WANT_LIB_EXT1__))
//StrPure : String I/O with the specified format.
//＊Mode I : Scan from the buffer.
//　Mode O : Print into the buffer.
//＊Return bool is true for success, false for failure.
#define StrP_NC_Form_(Mode,Buffer,...) xStrP_NC_Format_(Mode,Buffer,__VA_ARGS__)
#define xStrP_NC_Format_(Mode,Buffer,...) (xStrP_NC_Format_##Mode##_(Buffer,__VA_ARGS__)>=0)
#define xStrP_NC_Format_I_(S,...) sscanf_s(xStrP_NC_Guard_S_(S)->NC,__VA_ARGS__)
#define xStrP_NC_Format_O_(T,...) snprintf_s(xStrP_NC_Guard_T_(T)->NC,sizeof(*(T)),__VA_ARGS__)

//StrPure : Stream I/O with the specified format.
//＊Mode I : Scan from the stream.
//　Mode O : Print into the stream.
//＊Return bool is true for success, false for failure.
#define StrP_IO_Form_(Mode,Stream,...) xStrP_IO_Format_(Mode,Stream,__VA_ARGS__)
#define xStrP_IO_Format_(Mode,Stream,...) (xStrP_IO_Format_##Mode##_(Stream,__VA_ARGS__)>=0)
#define xStrP_IO_Format_I_(I,...) fscanf_s((I)?(I):(stdin),__VA_ARGS__)
#define xStrP_IO_Format_O_(O,...) fprintf_s((O)?(O):(stdout),__VA_ARGS__)

#else
#error #define __STDC_WANT_LIB_EXT1__ (1) before #include <strpure.h>
#endif

#if(1)
//StrPure : Type Guard for Source String
#define xStrP_NC_Guard_S_(S)\
_Generic\
(\
	*(S),\
		strp_nc_0x0010:(S),\
		strp_nc_0x0040:(S),\
		strp_nc_0x0100:(S),\
		strp_nc_0x0400:(S)\
)
//StrPure : Type Guard for Target String
#define xStrP_NC_Guard_T_(T)\
_Generic\
(\
	(T),\
		strp_nc_0x0010*:(T),\
		strp_nc_0x0040*:(T),\
		strp_nc_0x0100*:(T),\
		strp_nc_0x0400*:(T)\
)
//StrPure : Generic for 'strp_nc_0x####*' or 'STRP_NC_0X####*'.
#define xStrP_NC_Generic_(Func,S)\
_Generic\
(\
	*(S),\
		strp_nc_0x0010:StrP.NC.Func.x0010_,\
		strp_nc_0x0040:StrP.NC.Func.x0040_,\
		strp_nc_0x0100:StrP.NC.Func.x0100_,\
		strp_nc_0x0400:StrP.NC.Func.x0400_\
)
#endif

#endif

#endif
