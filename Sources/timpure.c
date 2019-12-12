#include "stdpain.h"
#include "timpure.h"

#if(1)
static const struct
{
	_Alignas(16) const char Version[16];
	const struct _timpack_size Size;
}
_Post=
{
	.Version=_INC_TIMPURE,
	.Size=
	{
		.Size=sizeof(size_t),
		.Long=sizeof(long),
		.Double=sizeof(double),
		.Time=sizeof(time_t),
		.TM=sizeof(struct tm),
		.TimeSpec=sizeof(struct timespec)
	}
};
#endif

#if(1)
static struct tm TimP_Cast_Obj_Val_(const time_t Val)
{
	struct tm Obj;

	if(gmtime_s(&Val,&Obj));
	else
		Obj.tm_isdst=Obj.tm_yday=Obj.tm_wday=Obj.tm_year=Obj.tm_mon=Obj.tm_mday=Obj.tm_hour=Obj.tm_min=Obj.tm_sec=-1;

	return Obj;
}
static time_t TimP_Cast_Val_Obj_(struct tm Obj) { return mktime(&Obj); }

static time_t TimP_Current_(void) { return time(NULL); }
static timp_tx TimP_Textual_(const time_t Time)
{
	timp_tx Text;

	if(ctime_s(Text.Text,sizeof(Text),&Time));
	else;

	return Text;
}

static struct tm TimP_TM_Current_(void) { return TimP_Cast_Obj_Val_(TimP_Current_()); }
static timp_tx TimP_TM_Textual_(const struct tm Time)
{
	timp_tx Text;

	if(asctime_s(Text.Text,sizeof(Text),&Time));
	else;

	return Text;
}
#endif

#if(1)
static struct timespec _TimP_Spec_Carry_(struct timespec A)
{
	const long Giga=+1000000000L;

	{
		const time_t Zero=(time_t)(0);
		const long Sign=(A.tv_sec>Zero)-(A.tv_sec<Zero);

		A.tv_sec-=(time_t)(Sign);
		A.tv_nsec+=Sign*Giga;
	}
	{
		const ldiv_t Nom=ldiv(A.tv_nsec,Giga);

		A.tv_sec+=(time_t)(Nom.quot);
		A.tv_nsec=Nom.rem;
	}

	return A;
}
static struct timespec TimP_Spec_Add_(const struct timespec A,const struct timespec B) { return _TimP_Spec_Carry_((const struct timespec) { .tv_sec=A.tv_sec+B.tv_sec,.tv_nsec=A.tv_nsec+B.tv_nsec }); }
static struct timespec TimP_Spec_Sub_(const struct timespec A,const struct timespec B) { return _TimP_Spec_Carry_((const struct timespec) { .tv_sec=A.tv_sec-B.tv_sec,.tv_nsec=A.tv_nsec-B.tv_nsec }); }

static struct timespec TimP_Spec_Mul_(const struct timespec A,const long Mul)
{
	const long long Giga=+1000000000LL;
	long long Temp[2]={[0]=(long long)(A.tv_sec),[1]=(long long)(A.tv_nsec)};

	{
		const long long Cast=(long long)(Mul);

		Temp[0]*=Cast;
		Temp[1]*=Cast;
	}
	{
		const lldiv_t Nom=lldiv(Temp[1],Giga);

		Temp[0]+=Nom.quot;
		Temp[1]=Nom.rem;
	}

	return ((const struct timespec) { .tv_sec=(time_t)(Temp[0]),.tv_nsec=(long)(Temp[1]) });
}
static struct timespec TimP_Spec_Div_(const struct timespec A,const long Div)
{
	const long long Giga=+1000000000LL;
	long long Temp[2]={[0]=(long long)(A.tv_sec),[1]=(long long)(A.tv_nsec)};

	{
		const long long Cast=(long long)(Div);

		Temp[0]%=Cast;
		Temp[0]*=Giga;

		Temp[1]+=Temp[0];
		Temp[1]/=Cast;
	}

	return ((const struct timespec) { .tv_sec=A.tv_sec/((time_t)(Div)),.tv_nsec=(long)(Temp[1]) });
}

static double TimP_Spec_Get_(const struct timespec Spec)
{
	const double Nano=+1.0E-9,Cast[2]={[0]=(double)(Spec.tv_sec),[1]=(double)(Spec.tv_nsec)};

	return fma(Nano,Cast[1],Cast[0]);
}
static struct timespec TimP_Spec_Set_(const double Double)
{
	const double Giga=+1.0E+9;

	return ((const struct timespec) { .tv_sec=(time_t)(trunc(Double)),.tv_nsec=(long)(Giga*fmod(Double,+1.0)) });
}

static struct timespec TimP_Spec_Current_(void)
{
	struct timespec Time;

	if(timespec_get(&Time,TIME_UTC));
	else
	{
		Time.tv_sec=0;
		Time.tv_nsec=-1L;
	}

	return Time;
}
static struct timespec TimP_Spec_Sum_(const struct timespec Sum,const struct timespec Mark) { return TimP_Spec_Add_(Sum,TimP_Spec_Sub_(TimP_Spec_Current_(),Mark)); }
#endif

#if(1)
_Static_assert(sizeof(TIMPACK)==(sizeof(TIMPACE)<<4),"sizeof(TIMPACK) != 16*sizeof(TIMPACE)");
extern _Alignas(TIMPACK) TIMPACK TimP=
{
	{
		{
			.Version=_Post.Version,
			.Size=&(_Post.Size)
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
	},
	.Spec=
	{
		{
			.Add_=TimP_Spec_Add_,
			.Sub_=TimP_Spec_Sub_,
			.Mul_=TimP_Spec_Mul_,
			.Div_=TimP_Spec_Div_
		},
		{
			.Get_=TimP_Spec_Get_,
			.Set_=TimP_Spec_Set_,
			.Now_=TimP_Spec_Current_,
			.Sum_=TimP_Spec_Sum_
		}
	}
};
extern TIMPACK *TimP_(void) { return &TimP; }
#endif
