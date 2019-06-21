#ifdef __STDC__
#if(__STDC__)
#ifdef __STDC_VERSION__
#if(__STDC_VERSION__<201710L)
#error The compiler does not satisfy the C18 Standard.
#else

#if(1)
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>

#include "thrpure.h"
#endif

#if(1)
struct _thrp_tp
{
	thrp_p_ Proc_;
	size_t Size;
};
typedef struct _thrp_tp thrp_tp;
typedef const struct _thrp_tp THRP_TP;

struct _thrp_qu
{
	mtx_t Lock;
	mtx_t Wait;
	thrd_t Master;
	thrd_t Thread;
	size_t Capacity;
	size_t Count;
	thrp_tp *Pin[2];
};

struct _thrp_mu
{
	mtx_t Tex;
};

_Static_assert(sizeof(char)==1,"sizeof(char) != 1");
_Static_assert(sizeof(void*)==sizeof(size_t),"sizeof(void*) != sizeof(size_t)");
_Static_assert(sizeof(int)<=sizeof(time_t),"sizeof(int) > sizeof(time_t)");
_Static_assert((sizeof(thrp_tp)%sizeof(size_t))==0,"sizeof(thrp_tp)%sizeof(size_t) != 0");
_Static_assert((sizeof(thrp_qu)%sizeof(size_t))==0,"sizeof(thrp_qu)%sizeof(size_t) != 0");

#define _THRP_SUCCESS_ ((_Bool)(0))
#define _THRP_FAILURE_ ((_Bool)(1))
#endif

#if(1)
static const thrd_t _ThreadEmpty;
static const char _StringVersion[16]="Date:2019.06.21";
#endif

#if(1)
#if(1)
static int _ThrP_Qu_Flag_(const int Flag,const int Temp)
{
	return ((Temp==thrd_success)?(Flag):(Temp));
}
static void _ThrP_Qu_Reset_(thrp_qu *const restrict Qu)
{
	Qu->Thread=_ThreadEmpty;
	Qu->Count=0;
	Qu->Pin[1]=Qu->Pin[0]=NULL;
	memset(Qu+1,0,Qu->Capacity);
}
static int _ThrP_Qu_Join_(thrp_qu *const restrict Qu)
{
	int Flag;
	const int Temp=thrd_join(Qu->Thread,&Flag);

	Flag=_ThrP_Qu_Flag_(Flag,Temp);

	if(Flag==thrd_success)
		Qu->Thread=_ThreadEmpty;
	else
		_ThrP_Qu_Reset_(Qu);

	return Flag;
}
static int _ThrP_Qu_Exist_(const thrd_t Thread)
{
	return memcmp(&Thread,&_ThreadEmpty,sizeof(thrd_t));
}
static int _ThrP_Qu_Count_(thrp_qu *const restrict Qu,size_t *const restrict Count)
{
	mtx_t *const Lock=&(Qu->Lock);
	int Flag=mtx_lock(Lock);

	if(Flag==thrd_success)
	{
		*Count=Qu->Count;
		Flag=mtx_unlock(Lock);
	}
	else
		*Count=0;

	return Flag;
}
static int _ThrP_Qu_Master_(THRP_QU *const restrict Qu)
{
	return ((Qu)?(thrd_equal(Qu->Master,thrd_current())):(0));
}
static void *_ThrP_Qu_Capable_(thrp_qu *const Qu,const size_t Pack)
{
	char *const Front=(char*)(Qu+1);

	if(Qu->Count)
	{
		thrp_tp *const *const Pin=Qu->Pin;
		char *const Ptr=((char*)(Pin[1]+1))+(Pin[1]->Size);

		if(Pin[0]>Pin[1])
			if((Ptr+Pack)>((char*)(Pin[0])))
				return NULL;
			else
				return Ptr;
		else
			if((Ptr+Pack)>(Front+(Qu->Capacity)))
				if(Front<(char*)(Pin[0]))
					if((Front+Pack)>(char*)(Pin[0]))
						return NULL;
					else
						return Front;
				else
					return NULL;
			else
				return Ptr;
	}
	else
		return Front;
}
static size_t _ThrP_Qu_Padding_(size_t Value)
{
	Value+=sizeof(size_t);
	Value--;
	Value/=sizeof(size_t);
	Value*=sizeof(size_t);

	return Value;
}
static int _ThrP_Qu_Waiting_(thrp_qu *const restrict Qu)
{
	mtx_t *const Wait=&(Qu->Wait);
	const int Flag=mtx_lock(Wait);
	
	return ((Flag==thrd_success)?(mtx_unlock(Wait)):(Flag));
}
#endif

