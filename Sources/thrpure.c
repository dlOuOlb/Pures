#ifdef __STDC__

#if(__STDC__)

#ifdef __STDC_VERSION__

#if(__STDC_VERSION__<201710L)
#error The compiler does not satisfy the C18 Standard.
#else

#ifdef __STDC_NO_THREADS__
#error The compiler does not support the thread library.
#else

#if(1)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>
#include "thrpure.h"
#endif

#if(1)
struct _thrp_tp
{
	union
	{
		thrp_e_ Event_;
		thrp_p_ Proc_;
	};
	size_t Size;
};
typedef struct _thrp_tp thrp_tp;
typedef const struct _thrp_tp THRP_TP;

struct _thrp_qu
{
	mtx_t Lock;
	mtx_t Wait;
	size_t Capacity;
	size_t Count;
	thrp_tp *Pin[2];
	thrd_t Thread;
};

struct _thrp_mu
{
	mtx_t Tex;
};

_Static_assert(sizeof(char)==1,"sizeof(char) != 1");
_Static_assert(sizeof(void*)==sizeof(size_t),"sizeof(void*) != sizeof(size_t)");
_Static_assert(sizeof(thrp_e_)==sizeof(thrp_p_),"sizeof(thrp_e_) != sizeof(thrp_p_)");
_Static_assert(sizeof(int)<=sizeof(time_t),"sizeof(int) > sizeof(time_t)");
_Static_assert((sizeof(thrp_tp)%sizeof(size_t))==0,"sizeof(thrp_tp)%sizeof(size_t) != 0");
_Static_assert((sizeof(thrp_qu)%sizeof(size_t))==0,"sizeof(thrp_qu)%sizeof(size_t) != 0");

#define _THRP_SUCCESS_ ((_Bool)(0))
#define _THRP_FAILURE_ ((_Bool)(1))
#endif

#if(1)
static const char _StringVersion[16]="Date:2019.07.09";
static const thrd_t _ThreadEmpty;
static const mtx_t _MutexEmpty;

static mtx_t _LockQu;
static mtx_t *const LockQu=&_LockQu;

static mtx_t _LockMu;
static mtx_t *const LockMu=&_LockMu;
#endif

#if(1)
static int _ThrP_Flag_(const int Flag,const int Temp)
{
	return ((Temp==thrd_success)?(Flag):(Temp));
}
static size_t _ThrP_Padding_(volatile size_t Value)
{
	Value--;
	Value+=sizeof(size_t);
	Value/=sizeof(size_t);
	Value*=sizeof(size_t);

	return Value;
}
static int _ThrP_Exist_Thread_(const thrd_t Thread)
{
	return memcmp(&Thread,&_ThreadEmpty,sizeof(thrd_t));
}
#endif

#if(1)
#if(1)
static void _ThrP_Qu_Exit_Once_(void)
{
	if(memcmp(&_LockQu,&_MutexEmpty,sizeof(mtx_t)))
	{
		mtx_destroy(&_LockQu);
		_LockQu=_MutexEmpty;
	}
	else;
}
static void _ThrP_Qu_Exit_(void)
{
	static once_flag _FlagExit=ONCE_FLAG_INIT;

	call_once(&_FlagExit,_ThrP_Qu_Exit_Once_);
}
static void _ThrP_Qu_Init_Once_(void)
{
	int Flag=mtx_init(LockQu,mtx_plain);

	if(Flag==thrd_success)
		Flag=atexit(_ThrP_Qu_Exit_);
	else
		exit(Flag);

	if(Flag)
		exit(Flag);
	else;
}
static void _ThrP_Qu_Init_(void)
{
	static once_flag _FlagInit=ONCE_FLAG_INIT;

	call_once(&_FlagInit,_ThrP_Qu_Init_Once_);
}
#endif

