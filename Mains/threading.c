#ifdef _MSC_BUILD//workaround for MSVC issues
#define restrict __restrict
#define _Alignas(Size)
static_assert(sizeof(void*)==sizeof(void(*)(void)),"");
#pragma warning(disable:4201)
#endif

#define _PURES_DLL_IMPORT_ __declspec(dllimport)//only for DLL usage
#define _THRP_MACRO_DEFINE_
#include <thrpure.h>
#include <stdio.h>
#include <stdlib.h>

typedef const struct { const int Period,Repeat;const char Msg[32]; }MY_TASK;//task argument holder

//function for task example
static _Bool _My_Process_(const void *const);

//main logic
int main(void)
#define _My_Do_(Flag,Oper) do{if((Flag)==(ThrP.Flag->Success))(Flag)=(Oper);else return(EXIT_FAILURE);}while(0)
{
	const size_t QueueSpace=1024;//internal queue space - 1KB
	thrp_qu *Qu[2]={NULL,NULL};//queue object table
	int Flag=ThrP.Flag->Success;//thread flag
	
	_My_Do_(Flag,ThrP.Qu.Create_(ThrP.UM,NULL,Qu+0,QueueSpace));//create queue 0
	_My_Do_(Flag,ThrP.Qu.Create_(ThrP.UM,NULL,Qu+1,QueueSpace));//create queue 1
	
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
	
	return ((Flag==ThrP.Flag->Success)?(EXIT_SUCCESS):(EXIT_FAILURE));
}
#undef _My_Do_

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