#if(1)
static int _ThrP_Qu_Remove_(thrp_qu *const Qu,size_t *const restrict Count)
{
	mtx_t *const Lock=&(Qu->Lock);
	int Flag=mtx_lock(Lock);

	if(Flag==thrd_success)
	{
		thrp_tp **const Pin=Qu->Pin;
		const size_t Pack=sizeof(thrp_tp)+(Pin[0]->Size);

		memset(Pin[0],0,Pack);
		if(--(Qu->Count))
		{
			void *const Front=Qu+1;
			char *const End=((char*)Front)+(Qu->Capacity);
			char *const Ptr=((char*)(Pin[0]))+Pack;

			if((Ptr+sizeof(thrp_tp))>End)
				Pin[0]=Front;
			else
			{
				thrp_tp *const Temp=(thrp_tp*)Ptr;

				Pin[0]=(Temp->Proc_)?(Temp):(Front);
			}
		}
		else
			Pin[1]=Pin[0]=NULL;

		*Count=Qu->Count;
		Flag=mtx_unlock(Lock);
	}

	return Flag;
}
static int _ThrP_Qu_Stream_(void *const Msg)
{
	thrp_qu *const Qu=Msg;
	mtx_t *const Wait=&(Qu->Wait);
	size_t Count;
	int Flag=_ThrP_Qu_Count_(Qu,&Count);

	while((Flag==thrd_success)&&(Count))
	{
		THRP_TP *const Task=Qu->Pin[0];
		const void *const Arg=(Task->Size)?(Task+1):(NULL);

		if(Task->Proc_(Arg)==_THRP_SUCCESS_)
			Flag=_ThrP_Qu_Remove_(Qu,&Count);
		else
			Flag=thrd_error;
	}

	return _ThrP_Qu_Flag_(Flag,mtx_unlock(Wait));
}
static int _ThrP_Qu_Attach_(thrp_qu *const Qu,THRP_P_ Proc_,const void *const Arg,const size_t Copy,const size_t Size,const size_t Pack)
{
	mtx_t *const Lock=&(Qu->Lock);
	mtx_t *const Wait=&(Qu->Wait);
	int Flag=mtx_lock(Lock);

	if(Flag==thrd_success)
	{
		thrp_tp *Take=_ThrP_Qu_Capable_(Qu,Pack);

		if(Take)
		{
			thrp_tp **const Pin=Qu->Pin;

			Take->Proc_=Proc_;
			Take->Size=Size;
			if(Copy)
				memcpy(Take+1,Arg,Copy);

			if((Qu->Count)++)
				Pin[1]=Take;
			else
			{
				Pin[1]=Pin[0]=Take;

				Flag=mtx_lock(Wait);
				if(Flag==thrd_success)
					if(_ThrP_Qu_Exist_(Qu->Thread))
					{
						Flag=_ThrP_Qu_Join_(Qu);
						if(Flag==thrd_success)
							goto NEW_STREAM;
						else
							Flag=_ThrP_Qu_Flag_(Flag,mtx_unlock(Wait));
					}
					else
					{
NEW_STREAM:
						Flag=thrd_create(&(Qu->Thread),_ThrP_Qu_Stream_,Qu);
					}
			}
		}
		else
			Flag=thrd_busy;

		Flag=_ThrP_Qu_Flag_(Flag,mtx_unlock(Lock));
	}

	return Flag;
}
#endif

