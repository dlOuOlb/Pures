﻿#include "stdpain.h"
#include "strpure.h"

#if(1)
typedef char strp_nc;
typedef const char STRP_NC;

typedef wchar_t strp_wc;
typedef const wchar_t STRP_WC;
#endif

#if(1)
static const struct
{
	_Alignas(16) const char Version[16];
	const struct _strpack_errno Errno;
	const struct _strpack_lc LC;
	const struct _strpack_bool Bool;
	const char Locale[2];
}
_Post=
{
	.Version=_INC_STRPURE,
	.Bool=
	{
		.Success=true,
		.Failure=false
	},
	.Errno=
	{
		.Zero=0,
		.Dom=EDOM,
		.IlSeq=EILSEQ,
		.Range=ERANGE
	},
	.LC=
	{
		.All=LC_ALL,
		.Collate=LC_COLLATE,
		.CType=LC_CTYPE,
		.Monetary=LC_MONETARY,
		.Numeric=LC_NUMERIC,
		.Time=LC_TIME
	},
	.Locale="C"
};
#endif

#if(1)
static char *_StrP_NC_Find_Forward_(const char *const String,const char Character) { return strchr(String,Character); }
static char *_StrP_NC_Find_Reverse_(const char *const String,const char Character) { return strrchr(String,Character); }

#include "strpain.c"

static _Bool StrP_NC_Puts_(const char *const restrict String,FILE *const restrict Stream) { return ((String)&&(fputs(String,(Stream)?(Stream):(stdout))>=0)); }
static _Bool StrP_WC_Puts_(const wchar_t *const restrict String,FILE *const restrict Stream) { return ((String)&&(fputws(String,(Stream)?(Stream):(stdout))>=0)); }
#endif

#if(1)
static int _StrP_Convert_(errno_t(*const Convert_)(size_t *const restrict,void *const restrict,const rsize_t,const void **const restrict,const rsize_t,mbstate_t *const restrict),void *const restrict Target,const void *const restrict Source,const size_t Size)
{
	size_t Length;

	{
		const void *Pin=Source;
		mbstate_t State={0};

		const int Flag=Convert_(&Length,NULL,0,&Pin,0,&State);

		if(Flag)
			return Flag;
		else if(Length<Size)
			Length++;
		else
			return ERANGE;
	}
	{
		const void *Pin=Source;
		mbstate_t State={0};

		return Convert_(&Length,Target,Size,&Pin,Length,&State);
	}
}

static errno_t _StrP_Convert_NC_WC_(size_t *const restrict OLength,void *const restrict OString,const rsize_t OSize,const void **const restrict IPin,const rsize_t ILength,mbstate_t *const restrict State) { return wcsrtombs_s(OLength,OString,OSize,(const wchar_t**)(IPin),ILength,State); }
static int StrP_NC_WC_0x0010_(strp_nc_0x0010 *const restrict Target,STRP_WC_0X0010 *const restrict Source) { return _StrP_Convert_(_StrP_Convert_NC_WC_,Target,Source,0x0010); }
static int StrP_NC_WC_0x0040_(strp_nc_0x0040 *const restrict Target,STRP_WC_0X0040 *const restrict Source) { return _StrP_Convert_(_StrP_Convert_NC_WC_,Target,Source,0x0040); }
static int StrP_NC_WC_0x0100_(strp_nc_0x0100 *const restrict Target,STRP_WC_0X0100 *const restrict Source) { return _StrP_Convert_(_StrP_Convert_NC_WC_,Target,Source,0x0100); }
static int StrP_NC_WC_0x0400_(strp_nc_0x0400 *const restrict Target,STRP_WC_0X0400 *const restrict Source) { return _StrP_Convert_(_StrP_Convert_NC_WC_,Target,Source,0x0400); }

static errno_t _StrP_Convert_WC_NC_(size_t *const restrict OLength,void *const restrict OString,const rsize_t OSize,const void **const restrict IPin,const rsize_t ILength,mbstate_t *const restrict State) { return mbsrtowcs_s(OLength,OString,OSize,(const char**)(IPin),ILength,State); }
static int StrP_WC_NC_0x0010_(strp_wc_0x0010 *const restrict Target,STRP_NC_0X0010 *const restrict Source) { return _StrP_Convert_(_StrP_Convert_WC_NC_,Target,Source,0x0010); }
static int StrP_WC_NC_0x0040_(strp_wc_0x0040 *const restrict Target,STRP_NC_0X0040 *const restrict Source) { return _StrP_Convert_(_StrP_Convert_WC_NC_,Target,Source,0x0040); }
static int StrP_WC_NC_0x0100_(strp_wc_0x0100 *const restrict Target,STRP_NC_0X0100 *const restrict Source) { return _StrP_Convert_(_StrP_Convert_WC_NC_,Target,Source,0x0100); }
static int StrP_WC_NC_0x0400_(strp_wc_0x0400 *const restrict Target,STRP_NC_0X0400 *const restrict Source) { return _StrP_Convert_(_StrP_Convert_WC_NC_,Target,Source,0x0400); }
#endif

