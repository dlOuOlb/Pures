#include "stdpain.h"
#include "thrpure.h"

static void xThrP_UM_Return_(void *const Memory) { free(Memory);return; }
static void *xThrP_UM_Borrow_(void *const Owner,const size_t Align,const size_t Size) { (void)(Owner);return aligned_alloc(Align,Size); }
static const struct
{
	_Alignas(16) const char Version[16];
	THRP_UM Handle;
	const struct othrpack_flag Flag;
	const struct othrpack_signal Signal;
	const thrd_t Empty;
}
xPost=
{
	.Version=oTHRPURE_INC_,
	.Handle=
	{
		.Return_=xThrP_UM_Return_,
		.Borrow_=xThrP_UM_Borrow_
	},
	.Signal=
	{
		.Continue=true,
		.Break=false
	},
	.Flag=
	{
		.Success=thrd_success,
		.TimedOut=thrd_timedout,
		.Busy=thrd_busy,
		.NoMem=thrd_nomem,
		.Error=thrd_error
	}
};
static struct { mtx_t *const Qu,*const Mu; }xGLock={.Qu=&(mtx_t) { 0 },.Mu=&(mtx_t) { 0 }};

#if(1)
static size_t xThrP_Padding_(register size_t V) { const size_t T=_Alignof(max_align_t);V--;V+=T;V/=T;V*=T;return V; }
static int xThrP_Exist_Thread_(const thrd_t Thread) { return memcmp(&Thread,&(xPost.Empty),sizeof(thrd_t)); }
static void xThrP_Empty_Thread_(thrd_t *const restrict Thread) { memcpy(Thread,&(xPost.Empty),sizeof(thrd_t));return; }
static int xThrP_Flag_(register const int Flag,register const int Temp) { return ((Temp==thrd_success)?(Flag):(Temp)); }
#endif

#if(1)
typedef struct { _Alignas(max_align_t) struct { thrp_p_ Proc_;size_t Size; }; } thrp_tp; typedef const thrp_tp THRP_TP;
struct othrp_qu
{
	_Alignas(max_align_t) struct
	{
		void(*Free_)(void *const),*(*Alloc_)(void *const,const size_t,const size_t);
		mtx_t Lock,Wait;
		size_t Capacity,Count;
		thrp_tp *Pin[2];
		thrd_t Thread;
	};
};

#if(1)
static void xThrP_Qu_Exit_Once_(void) { mtx_destroy(xGLock.Qu);return; }
static void xThrP_Qu_Exit_(void) { static once_flag xFlagExit=ONCE_FLAG_INIT;call_once(&xFlagExit,xThrP_Qu_Exit_Once_);return; }
static void xThrP_Qu_Init_Once_(void)
{
	int Flag=mtx_init(xGLock.Qu,mtx_plain);

	if(Flag==thrd_success)
		Flag=atexit(xThrP_Qu_Exit_);
	else
		exit(Flag);

	if(Flag)
		exit(Flag);
	else
		return;
}
static void xThrP_Qu_Init_(void) { static once_flag xFlagInit=ONCE_FLAG_INIT;call_once(&xFlagInit,xThrP_Qu_Init_Once_);return; }
#endif

#if(1)
static void *xThrP_Qu_Capable_(thrp_qu *const Qu,const size_t Pack)
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
		else if(Bnd>(Front+(Qu->Capacity)))
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
static void xThrP_Qu_Nullify_(thrp_qu *const Qu)
{
	thrp_tp *const restrict Take=xThrP_Qu_Capable_(Qu,sizeof(thrp_tp));

	if(Take)
	{
		Take->Proc_=NULL;
		Take->Size=0;
	}
	else;

	return;
}
static void xThrP_Qu_Reset_(thrp_qu *const Qu)
{
	Qu->Count=0;
	Qu->Pin[1]=Qu->Pin[0]=NULL;
	xThrP_Empty_Thread_(&(Qu->Thread));
	xThrP_Qu_Nullify_(Qu);

	return;
}
static int xThrP_Qu_Count_(thrp_qu *const Qu,size_t *const restrict Count)
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
static int xThrP_Qu_Join_(thrp_qu *const Qu)
{
	int Flag;
	const int Temp=thrd_join(Qu->Thread,&Flag);

	if((Flag=xThrP_Flag_(Flag,Temp))==thrd_success)
		xThrP_Empty_Thread_(&(Qu->Thread));
	else
		xThrP_Qu_Reset_(Qu);

	return Flag;
}
#endif

