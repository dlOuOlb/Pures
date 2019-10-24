#if(1)
#include "stdpain.h"
#include "timpure.h"
#endif

#if(1)
static const char _StringVersion[16]="2019.10.24";
static TIMP_TM _TMInvalid={.tm_sec=-1,.tm_min=-1,.tm_hour=-1,.tm_mday=-1,.tm_mon=-1,.tm_year=-1,.tm_wday=-1,.tm_yday=-1,.tm_isdst=-1};
#endif

#if(1)
static timp_tm TimP_Cast_Obj_Val_(const time_t Val,const _Bool Mode)
{
	timp_tm Obj;

	return ((((Mode)?(localtime_s):(gmtime_s))(&Val,&Obj))?(Obj):(_TMInvalid));
}
static time_t TimP_Cast_Val_Obj_(timp_tm Obj)
{
	return mktime(&Obj);
}
#endif

#if(1)
static time_t TimP_Current_(void)
{
	return time(NULL);
}
static _Bool TimP_Textual_(char *const Text,const time_t Time)
{
	if(ctime_s(Text,26,&Time))
		return _FAILURE_;
	else
		return _SUCCESS_;
}
#endif

#if(1)
static timp_tm TimP_TM_Current_(const _Bool Mode)
{
	return TimP_Cast_Obj_Val_(TimP_Current_(),Mode);
}
static _Bool TimP_TM_Textual_(char *const Text,TIMP_TM Time)
{
	if(asctime_s(Text,26,&Time))
		return _FAILURE_;
	else
		return _SUCCESS_;
}
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
