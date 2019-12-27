#ifdef oSTRPURE_INC
#ifdef xSTRPAIN_SRC

static size_t Punc_(Length)(TT_XXXX *const Str) { return xStrP_Length_(Str->TT,OxXXXX); }
static size_t Punc_(Find)(TT_XXXX *const Str,TT_UNIT Char,const _Bool Mode)
{
	TT_UNIT *const Where=((Mode)?(xStrP_Find_Forward_):(xStrP_Find_Reverse_))(Str->TT,Char);

	return ((Where)?(Where-(Str->TT)):(OxXXXX));
}
static size_t Punc_(Search)(TT_XXXX *const Str,TT_XXXX *const Sub)
{
	TT_UNIT *const Where=xStrP_Search_(Str->TT,Sub->TT);

	return ((Where)?(Where-(Str->TT)):(OxXXXX));
}
static int Punc_(Reset)(tt_xxxx *const restrict Str) { return memset_s(Str->TT,sizeof(tt_xxxx),0,sizeof(tt_xxxx)); }

static int Punc_(Copy)(tt_xxxx *const restrict Trg,TT_XXXX *const restrict Src) { return xStrP_Copy_(Trg->TT,OxXXXX,Src->TT); }
static int Punc_(Conc)(tt_xxxx *const restrict Trg,TT_XXXX *const restrict Src) { return xStrP_Conc_(Trg->TT,OxXXXX,Src->TT); }
static int Punc_(Crop)(tt_xxxx *const restrict Trg,TT_XXXX *const restrict Src,const size_t Ofs,const size_t Lng)
{
	const size_t Lim=xStrP_Length_(Src->TT,OxXXXX);

	if(Lim<OxXXXX)
	{
		const size_t Bnd=Ofs+Lng;

		if(Ofs>Bnd);
		else if(Bnd>Lim);
		else
			return xStrP_Cast_(Trg->TT,OxXXXX,Src->TT+Ofs,Lng);
	}
	else;

	if(Trg)
		Trg->TT[0]=0;
	else;
	
	return ERANGE;
}
static int Punc_(Comp)(TT_XXXX *const Left,TT_XXXX *const Right) { return xStrP_Comp_(Left->TT,Right->TT,OxXXXX); }
static int Punc_(Cast)(void *const restrict Trg,const void *const restrict Src)
{
	tt_xxxx *const restrict Target=Trg;
	TT_XXXX *const restrict Source=Src;

	return xStrP_Cast_(Target->TT,OxXXXX,Source->TT,OxXXXX-0x0001);
}

static _Bool Punc_(Gets)(FILE *const restrict Stream,tt_xxxx *const restrict String) { return ((String)&&(xStrP_Gets_(String->TT,OxXXXX,(Stream)?(Stream):(stdin)))&&(true)); }

#else

#if(1)
#define xConc_(A,B) A##B
#define Conc_(A,B) xConc_(A,B)

#define xFunc_(Type,Name,Nums) StrP_##Type##_##Name##_0x##Nums##_
#define Func_(Type,Name,Nums) xFunc_(Type,Name,Nums)
#define Punc_(Name) Func_(TT,Name,XXXX)

#define OxXXXX Conc_(0x,XXXX)

#define tt_unit Conc_(strp_,tt)
#define TT_UNIT Conc_(STRP_,TT)

#define tt_xxxx Conc_(tt_unit,Conc_(_0x,XXXX))
#define TT_XXXX Conc_(TT_UNIT,Conc_(_0X,XXXX))
#endif

#define xSTRPAIN_SRC

#if(1)
#define tt nc
#define TT NC
#define xStrP_Length_ strnlen_s
#define xStrP_Find_Forward_ xStrP_NC_Find_Forward_
#define xStrP_Find_Reverse_ xStrP_NC_Find_Reverse_
#define xStrP_Search_ strstr
#define xStrP_Copy_ strcpy_s
#define xStrP_Conc_ strcat_s
#define xStrP_Comp_ strncmp
#define xStrP_Cast_ strncpy_s
#define xStrP_Gets_ fgets

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

#undef xStrP_Gets_
#undef xStrP_Cast_
#undef xStrP_Comp_
#undef xStrP_Conc_
#undef xStrP_Copy_
#undef xStrP_Search_
#undef xStrP_Find_Reverse_
#undef xStrP_Find_Forward_
#undef xStrP_Length_
#undef TT
#undef tt
#endif

#undef xSTRPAIN_SRC

#if(1)
#undef TT_XXXX
#undef tt_xxxx
#undef TT_UNIT
#undef tt_unit
#undef OxXXXX
#undef Punc_
#undef Func_
#undef xFunc_
#undef Conc_
#undef xConc_
#endif

#endif

#else
#error Do not build this template directly.
#endif
