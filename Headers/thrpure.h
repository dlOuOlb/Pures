#ifndef _INC_THRPURE
#define _INC_THRPURE "ThrP:2019.12.12"
/*------------------------------------------------------------------+
|	ThrPure provides some simple thread managing functions.			|
|																	|
|	Written by Ranny Clover											|
|	http://github.com/dlOuOlb/Pures/								|
+-------------------------------------------------------------------+
|	[!] Non-Standard Assumptions:									|
|																	|
|	- All data pointers have the same size, a power of 2.			|
|	- All function pointers have the same size, a power of 2.		|
+-------------------------------------------------------------------+
|	[+] Pre-Header Definitions:										|
|																	|
|	#define _PURES_DLL_IMPORT_ __declspec(dllimport)				|
|	#define _THRP_MACRO_DEFINE_										|
+------------------------------------------------------------------*/

#include <stddef.h>

//ThrPure : Process Function Pointer
typedef _Bool(*thrp_p_)(const void *const);typedef const thrp_p_ THRP_P_;

//ThrPure : Task Queue
typedef struct _thrp_qu thrp_qu;typedef const thrp_qu THRP_QU;

//ThrPure : Mutex Holder
typedef struct _thrp_mu thrp_mu;typedef const thrp_mu THRP_MU;

//ThrPure : Library Alignment Union
typedef const union { const void *const D;void(*const F_)(void); }THRPACE;

//ThrPure : Library Pack Structure
typedef const struct
#define _ThrP_Align_(N) _Alignas((N)*sizeof(THRPACE))
{
	_ThrP_Align_(4) const struct
	{
		//ThrPure : Library Version - "ThrP:yyyy.mm.dd"
		_ThrP_Align_(1) const char *const restrict Version;

		//ThrPure : Process Return Signal
		//＊They are allowed return values of "thrp_p_" and "THRP_P_" type functions.
		_ThrP_Align_(1) const struct _thrpack_signal
		{
			const _Bool Continue;	//ThrPure : (1) Continue the task queue.
			const _Bool Break;		//ThrPure : (0) Break the task queue.
		}
		*const restrict Signal;

		//ThrPure : Error Numbers
		//＊They are known return values of "ThrP.Qu", "ThrP.Mu", and "ThrP.Event" functions.
		//＊When an error has occurred, terminate the program as soon as possible,
		//　since corrupted states of multi-threads are extremely hard to resolve.
		_ThrP_Align_(1) const struct _thrpack_flag
		{
			const int Success;	//ThrPure : Successful.
			const int TimedOut;	//ThrPure : Timed out.
			const int Busy;		//ThrPure : Temporary unavailable resource.
			const int NoMem;	//ThrPure : Out of memory condition.
			const int Error;	//ThrPure : Unknown error.
		}
		*const restrict Flag;

		//ThrPure : Event Functions
		//＊Return value is defined under "ThrP.Flag".
		_ThrP_Align_(1) const struct _thrpack_event
		{
			//ThrPure : Invoke an event.
			//＊Data at (ArgAddress) will be captured temporarily by (ArgSize) bytes.
			//＊The callee must return, not exit.
			_ThrP_Align_(1) int(*const Invoke_)(THRP_P_,const size_t ArgSize,const void *const ArgAddress);
		}
		Event;
	};

	//ThrPure : Task Functions
	_ThrP_Align_(4) const struct _thrpack_task
	{
		//ThrPure : Sleep the calling thread.
		//＊Argument's Type
		//　const int *const Milliseconds
		//＊Return value is defined under "ThrP.Signal".
		_ThrP_Align_(1) _Bool(*const Sleep_)(const void *const Milliseconds);
		//ThrPure : Yield the calling thread.
		//＊Input pointer is just ignored.
		//＊Return value is always "ThrP.Signal->Continue".
		_ThrP_Align_(1) _Bool(*const Yield_)(const void *const);
		//ThrPure : Return a break signal.
		//＊Input pointer is just ignored.
		//＊Return value is always "ThrP.Signal->Break".
		_ThrP_Align_(1) _Bool(*const Break_)(const void *const);
		//ThrPure : Print a message.
		//＊Argument's Type
		//　const char *const Message
		//＊Return value is defined under "ThrP.Signal".
		_ThrP_Align_(1) _Bool(*const Print_)(const void *const Message);
	}
	Task;

	//ThrPure : Task Queue Functions
	//＊This function set has its global mutex internally.
	//＊Return value is defined under "ThrP.Flag".
	_ThrP_Align_(4) const struct _thrpack_qu
	{
		//ThrPure : Task Queue Memory Allocation - Deallocate with "ThrP.Qu.Delete_".
		//＊Reference place should be initialized as NULL.
		_ThrP_Align_(1) int(*const Create_)(thrp_qu **const,const size_t MemorySize);
		//ThrPure : Task Queue Memory Deallocation
		//＊If "ThrP.Qu.Wait_" is not called properly before calling of this,
		//　then "ThrP.Flag->Busy" might be returned,
		//　though the memory is deallocated anyway.
		_ThrP_Align_(1) int(*const Delete_)(thrp_qu **const);

		//ThrPure : Push a task into the task queue.
		//＊Data at (ArgAddress) will be captured temporarily by (ArgSize) bytes.
		//＊If there is not enough space to capture the task,
		//　then this would wait for the queue to be emptied,
		//　as long as the task's size is acceptable.
		//＊The callee must return, not exit.
		_ThrP_Align_(1) int(*const Push_)(thrp_qu *const *const,THRP_P_,const size_t ArgSize,const void *const ArgAddress);
		//ThrPure : Wait the task queue and terminate the worker thread.
		//＊This should be called before "ThrP.Qu.Delete_" is called.
		_ThrP_Align_(1) int(*const Wait_)(thrp_qu *const *const);
	}
	Qu;

	//ThrPure : Mutex Functions
	//＊This function set has its global mutex internally.
	//＊Return value is defined under "ThrP.Flag".
	_ThrP_Align_(4) const struct _thrpack_mu
	{
		//ThrPure : Mutex Memory Allocation - Deallocate with "ThrP.Mu.Delete_".
		//＊Reference place should be initialized as NULL.
		_ThrP_Align_(1) int(*const Create_)(thrp_mu **const);
		//ThrPure : Mutex Memory Deallocation
		//＊All dependencies around the mutex must be released before deletion of it.
		_ThrP_Align_(1) int(*const Delete_)(thrp_mu **const);

		//ThrPure : Lock the Mutex
		//＊If (Wait) equals to 0,
		//　then this could intrude into the earlier locking,
		//　else this would wait for the earlier locking to be unlocked.
		//＊If an intrusion is occurred,
		//　then "ThrP.Flag->Busy" might be returned.
		_ThrP_Align_(1) int(*const Take_)(thrp_mu *const *const,const _Bool Wait);
		//ThrPure : Unlock the Mutex
		//＊If (Wait) equals to 0,
		//　then this could unlock the earlier locking,
		//　else this would wait for the earlier locking to be unlocked.
		//＊If an earlier locking exists and is unlocked without waiting,
		//　then "ThrP.Flag->Busy" might be returned.
		_ThrP_Align_(1) int(*const Give_)(thrp_mu *const *const,const _Bool Wait);
	}
	Mu;
}
#undef _ThrP_Align_
THRPACK;