#if(1)
static void _ThrP_Qu_Reset_(thrp_qu *const restrict Qu)
{
	Qu->Count=0;
	Qu->Pin[1]=Qu->Pin[0]=NULL;
	Qu->Thread=_ThreadEmpty;
	memset(Qu+1,0,Qu->Capacity);
}
static int _ThrP_Qu_Join_(thrp_qu *const restrict Qu)
{
	int Flag;
	const int Temp=thrd_join(Qu->Thread,&Flag);

	Flag=_ThrP_Flag_(Flag,Temp);

	if(Flag==thrd_success)
		Qu->Thread=_ThreadEmpty;
	else
		_ThrP_Qu_Reset_(Qu);

	return Flag;
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
	else;

	return Flag;
}
static int _ThrP_Qu_Stream_(thrp_qu *const Qu)
{
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

	return _ThrP_Flag_(Flag,mtx_unlock(Wait));
}
static int _ThrP_Qu_Attach_(thrp_qu *const Qu,THRP_P_ Proc_,const void *const restrict Arg,const size_t Copy,const size_t Size,const size_t Pack)
{
	mtx_t *const Lock=&(Qu->Lock);
	mtx_t *const Wait=&(Qu->Wait);
	int Flag=mtx_lock(Lock);
RETRY:
	if(Flag==thrd_success)
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
				Pin[1]=Take;
			else
			{
				Pin[1]=Pin[0]=Take;

				Flag=mtx_lock(Wait);
				if(Flag==thrd_success)
					if(_ThrP_Exist_Thread_(Qu->Thread))
					{
						Flag=_ThrP_Qu_Join_(Qu);

						if(Flag==thrd_success)
							goto NEW_STREAM;
						else
							Flag=_ThrP_Flag_(Flag,mtx_unlock(Wait));
					}
					else
NEW_STREAM:
						Flag=thrd_create(&(Qu->Thread),(thrd_start_t)_ThrP_Qu_Stream_,Qu);
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
				default:
					return thrd_error;
				case thrd_busy:
					Flag=mtx_lock(Wait);
				case thrd_success:;
				}
			else
			{
				if(Flag==thrd_success)
					mtx_unlock(Wait);

				return thrd_error;
			}

			if(Flag==thrd_success)
				Flag=mtx_lock(Lock);
			else
				return thrd_error;

			if(mtx_unlock(Wait)==thrd_success)
				goto RETRY;
			else
				return thrd_error;
		}
	}
	else
		return thrd_error;
}
#endif

