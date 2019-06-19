/*------------------------------------------------------------------*/
/*	ThrPure provides some simple thread managing functions.			*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Pures/					2019.06.19	*/
/*------------------------------------------------------------------*/

#ifndef _INC_THRPURE
#define _INC_THRPURE

#include <stddef.h>

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
	const struct
	{
		//ThrPure : Task Queue Memory Allocation - Deallocate with "ThrP.Qu.Delete_".
		thrp_qu*(*const Create_)(const size_t MemorySize);
		//ThrPure : Task Queue Memory Deallocation
		//＊Calling is only allowed in the creator thread.
		//＊Return value is defined under "ThrP.Flag".
		int(*const Delete_)(thrp_qu **const);

		//ThrPure : Push a task into the task queue.
		//＊Calling is only allowed in the creator thread.
		//＊Data at (ArgAddress) will be captured temporarily by (ArgSize) bytes.
		//＊Return value is defined under "ThrP.Flag".
		int(*const Push_)(thrp_qu *const,THRP_P_,const void *const ArgAddress,const size_t ArgSize);
		//ThrPure : Wait the task queue until its current thread terminates.
		//＊Calling is only allowed in the creator thread.
		//＊Return value is defined under "ThrP.Flag".
		int(*const Wait_)(thrp_qu *const);
	}
	Qu;

	//ThrPure : Mutex Functions
	const struct
	{
		//ThrPure : Mutex Memory Allocation - Deallocate with "ThrP.Mu.Delete_".
		thrp_mu*(*const Create_)(void);
		//ThrPure : Mutex Memory Deallocation
		//＊All dependencies around the mutex must be released before the deletion of it.
		//＊Return value is defined under "ThrP.Flag".
		int(*const Delete_)(thrp_mu **const);

		//ThrPure : Lock the Mutex
		//＊Return value is defined under "ThrP.Flag".
		int(*const Take_)(thrp_mu *const);
		//ThrPure : Unlock the Mutex
		//＊Return value is defined under "ThrP.Flag".
		int(*const Give_)(thrp_mu *const);
	}
	Mu;

	//ThrPure : Task Functions
	const struct
	{
		//ThrPure : Sleep the calling thread.
		//＊Return value is defined under "ThrP.Signal".
		_Bool(*const Sleep_)(const int *const Milliseconds);
		//ThrPure : Yield the calling thread.
		//＊Input value will be just ignored.
		//＊Return value is defined under "ThrP.Signal".
		_Bool(*const Yield_)(const void *const);
	}
	Task;

	//ThrPure : Library Version - "Date:yyyy.mm.dd"
	const char *const Version;

	//ThrPure : Thread Error Status
	//＊They are possible return values of some "ThrP.Qu" functions.
	const struct
	{
		const int Success;	//ThrPure : Successful
		const int TimedOut;	//ThrPure : Timed Out
		const int Busy;		//ThrPure : Temporary Unavailable Resource
		const int NoMem;	//ThrPure : Out of Memory Condition
		const int Error;	//ThrPure : Unknown
	}
	Flag;

	//ThrPure : Process Return Signal
	//＊They are allowed return values of "thrp_p_" or "THRP_P_" type functions.
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
