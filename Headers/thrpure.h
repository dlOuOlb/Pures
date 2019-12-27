#ifndef oTHRPURE_INC
#define oTHRPURE_INC "ThrP:2019.12.27"
/*------------------------------------------------------------------+
|	ThrPure provides some simple thread managing functions.			|
|																	|
|	Written by Ranny Clover											|
|	http://github.com/dlOuOlb/Pures/blob/master/Headers/thrpure.h	|
+-------------------------------------------------------------------+
|	[!] Non-Standard Assumptions:									|
|																	|
|	- All data pointers have the same size, a power of 2.			|
|	- All function pointers have the same size, a power of 2.		|
+-------------------------------------------------------------------+
|	[+] Optional Pre-Header Definitions:							|
|																	|
|	#define uPURES_DLL_IMPORT_ __declspec(dllimport)				|
|	#define uTHRP_MACRO_DEFINE_										|
+------------------------------------------------------------------*/

#include <stddef.h>

//ThrPure : User-Provided Memory Handler
typedef struct { void(*Return_)(void *const Memory),*(*Borrow_)(void *const Owner,const size_t Align,const size_t Size); }thrp_um;typedef const thrp_um THRP_UM;

//ThrPure : Process Function Pointer
typedef _Bool(*thrp_p_)(const void *const Arg);typedef const thrp_p_ THRP_P_;

//ThrPure : Task Queue
typedef struct othrp_qu thrp_qu;typedef const thrp_qu THRP_QU;

//ThrPure : Mutex Holder
typedef struct othrp_mu thrp_mu;typedef const thrp_mu THRP_MU;

//ThrPure : Library Alignment Union
typedef const union { const size_t S;const void *const X;void(*const X_)(void); }THRPACE;

//ThrPure : Library Pack Structure
typedef const struct
#define xThrP_Align_(N) _Alignas((N)*sizeof(THRPACE))
{
	//ThrPure : Pointers to Some Constants
	xThrP_Align_(4) const struct
	{
		//ThrPure : Library Version - "ThrP:yyyy.mm.dd"
		xThrP_Align_(1) const char *const restrict Version;

		//ThrPure : Process Return Signal
		//＊They are allowed return values of "thrp_p_" and "THRP_P_" type functions.
		xThrP_Align_(1) const struct othrpack_signal
		{
			const _Bool Continue;	//ThrPure : (1) Continue the task queue.
			const _Bool Break;		//ThrPure : (0) Break the task queue.
		}
		*const restrict Signal;

		//ThrPure : Error Numbers
		//＊They are known return values of "ThrP.Qu", "ThrP.Mu", and "ThrP.Event" functions.
		//＊When an error has occurred, terminate the program as soon as possible,
		//　since corrupted states of multi-threads are extremely hard to resolve.
		xThrP_Align_(1) const struct othrpack_flag
		{
			const int Success;	//ThrPure : Successful.
			const int TimedOut;	//ThrPure : Timed out.
			const int Busy;		//ThrPure : Temporary unavailable resource.
			const int NoMem;	//ThrPure : Out of memory condition.
			const int Error;	//ThrPure : Unknown error.
		}
		*const restrict Flag;

		//ThrPure : Default Memory Handler
		//＊Each calls "free" and "aligned_alloc", ignoring (Owner).
		xThrP_Align_(1) THRP_UM *const restrict UM;
	};

	//ThrPure : Task Functions
	xThrP_Align_(4) const struct othrpack_task
	{
		//ThrPure : Yield the calling thread.
		//＊Input pointer is just ignored.
		//＊Return value is always "ThrP.Signal->Continue".
		xThrP_Align_(1) THRP_P_ Yield_;
		//ThrPure : Return a break signal.
		//＊Input pointer is just ignored.
		//＊Return value is always "ThrP.Signal->Break".
		xThrP_Align_(1) THRP_P_ Break_;
		//ThrPure : Sleep the calling thread.
		//＊Argument's Type
		//　const int *const Milliseconds
		//＊Return value is defined under "ThrP.Signal".
		xThrP_Align_(1) THRP_P_ Sleep_;
		//ThrPure : Print a message.
		//＊Argument's Type
		//　const char *const Message
		//＊Return value is defined under "ThrP.Signal".
		xThrP_Align_(1) THRP_P_ Print_;
	}
	Task;

	//ThrPure : Task Queue Functions
	//＊This function set has its global mutex internally.
	//＊Return value is defined under "ThrP.Flag".
	xThrP_Align_(4) const struct othrpack_qu
	{
		//ThrPure : Task Queue Memory Allocation - Deallocate with "ThrP.Qu.Delete_".
		//＊A default memory handler is defined under "ThrP.UM".
		//＊Reference place should be initialized as NULL.
		xThrP_Align_(1) /*[[nodiscard]]*/ int(*const Create_)(THRP_UM *const restrict,void *const Owner,thrp_qu **const,const size_t MemorySize);
		//ThrPure : Task Queue Memory Deallocation
		//＊If "ThrP.Qu.Wait_" is not called properly before calling of this,
		//　then "ThrP.Flag->Busy" might be returned,
		//　though the memory is deallocated anyway.
		xThrP_Align_(1) /*[[nodiscard]]*/ int(*const Delete_)(thrp_qu **const);

		//ThrPure : Push a task into the task queue.
		//＊Data at (ArgAddress) are captured temporarily by (ArgSize) bytes.
		//＊If there is not enough space to capture the task,
		//　then this would wait for the queue to be emptied,
		//　as long as the task's size is acceptable.
		//＊The callee must return, not exit.
		xThrP_Align_(1) /*[[nodiscard]]*/ int(*const Push_)(thrp_qu *const *const,THRP_P_,const size_t ArgSize,const void *const restrict ArgAddress);
		//ThrPure : Wait the task queue and terminate the worker thread.
		//＊This should be called before "ThrP.Qu.Delete_" is called.
		xThrP_Align_(1) /*[[nodiscard]]*/ int(*const Wait_)(thrp_qu *const *const);
	}
	Qu;

	//ThrPure : Mutex Functions
	//＊This function set has its global mutex internally.
	//＊Return value is defined under "ThrP.Flag".
	xThrP_Align_(4) const struct othrpack_mu
	{
		//ThrPure : Mutex Memory Allocation - Deallocate with "ThrP.Mu.Delete_".
		//＊A default memory handler is defined under "ThrP.UM".
		//＊Reference place should be initialized as NULL.
		xThrP_Align_(1) /*[[nodiscard]]*/ int(*const Create_)(THRP_UM *const restrict,void *const Owner,thrp_mu **const);
		//ThrPure : Mutex Memory Deallocation
		//＊All dependencies around the mutex must be released before deletion of it.
		xThrP_Align_(1) /*[[nodiscard]]*/ int(*const Delete_)(thrp_mu **const);

		//ThrPure : Lock the Mutex
		//＊If (Wait) equals to 0,
		//　then this could intrude into the earlier locking,
		//　else this would wait for the earlier locking to be unlocked.
		//＊If an intrusion is occurred,
		//　then "ThrP.Flag->Busy" might be returned.
		xThrP_Align_(1) /*[[nodiscard]]*/ int(*const Take_)(thrp_mu *const *const,const _Bool Wait);
		//ThrPure : Unlock the Mutex
		//＊If (Wait) equals to 0,
		//　then this could unlock the earlier locking,
		//　else this would wait for the earlier locking to be unlocked.
		//＊If an earlier locking exists and is unlocked without waiting,
		//　then "ThrP.Flag->Busy" might be returned.
		xThrP_Align_(1) /*[[nodiscard]]*/ int(*const Give_)(thrp_mu *const *const,const _Bool Wait);
	}
	Mu;
}
#undef xThrP_Align_
THRPACK;