#ifdef _PURES_DLL_IMPORT_
_PURES_DLL_IMPORT_
#endif

//ThrPure : Library Pack Object
extern _Alignas(THRPACK) THRPACK ThrP;
//ThrPure : Indirect access to the library pack object. (&ThrP)
extern THRPACK *ThrP_(void);

#ifdef _THRP_MACRO_DEFINE_
//ThrPure : Abbreviation of "ThrP.Event.Invoke_" with an instant argument.
#define ThrP_Event_Invoke_(Event_,TYPE,...) ThrP.Event.Invoke_(Event_,sizeof(TYPE),&(TYPE){__VA_ARGS__})
//ThrPure : Abbreviation of "ThrP.Qu.Push_" with an instant argument.
#define ThrP_Qu_Push_(Queue,Proc_,TYPE,...) ThrP.Qu.Push_(Queue,Proc_,sizeof(TYPE),&(TYPE){__VA_ARGS__})
//ThrPure : Abbreviation of a once-loop over "ThrP.Mu.Take_" and "ThrP.Mu.Give_".
//＊Do not jump over the loop block, e.g. 'goto', 'break', and 'return'.
#define ThrP_Mu_Lock_Do_(Ret,Mutex) for(_Bool(_##Ret)=(((Ret)=ThrP.Mu.Take_(Mutex,1))==ThrP.Flag->Success);_##Ret;(Ret)=(ThrP.Mu.Give_(Mutex,(_##Ret)=0)==(ThrP.Flag->Busy))?(ThrP.Flag->Success):(ThrP.Flag->Error))
#endif

#endif
