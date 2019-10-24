#ifdef _INC_STRPURE
#ifdef _SRC_STRPAIN

static size_t Func_(TT,Length,XXXX)(TT_XXXX *const String)
{
	return _StrP_Length_(String->TT,OxXXXX);
}
static size_t Func_(TT,Find,XXXX)(TT_XXXX *const String,TT_UNIT Character,const _Bool Mode)
{
	TT_UNIT *const Where=(Mode)?(_StrP_Find_Forward_(String->TT,Character)):(_StrP_Find_Reverse_(String->TT,Character));

	return ((Where)?(Where-(String->TT)):(OxXXXX));
}
static size_t Func_(TT,Search,XXXX)(TT_XXXX *const String,TT_XXXX *const SubString)
{
	TT_UNIT *const Where=_StrP_Search_(String->TT,SubString->TT);

	return ((Where)?(Where-(String->TT)):(OxXXXX));
}
static int Func_(TT,Reset,XXXX)(tt_xxxx *const restrict String)
{
	return memset_s(String->TT,sizeof(tt_xxxx),0,sizeof(tt_xxxx));
}

static int Func_(TT,Copy,XXXX)(tt_xxxx *const restrict Target,TT_XXXX *const restrict Source)
{
	return _StrP_Copy_(Target->TT,OxXXXX,Source->TT);
}
static int Func_(TT,Conc,XXXX)(tt_xxxx *const restrict Target,TT_XXXX *const restrict Source)
{
	return _StrP_Conc_(Target->TT,OxXXXX,Source->TT);
}
static int Func_(TT,Crop,XXXX)(tt_xxxx *const restrict Target,TT_XXXX *const restrict Source,const size_t Offset,const size_t Length)
{
	const size_t Limit=_StrP_Length_(Source->TT,OxXXXX);

	if(Limit<OxXXXX)
	{
		volatile const size_t There=Offset+Length;

		if(Offset>There);
		else if(There>Limit);
		else
			return _StrP_Cast_(Target->TT,OxXXXX,Source->TT+Offset,Length);
	}
	else;

	if(Target)
		Target->TT[0]=0;
	else;
	
	return ERANGE;
}
static int Func_(TT,Comp,XXXX)(TT_XXXX *const Left,TT_XXXX *const Right)
{
	return _StrP_Comp_(Left->TT,Right->TT,OxXXXX);
}
static int Func_(TT,Cast,XXXX)(void *const restrict Target,const void *const restrict Source)
{
	const size_t Limit=OxXXXX-0x0001;

	return _StrP_Cast_(Target,OxXXXX,Source,Limit);
}

static _Bool Func_(TT,Gets,XXXX)(tt_xxxx *const restrict String,FILE *const restrict Stream)
{
	if(String)
		if(_StrP_Gets_(String->TT,OxXXXX,(Stream)?(Stream):(stdin))==(String->TT))
			return _SUCCESS_;
		else
			return _FAILURE_;
	else
		return _FAILURE_;
}

#else

#if(1)
#define _Conc_(A,B) A##B
#define Conc_(A,B) _Conc_(A,B)

#define _Func_(Type,Name,Nums) StrP_##Type##_##Name##_0x##Nums##_
#define Func_(Type,Name,Nums) _Func_(Type,Name,Nums)

#define OxXXXX Conc_(0x,XXXX)

#define tt_unit Conc_(strp_,tt)
#define TT_UNIT Conc_(STRP_,TT)

#define tt_xxxx Conc_(tt_unit,Conc_(_0x,XXXX))
#define TT_XXXX Conc_(TT_UNIT,Conc_(_0X,XXXX))
#endif

#define _SRC_STRPAIN

#if(1)
#define tt nc
#define TT NC
#define _StrP_Length_ strnlen_s
#define _StrP_Find_Forward_ strchr
#define _StrP_Find_Reverse_ strrchr
#define _StrP_Search_ strstr
#define _StrP_Copy_ strcpy_s
#define _StrP_Conc_ strcat_s
#define _StrP_Comp_ strncmp
#define _StrP_Cast_ strncpy_s
#define _StrP_Gets_ fgets

#define XXXX 0010
#include "strpain.c"
#undef XXXX
#define XXXX 0040
#include "strpain.c"
#undef XXXX
#define XXXX 0100
#include "strpain.c"
#undef XXXX
#define XXXX 0400
#include "strpain.c"
#undef XXXX

#undef _StrP_Gets_
#undef _StrP_Cast_
#undef _StrP_Comp_
#undef _StrP_Conc_
#undef _StrP_Copy_
#undef _StrP_Search_
#undef _StrP_Find_Reverse_
#undef _StrP_Find_Forward_
#undef _StrP_Length_
#undef TT
#undef tt
#endif

#if(1)
#define tt wc
#define TT WC
#define _StrP_Length_ wcsnlen_s
#define _StrP_Find_Forward_ wcschr
#define _StrP_Find_Reverse_ wcsrchr
#define _StrP_Search_ wcsstr
#define _StrP_Copy_ wcscpy_s
#define _StrP_Conc_ wcscat_s
#define _StrP_Comp_ wcsncmp
#define _StrP_Cast_ wcsncpy_s
#define _StrP_Gets_ fgetws

#define XXXX 0010
#include "strpain.c"
#undef XXXX
#define XXXX 0040
#include "strpain.c"
#undef XXXX
#define XXXX 0100
#include "strpain.c"
#undef XXXX
#define XXXX 0400
#include "strpain.c"
#undef XXXX

#undef _StrP_Gets_
#undef _StrP_Cast_
#undef _StrP_Comp_
#undef _StrP_Conc_
#undef _StrP_Copy_
#undef _StrP_Search_
#undef _StrP_Find_Reverse_
#undef _StrP_Find_Forward_
#undef _StrP_Length_
#undef TT
#undef tt
#endif

#undef _SRC_STRPAIN

#if(1)
#undef TT_XXXX
#undef tt_xxxx
#undef TT_UNIT
#undef tt_unit
#undef OxXXXX
#undef Func_
#undef _Func_
#undef Conc_
#undef _Conc_
#endif

#endif

#else
static void _StrP_Void_(void) { (void)(_StrP_Void_);return; }
#endif
