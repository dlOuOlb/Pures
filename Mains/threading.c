#ifdef _MSC_BUILD//workaround for MSVC issues
#define restrict __restrict
#define _Alignas(Size)
static_assert(sizeof(void*)==sizeof(void(*)(void)),"");
#define _USE_32BIT_TIME_T//to match the 'time_t' between build and usage
#pragma warning(disable:4201 4204)
#endif

#define _PURES_DLL_IMPORT_ __declspec(dllimport)//only for DLL usage
#define _THRP_MACRO_DEFINE_
#define _TIMP_MACRO_DEFINE_
#include <thrpure.h>
#include <timpure.h>
#include <stdio.h>
#include <stdlib.h>

typedef const struct { const struct timespec Time; }MY_TIME;//wrapper for 'struct timespec'
typedef const struct { const int Period,Repeat;const char Msg[32]; }MY_TASK;//task argument holder

//ABI test but not sufficient
static void _My_Test_(void);
//function for event example
static _Bool _My_Event_(const void *const);
//function for task example
static _Bool _My_Process_(const void *const);

//main logic
int main(void)
#define _My_Do_(Flag,Oper) do{if((Flag)==(ThrP.Flag->Success))(Flag)=(Oper);else return(Flag);}while(0)
{
	_My_Test_();

	const size_t QueueSpace=1024;//internal queue space - 1KB
	thrp_qu *Qu[2]={NULL,NULL};//queue object table
	int Flag=ThrP.Flag->Success;//thread flag
	
	_My_Do_(Flag,ThrP_Event_Invoke_(_My_Event_,MY_TIME,.Time=TimP.Spec.Now_()));//send an event arg
	
	_My_Do_(Flag,ThrP.Qu.Create_(Qu+0,QueueSpace));//create queue 0
	_My_Do_(Flag,ThrP.Qu.Create_(Qu+1,QueueSpace));//create queue 1
	
	_My_Do_(Flag,ThrP_Qu_Push_(Qu+0,ThrP.Task.Sleep_,const int,+10));
	_My_Do_(Flag,ThrP_Qu_Push_(Qu+1,ThrP.Task.Sleep_,const int,+10));

	_My_Do_(Flag,ThrP_Qu_Push_(Qu+0,ThrP.Task.Print_,const char[8],"[Fine]"));
	_My_Do_(Flag,ThrP_Qu_Push_(Qu+1,ThrP.Task.Print_,const char[12],"[thank you]"));

	_My_Do_(Flag,ThrP_Qu_Push_(Qu+0,_My_Process_,MY_TASK,.Repeat=+3,.Period=+250,.Msg="Hi, there!"));
	_My_Do_(Flag,ThrP_Qu_Push_(Qu+1,_My_Process_,MY_TASK,.Repeat=+3,.Period=+250,.Msg="Who are you?"));
	_My_Do_(Flag,ThrP_Qu_Push_(Qu+0,_My_Process_,MY_TASK,.Repeat=+5,.Period=+500,.Msg="I'm Fine, thank you."));
	_My_Do_(Flag,ThrP_Qu_Push_(Qu+1,_My_Process_,MY_TASK,.Repeat=+5,.Period=+500,.Msg="Nice to meet you, Fine."));
	
	_My_Do_(Flag,ThrP_Qu_Push_(Qu+0,ThrP.Task.Sleep_,const int,+750));
	_My_Do_(Flag,ThrP_Qu_Push_(Qu+1,ThrP.Task.Sleep_,const int,+750));
	
	_My_Do_(Flag,ThrP.Qu.Wait_(Qu+0));//synchronize queue 0
	_My_Do_(Flag,ThrP.Qu.Wait_(Qu+1));//synchronize queue 1

	_My_Do_(Flag,ThrP.Qu.Delete_(Qu+0));//delete queue 0
	_My_Do_(Flag,ThrP.Qu.Delete_(Qu+1));//delete queue 1
	
	return Flag;
}
#undef _My_Do_

static void _My_Test_(void)
{
	if((TimP.Size->Double)==sizeof(double))//'double' mismatch
		if((TimP.Size->TimeSpec)==sizeof(struct timespec))//'struct timespec' mismatch
		{
			const double Number=+2.5;//any number which would not truncate during cast

			if(TimP.Spec.Get_(TimP.Spec.Set_(Number))==Number)
				return;
			else;
		}
		else;
	else;

	puts("Library build and usage is not matched!");
	ThrP.Task.Sleep_(&(const int) { +999 });
	exit(EXIT_FAILURE);
}
static _Bool _My_Event_(const void *const Arg)//receive an event
{
	const struct timespec Old=*((const struct timespec*)(Arg));//send time
	const struct timespec New=TimP.Spec.Now_();//receive time
	const struct timespec Diff=TimP.Spec.Sub_(New,Old);//time difference

	if(printf("Sending to receiving : about %+.3Es seconds have past.\r\n",TimP.Spec.Get_(Diff))<0)
		return ThrP.Signal->Break;
	else
		return ThrP.Signal->Continue;
}
static _Bool _My_Process_(const void *const Arg)//receive a task
{
	MY_TASK Task=*((MY_TASK*)(Arg));//task argument holder
	const struct _thrpack_signal Sign=*(ThrP.Signal);//signal table

	for(int Count=0;Count<Task.Repeat;Count++)
		if(ThrP.Task.Sleep_(&(Task.Period))==Sign.Continue)
			if(printf("[%3d ms] [%d/%d] %s\r\n",Task.Period,Count,Task.Repeat,Task.Msg)<0)
				return Sign.Break;
			else
				continue;
		else
			return Sign.Break;

	return Sign.Continue;
}
