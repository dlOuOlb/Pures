/*------------------------------------------------------------------*/
/*	ThrPure provides some simple thread managing functions.			*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Pures/					2019.07.09	*/
/*------------------------------------------------------------------*/

#ifndef _INC_THRPURE
#define _INC_THRPURE

#include <stddef.h>

typedef void(*thrp_e_)(const void *const);			//ThrPure : Event Variable
typedef void(*const THRP_E_)(const void *const);	//ThrPure : Event Constant

typedef _Bool(*thrp_p_)(const void *const);			//ThrPure : Task Process Variable
typedef _Bool(*const THRP_P_)(const void *const);	//ThrPure : Task Process Constant

typedef struct _thrp_qu thrp_qu;		//ThrPure : Task Queue Variable
typedef const struct _thrp_qu THRP_QU;	//ThrPure : Task Queue Constant

typedef struct _thrp_mu thrp_mu;		//ThrPure : Mutex Variable
typedef const struct _thrp_mu THRP_MU;	//ThrPure : Mutex Constant

//ThrPure : Library Pack Structure
struct _thrpack
{
	//ThrPure : Task Queue Functions
	//＊This function set has its global mutex internally.
	//＊Return value is defined under "ThrP.Flag".
	const struct
	{
		//ThrPure : Task Queue Memory Allocation - Deallocate with "ThrP.Qu.Delete_".
		//＊Reference place should be initialized as NULL.
		int(*const Create_)(thrp_qu **const,const size_t MemorySize);
		//ThrPure : Task Queue Memory Deallocation
		//＊If "ThrP.Qu.Wait_" is not called properly before calling of this,
		//　then "ThrP.Flag.Busy" might be returned.
		int(*const Delete_)(thrp_qu **const);

		//ThrPure : Push a task into the task queue.
		//＊Data at (ArgAddress) will be captured temporarily by (ArgSize) bytes.
		//＊If there is not enough space to capture the task,
		//　then this would wait for the queue to be emptied,
		//　as long as the task's size is acceptable.
		//＊The callee must return, not exit.
		int(*const Push_)(thrp_qu *const *const,THRP_P_,const void *const restrict ArgAddress,const size_t ArgSize);
		//ThrPure : Wait the task queue and terminate the worker thread.
		//＊This should be called before "ThrP.Qu.Delete_" is called.
		int(*const Wait_)(thrp_qu *const *const);
	}
	Qu;

	//ThrPure : Mutex Functions
	//＊This function set has its global mutex internally.
	//＊Return value is defined under "ThrP.Flag".
	const struct
	{
		//ThrPure : Mutex Memory Allocation - Deallocate with "ThrP.Mu.Delete_".
		//＊Reference place should be initialized as NULL.
		int(*const Create_)(thrp_mu **const);
		//ThrPure : Mutex Memory Deallocation
		//＊All dependencies around the mutex must be released before deletion of it.
		int(*const Delete_)(thrp_mu **const);

		//ThrPure : Lock the Mutex
		//＊If (Wait) equals to 0,
		//　then this could intrude into the earlier locking,
		//　else this would wait for the earlier locking to be unlocked.
		//＊If an intrusion is occurred,
		//　then "ThrP.Flag.Busy" might be returned.
		int(*const Take_)(thrp_mu *const *const,const _Bool Wait);
		//ThrPure : Unlock the Mutex
		//＊If (Wait) equals to 0,
		//　then this could unlock the earlier locking,
		//　else this would wait for the earlier locking to be unlocked.
		//＊If an earlier locking exists and is unlocked without waiting,
		//　then "ThrP.Flag.Busy" might be returned.
		int(*const Give_)(thrp_mu *const *const,const _Bool Wait);
	}
	Mu;

	//ThrPure : Task Functions
	//＊Return value is defined under "ThrP.Signal".
	const struct
	{
		//ThrPure : Sleep the calling thread.
		_Bool(*const Sleep_)(const int *const restrict Milliseconds);
		//ThrPure : Yield the calling thread.
		//＊Input value will be just ignored.
		//＊Return value will always be "ThrP.Signal.Continue".
		_Bool(*const Yield_)(const void *const);
		//ThrPure : Return a break signal.
		//＊Input value will be just ignored.
		//＊Return value will always be "ThrP.Signal.Break".
		_Bool(*const Break_)(const void *const);
		//ThrPure : Print a message.
		//＊Input value must be a null-terminated character sequence.
		_Bool(*const Print_)(const char *const restrict Message);
	}
	Task;

	//ThrPure : Event Functions
	//＊Return value is defined under "ThrP.Flag".
	const struct
	{
		//ThrPure : Invoke an event.
		//＊Data at (ArgAddress) will be captured temporarily by (ArgSize) bytes.
		//＊The callee must return, not exit.
		int(*const Invoke_)(THRP_E_,const void *const restrict ArgAddress,const size_t ArgSize);
	}
	Event;

	//ThrPure : Library Version - "Date:yyyy.mm.dd"
	const char *const Version;

	//ThrPure : Thread Error Status
	//＊They are known return values of "ThrP.Qu", "ThrP.Mu", and "ThrP.Event" functions.
	//＊When an error has occurred, terminate the program as soon as possible,
	//　since corrupted states of multi-threads are extremely hard to resolve.
	const struct
	{
		const int Success;	//ThrPure : Successful.
		const int TimedOut;	//ThrPure : Timed out.
		const int Busy;		//ThrPure : Temporary unavailable resource.
		const int NoMem;	//ThrPure : Out of memory condition.
		const int Error;	//ThrPure : Unknown error.
	}
	Flag;

	//ThrPure : Process Return Signal
	//＊They are allowed return values of "thrp_p_" and "THRP_P_" type functions.
	const struct
	{
		const _Bool Continue;	//ThrPure : Continue the task queue. (Success)
		const _Bool Break;		//ThrPure : Break the task queue. (Failure)
	}
	Signal;
};
typedef struct _thrpack thrpack;		//ThrPure : Library Pack Variable (Prohibited)
typedef const struct _thrpack THRPACK;	//ThrPure : Library Pack Constant

//ThrPure : Library Pack Object
extern THRPACK ThrP;
//ThrPure : Indirect access to the library pack object.
extern THRPACK *ThrP_(void);
#endif
