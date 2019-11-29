﻿#include "stdpain.h"
#include "thrpure.h"

#if(1)
typedef struct { _Alignas(void*) struct { union { thrp_e_ Event_;thrp_p_ Proc_; };size_t Size; }; }thrp_tp;
typedef const thrp_tp THRP_TP;

struct _thrp_qu { _Alignas(void*) struct { mtx_t Lock,Wait;size_t Capacity,Count;thrp_tp *Pin[2];thrd_t Thread; }; };
struct _thrp_mu { mtx_t Tex; };
#endif

#if(1)
static const struct { const thrd_t Thread;THRP_TP TP; }Empty;
static struct { mtx_t *const Qu,*const Mu; }GLock={.Qu=&(mtx_t) { 0 },.Mu=&(mtx_t) { 0 }};

static void *_ThrP_Malloc_(const size_t Size) { return aligned_alloc(sizeof(void*),Size); }
static size_t _ThrP_Padding_(register size_t V) { const size_t T=sizeof(void*);V--;V+=T;V/=T;V*=T;return V; }
static int _ThrP_Exist_Thread_(const thrd_t Thread) { return memcmp(&Thread,&(Empty.Thread),sizeof(thrd_t)); }
static void _ThrP_Empty_Thread_(thrd_t *const Thread) { memcpy(Thread,&(Empty.Thread),sizeof(thrd_t));return; }
static int _ThrP_Flag_(register const int Flag,register const int Temp) { return ((Temp==thrd_success)?(Flag):(Temp)); }
#endif

#if(1)
#if(1)
static void _ThrP_Qu_Exit_Once_(void) { mtx_destroy(GLock.Qu);return; }
static void _ThrP_Qu_Exit_(void) { static once_flag _FlagExit=ONCE_FLAG_INIT;call_once(&_FlagExit,_ThrP_Qu_Exit_Once_);return; }
static void _ThrP_Qu_Init_Once_(void)
{
	int Flag=mtx_init(GLock.Qu,mtx_plain);

	if(Flag==thrd_success)
		Flag=atexit(_ThrP_Qu_Exit_);
	else
		exit(Flag);

	if(Flag)
		exit(Flag);
	else
		return;
}
static void _ThrP_Qu_Init_(void) { static once_flag _FlagInit=ONCE_FLAG_INIT;call_once(&_FlagInit,_ThrP_Qu_Init_Once_);return; }
#endif

