#ifndef _INC_STRPURE
#define _INC_STRPURE "Date:2019.11.22"
/*------------------------------------------------------------------*/
/*	StrPure provides some inflexible string handling functions.		*/
/*																	*/
/*	Written by Ranny Clover											*/
/*	http://github.com/dlOuOlb/Pures/								*/
/*------------------------------------------------------------------*/

#include <stddef.h>
#include <stdio.h>

#define _StrP_Define_(type,form,FORM,Nums) struct _strp_##form##_0x##Nums{type FORM[0x##Nums];};typedef struct _strp_##form##_0x##Nums strp_##form##_0x##Nums;typedef const struct _strp_##form##_0x##Nums STRP_##FORM##_0X##Nums

_StrP_Define_(char,nc,NC,0010);	//StrPure : strp_nc_0x0010.NC for char [0x0010]
_StrP_Define_(char,nc,NC,0040);	//StrPure : strp_nc_0x0040.NC for char [0x0040]
_StrP_Define_(char,nc,NC,0100);	//StrPure : strp_nc_0x0100.NC for char [0x0100]
_StrP_Define_(char,nc,NC,0400);	//StrPure : strp_nc_0x0400.NC for char [0x0400]

_StrP_Define_(wchar_t,wc,WC,0010);	//StrPure : strp_wc_0x0010.WC for wchar_t [0x0010]
_StrP_Define_(wchar_t,wc,WC,0040);	//StrPure : strp_wc_0x0040.WC for wchar_t [0x0040]
_StrP_Define_(wchar_t,wc,WC,0100);	//StrPure : strp_wc_0x0100.WC for wchar_t [0x0100]
_StrP_Define_(wchar_t,wc,WC,0400);	//StrPure : strp_wc_0x0400.WC for wchar_t [0x0400]

#undef _StrP_Define_

//StrPure : Automatic String Declaration
#define StrP_Auto_(type,Auto,String) type*const(Auto)=&(type){String}