#if(1)
static int ThrP_Qu_Push_(thrp_qu *const Qu,THRP_P_ Proc_,const void *const Arg,const size_t Copy)
{
	if(Proc_)
		if(_ThrP_Qu_Master_(Qu))
		{
			const size_t Size=_ThrP_Qu_Padding_(Copy);
			const size_t Pack=Size+sizeof(thrp_tp);

			if(Size<Copy)
				return thrd_error;
			else if(Pack<Size)
				return thrd_error;
			else if(Pack>(Qu->Capacity))
				return thrd_nomem;
			else
			{
				const int Flag=_ThrP_Qu_Attach_(Qu,Proc_,Arg,Copy,Size,Pack);

				if(Flag==thrd_busy)
					thrd_yield();
				else
					return Flag;
			}
			if(_ThrP_Qu_Waiting_(Qu)==thrd_success)
				if(_ThrP_Qu_Attach_(Qu,Proc_,Arg,Copy,Size,Pack)==thrd_success)
					return thrd_busy;
				else
					return thrd_error;
			else
				return thrd_error;
		}
		else
			return thrd_error;
	else
		return thrd_error;
}
static int ThrP_Qu_Wait_(thrp_qu *const Qu)
{
	if(_ThrP_Qu_Master_(Qu))
	{
		mtx_t *const Wait=&(Qu->Wait);
		int Flag=mtx_lock(Wait);

		if(Flag==thrd_success)
			if(_ThrP_Qu_Exist_(Qu->Thread))
			{
				Flag=_ThrP_Qu_Join_(Qu);

				return _ThrP_Qu_Flag_(Flag,mtx_unlock(Wait));
			}
			else
				return mtx_unlock(Wait);
		else
			return Flag;
	}
	else
		return thrd_error;
}
#endif

#if(1)
static thrp_qu *ThrP_Qu_Create_(const size_t Space)
{
	const size_t Size=_ThrP_Qu_Padding_(Space);
	thrp_qu *Qu=(Size<Space)?(NULL):((Size<sizeof(thrp_qu))?(NULL):(malloc(Size)));

	if(Qu)
		if(mtx_init(&(Qu->Lock),mtx_plain)==thrd_success)
			if(mtx_init(&(Qu->Wait),mtx_plain)==thrd_success)
			{
				Qu->Capacity=Size-sizeof(thrp_qu);
				Qu->Master=thrd_current();

				_ThrP_Qu_Reset_(Qu);
			}
			else
			{
				mtx_destroy(&(Qu->Lock));
				goto KILL;
			}
		else
		{
KILL:
			free(Qu);
			Qu=NULL;
		}

	return Qu;
}
static int ThrP_Qu_Delete_(thrp_qu **const Ptr)
{
	thrp_qu *const Qu=*Ptr;
	int Flag;

	if(_ThrP_Qu_Master_(Qu))
	{
		mtx_t *const Lock=&(Qu->Lock);
		mtx_t *const Wait=&(Qu->Wait);

		Flag=mtx_trylock(Wait);
		switch(Flag)
		{
		case thrd_busy:
			Flag=_ThrP_Qu_Flag_(Flag,mtx_lock(Wait));
		case thrd_success:
			if(_ThrP_Qu_Exist_(Qu->Thread))
				Flag=_ThrP_Qu_Flag_(Flag,_ThrP_Qu_Join_(Qu));
			Flag=_ThrP_Qu_Flag_(Flag,mtx_unlock(Wait));
		default:;
		}

		mtx_destroy(Wait);
		mtx_destroy(Lock);

		free(Qu);
		*Ptr=NULL;
	}
	else
		Flag=thrd_error;

	return Flag;
}
#endif
#endif

#if(1)
#if(1)
static int ThrP_Mu_Take_(thrp_mu *const Mu,const _Bool Wait)
{
	if(Mu)
	{
		mtx_t *const Mutex=&(Mu->Tex);

		return ((Wait)?(mtx_lock(Mutex)):(mtx_trylock(Mutex)));
	}
	else
		return thrd_error;
}
static int ThrP_Mu_Give_(thrp_mu *const Mu,const _Bool Wait)
{
	if(Mu)
	{
		mtx_t *const Mutex=&(Mu->Tex);
		int Flag=mtx_trylock(Mutex);

		switch(Flag)
		{
		case thrd_busy:
			if(Wait)
				Flag=mtx_lock(Mutex);
		case thrd_success:
			Flag=_ThrP_Qu_Flag_(Flag,mtx_unlock(Mutex));
		default:
			return Flag;
		}
	}
	else
		return thrd_error;
}
#endif