#if(1)
static int xThrP_Qu_Remove_(thrp_qu *const Qu,size_t *const restrict Count)
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
				thrp_tp *const Temp=(thrp_tp*)(Ptr);

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
static int xThrP_Qu_Stream_(void *const Pass)
{
	thrp_qu *const Qu=Pass;
	mtx_t *const Wait=&(Qu->Wait);
	size_t Count;
	int Flag=xThrP_Qu_Count_(Qu,&Count);

	while((Flag==thrd_success)&&(Count))
	{
		THRP_TP *const Task=Qu->Pin[0];
		const void *const Arg=(Task->Size)?(Task+1):(NULL);

		if(Task->Proc_(Arg))
			Flag=xThrP_Qu_Remove_(Qu,&Count);
		else
			Flag=thrd_error;
	}

	return xThrP_Flag_(Flag,mtx_unlock(Wait));
}
static int xThrP_Qu_Attach_(thrp_qu *const Qu,THRP_P_ Proc_,const void *const restrict Arg,const size_t Copy,const size_t Size,const size_t Pack)
{
	mtx_t *const Lock=&(Qu->Lock),*const Wait=&(Qu->Wait);
	int Flag=mtx_lock(Lock);

	while(Flag==thrd_success)
	{
		thrp_tp *const Take=xThrP_Qu_Capable_(Qu,Pack);

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
				xThrP_Qu_Nullify_(Qu);
			}
			else
			{
				Pin[1]=Pin[0]=Take;
				xThrP_Qu_Nullify_(Qu);

				if((Flag=mtx_lock(Wait))==thrd_success)
					if(xThrP_Exist_Thread_(Qu->Thread))
						if((Flag=xThrP_Qu_Join_(Qu))==thrd_success)
							goto NEW_STREAM;
						else
							Flag=xThrP_Flag_(Flag,mtx_unlock(Wait));
					else
NEW_STREAM:				Flag=thrd_create(&(Qu->Thread),xThrP_Qu_Stream_,Qu);
				else;
			}

			return xThrP_Flag_(Flag,mtx_unlock(Lock));
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
						//[[fallthrough]];
				case thrd_success:
						Flag=mtx_lock(Lock);
						if(mtx_unlock(Wait)==thrd_success)
							continue;
						else;
					}
					else;
					//[[fallthrough]];
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
	xThrP_Qu_Init_();

	if(mtx_lock(xGLock.Qu)==thrd_success)
	{
		thrp_qu *const Qu=*Ptr;

		if(Qu)
		{
			mtx_t *const Wait=&(Qu->Wait);
			int Flag=mtx_trylock(Wait);

			if(mtx_unlock(xGLock.Qu)==thrd_success)
				switch(Flag)
				{
				case thrd_busy:
					if((Flag=mtx_lock(Wait))==thrd_success)
					{
						//[[fallthrough]];
				case thrd_success:
						if(xThrP_Exist_Thread_(Qu->Thread))
							Flag=xThrP_Qu_Join_(Qu);
						else;

						Flag=xThrP_Flag_(Flag,mtx_unlock(Wait));
					}
					else;
					//[[fallthrough]];
				default:
					return Flag;
				}
			else if(Flag==thrd_success)
				mtx_unlock(Wait);
			else;
		}
		else
			mtx_unlock(xGLock.Qu);
	}
	else;

	return thrd_error;
}
static int ThrP_Qu_Push_(thrp_qu *const *const Ptr,THRP_P_ Proc_,const size_t Copy,const void *const restrict Arg)
{
	xThrP_Qu_Init_();

	if(Proc_)
	{
		const size_t Size=xThrP_Padding_(Copy);
		const size_t Pack=Size+sizeof(thrp_tp);

		if(Size<Copy);
		else if(Pack<Size);
		else if(mtx_lock(xGLock.Qu)==thrd_success)
		{
			thrp_qu *const Qu=*Ptr;

			if(Qu)
			{
				const int Flag=(Pack>(Qu->Capacity))?(thrd_nomem):(xThrP_Qu_Attach_(Qu,Proc_,Arg,Copy,Size,Pack));

				return xThrP_Flag_(Flag,mtx_unlock(xGLock.Qu));
			}
			else
				mtx_unlock(xGLock.Qu);
		}
		else;
	}
	else;

	return thrd_error;
}
#endif