typedef const struct
{
	//StrPure : Null-terminated Native Narrow Character String Functions
	//＊(strp_nc_0x#### *)'s capacity must not be smaller than char[0x####].
	//＊(STRP_NC_0X#### *)'s capacity can be smaller than char[0x####],
	//　but must be null-terminated within it.
	const struct
	{
		//StrPure : String Length Functions
		//＊Return value is, if a null character is found,
		//　then the length of the string, else the capacity of the buffer.
		const struct
		{
			//StrPure : Length for char [0x0010]
			size_t(*const x0010_)(STRP_NC_0X0010 *const String);
			//StrPure : Length for char [0x0040]
			size_t(*const x0040_)(STRP_NC_0X0040 *const String);
			//StrPure : Length for char [0x0100]
			size_t(*const x0100_)(STRP_NC_0X0100 *const String);
			//StrPure : Length for char [0x0400]
			size_t(*const x0400_)(STRP_NC_0X0400 *const String);
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
				//StrPure : Find the character for char [0x0010]
				size_t(*const x0010_)(STRP_NC_0X0010 *const String,const char Character,const _Bool Mode);
				//StrPure : Find the character for char [0x0040]
				size_t(*const x0040_)(STRP_NC_0X0040 *const String,const char Character,const _Bool Mode);
				//StrPure : Find the character for char [0x0100]
				size_t(*const x0100_)(STRP_NC_0X0100 *const String,const char Character,const _Bool Mode);
				//StrPure : Find the character for char [0x0400]
				size_t(*const x0400_)(STRP_NC_0X0400 *const String,const char Character,const _Bool Mode);
			}
			Char;

			//StrPure : String Find Functions
			//＊Return value is, if the sub-string is found,
			//　then its offset in the string, else the capacity of the buffer.
			const struct
			{
				//StrPure : Find the sub-string for char [0x0010]
				size_t(*const x0010_)(STRP_NC_0X0010 *const String,STRP_NC_0X0010 *const SubString);
				//StrPure : Find the sub-string for char [0x0040]
				size_t(*const x0040_)(STRP_NC_0X0040 *const String,STRP_NC_0X0040 *const SubString);
				//StrPure : Find the sub-string for char [0x0100]
				size_t(*const x0100_)(STRP_NC_0X0100 *const String,STRP_NC_0X0100 *const SubString);
				//StrPure : Find the sub-string for char [0x0400]
				size_t(*const x0400_)(STRP_NC_0X0400 *const String,STRP_NC_0X0400 *const SubString);
			}
			String;
		}
		Find;

		//StrPure : String Reset Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			//StrPure : Reset for char [0x0010]
			int(*const x0010_)(strp_nc_0x0010 *const restrict String);
			//StrPure : Reset for char [0x0040]
			int(*const x0040_)(strp_nc_0x0040 *const restrict String);
			//StrPure : Reset for char [0x0100]
			int(*const x0100_)(strp_nc_0x0100 *const restrict String);
			//StrPure : Reset for char [0x0400]
			int(*const x0400_)(strp_nc_0x0400 *const restrict String);
		}
		Reset;

		//StrPure : String Copy Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			//StrPure : Copy for char [0x0010]
			int(*const x0010_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0010 *const restrict Source);
			//StrPure : Copy for char [0x0040]
			int(*const x0040_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0040 *const restrict Source);
			//StrPure : Copy for char [0x0100]
			int(*const x0100_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0100 *const restrict Source);
			//StrPure : Copy for char [0x0400]
			int(*const x0400_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0400 *const restrict Source);
		}
		Copy;

		//StrPure : String Concatenation Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			//StrPure : Concatenation for char [0x0010]
			int(*const x0010_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0010 *const restrict Source);
			//StrPure : Concatenation for char [0x0040]
			int(*const x0040_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0040 *const restrict Source);
			//StrPure : Concatenation for char [0x0100]
			int(*const x0100_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0100 *const restrict Source);
			//StrPure : Concatenation for char [0x0400]
			int(*const x0400_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0400 *const restrict Source);
		}
		Conc;

		//StrPure : String Crop Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			//StrPure : Crop for char [0x0010]
			int(*const x0010_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0010 *const restrict Source,const size_t Offset,const size_t Length);
			//StrPure : Crop for char [0x0040]
			int(*const x0040_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0040 *const restrict Source,const size_t Offset,const size_t Length);
			//StrPure : Crop for char [0x0100]
			int(*const x0100_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0100 *const restrict Source,const size_t Offset,const size_t Length);
			//StrPure : Crop for char [0x0400]
			int(*const x0400_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0400 *const restrict Source,const size_t Offset,const size_t Length);
		}
		Crop;

		//StrPure : String Comparison Functions
		//＊Return value is,
		//　with the left one against the right one in lexicographical order,
		//　negative for 'before', zero for 'equal', or positive for 'after'.
		const struct
		{
			//StrPure : Comparison for char [0x0010]
			int(*const x0010_)(STRP_NC_0X0010 *const Left,STRP_NC_0X0010 *const Right);
			//StrPure : Comparison for char [0x0040]
			int(*const x0040_)(STRP_NC_0X0040 *const Left,STRP_NC_0X0040 *const Right);
			//StrPure : Comparison for char [0x0100]
			int(*const x0100_)(STRP_NC_0X0100 *const Left,STRP_NC_0X0100 *const Right);
			//StrPure : Comparison for char [0x0400]
			int(*const x0400_)(STRP_NC_0X0400 *const Left,STRP_NC_0X0400 *const Right);
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
				//StrPure : Cast from char [0x0010]
				int(*const x0010_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0010 *const restrict Source);
				//StrPure : Cast from char [0x0040]
				int(*const x0040_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0040 *const restrict Source);
				//StrPure : Cast from char [0x0100]
				int(*const x0100_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0100 *const restrict Source);
				//StrPure : Cast from char [0x0400]
				int(*const x0400_)(strp_nc_0x0010 *const restrict Target,STRP_NC_0X0400 *const restrict Source);
			}
			x0010;

			//StrPure : Cast to char [0x0040]
			const struct
			{
				//StrPure : Cast from char [0x0010]
				int(*const x0010_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0010 *const restrict Source);
				//StrPure : Cast from char [0x0040]
				int(*const x0040_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0040 *const restrict Source);
				//StrPure : Cast from char [0x0100]
				int(*const x0100_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0100 *const restrict Source);
				//StrPure : Cast from char [0x0400]
				int(*const x0400_)(strp_nc_0x0040 *const restrict Target,STRP_NC_0X0400 *const restrict Source);
			}
			x0040;

			//StrPure : Cast to char [0x0100]
			const struct
			{
				//StrPure : Cast from char [0x0010]
				int(*const x0010_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0010 *const restrict Source);
				//StrPure : Cast from char [0x0040]
				int(*const x0040_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0040 *const restrict Source);
				//StrPure : Cast from char [0x0100]
				int(*const x0100_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0100 *const restrict Source);
				//StrPure : Cast from char [0x0400]
				int(*const x0400_)(strp_nc_0x0100 *const restrict Target,STRP_NC_0X0400 *const restrict Source);
			}
			x0100;

			//StrPure : Cast to char [0x0400]
			const struct
			{
				//StrPure : Cast from char [0x0010]
				int(*const x0010_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0010 *const restrict Source);
				//StrPure : Cast from char [0x0040]
				int(*const x0040_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0040 *const restrict Source);
				//StrPure : Cast from char [0x0100]
				int(*const x0100_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0100 *const restrict Source);
				//StrPure : Cast from char [0x0400]
				int(*const x0400_)(strp_nc_0x0400 *const restrict Target,STRP_NC_0X0400 *const restrict Source);
			}
			x0400;
		}
		Cast;

		//StrPure : String Put Functions
		//＊If (Stream) is NULL, then (stdout) will be used.
		//＊Return value is defined under "StrP.Bool".
		const struct
		{
			//StrPure : Put string for char [0x0010]
			_Bool(*const x0010_)(STRP_NC_0X0010 *const restrict String,FILE *const restrict Stream);
			//StrPure : Put string for char [0x0040]
			_Bool(*const x0040_)(STRP_NC_0X0040 *const restrict String,FILE *const restrict Stream);
			//StrPure : Put string for char [0x0100]
			_Bool(*const x0100_)(STRP_NC_0X0100 *const restrict String,FILE *const restrict Stream);
			//StrPure : Put string for char [0x0400]
			_Bool(*const x0400_)(STRP_NC_0X0400 *const restrict String,FILE *const restrict Stream);
		}
		Puts;

		//StrPure : String Get Functions
		//＊If (Stream) is NULL, then (stdin) will be used.
		//＊Return value is defined under "StrP.Bool".
		const struct
		{
			//StrPure : Get string for char [0x0010]
			_Bool(*const x0010_)(strp_nc_0x0010 *const restrict String,FILE *const restrict Stream);
			//StrPure : Get string for char [0x0040]
			_Bool(*const x0040_)(strp_nc_0x0040 *const restrict String,FILE *const restrict Stream);
			//StrPure : Get string for char [0x0100]
			_Bool(*const x0100_)(strp_nc_0x0100 *const restrict String,FILE *const restrict Stream);
			//StrPure : Get string for char [0x0400]
			_Bool(*const x0400_)(strp_nc_0x0400 *const restrict String,FILE *const restrict Stream);
		}
		Gets;
	}
	NC;

	//StrPure : Null-terminated Native Wide Character String Functions
	//＊(strp_wc_0x#### *)'s capacity must not be smaller than wchar_t[0x####].
	//＊(STRP_WC_0X#### *)'s capacity can be smaller than wchar_t[0x####],
	//　but must be null-terminated within it.
	const struct
	{
		//StrPure : String Length Functions
		//＊Return value is, if a null character is found,
		//　then the length of the string, else the capacity of the buffer.
		const struct
		{
			//StrPure : Length for wchar_t [0x0010]
			size_t(*const x0010_)(STRP_WC_0X0010 *const String);
			//StrPure : Length for wchar_t [0x0040]
			size_t(*const x0040_)(STRP_WC_0X0040 *const String);
			//StrPure : Length for wchar_t [0x0100]
			size_t(*const x0100_)(STRP_WC_0X0100 *const String);
			//StrPure : Length for wchar_t [0x0400]
			size_t(*const x0400_)(STRP_WC_0X0400 *const String);
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
				//StrPure : Find the character for wchar_t [0x0010]
				size_t(*const x0010_)(STRP_WC_0X0010 *const String,const wchar_t Character,const _Bool Mode);
				//StrPure : Find the character for wchar_t [0x0040]
				size_t(*const x0040_)(STRP_WC_0X0040 *const String,const wchar_t Character,const _Bool Mode);
				//StrPure : Find the character for wchar_t [0x0100]
				size_t(*const x0100_)(STRP_WC_0X0100 *const String,const wchar_t Character,const _Bool Mode);
				//StrPure : Find the character for wchar_t [0x0400]
				size_t(*const x0400_)(STRP_WC_0X0400 *const String,const wchar_t Character,const _Bool Mode);
			}
			Char;

			//StrPure : String Find Functions
			//＊Return value is, if the sub-string is found,
			//　then its offset in the string, else the capacity of the buffer.
			const struct
			{
				//StrPure : Find the sub-string for wchar_t [0x0010]
				size_t(*const x0010_)(STRP_WC_0X0010 *const String,STRP_WC_0X0010 *const SubString);
				//StrPure : Find the sub-string for wchar_t [0x0040]
				size_t(*const x0040_)(STRP_WC_0X0040 *const String,STRP_WC_0X0040 *const SubString);
				//StrPure : Find the sub-string for wchar_t [0x0100]
				size_t(*const x0100_)(STRP_WC_0X0100 *const String,STRP_WC_0X0100 *const SubString);
				//StrPure : Find the sub-string for wchar_t [0x0400]
				size_t(*const x0400_)(STRP_WC_0X0400 *const String,STRP_WC_0X0400 *const SubString);
			}
			String;
		}
		Find;

		//StrPure : String Reset Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			//StrPure : Reset for wchar_t [0x0010]
			int(*const x0010_)(strp_wc_0x0010 *const restrict String);
			//StrPure : Reset for wchar_t [0x0040]
			int(*const x0040_)(strp_wc_0x0040 *const restrict String);
			//StrPure : Reset for wchar_t [0x0100]
			int(*const x0100_)(strp_wc_0x0100 *const restrict String);
			//StrPure : Reset for wchar_t [0x0400]
			int(*const x0400_)(strp_wc_0x0400 *const restrict String);
		}
		Reset;

		//StrPure : String Copy Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			//StrPure : Copy for wchar_t [0x0010]
			int(*const x0010_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0010 *const restrict Source);
			//StrPure : Copy for wchar_t [0x0040]
			int(*const x0040_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0040 *const restrict Source);
			//StrPure : Copy for wchar_t [0x0100]
			int(*const x0100_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0100 *const restrict Source);
			//StrPure : Copy for wchar_t [0x0400]
			int(*const x0400_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0400 *const restrict Source);
		}
		Copy;

		//StrPure : String Concatenation Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			//StrPure : Concatenation for wchar_t [0x0010]
			int(*const x0010_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0010 *const restrict Source);
			//StrPure : Concatenation for wchar_t [0x0040]
			int(*const x0040_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0040 *const restrict Source);
			//StrPure : Concatenation for wchar_t [0x0100]
			int(*const x0100_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0100 *const restrict Source);
			//StrPure : Concatenation for wchar_t [0x0400]
			int(*const x0400_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0400 *const restrict Source);
		}
		Conc;

		//StrPure : String Crop Functions
		//＊Return value is defined under "StrP.Errno".
		const struct
		{
			//StrPure : Crop for wchar_t [0x0010]
			int(*const x0010_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0010 *const restrict Source,const size_t Offset,const size_t Length);
			//StrPure : Crop for wchar_t [0x0040]
			int(*const x0040_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0040 *const restrict Source,const size_t Offset,const size_t Length);
			//StrPure : Crop for wchar_t [0x0100]
			int(*const x0100_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0100 *const restrict Source,const size_t Offset,const size_t Length);
			//StrPure : Crop for wchar_t [0x0400]
			int(*const x0400_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0400 *const restrict Source,const size_t Offset,const size_t Length);
		}
		Crop;

		//StrPure : String Comparison Functions
		//＊Return value is,
		//　with the left one against the right one in lexicographical order,
		//　negative for 'before', zero for 'equal', or positive for 'after'.
		const struct
		{
			//StrPure : Comparison for wchar_t [0x0010]
			int(*const x0010_)(STRP_WC_0X0010 *const Left,STRP_WC_0X0010 *const Right);
			//StrPure : Comparison for wchar_t [0x0040]
			int(*const x0040_)(STRP_WC_0X0040 *const Left,STRP_WC_0X0040 *const Right);
			//StrPure : Comparison for wchar_t [0x0100]
			int(*const x0100_)(STRP_WC_0X0100 *const Left,STRP_WC_0X0100 *const Right);
			//StrPure : Comparison for wchar_t [0x0400]
			int(*const x0400_)(STRP_WC_0X0400 *const Left,STRP_WC_0X0400 *const Right);
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
				//StrPure : Cast from wchar_t [0x0010]
				int(*const x0010_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0010 *const restrict Source);
				//StrPure : Cast from wchar_t [0x0040]
				int(*const x0040_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0040 *const restrict Source);
				//StrPure : Cast from wchar_t [0x0100]
				int(*const x0100_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0100 *const restrict Source);
				//StrPure : Cast from wchar_t [0x0400]
				int(*const x0400_)(strp_wc_0x0010 *const restrict Target,STRP_WC_0X0400 *const restrict Source);
			}
			x0010;

			//StrPure : Cast to wchar_t [0x0040]
			const struct
			{
				//StrPure : Cast from wchar_t [0x0010]
				int(*const x0010_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0010 *const restrict Source);
				//StrPure : Cast from wchar_t [0x0040]
				int(*const x0040_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0040 *const restrict Source);
				//StrPure : Cast from wchar_t [0x0100]
				int(*const x0100_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0100 *const restrict Source);
				//StrPure : Cast from wchar_t [0x0400]
				int(*const x0400_)(strp_wc_0x0040 *const restrict Target,STRP_WC_0X0400 *const restrict Source);
			}
			x0040;

			//StrPure : Cast to wchar_t [0x0100]
			const struct
			{
				//StrPure : Cast from wchar_t [0x0010]
				int(*const x0010_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0010 *const restrict Source);
				//StrPure : Cast from wchar_t [0x0040]
				int(*const x0040_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0040 *const restrict Source);
				//StrPure : Cast from wchar_t [0x0100]
				int(*const x0100_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0100 *const restrict Source);
				//StrPure : Cast from wchar_t [0x0400]
				int(*const x0400_)(strp_wc_0x0100 *const restrict Target,STRP_WC_0X0400 *const restrict Source);
			}
			x0100;

			//StrPure : Cast to wchar_t [0x0400]
			const struct
			{
				//StrPure : Cast from wchar_t [0x0010]
				int(*const x0010_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0010 *const restrict Source);
				//StrPure : Cast from wchar_t [0x0040]
				int(*const x0040_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0040 *const restrict Source);
				//StrPure : Cast from wchar_t [0x0100]
				int(*const x0100_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0100 *const restrict Source);
				//StrPure : Cast from wchar_t [0x0400]
				int(*const x0400_)(strp_wc_0x0400 *const restrict Target,STRP_WC_0X0400 *const restrict Source);
			}
			x0400;
		}
		Cast;

		//StrPure : String Put Functions
		//＊If (Stream) is NULL, then (stdout) will be used.
		//＊Return value is defined under "StrP.Bool".
		const struct
		{
			//StrPure : Put string for wchar_t [0x0010]
			_Bool(*const x0010_)(STRP_WC_0X0010 *const restrict String,FILE *const restrict Stream);
			//StrPure : Put string for wchar_t [0x0040]
			_Bool(*const x0040_)(STRP_WC_0X0040 *const restrict String,FILE *const restrict Stream);
			//StrPure : Put string for wchar_t [0x0100]
			_Bool(*const x0100_)(STRP_WC_0X0100 *const restrict String,FILE *const restrict Stream);
			//StrPure : Put string for wchar_t [0x0400]
			_Bool(*const x0400_)(STRP_WC_0X0400 *const restrict String,FILE *const restrict Stream);
		}
		Puts;

		//StrPure : String Get Functions
		//＊If (Stream) is NULL, then (stdin) will be used.
		//＊Return value is defined under "StrP.Bool".
		const struct
		{
			//StrPure : Get string for wchar_t [0x0010]
			_Bool(*const x0010_)(strp_wc_0x0010 *const restrict String,FILE *const restrict Stream);
			//StrPure : Get string for wchar_t [0x0040]
			_Bool(*const x0040_)(strp_wc_0x0040 *const restrict String,FILE *const restrict Stream);
			//StrPure : Get string for wchar_t [0x0100]
			_Bool(*const x0100_)(strp_wc_0x0100 *const restrict String,FILE *const restrict Stream);
			//StrPure : Get string for wchar_t [0x0400]
			_Bool(*const x0400_)(strp_wc_0x0400 *const restrict String,FILE *const restrict Stream);
		}
		Gets;
	}
	WC;

	//StrPure : String Conversion Functions
	//＊Return value is defined under "StrP.Errno".
	const struct
	{
		//StrPure : Convert to char[]
		const struct
		{
			//StrPure : Convert from wchar_t[]
			const struct
			{
				//StrPure : [0x0010]
				int(*const x0010_)(strp_nc_0x0010 *const restrict Target,STRP_WC_0X0010 *const restrict Source);
				//StrPure : [0x0040]
				int(*const x0040_)(strp_nc_0x0040 *const restrict Target,STRP_WC_0X0040 *const restrict Source);
				//StrPure : [0x0100]
				int(*const x0100_)(strp_nc_0x0100 *const restrict Target,STRP_WC_0X0100 *const restrict Source);
				//StrPure : [0x0400]
				int(*const x0400_)(strp_nc_0x0400 *const restrict Target,STRP_WC_0X0400 *const restrict Source);
			}
			WC;
		}
		NC;

		//StrPure : Convert to wchar_t[]
		const struct
		{
			//StrPure : Convert from char[]
			const struct
			{
				//StrPure : [0x0010]
				int(*const x0010_)(strp_wc_0x0010 *const restrict Target,STRP_NC_0X0010 *const restrict Source);
				//StrPure : [0x0040]
				int(*const x0040_)(strp_wc_0x0040 *const restrict Target,STRP_NC_0X0040 *const restrict Source);
				//StrPure : [0x0100]
				int(*const x0100_)(strp_wc_0x0100 *const restrict Target,STRP_NC_0X0100 *const restrict Source);
				//StrPure : [0x0400]
				int(*const x0400_)(strp_wc_0x0400 *const restrict Target,STRP_NC_0X0400 *const restrict Source);
			}
			NC;
		}
		WC;
	}
	Convert;

	//StrPure : Error Numbers
	const struct
	{
		const int Zero;		//StrPure : No error.
		const int Dom;		//StrPure : Mathematics argument out of domain of function.
		const int IlSeq;	//StrPure : Illegal byte sequence.
		const int Range;	//StrPure : Result too large.
	}
	Errno;

	//StrPure : Locale Categories
	const struct
	{
		const int All;		//StrPure : Entire C locale.
		const int Collate;	//StrPure : Collation category.
		const int CType;	//StrPure : Character classification category.
		const int Monetary;	//StrPure : Monetary formatting category.
		const int Numeric;	//StrPure : Numeric formatting category.
		const int Time;		//StrPure : Time formatting category.
	}
	LC;

	//StrPure : Library Version - "Date:yyyy.mm.dd"
	const char *const Version;

	//StrPure : Boolean Return Values
	const struct
	{
		const _Bool Success;	//StrPure : No problem.
		const _Bool Failure;	//StrPure : Something wrong.
	}
	Bool;
}
STRPACK;	//StrPure : Library Pack Structure

//StrPure : Library Pack Object
extern STRPACK StrP;
//StrPure : Indirect access to the library pack object.
extern STRPACK *StrP_(void);
#endif
