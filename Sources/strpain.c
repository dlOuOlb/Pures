#ifdef _INC_STRPURE
#ifdef _SRC_STRPAIN

static size_t Punc_(Length)(TT_XXXX *const Str) { return _StrP_Length_(Str->TT,OxXXXX); }
static size_t Punc_(Find)(TT_XXXX *const Str,TT_UNIT Char,const _Bool Mode)
{
	TT_UNIT *const Where=((Mode)?(_StrP_Find_Forward_):(_StrP_Find_Reverse_))(Str->TT,Char);

	return ((Where)?(Where-(Str->TT)):(OxXXXX));
}
static size_t Punc_(Search)(TT_XXXX *const Str,TT_XXXX *const Sub)
{
	TT_UNIT *const Where=_StrP_Search_(Str->TT,Sub->TT);

	return ((Where)?(Where-(Str->TT)):(OxXXXX));
}
static int Punc_(Reset)(tt_xxxx *const restrict Str) { return memset_s(Str->TT,sizeof(tt_xxxx),0,sizeof(tt_xxxx)); }

static int Punc_(Copy)(tt_xxxx *const restrict Trg,TT_XXXX *const restrict Src) { return _StrP_Copy_(Trg->TT,OxXXXX,Src->TT); }
static int Punc_(Conc)(tt_xxxx *const restrict Trg,TT_XXXX *const restrict Src) { return _StrP_Conc_(Trg->TT,OxXXXX,Src->TT); }
static int Punc_(Crop)(tt_xxxx *const restrict Trg,TT_XXXX *const restrict Src,const size_t Ofs,const size_t Lng)
{
	const size_t Lim=_StrP_Length_(Src->TT,OxXXXX);

	if(Lim<OxXXXX)
	{
		const size_t Bnd=Ofs+Lng;

		if(Ofs>Bnd);
		else if(Bnd>Lim);
		else
			return _StrP_Cast_(Trg->TT,OxXXXX,Src->TT+Ofs,Lng);
	}
	else;

	if(Trg)
		Trg->TT[0]=0;
	else;
	
	return ERANGE;
}
static int Punc_(Comp)(TT_XXXX *const Left,TT_XXXX *const Right) { return _StrP_Comp_(Left->TT,Right->TT,OxXXXX); }
static int Punc_(Cast)(tt_xxxx *const restrict Trg,TT_XXXX *const restrict Src) { return _StrP_Cast_(Trg->TT,OxXXXX,Src->TT,OxXXXX-0x0001); }

static _Bool Punc_(Puts)(FILE *const restrict Stream,TT_XXXX *const restrict String) { return ((String)&&(_StrP_Puts_(String->TT,(Stream)?(Stream):(stdout))>=0)); }
static _Bool Punc_(Gets)(FILE *const restrict Stream,tt_xxxx *const restrict String) { return ((String)&&(_StrP_Gets_(String->TT,OxXXXX,(Stream)?(Stream):(stdin)))&&(true)); }

#else

#if(1)
#define _Conc_(A,B) A##B
#define Conc_(A,B) _Conc_(A,B)

#define _Func_(Type,Name,Nums) StrP_##Type##_##Name##_0x##Nums##_
#define Func_(Type,Name,Nums) _Func_(Type,Name,Nums)
#define Punc_(Name) Func_(TT,Name,XXXX)

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
#define _StrP_Find_Forward_ _StrP_NC_Find_Forward_
#define _StrP_Find_Reverse_ _StrP_NC_Find_Reverse_
#define _StrP_Search_ strstr
#define _StrP_Copy_ strcpy_s
#define _StrP_Conc_ strcat_s
#define _StrP_Comp_ strncmp
#define _StrP_Cast_ strncpy_s
#define _StrP_Puts_ fputs
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
#undef _StrP_Puts_
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
#undef Punc_
#undef Func_
#undef _Func_
#undef Conc_
#undef _Conc_
#endif

#endif

#else
#error Do not build this template directly.
#endif