#if(1)
static int ThrP_Qu_Create_(THRP_UM *const restrict UM,void *const Owner,thrp_qu **const Ptr,const size_t Space)
{
	xThrP_Qu_Init_();

	if((Ptr)&&(UM)&&(UM->Return_)&&(UM->Borrow_))
	{
		const size_t Size=xThrP_Padding_(Space);

		if(Size<sizeof(thrp_qu));
		else if(Size<Space);
		else if(mtx_lock(xGLock.Qu)==thrd_success)
			if(*Ptr)
				goto UNLOCK;
			else
			{
				thrp_qu *const Qu=UM->Borrow_(Owner,_Alignof(max_align_t),Size);

				if(Qu)
					if(mtx_init(&(Qu->Lock),mtx_plain)==thrd_success)
						if(mtx_init(&(Qu->Wait),mtx_plain)==thrd_success)
						{
							Qu->Free_=UM->Return_;
							Qu->Alloc_=UM->Borrow_;
							Qu->Capacity=Size-sizeof(thrp_qu);

							xThrP_Qu_Reset_(*Ptr=Qu);

							return mtx_unlock(xGLock.Qu);
						}
						else
							goto KILL_LOCK;
					else
						goto KILL_THIS;
				else
					goto UNLOCK;

KILL_LOCK:		mtx_destroy(&(Qu->Lock));
KILL_THIS:		UM->Return_(Qu);
UNLOCK:			mtx_unlock(xGLock.Qu);
			}
		else;
	}
	else;

	return thrd_error;
}
static int ThrP_Qu_Delete_(thrp_qu **const Ptr)
{
	xThrP_Qu_Init_();

	if(mtx_lock(xGLock.Qu)==thrd_success)
	{
		thrp_qu *const Qu=*Ptr;

		if(Qu)
		{
			mtx_t *const Lock=&(Qu->Lock),*const Wait=&(Qu->Wait);
			const int Flag=(xThrP_Exist_Thread_(Qu->Thread))?((xThrP_Qu_Join_(Qu)==thrd_success)?(thrd_busy):(thrd_error)):(thrd_success);

			mtx_destroy(Wait);
			mtx_destroy(Lock);
			Qu->Free_(Qu);
			*Ptr=NULL;

			return xThrP_Flag_(Flag,mtx_unlock(xGLock.Qu));
		}
		else
			mtx_unlock(xGLock.Qu);
	}
	else;

	return thrd_error;
}
#endif

#endif

#if(1)
struct othrp_mu
{
	_Alignas(max_align_t) struct
	{
		void(*Free_)(void *const);
		mtx_t Tex;
	};
};

#if(1)
static void xThrP_Mu_Exit_Once_(void) { mtx_destroy(xGLock.Mu);return; }
static void xThrP_Mu_Exit_(void) { static once_flag xFlagExit=ONCE_FLAG_INIT;call_once(&xFlagExit,xThrP_Mu_Exit_Once_);return; }
static void xThrP_Mu_Init_Once_(void)
{
	int Flag=mtx_init(xGLock.Mu,mtx_plain);

	if(Flag==thrd_success)
		Flag=atexit(xThrP_Mu_Exit_);
	else
		exit(Flag);

	if(Flag)
		exit(Flag);
	else
		return;
}
static void xThrP_Mu_Init_(void) { static once_flag xFlagInit=ONCE_FLAG_INIT;call_once(&xFlagInit,xThrP_Mu_Init_Once_);return; }
#endif

