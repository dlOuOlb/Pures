#include "stdpain.h"
#include "timpure.h"

#if(1)
static struct tm TimP_Cast_Obj_Val_(const time_t Val,const _Bool Mode)
{
	struct tm Obj;

	if(((Mode)?(localtime_s):(gmtime_s))(&Val,&Obj));
	else
		Obj.tm_isdst=Obj.tm_yday=Obj.tm_wday=Obj.tm_year=Obj.tm_mon=Obj.tm_mday=Obj.tm_hour=Obj.tm_min=Obj.tm_sec=-1;

	return Obj;
}
static time_t TimP_Cast_Val_Obj_(struct tm Obj) { return mktime(&Obj); }
#endif

#if(1)
static time_t TimP_Current_(void) { return time(NULL); }
static _Bool TimP_Textual_(char *const Text,const time_t Time)
{
	if(ctime_s(Text,26,&Time))
		return _FAILURE_;
	else
		return _SUCCESS_;
}
#endif

#if(1)
static struct tm TimP_TM_Current_(const _Bool Mode) { return TimP_Cast_Obj_Val_(TimP_Current_(),Mode); }
static _Bool TimP_TM_Textual_(char *const Text,const struct tm Time)
{
	if(asctime_s(Text,26,&Time))
		return _FAILURE_;
	else
		return _SUCCESS_;
}
#endif

#if(1)
_Static_assert((sizeof(TIMPACE)<<3)==sizeof(TIMPACK),"sizeof(TIMPACK) != 8*sizeof(TIMPACE)");
extern _Alignas(sizeof(TIMPACE)<<3) TIMPACK TimP=
{
	.Version=_INC_TIMPURE,
	.Bool=&(const struct _timp_b2)
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
extern TIMPACK *TimP_(void) { return &TimP; }
#endif