#if(1)
static int ThrP_Qu_Wait_(thrp_qu *const *const Ptr)
{
	_ThrP_Qu_Init_();

	int Flag=mtx_lock(LockQu);

	if(Flag==thrd_success)
	{
		thrp_qu *const Qu=*Ptr;

		if(Qu)
		{
			mtx_t *const Wait=&(Qu->Wait);

			Flag=mtx_trylock(Wait);

			if(mtx_unlock(LockQu)==thrd_success)
				switch(Flag)
				{
				case thrd_busy:
					Flag=mtx_lock(Wait);

					if(Flag==thrd_success)
					{
				case thrd_success:
						if(_ThrP_Exist_Thread_(Qu->Thread))
							Flag=_ThrP_Qu_Join_(Qu);
						else;

						Flag=_ThrP_Flag_(Flag,mtx_unlock(Wait));
					}
					else
				default:;
				}
			else
			{
				if(Flag==thrd_success)
					mtx_unlock(Wait);
				else;

				Flag=thrd_error;
			}
		}
		else
		{
			mtx_unlock(LockQu);

			Flag=thrd_error;
		}
	}
	else;

	return Flag;
}
static int ThrP_Qu_Push_(thrp_qu *const *const Ptr,THRP_P_ Proc_,const void *const restrict Arg,const size_t Copy)
{
	_ThrP_Qu_Init_();

	if(Proc_)
	{
		volatile const size_t Size=_ThrP_Padding_(Copy);
		volatile const size_t Pack=Size+sizeof(thrp_tp);

		if(Size<Copy);
		else if(Pack<Size);
		else if(mtx_lock(LockQu)==thrd_success)
		{
			thrp_qu *const Qu=*Ptr;

			if(Qu)
			{
				const int Flag=(Pack>(Qu->Capacity))?(thrd_nomem):(_ThrP_Qu_Attach_(Qu,Proc_,Arg,Copy,Size,Pack));

				return _ThrP_Flag_(Flag,mtx_unlock(LockQu));
			}
			else
				mtx_unlock(LockQu);
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

	volatile const size_t Size=_ThrP_Padding_(Space);

	if(Size<sizeof(thrp_qu));
	else if(Size<Space);
	else if(mtx_lock(LockQu)==thrd_success)
		if(*Ptr)
			goto UNLOCK;
		else
		{
			thrp_qu *const Qu=malloc(Size);

			if(Qu)
				if(mtx_init(&(Qu->Lock),mtx_plain)==thrd_success)
					if(mtx_init(&(Qu->Wait),mtx_plain)==thrd_success)
					{
						Qu->Capacity=Size-sizeof(thrp_qu);

						_ThrP_Qu_Reset_(Qu);

						*Ptr=Qu;

						return mtx_unlock(LockQu);
					}
					else
						goto KILL_LOCK;
				else
					goto KILL_THIS;
			else
				goto UNLOCK;
KILL_LOCK:
			mtx_destroy(&(Qu->Lock));
KILL_THIS:
			free(Qu);
UNLOCK:
			mtx_unlock(LockQu);
		}
	else;

	return thrd_error;
}
static int ThrP_Qu_Delete_(thrp_qu **const Ptr)
{
	_ThrP_Qu_Init_();

	if(mtx_lock(LockQu)==thrd_success)
	{
		thrp_qu *const Qu=*Ptr;

		if(Qu)
		{
			mtx_t *const Lock=&(Qu->Lock);
			mtx_t *const Wait=&(Qu->Wait);
			const int Flag=(_ThrP_Exist_Thread_(Qu->Thread))?((_ThrP_Qu_Join_(Qu)==thrd_success)?(thrd_busy):(thrd_error)):(thrd_success);

			mtx_destroy(Wait);
			mtx_destroy(Lock);
			free(Qu);
			*Ptr=NULL;

			return _ThrP_Flag_(Flag,mtx_unlock(LockQu));
		}
		else
			mtx_unlock(LockQu);
	}
	else;

	return thrd_error;
}
#endif
#endif

#if(1)
#if(1)
static void _ThrP_Mu_Exit_Once_(void)
{
	if(memcmp(&_LockMu,&_MutexEmpty,sizeof(mtx_t)))
	{
		mtx_destroy(&_LockMu);
		_LockMu=_MutexEmpty;
	}
	else;
}
static void _ThrP_Mu_Exit_(void)
{
	static once_flag _FlagExit=ONCE_FLAG_INIT;

	call_once(&_FlagExit,_ThrP_Mu_Exit_Once_);
}
static void _ThrP_Mu_Init_Once_(void)
{
	int Flag=mtx_init(LockMu,mtx_plain);

	if(Flag==thrd_success)
		Flag=atexit(_ThrP_Mu_Exit_);
	else
		exit(Flag);

	if(Flag)
		exit(Flag);
	else;
}
static void _ThrP_Mu_Init_(void)
{
	static once_flag _FlagInit=ONCE_FLAG_INIT;

	call_once(&_FlagInit,_ThrP_Mu_Init_Once_);
}
#endif

#if(1)
static int ThrP_Mu_Take_(thrp_mu *const *const Ptr,const _Bool Wait)
{
	_ThrP_Mu_Init_();

	int Flag=mtx_lock(LockMu);

	if(Flag==thrd_success)
	{
		thrp_mu *const Mu=*Ptr;

		if(Mu)
		{
			mtx_t *const Mutex=&(Mu->Tex);

			Flag=mtx_trylock(Mutex);

			if(mtx_unlock(LockMu)==thrd_success)
				if(Flag==thrd_busy)
					if(Wait)
						Flag=mtx_lock(Mutex);
					else;
				else;
			else
			{
				if(Flag==thrd_success)
					mtx_unlock(Mutex);
				else;

				Flag=thrd_error;
			}
		}
		else
		{
			mtx_unlock(LockMu);

			Flag=thrd_error;
		}
	}
	else;

	return Flag;
}
static int ThrP_Mu_Give_(thrp_mu *const *const Ptr,const _Bool Wait)
{
	_ThrP_Mu_Init_();

	int Flag=mtx_lock(LockMu);

	if(Flag==thrd_success)
	{
		thrp_mu *const Mu=*Ptr;

		if(Mu)
		{
			mtx_t *const Mutex=&(Mu->Tex);

			Flag=mtx_trylock(Mutex);

			if(mtx_unlock(LockMu)==thrd_success)
				switch(Flag)
				{
				case thrd_busy:
					if(Wait)
					{
						Flag=mtx_lock(Mutex);
						if(Flag==thrd_success)
						{
				case thrd_success:
							Flag=mtx_unlock(Mutex);
						}
						else
				default:;
					}
					else
						Flag=_ThrP_Flag_(Flag,mtx_unlock(Mutex));
				}
			else
			{
				if(Flag==thrd_success)
					mtx_unlock(Mutex);
				else;

				Flag=thrd_error;
			}
		}
		else
		{
			mtx_unlock(LockMu);

			Flag=thrd_error;
		}
	}
	else;

	return Flag;
}
#endif

#if(1)
static int ThrP_Mu_Create_(thrp_mu **const Ptr)
{
	_ThrP_Mu_Init_();

	if(mtx_lock(LockMu)==thrd_success)
		if(*Ptr)
			goto UNLOCK;
		else
		{
			thrp_mu *const Mu=malloc(sizeof(thrp_mu));

			if(Mu)
				if(mtx_init(&(Mu->Tex),mtx_plain)==thrd_success)
				{
					*Ptr=Mu;

					return mtx_unlock(LockMu);
				}
				else
					goto KILL_THIS;
			else
				goto UNLOCK;
KILL_THIS:
			free(Mu);
UNLOCK:
			mtx_unlock(LockMu);
		}
	else;

	return thrd_error;
}
static int ThrP_Mu_Delete_(thrp_mu **const Ptr)
{
	_ThrP_Mu_Init_();

	if(mtx_lock(LockMu)==thrd_success)
	{
		thrp_mu *const Mu=*Ptr;

		if(Mu)
		{
			mtx_t *const Mutex=&(Mu->Tex);
			const int Flag=mtx_trylock(Mutex);

			switch(Flag)
			{
			case thrd_busy:
				if(mtx_unlock(LockMu)==thrd_success);else break;
				if(mtx_lock(Mutex)==thrd_success);else break;
				if(mtx_lock(LockMu)==thrd_success)
			case thrd_success:
					if(mtx_unlock(Mutex)==thrd_success)
					{
						mtx_destroy(Mutex);
						free(Mu);
						*Ptr=NULL;

						return _ThrP_Flag_(Flag,mtx_unlock(LockMu));
					}
					else
			default:
						mtx_unlock(LockMu);
				else
					mtx_unlock(Mutex);
			}
		}
		else
			mtx_unlock(LockMu);
	}
	else;

	return thrd_error;
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
	volatile long Temp[2];

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
static _Bool ThrP_Thread_Yield_(const void *const _)
{
	(void)(_);

	thrd_yield();

	return _THRP_SUCCESS_;
}
static _Bool ThrP_Thread_Break_(const void *const _)
{
	(void)(_);

	return _THRP_FAILURE_;
}
static _Bool ThrP_Thread_Print_(const char *const restrict Msg)
{
	if(puts(Msg)<0)
		return _THRP_FAILURE_;
	else
		return _THRP_SUCCESS_;
}
#endif

#if(1)
static int _ThrP_Event_Thread_(thrp_tp *const Task)
{
	const void *const Arg=(Task->Size)?(Task+1):(NULL);

	Task->Event_(Arg);

	free(Task);

	return thrd_success;
}
static int _ThrP_Event_Launch_(thrp_tp *const Task)
{
	thrd_t Thread;
	int Flag=thrd_create(&Thread,(thrd_start_t)_ThrP_Event_Thread_,Task);

	if(Flag==thrd_success)
		Flag=thrd_detach(Thread);
	else
		free(Task);

	return Flag;
}
static int ThrP_Event_Invoke_(THRP_E_ Event_,const void *const restrict Arg,const size_t Copy)
{
	if(Event_)
	{
		volatile const size_t Size=_ThrP_Padding_(Copy);
		volatile const size_t Pack=Size+sizeof(thrp_tp);

		if(Size<Copy);
		else if(Pack<Size);
		else
		{
			thrp_tp *const Hold=malloc(Pack);

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
		.Yield_=ThrP_Thread_Yield_,
		.Break_=ThrP_Thread_Break_,
		.Print_=ThrP_Thread_Print_
	},
	.Event=
	{
		.Invoke_=ThrP_Event_Invoke_
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
