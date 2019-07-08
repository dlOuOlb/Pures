#ifdef __STDC__

#if(__STDC__)

#ifdef __STDC_VERSION__

#if(__STDC_VERSION__<201710L)
#error The compiler does not satisfy the C18 Standard.
#else

#ifdef __STDC_LIB_EXT1__

#if(1)
#define __STDC_WANT_LIB_EXT1__ (1)
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "strpure.h"
#endif

#if(1)
typedef char strp_nc;
typedef const char STRP_NC;

typedef wchar_t strp_wc;
typedef const wchar_t STRP_WC;

_Static_assert(CHAR_BIT==8,"CHAR_BIT != 8");
_Static_assert(sizeof(char)==1,"sizeof(char) != 1");
_Static_assert(sizeof(errno_t)==sizeof(int),"sizeof(errno_t) != sizeof(int)");
_Static_assert(sizeof(rsize_t)==sizeof(size_t),"sizeof(rsize_t) != sizeof(size_t)");
_Static_assert(RSIZE_MAX>(0x0400*sizeof(wchar_t)),"RSIZE_MAX <= (0x0400*sizeof(wchar_t))");

#include "strpain.c"
#endif

#if(1)
static const char _StringVersion[16]="2019.07.08";
#endif

#if(1)
STRPACK StrP=
{
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
		}
	},
	.WC=
	{
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
		}
	},
	.Errno=
	{
		.Zero=0,
		.Dom=EDOM,
		.IlSeq=EILSEQ,
		.Range=ERANGE
	},
	.Version=_StringVersion
};
STRPACK *StrP_(void) { return &StrP; }
#endif

#else
#error The compiler does not support the C Library Extension 1.
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
