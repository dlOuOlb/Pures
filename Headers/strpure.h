/*------------------------------------------------------------------*/
/*	StrPure provides some rigid string handling functions.			*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Pures/					2019.07.08	*/
/*------------------------------------------------------------------*/

#ifndef _INC_STRPURE
#define _INC_STRPURE

#include <stddef.h>

#define _StrP_Define_(type,form,FORM,Nums) struct _strp_##form##_0x##Nums{type FORM[0x##Nums];};typedef struct _strp_##form##_0x##Nums strp_##form##_0x##Nums;typedef const struct _strp_##form##_0x##Nums STRP_##FORM##_0X##Nums;

_StrP_Define_(char,nc,NC,0010)	//StrPure : strp_nc_0x0010.NC for char [0x0010]
_StrP_Define_(char,nc,NC,0040)	//StrPure : strp_nc_0x0040.NC for char [0x0040]
_StrP_Define_(char,nc,NC,0100)	//StrPure : strp_nc_0x0100.NC for char [0x0100]
_StrP_Define_(char,nc,NC,0400)	//StrPure : strp_nc_0x0400.NC for char [0x0400]

_StrP_Define_(wchar_t,wc,WC,0010)	//StrPure : strp_wc_0x0010.WC for wchar_t [0x0010]
_StrP_Define_(wchar_t,wc,WC,0040)	//StrPure : strp_wc_0x0040.WC for wchar_t [0x0040]
_StrP_Define_(wchar_t,wc,WC,0100)	//StrPure : strp_wc_0x0100.WC for wchar_t [0x0100]
_StrP_Define_(wchar_t,wc,WC,0400)	//StrPure : strp_wc_0x0400.WC for wchar_t [0x0400]

#undef _StrP_Define_

//StrPure : Library Pack Structure
struct _strpack
{
	//StrPure : Null-terminated Native Narrow Character String Functions
	const struct
	{
		//StrPure : String Length Functions
		//＊Return value is, if a null character is found,
		//　then the length of the string, else the capacity of the buffer.
		const struct
		{
			size_t(*const x0010_)(STRP_NC_0X0010 *const String);	//StrPure : Length for char [0x0010]
			size_t(*const x0040_)(STRP_NC_0X0040 *const String);	//StrPure : Length for char [0x0040]
			size_t(*const x0100_)(STRP_NC_0X0100 *const String);	//StrPure : Length for char [0x0100]
			size_t(*const x0400_)(STRP_NC_0X0400 *const String);	//StrPure : Length for char [0x0400]
		}
		Length;

		//StrPure : Find Functions
		const struct
		{
			//StrPure : Character Find Functions
			//＊Finding will be committed, if the mode is true,
			//　then by forward direction, else by reverse direction.
			//＊Return value is, if the character is found,
			//　then its index in the string, else the capacity of the buffer.
			const struct
			{
				size_t(*const x0010_)(STRP_NC_0X0010 *const String,const char Character,const _Bool Mode);	//StrPure : Find the character for char [0x0010]
				size_t(*const x0040_)(STRP_NC_0X0040 *const String,const char Character,const _Bool Mode);	//StrPure : Find the character for char [0x0040]
				size_t(*const x0100_)(STRP_NC_0X0100 *const String,const char Character,const _Bool Mode);	//StrPure : Find the character for char [0x0100]
				size_t(*const x0400_)(STRP_NC_0X0400 *const String,const char Character,const _Bool Mode);	//StrPure : Find the character for char [0x0400]
			}
			Char;

			//StrPure : String Find Functions
			//＊Return value is, if the sub-string is found,
			//　then its offset in the string, else the capacity of the buffer.
			const struct
			{
				size_t(*const x0010_)(STRP_NC_0X0010 *const String,STRP_NC_0X0010 *const SubString);	//StrPure : Find the sub-string for char [0x0010]
				size_t(*const x0040_)(STRP_NC_0X0040 *const String,STRP_NC_0X0040 *const SubString);	//StrPure : Find the sub-string for char [0x0040]
				size_t(*const x0100_)(STRP_NC_0X0100 *const String,STRP_NC_0X0100 *const SubString);	//StrPure : Find the sub-string for char [0x0100]
				size_t(*const x0400_)(STRP_NC_0X0400 *const String,STRP_NC_0X0400 *const SubString);	//StrPure : Find the sub-string for char [0x0400]
			}
			String;
		}
		Find;

		//StrPure : String Reset Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			int(*const x0010_)(strp_nc_0x0010 *const restrict String);	//StrPure : Reset for char [0x0010]
			int(*const x0040_)(strp_nc_0x0040 *const restrict String);	//StrPure : Reset for char [0x0040]
			int(*const x0100_)(strp_nc_0x0100 *const restrict String);	//StrPure : Reset for char [0x0100]
			int(*const x0400_)(strp_nc_0x0400 *const restrict String);	//StrPure : Reset for char [0x0400]
		}
		Reset;