#if(1)
static int ThrP_Mu_Take_(thrp_mu *const *const Ptr,const _Bool Wait)
{
	xThrP_Mu_Init_();

	if(mtx_lock(xGLock.Mu)==thrd_success)
	{
		thrp_mu *const Mu=*Ptr;

		if(Mu)
		{
			mtx_t *const Mutex=&(Mu->Tex);
			int Flag=mtx_trylock(Mutex);

			if(mtx_unlock(xGLock.Mu)==thrd_success)
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
			mtx_unlock(xGLock.Mu);
	}
	else;

	return thrd_error;
}
static int ThrP_Mu_Give_(thrp_mu *const *const Ptr,const _Bool Wait)
{
	xThrP_Mu_Init_();

	if(mtx_lock(xGLock.Mu)==thrd_success)
	{
		thrp_mu *const Mu=*Ptr;

		if(Mu)
		{
			mtx_t *const Mutex=&(Mu->Tex);
			int Flag=mtx_trylock(Mutex);

			if(mtx_unlock(xGLock.Mu)==thrd_success)
				switch(Flag)
				{
				case thrd_busy:
					if(Wait)
						if((Flag=mtx_lock(Mutex))==thrd_success)
						{
							//[[fallthrough]];
				case thrd_success:
							Flag=mtx_unlock(Mutex);
						}
						else;
					else
						Flag=xThrP_Flag_(Flag,mtx_unlock(Mutex));
					//[[fallthrough]];
				default:
					return Flag;
				}
			else if(Flag==thrd_success)
				mtx_unlock(Mutex);
			else;
		}
		else
			mtx_unlock(xGLock.Mu);
	}
	else;

	return thrd_error;
}
#endif

#if(1)
static int ThrP_Mu_Create_(THRP_UM *const restrict UM,void *const Owner,thrp_mu **const Ptr)
{
	xThrP_Mu_Init_();

	if((Ptr)&&(UM)&&(UM->Return_)&&(UM->Borrow_))
		if(mtx_lock(xGLock.Mu)==thrd_success)
			if(*Ptr)
				goto UNLOCK;
			else
			{
				thrp_mu *const Mu=UM->Borrow_(Owner,_Alignof(max_align_t),sizeof(thrp_mu));

				if(Mu)
					if(mtx_init(&(Mu->Tex),mtx_plain)==thrd_success)
					{
						(*Ptr=Mu)->Free_=UM->Return_;

						return mtx_unlock(xGLock.Mu);
					}
					else
						goto KILL_THIS;
				else
					goto UNLOCK;

KILL_THIS:		UM->Return_(Mu);
UNLOCK:			mtx_unlock(xGLock.Mu);
			}
		else;
	else;

	return thrd_error;
}
static int ThrP_Mu_Delete_(thrp_mu **const Ptr)
{
	xThrP_Mu_Init_();

	if(mtx_lock(xGLock.Mu)==thrd_success)
	{
		thrp_mu *const Mu=*Ptr;

		if(Mu)
		{
			mtx_t *const Mutex=&(Mu->Tex);
			const int Flag=mtx_trylock(Mutex);

			switch(Flag)
			{
			case thrd_busy:
				if(mtx_unlock(xGLock.Mu)==thrd_success);else break;
				if(mtx_lock(Mutex)==thrd_success);else break;
				if(mtx_lock(xGLock.Mu)==thrd_success)
				{
					//[[fallthrough]];
			case thrd_success:
					if(mtx_unlock(Mutex)==thrd_success)
					{
						mtx_destroy(Mutex);
						Mu->Free_(Mu);
						*Ptr=NULL;

						return xThrP_Flag_(Flag,mtx_unlock(xGLock.Mu));
					}
					else
					{
						//[[fallthrough]];
			default:	mtx_unlock(xGLock.Mu);
					}
				}
				else
					mtx_unlock(Mutex);
			}
		}
		else
			mtx_unlock(xGLock.Mu);
	}
	else;

	return thrd_error;
}
#endif

#endif

#if(1)
static _Bool xThrP_Thread_Okay_(int Time)
{
	if(Time<0)
		return false;
	else
	{
		const int Kilo=+1000;
		const time_t Cast=(time_t)(Time/=Kilo);
		const int Back=(int)(Cast);

		return (Back==Time);
	}
}
static struct timespec xThrP_Thread_Time_(register const int T)
{
	const int K=+1000;
	const long M=+1000000L;

	return (struct timespec) { .tv_sec=(time_t)(T/K),.tv_nsec=M*(long)(T%K) };
}
static _Bool ThrP_Thread_Sleep_(const void *const Arg)
{
	const int Time=*((const int*)(Arg));

	if(xThrP_Thread_Okay_(Time))
		for(struct timespec Remain,Holder=xThrP_Thread_Time_(Time);1;Holder=Remain)
			switch(thrd_sleep(&Holder,&Remain))
			{
			case 0:
				return true;
			case-1:
				if(Remain.tv_sec<0);
				else if(Holder.tv_sec<Remain.tv_sec);
				else if(Holder.tv_sec>Remain.tv_sec)
					break;
				else if(Holder.tv_nsec<Remain.tv_nsec);
				else
					break;
				//[[fallthrough]];
			default:
				return false;
			}
	else
		return false;
}
static _Bool ThrP_Thread_Yield_(const void *const Arg) { (void)(Arg);thrd_yield();return true; }
static _Bool ThrP_Thread_Break_(const void *const Arg) { (void)(Arg);return false; }
static _Bool ThrP_Thread_Print_(const void *const Arg) { return (puts(Arg)>=0); }
#endif

_Static_assert(sizeof(THRPACK)==(sizeof(THRPACE)<<4),"sizeof(THRPACK) != 16*sizeof(THRPACE)");
extern THRPACK ThrP=
{
	{
		.Version=xPost.Version,
		.Signal=&(xPost.Signal),
		.Flag=&(xPost.Flag),
		.UM=&(xPost.Handle)
	},
	.Task=
	{
		.Yield_=ThrP_Thread_Yield_,
		.Break_=ThrP_Thread_Break_,
		.Sleep_=ThrP_Thread_Sleep_,
		.Print_=ThrP_Thread_Print_
	},
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
	}
};
extern THRPACK *ThrP_(void) { return &ThrP; }
