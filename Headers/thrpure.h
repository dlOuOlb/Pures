#ifndef _INC_THRPURE
#define _INC_THRPURE "ThrP:2019.11.29"
/*------------------------------------------------------------------*/
/*	ThrPure provides some simple thread managing functions.			*/
/*																	*/
/*	Written by Ranny Clover											*/
/*	http://github.com/dlOuOlb/Pures/								*/
/*------------------------------------------------------------------*/
/*	[!] Non-Standard Assumptions:									*/
/*																	*/
/*	- All data pointers have the same size, a power of 2.			*/
/*	- All function pointers have the same size, a power of 2.		*/
/*------------------------------------------------------------------*/
/*	DLL IMPORT EXAMPLE:												*/
/*																	*/
/*	#define _PURES_DLL_IMPORT_ __declspec(dllimport)				*/
/*	#include <thrpure.h>											*/
/*------------------------------------------------------------------*/

#include <stddef.h>

typedef void(*thrp_e_)(const void *const);	//ThrPure : Event Variable
typedef const thrp_e_ THRP_E_;				//ThrPure : Event Constant

typedef _Bool(*thrp_p_)(const void *const);	//ThrPure : Process Variable
typedef const thrp_p_ THRP_P_;				//ThrPure : Process Constant

typedef struct _thrp_qu thrp_qu;	//ThrPure : Task Queue Variable
typedef const thrp_qu THRP_QU;		//ThrPure : Task Queue Constant

typedef struct _thrp_mu thrp_mu;	//ThrPure : Mutex Variable
typedef const thrp_mu THRP_MU;		//ThrPure : Mutex Constant

//ThrPure : Union for Library Alignment
typedef const union { const void *const D;void(*const F_)(void); }THRPACE;

//ThrPure : Library Pack Structure
typedef const struct
#define _ThrP_Align_(N) _Alignas((N)*sizeof(THRPACE))
{
	_ThrP_Align_(4) const struct
	{
		//ThrPure : Library Version - "ThrP:yyyy.mm.dd"
		_ThrP_Align_(1) const char *const Version;

		//ThrPure : Process Return Signal
		//＊They are allowed return values of "thrp_p_" and "THRP_P_" type functions.
		_ThrP_Align_(1) const struct _thrp_b2
		{
			const _Bool Continue;	//ThrPure : Continue the task queue. (Success)
			const _Bool Break;		//ThrPure : Break the task queue. (Failure)
		}
		*const Signal;

		//ThrPure : Error Numbers
		//＊They are known return values of "ThrP.Qu", "ThrP.Mu", and "ThrP.Event" functions.
		//＊When an error has occurred, terminate the program as soon as possible,
		//　since corrupted states of multi-threads are extremely hard to resolve.
		_ThrP_Align_(1) const struct _thrp_en
		{
			const int Success;	//ThrPure : Successful.
			const int TimedOut;	//ThrPure : Timed out.
			const int Busy;		//ThrPure : Temporary unavailable resource.
			const int NoMem;	//ThrPure : Out of memory condition.
			const int Error;	//ThrPure : Unknown error.
		}
		*const Flag;

		//ThrPure : Event Functions
		//＊Return value is defined under "ThrP.Flag".
		_ThrP_Align_(1) const struct
		{
			//ThrPure : Invoke an event.
			//＊Data at (ArgAddress) will be captured temporarily by (ArgSize) bytes.
			//＊The callee must return, not exit.
			_ThrP_Align_(1) int(*const Invoke_)(THRP_E_,const void *const ArgAddress,const size_t ArgSize);
		}
		Event;
	};

	//ThrPure : Task Queue Functions
	//＊This function set has its global mutex internally.
	//＊Return value is defined under "ThrP.Flag".
	_ThrP_Align_(4) const struct
	{
		//ThrPure : Task Queue Memory Allocation - Deallocate with "ThrP.Qu.Delete_".
		//＊Reference place should be initialized as NULL.
		_ThrP_Align_(1) int(*const Create_)(thrp_qu **const,const size_t MemorySize);
		//ThrPure : Task Queue Memory Deallocation
		//＊If "ThrP.Qu.Wait_" is not called properly before calling of this,
		//　then "ThrP.Flag->Busy" might be returned.
		_ThrP_Align_(1) int(*const Delete_)(thrp_qu **const);

		//ThrPure : Push a task into the task queue.
		//＊Data at (ArgAddress) will be captured temporarily by (ArgSize) bytes.
		//＊If there is not enough space to capture the task,
		//　then this would wait for the queue to be emptied,
		//　as long as the task's size is acceptable.
		//＊The callee must return, not exit.
		_ThrP_Align_(1) int(*const Push_)(thrp_qu *const *const,THRP_P_,const void *const ArgAddress,const size_t ArgSize);
		//ThrPure : Wait the task queue and terminate the worker thread.
		//＊This should be called before "ThrP.Qu.Delete_" is called.
		_ThrP_Align_(1) int(*const Wait_)(thrp_qu *const *const);
	}
	Qu;

	//ThrPure : Mutex Functions
	//＊This function set has its global mutex internally.
	//＊Return value is defined under "ThrP.Flag".
	_ThrP_Align_(4) const struct
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

	//ThrPure : Task Functions
	_ThrP_Align_(4) const struct
	{
		//ThrPure : Sleep the calling thread.
		//＊Argument's Type
		//　const int *const Milliseconds
		//＊Return value is defined under "ThrP.Signal".
		_ThrP_Align_(1) _Bool(*const Sleep_)(const void *const Milliseconds);
		//ThrPure : Yield the calling thread.
		//＊Input pointer will be just ignored.
		//＊Return value is always "ThrP.Signal->Continue".
		_ThrP_Align_(1) _Bool(*const Yield_)(const void *const);
		//ThrPure : Return a break signal.
		//＊Input pointer will be just ignored.
		//＊Return value is always "ThrP.Signal->Break".
		_ThrP_Align_(1) _Bool(*const Break_)(const void *const);
		//ThrPure : Print a message.
		//＊Argument's Type
		//　const char *const Message
		//＊Return value is defined under "ThrP.Signal".
		_ThrP_Align_(1) _Bool(*const Print_)(const void *const Message);
	}
	Task;
}
#undef _ThrP_Align_
THRPACK;

#ifdef _PURES_DLL_IMPORT_
_PURES_DLL_IMPORT_
#endif

//ThrPure : Library Pack Object
extern _Alignas(sizeof(THRPACE)<<4) THRPACK ThrP;
//ThrPure : Indirect access to the library pack object.
extern THRPACK *ThrP_(void);
#endif
