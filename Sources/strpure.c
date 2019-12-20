#include "stdpain.h"
#include "strpure.h"

#if(1)
typedef char strp_nc;
typedef const char STRP_NC;
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
_Static_assert(sizeof(STRPACK)==(sizeof(STRPACE)<<6),"sizeof(STRPACK) != 64*sizeof(STRPACE)");
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
			.x0010_=StrP_NC_Puts_0x0010_,
			.x0040_=StrP_NC_Puts_0x0040_,
			.x0100_=StrP_NC_Puts_0x0100_,
			.x0400_=StrP_NC_Puts_0x0400_
		},
		.Gets=
		{
			.x0010_=StrP_NC_Gets_0x0010_,
			.x0040_=StrP_NC_Gets_0x0040_,
			.x0100_=StrP_NC_Gets_0x0100_,
			.x0400_=StrP_NC_Gets_0x0400_
		}
	}
};
extern STRPACK *StrP_(void) { return &StrP; }
#endif