#if(1)
static thrp_mu *ThrP_Mu_Create_(void)
{
	thrp_mu *Mu=malloc(sizeof(thrp_mu));

	if(Mu)
		if(mtx_init(&(Mu->Tex),mtx_plain)==thrd_success);
		else
		{
			free(Mu);
			Mu=NULL;
		}

	return Mu;
}
static int ThrP_Mu_Delete_(thrp_mu **const Ptr)
{
	thrp_mu *const Mu=*Ptr;
	int Flag;

	if(Mu)
	{
		mtx_t *const Mutex=&(Mu->Tex);

		Flag=mtx_trylock(Mutex);
		switch(Flag)
		{
		case thrd_busy:
			Flag=_ThrP_Qu_Flag_(Flag,mtx_lock(Mutex));
		case thrd_success:
			Flag=_ThrP_Qu_Flag_(Flag,mtx_unlock(Mutex));
		default:;
		}

		mtx_destroy(Mutex);
		free(Mu);
		*Ptr=NULL;
	}
	else
		Flag=thrd_error;

	return Flag;
}
#endif
#endif

#if(1)
static _Bool _ThrP_Thread_Sec_(time_t *const restrict Sec,const int Time)
{
	if(Time<0)
		return _THRP_FAILURE_;
	else
	{
		const int Div=1000;

		*Sec=Time/Div;

		return _THRP_SUCCESS_;
	}
}
static _Bool _ThrP_Thread_Nsec_(long *const restrict Nsec,const int Time)
{
	const int Mod=1000;
	const long Mul=1000000;
	long Temp[2];

	Temp[0]=Time%Mod;
	*Nsec=Mul*Temp[0];
	Temp[1]=(*Nsec)/Mul;

	if(Temp[0]==Temp[1])
		return _THRP_SUCCESS_;
	else
		return _THRP_FAILURE_;
}
static _Bool ThrP_Thread_Sleep_(const int *const restrict Time)
{
	struct timespec Holder;

	if(_ThrP_Thread_Sec_(&(Holder.tv_sec),*Time)==_THRP_SUCCESS_)
		if(_ThrP_Thread_Nsec_(&(Holder.tv_nsec),*Time)==_THRP_SUCCESS_)
			while(1)
			{
				struct timespec Remain;

				switch(thrd_sleep(&Holder,&Remain))
				{
				default:
					return _THRP_FAILURE_;
				case 0:
					return _THRP_SUCCESS_;
				case-1:
					if(Remain.tv_sec<0)
						return _THRP_FAILURE_;
					else if(Holder.tv_sec<Remain.tv_sec)
						return _THRP_FAILURE_;
					else if(Holder.tv_sec>Remain.tv_sec)
						Holder=Remain;
					else if(Holder.tv_nsec<Remain.tv_nsec)
						return _THRP_FAILURE_;
					else
						Holder=Remain;
				}
			}
		else
			return _THRP_FAILURE_;
	else
		return _THRP_FAILURE_;
}
static _Bool ThrP_Thread_Yield_(const void *const Nope)
{
	(void)(Nope);

	thrd_yield();

	return _THRP_SUCCESS_;
}
#endif

#if(1)
THRPACK ThrP=
{
	.Qu=
	{
		.Create_=ThrP_Qu_Create_,
		.Delete_=ThrP_Qu_Delete_,
		.Push_=ThrP_Qu_Push_,
		.Wait_=ThrP_Qu_Wait_
	},
	.Mu=
	{
		.Create_=ThrP_Mu_Create_,
		.Delete_=ThrP_Mu_Delete_,
		.Take_=ThrP_Mu_Take_,
		.Give_=ThrP_Mu_Give_
	},
	.Task=
	{
		.Sleep_=ThrP_Thread_Sleep_,
		.Yield_=ThrP_Thread_Yield_
	},
	.Version=_StringVersion,
	.Flag=
	{
		.Success=thrd_success,
		.TimedOut=thrd_timedout,
		.Busy=thrd_busy,
		.NoMem=thrd_nomem,
		.Error=thrd_error
	},
	.Signal=
	{
		.Continue=_THRP_SUCCESS_,
		.Break=_THRP_FAILURE_
	}
};
THRPACK *ThrP_(void) { return &ThrP; }
#endif

#endif

#else
#error The compiler does not inform the C Standard version number.
#endif

#else
#error The compiler does not conform to the C Standard.
#endif

#else
#error The compiler does not conform to the C Standard.
#endif