#if(1)
static _Bool StrP_Locale_Get_(const int Category,const size_t Size,char *const Buffer)
{
	const char *const Locale=setlocale(Category,NULL);

	return ((Locale)&&(strcpy_s(Buffer,Size,Locale)==0));
}
static _Bool StrP_Locale_Set_(const int Category,const char *const Locale) { return ((setlocale(Category,Locale))&&(true)); }
#endif

#if(1)
_Static_assert(sizeof(STRPACK)==(sizeof(STRPACE)<<7),"sizeof(STRPACK) != 128*sizeof(STRPACE)");
extern _Alignas(STRPACK) STRPACK StrP=
{
	{
		.Version=_Post.Version,
		.Bool=&(_Post.Bool),
		.Errno=&(_Post.Errno),
		.LC=&(_Post.LC)
	},
	.Locale=
	{
		.Default=_Post.Locale+0,
		.Environment=_Post.Locale+1,
		.Get_=StrP_Locale_Get_,
		.Set_=StrP_Locale_Set_
	},
	.NC=
	{
		.WC=
		{
			.x0010_=StrP_NC_WC_0x0010_,
			.x0040_=StrP_NC_WC_0x0040_,
			.x0100_=StrP_NC_WC_0x0100_,
			.x0400_=StrP_NC_WC_0x0400_
		},
		.Length=
		{
			.x0010_=StrP_NC_Length_0x0010_,
			.x0040_=StrP_NC_Length_0x0040_,
			.x0100_=StrP_NC_Length_0x0100_,
			.x0400_=StrP_NC_Length_0x0400_
		},
		.Find=
		{
			.Char=
			{
				.x0010_=StrP_NC_Find_0x0010_,
				.x0040_=StrP_NC_Find_0x0040_,
				.x0100_=StrP_NC_Find_0x0100_,
				.x0400_=StrP_NC_Find_0x0400_
			},
			.String=
			{
				.x0010_=StrP_NC_Search_0x0010_,
				.x0040_=StrP_NC_Search_0x0040_,
				.x0100_=StrP_NC_Search_0x0100_,
				.x0400_=StrP_NC_Search_0x0400_
			}
		},
		.Reset=
		{
			.x0010_=StrP_NC_Reset_0x0010_,
			.x0040_=StrP_NC_Reset_0x0040_,
			.x0100_=StrP_NC_Reset_0x0100_,
			.x0400_=StrP_NC_Reset_0x0400_
		},
		.Copy=
		{
			.x0010_=StrP_NC_Copy_0x0010_,
			.x0040_=StrP_NC_Copy_0x0040_,
			.x0100_=StrP_NC_Copy_0x0100_,
			.x0400_=StrP_NC_Copy_0x0400_
		},
		.Conc=
		{
			.x0010_=StrP_NC_Conc_0x0010_,
			.x0040_=StrP_NC_Conc_0x0040_,
			.x0100_=StrP_NC_Conc_0x0100_,
			.x0400_=StrP_NC_Conc_0x0400_
		},
		.Crop=
		{
			.x0010_=StrP_NC_Crop_0x0010_,
			.x0040_=StrP_NC_Crop_0x0040_,
			.x0100_=StrP_NC_Crop_0x0100_,
			.x0400_=StrP_NC_Crop_0x0400_
		},
		.Comp=
		{
			.x0010_=StrP_NC_Comp_0x0010_,
			.x0040_=StrP_NC_Comp_0x0040_,
			.x0100_=StrP_NC_Comp_0x0100_,
			.x0400_=StrP_NC_Comp_0x0400_
		},
		.Cast=
		{
			.x0010=
			{
				.x0010_=(int(*)(strp_nc_0x0010 *const restrict,STRP_NC_0X0010 *const restrict))(StrP_NC_Cast_0x0010_),
				.x0040_=(int(*)(strp_nc_0x0010 *const restrict,STRP_NC_0X0040 *const restrict))(StrP_NC_Cast_0x0010_),
				.x0100_=(int(*)(strp_nc_0x0010 *const restrict,STRP_NC_0X0100 *const restrict))(StrP_NC_Cast_0x0010_),
				.x0400_=(int(*)(strp_nc_0x0010 *const restrict,STRP_NC_0X0400 *const restrict))(StrP_NC_Cast_0x0010_)
			},
			.x0040=
			{
				.x0010_=(int(*)(strp_nc_0x0040 *const restrict,STRP_NC_0X0010 *const restrict))(StrP_NC_Cast_0x0010_),
				.x0040_=(int(*)(strp_nc_0x0040 *const restrict,STRP_NC_0X0040 *const restrict))(StrP_NC_Cast_0x0040_),
				.x0100_=(int(*)(strp_nc_0x0040 *const restrict,STRP_NC_0X0100 *const restrict))(StrP_NC_Cast_0x0040_),
				.x0400_=(int(*)(strp_nc_0x0040 *const restrict,STRP_NC_0X0400 *const restrict))(StrP_NC_Cast_0x0040_)
			},
			.x0100=
			{
				.x0010_=(int(*)(strp_nc_0x0100 *const restrict,STRP_NC_0X0010 *const restrict))(StrP_NC_Cast_0x0010_),
				.x0040_=(int(*)(strp_nc_0x0100 *const restrict,STRP_NC_0X0040 *const restrict))(StrP_NC_Cast_0x0040_),
				.x0100_=(int(*)(strp_nc_0x0100 *const restrict,STRP_NC_0X0100 *const restrict))(StrP_NC_Cast_0x0100_),
				.x0400_=(int(*)(strp_nc_0x0100 *const restrict,STRP_NC_0X0400 *const restrict))(StrP_NC_Cast_0x0100_)
			},
			.x0400=
			{
				.x0010_=(int(*)(strp_nc_0x0400 *const restrict,STRP_NC_0X0010 *const restrict))(StrP_NC_Cast_0x0010_),
				.x0040_=(int(*)(strp_nc_0x0400 *const restrict,STRP_NC_0X0040 *const restrict))(StrP_NC_Cast_0x0040_),
				.x0100_=(int(*)(strp_nc_0x0400 *const restrict,STRP_NC_0X0100 *const restrict))(StrP_NC_Cast_0x0100_),
				.x0400_=(int(*)(strp_nc_0x0400 *const restrict,STRP_NC_0X0400 *const restrict))(StrP_NC_Cast_0x0400_)
			}
		},
		.Puts=
		{
			.x0010_=(_Bool(*)(STRP_NC_0X0010 *const restrict,FILE *const restrict))(StrP_NC_Puts_),
			.x0040_=(_Bool(*)(STRP_NC_0X0040 *const restrict,FILE *const restrict))(StrP_NC_Puts_),
			.x0100_=(_Bool(*)(STRP_NC_0X0100 *const restrict,FILE *const restrict))(StrP_NC_Puts_),
			.x0400_=(_Bool(*)(STRP_NC_0X0400 *const restrict,FILE *const restrict))(StrP_NC_Puts_)
		},
		.Gets=
		{
			.x0010_=StrP_NC_Gets_0x0010_,
			.x0040_=StrP_NC_Gets_0x0040_,
			.x0100_=StrP_NC_Gets_0x0100_,
			.x0400_=StrP_NC_Gets_0x0400_
		}
	},
	.WC=
	{
		.NC=
		{
			.x0010_=StrP_WC_NC_0x0010_,
			.x0040_=StrP_WC_NC_0x0040_,
			.x0100_=StrP_WC_NC_0x0100_,
			.x0400_=StrP_WC_NC_0x0400_
		},
		.Length=
		{
			.x0010_=StrP_WC_Length_0x0010_,
			.x0040_=StrP_WC_Length_0x0040_,
			.x0100_=StrP_WC_Length_0x0100_,
			.x0400_=StrP_WC_Length_0x0400_
		},
		.Find=
		{
			.Char=
			{
				.x0010_=StrP_WC_Find_0x0010_,
				.x0040_=StrP_WC_Find_0x0040_,
				.x0100_=StrP_WC_Find_0x0100_,
				.x0400_=StrP_WC_Find_0x0400_
			},
			.String=
			{
				.x0010_=StrP_WC_Search_0x0010_,
				.x0040_=StrP_WC_Search_0x0040_,
				.x0100_=StrP_WC_Search_0x0100_,
				.x0400_=StrP_WC_Search_0x0400_
			}
		},
		.Reset=
		{
			.x0010_=StrP_WC_Reset_0x0010_,
			.x0040_=StrP_WC_Reset_0x0040_,
			.x0100_=StrP_WC_Reset_0x0100_,
			.x0400_=StrP_WC_Reset_0x0400_
		},
		.Copy=
		{
			.x0010_=StrP_WC_Copy_0x0010_,
			.x0040_=StrP_WC_Copy_0x0040_,
			.x0100_=StrP_WC_Copy_0x0100_,
			.x0400_=StrP_WC_Copy_0x0400_
		},
		.Conc=
		{
			.x0010_=StrP_WC_Conc_0x0010_,
			.x0040_=StrP_WC_Conc_0x0040_,
			.x0100_=StrP_WC_Conc_0x0100_,
			.x0400_=StrP_WC_Conc_0x0400_
		},
		.Crop=
		{
			.x0010_=StrP_WC_Crop_0x0010_,
			.x0040_=StrP_WC_Crop_0x0040_,
			.x0100_=StrP_WC_Crop_0x0100_,
			.x0400_=StrP_WC_Crop_0x0400_
		},
		.Comp=
		{
			.x0010_=StrP_WC_Comp_0x0010_,
			.x0040_=StrP_WC_Comp_0x0040_,
			.x0100_=StrP_WC_Comp_0x0100_,
			.x0400_=StrP_WC_Comp_0x0400_
		},
		.Cast=
		{
			.x0010=
			{
				.x0010_=(int(*)(strp_wc_0x0010 *const restrict,STRP_WC_0X0010 *const restrict))(StrP_WC_Cast_0x0010_),
				.x0040_=(int(*)(strp_wc_0x0010 *const restrict,STRP_WC_0X0040 *const restrict))(StrP_WC_Cast_0x0010_),
				.x0100_=(int(*)(strp_wc_0x0010 *const restrict,STRP_WC_0X0100 *const restrict))(StrP_WC_Cast_0x0010_),
				.x0400_=(int(*)(strp_wc_0x0010 *const restrict,STRP_WC_0X0400 *const restrict))(StrP_WC_Cast_0x0010_)
			},
			.x0040=
			{
				.x0010_=(int(*)(strp_wc_0x0040 *const restrict,STRP_WC_0X0010 *const restrict))(StrP_WC_Cast_0x0010_),
				.x0040_=(int(*)(strp_wc_0x0040 *const restrict,STRP_WC_0X0040 *const restrict))(StrP_WC_Cast_0x0040_),
				.x0100_=(int(*)(strp_wc_0x0040 *const restrict,STRP_WC_0X0100 *const restrict))(StrP_WC_Cast_0x0040_),
				.x0400_=(int(*)(strp_wc_0x0040 *const restrict,STRP_WC_0X0400 *const restrict))(StrP_WC_Cast_0x0040_)
			},
			.x0100=
			{
				.x0010_=(int(*)(strp_wc_0x0100 *const restrict,STRP_WC_0X0010 *const restrict))(StrP_WC_Cast_0x0010_),
				.x0040_=(int(*)(strp_wc_0x0100 *const restrict,STRP_WC_0X0040 *const restrict))(StrP_WC_Cast_0x0040_),
				.x0100_=(int(*)(strp_wc_0x0100 *const restrict,STRP_WC_0X0100 *const restrict))(StrP_WC_Cast_0x0100_),
				.x0400_=(int(*)(strp_wc_0x0100 *const restrict,STRP_WC_0X0400 *const restrict))(StrP_WC_Cast_0x0100_)
			},
			.x0400=
			{
				.x0010_=(int(*)(strp_wc_0x0400 *const restrict,STRP_WC_0X0010 *const restrict))(StrP_WC_Cast_0x0010_),
				.x0040_=(int(*)(strp_wc_0x0400 *const restrict,STRP_WC_0X0040 *const restrict))(StrP_WC_Cast_0x0040_),
				.x0100_=(int(*)(strp_wc_0x0400 *const restrict,STRP_WC_0X0100 *const restrict))(StrP_WC_Cast_0x0100_),
				.x0400_=(int(*)(strp_wc_0x0400 *const restrict,STRP_WC_0X0400 *const restrict))(StrP_WC_Cast_0x0400_)
			}
		},
		.Puts=
		{
			.x0010_=(_Bool(*)(STRP_WC_0X0010 *const restrict,FILE *const restrict))(StrP_WC_Puts_),
			.x0040_=(_Bool(*)(STRP_WC_0X0040 *const restrict,FILE *const restrict))(StrP_WC_Puts_),
			.x0100_=(_Bool(*)(STRP_WC_0X0100 *const restrict,FILE *const restrict))(StrP_WC_Puts_),
			.x0400_=(_Bool(*)(STRP_WC_0X0400 *const restrict,FILE *const restrict))(StrP_WC_Puts_)
		},
		.Gets=
		{
			.x0010_=StrP_WC_Gets_0x0010_,
			.x0040_=StrP_WC_Gets_0x0040_,
			.x0100_=StrP_WC_Gets_0x0100_,
			.x0400_=StrP_WC_Gets_0x0400_
		}
	}
};
extern STRPACK *StrP_(void) { return &StrP; }
#endif