		//StrPure : String Copy Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			int(*const x0010_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0010 *const restrict Source);	//StrPure : Copy for char [0x0010]
			int(*const x0040_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0040 *const restrict Source);	//StrPure : Copy for char [0x0040]
			int(*const x0100_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0100 *const restrict Source);	//StrPure : Copy for char [0x0100]
			int(*const x0400_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0400 *const restrict Source);	//StrPure : Copy for char [0x0400]
		}
		Copy;

		//StrPure : String Concatenation Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			int(*const x0010_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0010 *const restrict Source);	//StrPure : Concatenation for char [0x0010]
			int(*const x0040_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0040 *const restrict Source);	//StrPure : Concatenation for char [0x0040]
			int(*const x0100_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0100 *const restrict Source);	//StrPure : Concatenation for char [0x0100]
			int(*const x0400_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0400 *const restrict Source);	//StrPure : Concatenation for char [0x0400]
		}
		Conc;

		//StrPure : String Crop Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			int(*const x0010_)(strp_nc_0x0010 *const Target,STRP_NC_0X0010 *const Source,const size_t Offset,const size_t Length);	//StrPure : Crop for char [0x0010]
			int(*const x0040_)(strp_nc_0x0040 *const Target,STRP_NC_0X0040 *const Source,const size_t Offset,const size_t Length);	//StrPure : Crop for char [0x0040]
			int(*const x0100_)(strp_nc_0x0100 *const Target,STRP_NC_0X0100 *const Source,const size_t Offset,const size_t Length);	//StrPure : Crop for char [0x0100]
			int(*const x0400_)(strp_nc_0x0400 *const Target,STRP_NC_0X0400 *const Source,const size_t Offset,const size_t Length);	//StrPure : Crop for char [0x0400]
		}
		Crop;

		//StrPure : String Comparison Functions
		//＊Return value is,
		//　with the left one against the right one in lexicographical order,
		//　negative for 'before', zero for 'equal', or positive for 'after'.
		const struct
		{
			int(*const x0010_)(STRP_NC_0X0010 *const Left,STRP_NC_0X0010 *const Right);	//StrPure : Comparison for char [0x0010]
			int(*const x0040_)(STRP_NC_0X0040 *const Left,STRP_NC_0X0040 *const Right);	//StrPure : Comparison for char [0x0040]
			int(*const x0100_)(STRP_NC_0X0100 *const Left,STRP_NC_0X0100 *const Right);	//StrPure : Comparison for char [0x0100]
			int(*const x0400_)(STRP_NC_0X0400 *const Left,STRP_NC_0X0400 *const Right);	//StrPure : Comparison for char [0x0400]
		}
		Comp;

		//StrPure : String Cast Functions
		//＊Truncation could occur.
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			//StrPure : Cast to char [0x0010]
			const struct
			{
				int(*const x0010_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0010 *const restrict Source);	//StrPure : Cast from char [0x0010]
				int(*const x0040_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0040 *const restrict Source);	//StrPure : Cast from char [0x0040]
				int(*const x0100_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0100 *const restrict Source);	//StrPure : Cast from char [0x0100]
				int(*const x0400_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0400 *const restrict Source);	//StrPure : Cast from char [0x0400]
			}
			x0010;

			//StrPure : Cast to char [0x0040]
			const struct
			{
				int(*const x0010_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0010 *const restrict Source);	//StrPure : Cast from char [0x0010]
				int(*const x0040_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0040 *const restrict Source);	//StrPure : Cast from char [0x0040]
				int(*const x0100_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0100 *const restrict Source);	//StrPure : Cast from char [0x0100]
				int(*const x0400_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0400 *const restrict Source);	//StrPure : Cast from char [0x0400]
			}
			x0040;

			//StrPure : Cast to char [0x0100]
			const struct
			{
				int(*const x0010_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0010 *const restrict Source);	//StrPure : Cast from char [0x0010]
				int(*const x0040_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0040 *const restrict Source);	//StrPure : Cast from char [0x0040]
				int(*const x0100_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0100 *const restrict Source);	//StrPure : Cast from char [0x0100]
				int(*const x0400_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0400 *const restrict Source);	//StrPure : Cast from char [0x0400]
			}
			x0100;

			//StrPure : Cast to char [0x0400]
			const struct
			{
				int(*const x0010_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0010 *const restrict Source);	//StrPure : Cast from char [0x0010]
				int(*const x0040_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0040 *const restrict Source);	//StrPure : Cast from char [0x0040]
				int(*const x0100_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0100 *const restrict Source);	//StrPure : Cast from char [0x0100]
				int(*const x0400_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0400 *const restrict Source);	//StrPure : Cast from char [0x0400]
			}
			x0400;
		}
		Cast;
	}
	NC;

	//StrPure : Null-terminated Native Wide Character String Functions
	const struct
	{
		//StrPure : String Length Functions
		//＊Return value is, if a null character is found,
		//　then the length of the string, else the capacity of the buffer.
		const struct
		{
			size_t(*const x0010_)(STRP_WC_0X0010 *const String);	//StrPure : Length for wchar_t [0x0010]
			size_t(*const x0040_)(STRP_WC_0X0040 *const String);	//StrPure : Length for wchar_t [0x0040]
			size_t(*const x0100_)(STRP_WC_0X0100 *const String);	//StrPure : Length for wchar_t [0x0100]
			size_t(*const x0400_)(STRP_WC_0X0400 *const String);	//StrPure : Length for wchar_t [0x0400]
		}
		Length;

		//StrPure : Find Functions
		const struct
		{
			//StrPure : Character Find Functions
			//＊Finding will be done, if the mode is true,
			//　then by forward direction, else by reverse direction.
			//＊Return value is, if the character is found,
			//　then its index in the string, else the capacity of the buffer.
			const struct
			{
				size_t(*const x0010_)(STRP_WC_0X0010 *const String,const wchar_t Character,const _Bool Mode);	//StrPure : Find the character for wchar_t [0x0010]
				size_t(*const x0040_)(STRP_WC_0X0040 *const String,const wchar_t Character,const _Bool Mode);	//StrPure : Find the character for wchar_t [0x0040]
				size_t(*const x0100_)(STRP_WC_0X0100 *const String,const wchar_t Character,const _Bool Mode);	//StrPure : Find the character for wchar_t [0x0100]
				size_t(*const x0400_)(STRP_WC_0X0400 *const String,const wchar_t Character,const _Bool Mode);	//StrPure : Find the character for wchar_t [0x0400]
			}
			Char;

			//StrPure : String Find Functions
			//＊Return value is, if the sub-string is found,
			//　then its offset in the string, else the capacity of the buffer.
			const struct
			{
				size_t(*const x0010_)(STRP_WC_0X0010 *const String,STRP_WC_0X0010 *const SubString);	//StrPure : Find the sub-string for wchar_t [0x0010]
				size_t(*const x0040_)(STRP_WC_0X0040 *const String,STRP_WC_0X0040 *const SubString);	//StrPure : Find the sub-string for wchar_t [0x0040]
				size_t(*const x0100_)(STRP_WC_0X0100 *const String,STRP_WC_0X0100 *const SubString);	//StrPure : Find the sub-string for wchar_t [0x0100]
				size_t(*const x0400_)(STRP_WC_0X0400 *const String,STRP_WC_0X0400 *const SubString);	//StrPure : Find the sub-string for wchar_t [0x0400]
			}
			String;
		}
		Find;

		//StrPure : String Reset Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			int(*const x0010_)(strp_wc_0x0010 *const restrict String);	//StrPure : Reset for wchar_t [0x0010]
			int(*const x0040_)(strp_wc_0x0040 *const restrict String);	//StrPure : Reset for wchar_t [0x0040]
			int(*const x0100_)(strp_wc_0x0100 *const restrict String);	//StrPure : Reset for wchar_t [0x0100]
			int(*const x0400_)(strp_wc_0x0400 *const restrict String);	//StrPure : Reset for wchar_t [0x0400]
		}
		Reset;

		//StrPure : String Copy Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			int(*const x0010_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0010 *const restrict Source);	//StrPure : Copy for wchar_t [0x0010]
			int(*const x0040_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0040 *const restrict Source);	//StrPure : Copy for wchar_t [0x0040]
			int(*const x0100_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0100 *const restrict Source);	//StrPure : Copy for wchar_t [0x0100]
			int(*const x0400_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0400 *const restrict Source);	//StrPure : Copy for wchar_t [0x0400]
		}
		Copy;

		//StrPure : String Concatenation Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			int(*const x0010_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0010 *const restrict Source);	//StrPure : Concatenation for wchar_t [0x0010]
			int(*const x0040_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0040 *const restrict Source);	//StrPure : Concatenation for wchar_t [0x0040]
			int(*const x0100_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0100 *const restrict Source);	//StrPure : Concatenation for wchar_t [0x0100]
			int(*const x0400_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0400 *const restrict Source);	//StrPure : Concatenation for wchar_t [0x0400]
		}
		Conc;

		//StrPure : String Crop Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			int(*const x0010_)(strp_wc_0x0010 *const Target,STRP_WC_0X0010 *const Source,const size_t Offset,const size_t Length);	//StrPure : Crop for wchar_t [0x0010]
			int(*const x0040_)(strp_wc_0x0040 *const Target,STRP_WC_0X0040 *const Source,const size_t Offset,const size_t Length);	//StrPure : Crop for wchar_t [0x0040]
			int(*const x0100_)(strp_wc_0x0100 *const Target,STRP_WC_0X0100 *const Source,const size_t Offset,const size_t Length);	//StrPure : Crop for wchar_t [0x0100]
			int(*const x0400_)(strp_wc_0x0400 *const Target,STRP_WC_0X0400 *const Source,const size_t Offset,const size_t Length);	//StrPure : Crop for wchar_t [0x0400]
		}
		Crop;

		//StrPure : String Comparison Functions
		//＊Return value is,
		//　with the left one against the right one in lexicographical order,
		//　negative for 'before', zero for 'equal', or positive for 'after'.
		const struct
		{
			int(*const x0010_)(STRP_WC_0X0010 *const Left,STRP_WC_0X0010 *const Right);	//StrPure : Comparison for wchar_t [0x0010]
			int(*const x0040_)(STRP_WC_0X0040 *const Left,STRP_WC_0X0040 *const Right);	//StrPure : Comparison for wchar_t [0x0040]
			int(*const x0100_)(STRP_WC_0X0100 *const Left,STRP_WC_0X0100 *const Right);	//StrPure : Comparison for wchar_t [0x0100]
			int(*const x0400_)(STRP_WC_0X0400 *const Left,STRP_WC_0X0400 *const Right);	//StrPure : Comparison for wchar_t [0x0400]
		}
		Comp;

		//StrPure : String Cast Functions
		//＊Truncation could occur.
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			//StrPure : Cast to wchar_t [0x0010]
			const struct
			{
				int(*const x0010_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0010 *const restrict Source);	//StrPure : Cast from wchar_t [0x0010]
				int(*const x0040_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0040 *const restrict Source);	//StrPure : Cast from wchar_t [0x0040]
				int(*const x0100_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0100 *const restrict Source);	//StrPure : Cast from wchar_t [0x0100]
				int(*const x0400_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0400 *const restrict Source);	//StrPure : Cast from wchar_t [0x0400]
			}
			x0010;

			//StrPure : Cast to wchar_t [0x0040]
			const struct
			{
				int(*const x0010_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0010 *const restrict Source);	//StrPure : Cast from wchar_t [0x0010]
				int(*const x0040_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0040 *const restrict Source);	//StrPure : Cast from wchar_t [0x0040]
				int(*const x0100_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0100 *const restrict Source);	//StrPure : Cast from wchar_t [0x0100]
				int(*const x0400_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0400 *const restrict Source);	//StrPure : Cast from wchar_t [0x0400]
			}
			x0040;

			//StrPure : Cast to wchar_t [0x0100]
			const struct
			{
				int(*const x0010_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0010 *const restrict Source);	//StrPure : Cast from wchar_t [0x0010]
				int(*const x0040_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0040 *const restrict Source);	//StrPure : Cast from wchar_t [0x0040]
				int(*const x0100_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0100 *const restrict Source);	//StrPure : Cast from wchar_t [0x0100]
				int(*const x0400_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0400 *const restrict Source);	//StrPure : Cast from wchar_t [0x0400]
			}
			x0100;

			//StrPure : Cast to wchar_t [0x0400]
			const struct
			{
				int(*const x0010_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0010 *const restrict Source);	//StrPure : Cast from wchar_t [0x0010]
				int(*const x0040_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0040 *const restrict Source);	//StrPure : Cast from wchar_t [0x0040]
				int(*const x0100_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0100 *const restrict Source);	//StrPure : Cast from wchar_t [0x0100]
				int(*const x0400_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0400 *const restrict Source);	//StrPure : Cast from wchar_t [0x0400]
			}
			x0400;
		}
		Cast;
	}
	WC;

	//StrPure : Error Numbers
	const struct
	{
		const int Zero;		//StrPure : No error.
		const int Dom;		//StrPure : Mathematics argument out of domain of function.
		const int IlSeq;	//StrPure : Illegal byte sequence.
		const int Range;	//StrPure : Result too large.
	}
	Errno;

	//StrPure : Library Version - "Date:yyyy.mm.dd"
	const char *const Version;
};
typedef struct _strpack strpack;		//StrPure : Library Pack Variable (Prohibited)
typedef const struct _strpack STRPACK;	//StrPure : Library Pack Constant

//StrPure : Library Pack Object
extern STRPACK StrP;
//StrPure : Indirect access to the library pack object.
extern STRPACK *StrP_(void);
#endif