#ifdef uPURES_DLL_IMPORT_
uPURES_DLL_IMPORT_
#endif

//ThrPure : Library Pack Object
extern _Alignas(THRPACK) THRPACK ThrP;
//ThrPure : Indirect access to the library pack object. (&ThrP)
extern THRPACK *ThrP_(void);

#ifdef uTHRP_MACRO_DEFINE_
//ThrPure : Abbreviation of "ThrP.Task.Yield_" with a null pointer.
#define ThrP_Task_Yield_() ThrP.Task.Yield_(NULL)
//ThrPure : Abbreviation of "ThrP.Task.Break_" with a null pointer.
#define ThrP_Task_Break_() ThrP.Task.Break_(NULL)
//ThrPure : Abbreviation of "ThrP.Task.Sleep_" with an instant 'int' value.
#define ThrP_Task_Sleep_(Milliseconds) _Generic((Milliseconds),int:ThrP.Task.Sleep_)(&(const int){(Milliseconds)})
//ThrPure : Alias for "ThrP.Task.Print_" with a 'char*' type guard.
#define ThrP_Task_Print_(Message) _Generic((Message),char*:ThrP.Task.Print_)(Message)
//ThrPure : Abbreviation of "ThrP.Qu.Push_" with an instant argument.
#define ThrP_Qu_Push_(Queue,Proc_,TYPE,...) ThrP.Qu.Push_((Queue),(Proc_),sizeof(TYPE),&(TYPE){__VA_ARGS__})
//ThrPure : Abbreviation of a once-loop over "ThrP.Mu.Take_" and "ThrP.Mu.Give_".
//＊Do not jump over the loop block, e.g. 'goto', 'break', and 'return'.
#define ThrP_Mu_Lock_Do_(Ret,Mutex) for(_Bool(xThrP_Temp_(Flag))=(((Ret)=ThrP.Mu.Take_((Mutex),1))==ThrP.Flag->Success);(xThrP_Temp_(Flag));(Ret)=(ThrP.Mu.Give_((Mutex),(xThrP_Temp_(Flag))=0)==(ThrP.Flag->Busy))?(ThrP.Flag->Success):(ThrP.Flag->Error))

//ThrPure : Macro for naming.
#define xThrP_Temp_(Var) xThrP_Temp_Wrap_(xThrP,Var,__LINE__)
//ThrPure : Macro for expansion.
#define xThrP_Temp_Wrap_(Prefix,Name,Suffix) xThrP_Temp_Conc_(Prefix,Name,Suffix)
//ThrPure : Macro for concatenation.
#define xThrP_Temp_Conc_(Prefix,Name,Suffix) Prefix##Name##Suffix
#endif

#endif