#if(1)
static void *_ThrP_Qu_Capable_(thrp_qu *const restrict Qu,const size_t Pack)
{
	char *const Front=(char*)(Qu+1);

	if(Qu->Count)
	{
		thrp_tp *const *const Pin=Qu->Pin;
		char *const Foo=(char*)(Pin[0]),*const Bar=(char*)(Pin[1]+1),*const Ptr=Bar+(Pin[1]->Size),*const Bnd=Ptr+Pack;

		if(Pin[0]>Pin[1])
			if(Bnd>Foo)
				return NULL;
			else
				return Ptr;
		else
			if(Bnd>(Front+(Qu->Capacity)))
				if(Front<Foo)
					if((Front+Pack)>Foo)
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
static void _ThrP_Qu_Nullify_(thrp_qu *const Qu)
{
	thrp_tp *const restrict Take=_ThrP_Qu_Capable_(Qu,sizeof(thrp_tp));

	if(Take)
		*Take=Empty.TP;
	else;

	return;
}
static void _ThrP_Qu_Reset_(thrp_qu *const restrict Qu)
{
	Qu->Count=0;
	Qu->Pin[1]=Qu->Pin[0]=NULL;
	_ThrP_Empty_Thread_(&(Qu->Thread));
	_ThrP_Qu_Nullify_(Qu);

	return;
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
static int _ThrP_Qu_Join_(thrp_qu *const restrict Qu)
{
	int Flag;
	const int Temp=thrd_join(Qu->Thread,&Flag);

	if((Flag=_ThrP_Flag_(Flag,Temp))==thrd_success)
		_ThrP_Empty_Thread_(&(Qu->Thread));
	else
		_ThrP_Qu_Reset_(Qu);

	return Flag;
}
#endif

#if(1)
static int _ThrP_Qu_Remove_(thrp_qu *const restrict Qu,size_t *const restrict Count)
{
	mtx_t *const Lock=&(Qu->Lock);

	if(mtx_lock(Lock)==thrd_success)
	{
		thrp_tp **const Pin=Qu->Pin;

		if(--(Qu->Count))
		{
			void *const Front=Qu+1;
			char *const End=((char*)(Front))+(Qu->Capacity);
			char *const Ptr=((char*)(Pin[0]+1))+(Pin[0]->Size);

			if((Ptr+sizeof(thrp_tp))>End)
				Pin[0]=Front;
			else
			{
				thrp_tp *const restrict Temp=(thrp_tp*)(Ptr);

				Pin[0]=(Temp->Proc_)?(Temp):(Front);
			}
		}
		else
			Pin[1]=Pin[0]=NULL;

		*Count=Qu->Count;

		return mtx_unlock(Lock);
	}
	else
		return thrd_error;
}
static int _ThrP_Qu_Stream_(void *const Pass)
{
	thrp_qu *const restrict Qu=Pass;
	mtx_t *const Wait=&(Qu->Wait);
	size_t Count;
	int Flag=_ThrP_Qu_Count_(Qu,&Count);

	while((Flag==thrd_success)&&(Count))
	{
		THRP_TP *const restrict Task=Qu->Pin[0];
		const void *const Arg=(Task->Size)?(Task+1):(NULL);

		if(Task->Proc_(Arg)==_SUCCESS_)
			Flag=_ThrP_Qu_Remove_(Qu,&Count);
		else
			Flag=thrd_error;
	}

	return _ThrP_Flag_(Flag,mtx_unlock(Wait));
}
static int _ThrP_Qu_Attach_(thrp_qu *const restrict Qu,THRP_P_ Proc_,const void *const Arg,const size_t Copy,const size_t Size,const size_t Pack)
{
	mtx_t *const Lock=&(Qu->Lock);
	mtx_t *const Wait=&(Qu->Wait);
	int Flag=mtx_lock(Lock);

	while(Flag==thrd_success)
	{
		thrp_tp *const Take=_ThrP_Qu_Capable_(Qu,Pack);

		if(Take)
		{
			thrp_tp **const Pin=Qu->Pin;

			Take->Proc_=Proc_;
			Take->Size=Size;

			if(Copy)
				memcpy(Take+1,Arg,Copy);
			else;

			if((Qu->Count)++)
			{
				Pin[1]=Take;
				_ThrP_Qu_Nullify_(Qu);
			}
			else
			{
				Pin[1]=Pin[0]=Take;
				_ThrP_Qu_Nullify_(Qu);

				if((Flag=mtx_lock(Wait))==thrd_success)
					if(_ThrP_Exist_Thread_(Qu->Thread))
						if((Flag=_ThrP_Qu_Join_(Qu))==thrd_success)
							goto NEW_STREAM;
						else
							Flag=_ThrP_Flag_(Flag,mtx_unlock(Wait));
					else
NEW_STREAM:				Flag=thrd_create(&(Qu->Thread),_ThrP_Qu_Stream_,Qu);
				else;
			}

			return _ThrP_Flag_(Flag,mtx_unlock(Lock));
		}
		else
		{
			Flag=mtx_trylock(Wait);

			if(mtx_unlock(Lock)==thrd_success)
				switch(Flag)
				{
				case thrd_busy:
					if((Flag=mtx_lock(Wait))==thrd_success)
					{
				case thrd_success:
						Flag=mtx_lock(Lock);
						if(mtx_unlock(Wait)==thrd_success)
							continue;
						else;
					}
					else
				default:;
				}
			else if(Flag==thrd_success)
				mtx_unlock(Wait);
			else;

			break;
		}
	}

	return thrd_error;
}
#endif

#if(1)
static int ThrP_Qu_Wait_(thrp_qu *const *const Ptr)
{
	_ThrP_Qu_Init_();

	if(mtx_lock(GLock.Qu)==thrd_success)
	{
		thrp_qu *const restrict Qu=*Ptr;

		if(Qu)
		{
			mtx_t *const Wait=&(Qu->Wait);
			int Flag=mtx_trylock(Wait);

			if(mtx_unlock(GLock.Qu)==thrd_success)
				switch(Flag)
				{
				case thrd_busy:
					if((Flag=mtx_lock(Wait))==thrd_success)
					{
				case thrd_success:
						if(_ThrP_Exist_Thread_(Qu->Thread))
							Flag=_ThrP_Qu_Join_(Qu);
						else;

						Flag=_ThrP_Flag_(Flag,mtx_unlock(Wait));
					}
					else;
				default:
					return Flag;
				}
			else if(Flag==thrd_success)
				mtx_unlock(Wait);
			else;
		}
		else
			mtx_unlock(GLock.Qu);
	}
	else;

	return thrd_error;
}
static int ThrP_Qu_Push_(thrp_qu *const *const Ptr,THRP_P_ Proc_,const void *const Arg,const size_t Copy)
{
	_ThrP_Qu_Init_();

	if(Proc_)
	{
		const size_t Size=_ThrP_Padding_(Copy);
		const size_t Pack=Size+sizeof(thrp_tp);

		if(Size<Copy);
		else if(Pack<Size);
		else if(mtx_lock(GLock.Qu)==thrd_success)
		{
			thrp_qu *const restrict Qu=*Ptr;

			if(Qu)
			{
				const int Flag=(Pack>(Qu->Capacity))?(thrd_nomem):(_ThrP_Qu_Attach_(Qu,Proc_,Arg,Copy,Size,Pack));

				return _ThrP_Flag_(Flag,mtx_unlock(GLock.Qu));
			}
			else
				mtx_unlock(GLock.Qu);
		}
		else;
	}
	else;

	return thrd_error;
}
#endif

#if(1)
static int ThrP_Qu_Create_(thrp_qu **const Ptr,const size_t Space)
{
	_ThrP_Qu_Init_();

	const size_t Size=_ThrP_Padding_(Space);

	if(Size<sizeof(thrp_qu));
	else if(Size<Space);
	else if(mtx_lock(GLock.Qu)==thrd_success)
		if(*Ptr)
			goto UNLOCK;
		else
		{
			thrp_qu *const restrict Qu=_ThrP_Malloc_(Size);

			if(Qu)
				if(mtx_init(&(Qu->Lock),mtx_plain)==thrd_success)
					if(mtx_init(&(Qu->Wait),mtx_plain)==thrd_success)
					{
						Qu->Capacity=Size-sizeof(thrp_qu);

						_ThrP_Qu_Reset_(*Ptr=Qu);

						return mtx_unlock(GLock.Qu);
					}
					else
						goto KILL_LOCK;
				else
					goto KILL_THIS;
			else
				goto UNLOCK;

KILL_LOCK:	mtx_destroy(&(Qu->Lock));
KILL_THIS:	free(Qu);
UNLOCK:		mtx_unlock(GLock.Qu);
		}
	else;

	return thrd_error;
}
static int ThrP_Qu_Delete_(thrp_qu **const Ptr)
{
	_ThrP_Qu_Init_();

	if(mtx_lock(GLock.Qu)==thrd_success)
	{
		thrp_qu *const restrict Qu=*Ptr;

		if(Qu)
		{
			mtx_t *const Lock=&(Qu->Lock);
			mtx_t *const Wait=&(Qu->Wait);
			const int Flag=(_ThrP_Exist_Thread_(Qu->Thread))?((_ThrP_Qu_Join_(Qu)==thrd_success)?(thrd_busy):(thrd_error)):(thrd_success);

			mtx_destroy(Wait);
			mtx_destroy(Lock);
			free(Qu);
			*Ptr=NULL;

			return _ThrP_Flag_(Flag,mtx_unlock(GLock.Qu));
		}
		else
			mtx_unlock(GLock.Qu);
	}
	else;

	return thrd_error;
}
#endif
#endif

#if(1)
#if(1)
static void _ThrP_Mu_Exit_Once_(void) { mtx_destroy(GLock.Mu);return; }
static void _ThrP_Mu_Exit_(void) { static once_flag _FlagExit=ONCE_FLAG_INIT;call_once(&_FlagExit,_ThrP_Mu_Exit_Once_);return; }
static void _ThrP_Mu_Init_Once_(void)
{
	int Flag=mtx_init(GLock.Mu,mtx_plain);

	if(Flag==thrd_success)
		Flag=atexit(_ThrP_Mu_Exit_);
	else
		exit(Flag);

	if(Flag)
		exit(Flag);
	else
		return;
}
static void _ThrP_Mu_Init_(void) { static once_flag _FlagInit=ONCE_FLAG_INIT;call_once(&_FlagInit,_ThrP_Mu_Init_Once_);return; }
#endif

#if(1)
static int ThrP_Mu_Take_(thrp_mu *const *const Ptr,const _Bool Wait)
{
	_ThrP_Mu_Init_();

	if(mtx_lock(GLock.Mu)==thrd_success)
	{
		thrp_mu *const restrict Mu=*Ptr;

		if(Mu)
		{
			mtx_t *const Mutex=&(Mu->Tex);
			int Flag=mtx_trylock(Mutex);

			if(mtx_unlock(GLock.Mu)==thrd_success)
			{
				if(Flag==thrd_busy)
					if(Wait)
						Flag=mtx_lock(Mutex);
					else;
				else;

				return Flag;
			}
			else if(Flag==thrd_success)
				mtx_unlock(Mutex);
			else;
		}
		else
			mtx_unlock(GLock.Mu);
	}
	else;

	return thrd_error;
}
static int ThrP_Mu_Give_(thrp_mu *const *const Ptr,const _Bool Wait)
{
	_ThrP_Mu_Init_();

	if(mtx_lock(GLock.Mu)==thrd_success)
	{
		thrp_mu *const restrict Mu=*Ptr;

		if(Mu)
		{
			mtx_t *const Mutex=&(Mu->Tex);
			int Flag=mtx_trylock(Mutex);

			if(mtx_unlock(GLock.Mu)==thrd_success)
				switch(Flag)
				{
				case thrd_busy:
					if(Wait)
						if((Flag=mtx_lock(Mutex))==thrd_success)
				case thrd_success:
							Flag=mtx_unlock(Mutex);
						else;
					else
						Flag=_ThrP_Flag_(Flag,mtx_unlock(Mutex));
				default:
					return Flag;
				}
			else if(Flag==thrd_success)
				mtx_unlock(Mutex);
			else;
		}
		else
			mtx_unlock(GLock.Mu);
	}
	else;

	return thrd_error;
}
#endif

#if(1)
static int ThrP_Mu_Create_(thrp_mu **const Ptr)
{
	_ThrP_Mu_Init_();

	if(mtx_lock(GLock.Mu)==thrd_success)
		if(*Ptr)
			goto UNLOCK;
		else
		{
			thrp_mu *const restrict Mu=_ThrP_Malloc_(sizeof(thrp_mu));

			if(Mu)
				if(mtx_init(&(Mu->Tex),mtx_plain)==thrd_success)
				{
					*Ptr=Mu;

					return mtx_unlock(GLock.Mu);
				}
				else
					goto KILL_THIS;
			else
				goto UNLOCK;

KILL_THIS:	free(Mu);
UNLOCK:		mtx_unlock(GLock.Mu);
		}
	else;

	return thrd_error;
}
static int ThrP_Mu_Delete_(thrp_mu **const Ptr)
{
	_ThrP_Mu_Init_();

	if(mtx_lock(GLock.Mu)==thrd_success)
	{
		thrp_mu *const restrict Mu=*Ptr;

		if(Mu)
		{
			mtx_t *const Mutex=&(Mu->Tex);
			const int Flag=mtx_trylock(Mutex);

			switch(Flag)
			{
			case thrd_busy:
				if(mtx_unlock(GLock.Mu)==thrd_success);else break;
				if(mtx_lock(Mutex)==thrd_success);else break;
				if(mtx_lock(GLock.Mu)==thrd_success)
			case thrd_success:
					if(mtx_unlock(Mutex)==thrd_success)
					{
						mtx_destroy(Mutex);
						free(Mu);
						*Ptr=NULL;

						return _ThrP_Flag_(Flag,mtx_unlock(GLock.Mu));
					}
					else
			default:	mtx_unlock(GLock.Mu);
				else
					mtx_unlock(Mutex);
			}
		}
		else
			mtx_unlock(GLock.Mu);
	}
	else;

	return thrd_error;
}
#endif
#endif

#if(1)
static _Bool _ThrP_Thread_Okay_(int Time)
{
	if(Time<0)
		return _FAILURE_;
	else
	{
		const int Kilo=+1000;
		const time_t Cast=(time_t)(Time/=Kilo);
		const int Back=(int)(Cast);

		if(Back==Time)
			return _SUCCESS_;
		else
			return _FAILURE_;
	}
}
static struct timespec _ThrP_Thread_Time_(register const int T) { const int K=+1000;const long M=+1000000L;return (struct timespec) { .tv_sec=(time_t)(T/K),.tv_nsec=M*(long)(T%K) }; }
static _Bool ThrP_Thread_Sleep_(const void *const _)
{
	const int Time=*((const int*)(_));

	if(_ThrP_Thread_Okay_(Time))
		for(struct timespec Holder=_ThrP_Thread_Time_(Time),Remain;1;Holder=Remain)
			switch(thrd_sleep(&Holder,&Remain))
			{
			case 0:
				return _SUCCESS_;
			case-1:
				if(Remain.tv_sec<0);
				else if(Holder.tv_sec<Remain.tv_sec);
				else if(Holder.tv_sec>Remain.tv_sec)
					break;
				else if(Holder.tv_nsec<Remain.tv_nsec);
				else
					break;
			default:
				return _FAILURE_;
			}
	else
		return _FAILURE_;
}
static _Bool ThrP_Thread_Yield_(const void *const _) { (void)(_);thrd_yield();return _SUCCESS_; }
static _Bool ThrP_Thread_Break_(const void *const _) { (void)(_);return _FAILURE_; }
static _Bool ThrP_Thread_Print_(const void *const _)
{
	if(puts(_)<0)
		return _FAILURE_;
	else
		return _SUCCESS_;
}
#endif

#if(1)
static int _ThrP_Event_Thread_(void *const Pass)
{
	thrp_tp *const restrict Task=Pass;
	const void *const Arg=(Task->Size)?(Task+1):(NULL);

	Task->Event_(Arg);

	free(Task);

	return thrd_success;
}
static int _ThrP_Event_Launch_(thrp_tp *const Task)
{
	thrd_t Thread;
	int Flag=thrd_create(&Thread,_ThrP_Event_Thread_,Task);

	if(Flag==thrd_success)
		Flag=thrd_detach(Thread);
	else
		free(Task);

	return Flag;
}
static int ThrP_Event_Invoke_(THRP_E_ Event_,const void *const Arg,const size_t Copy)
{
	if(Event_)
	{
		const size_t Size=_ThrP_Padding_(Copy);
		const size_t Pack=Size+sizeof(thrp_tp);

		if(Size<Copy);
		else if(Pack<Size);
		else
		{
			thrp_tp *const restrict Hold=_ThrP_Malloc_(Pack);

			if(Hold)
			{
				Hold->Event_=Event_;
				Hold->Size=Size;

				if(Copy)
					memcpy(Hold+1,Arg,Copy);
				else;

				return _ThrP_Event_Launch_(Hold);
			}
			else
				return thrd_nomem;
		}
	}
	else;

	return thrd_error;
}
#endif

#if(1)
_Static_assert((sizeof(THRPACE)<<4)==sizeof(THRPACK),"sizeof(THRPACK) != 16*sizeof(THRPACE)");
extern _Alignas(sizeof(THRPACE)<<4) THRPACK ThrP=
{
	.Version=_INC_THRPURE,
	.Signal=&(const struct _thrp_b2)
	{
		.Continue=_SUCCESS_,
		.Break=_FAILURE_
	},
	.Flag=&(const struct _thrp_en)
	{
		.Success=thrd_success,
		.TimedOut=thrd_timedout,
		.Busy=thrd_busy,
		.NoMem=thrd_nomem,
		.Error=thrd_error
	},
	.Event.Invoke_=ThrP_Event_Invoke_,
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
		.Yield_=ThrP_Thread_Yield_,
		.Break_=ThrP_Thread_Break_,
		.Print_=ThrP_Thread_Print_
	}
};
extern THRPACK *ThrP_(void) { return &ThrP; }
#endif
