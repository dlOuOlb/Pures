#include "stdpain.h"
#include "timpure.h"

#if(1)
static _Alignas(16) const char _StringVersion[16]=_INC_TIMPURE;
static _Alignas(int) const struct tm _TMInvalid={.tm_sec=-1,.tm_min=-1,.tm_hour=-1,.tm_mday=-1,.tm_mon=-1,.tm_year=-1,.tm_wday=-1,.tm_yday=-1,.tm_isdst=-1};
#endif

#if(1)
static struct tm TimP_Cast_Obj_Val_(const time_t Val,const _Bool Mode)
{
	struct tm Obj,*(*const Cast_[2])(const time_t *const restrict,struct tm *const restrict)={[0]=gmtime_s,[1]=localtime_s};
	const struct tm *const Table[2]={[_SUCCESS_]=&Obj,[_FAILURE_]=&_TMInvalid};

	return *(Table[_StdP_Fine_Some_(Cast_[Mode&1](&Val,&Obj))]);
}
static time_t TimP_Cast_Val_Obj_(struct tm Obj) { return mktime(&Obj); }
#endif

#if(1)
static time_t TimP_Current_(void) { return time(NULL); }
static _Bool TimP_Textual_(char *const Text,const time_t Time) { return _StdP_Fine_Zero_(ctime_s(Text,26,&Time)); }
#endif

#if(1)
static struct tm TimP_TM_Current_(const _Bool Mode) { return TimP_Cast_Obj_Val_(TimP_Current_(),Mode); }
static _Bool TimP_TM_Textual_(char *const Text,const struct tm Time) { return _StdP_Fine_Zero_(asctime_s(Text,26,&Time)); }
#endif

#if(1)
TIMPACK TimP=
{
	.Version=_StringVersion,
	.Bool=
	{
		.Success=_SUCCESS_,
		.Failure=_FAILURE_
	},
	.Val=
	{
		.Now_=TimP_Current_,
		.Obj_=TimP_Cast_Val_Obj_
	},
	.Obj=
	{
		.Now_=TimP_TM_Current_,
		.Val_=TimP_Cast_Obj_Val_
	},
	.Text=
	{
		.Val_=TimP_Textual_,
		.Obj_=TimP_TM_Textual_
	}
};
TIMPACK *TimP_(void) { return &TimP; }
#endif
