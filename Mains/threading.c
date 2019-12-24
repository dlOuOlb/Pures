#ifdef _MSC_BUILD//workaround for MSVC issues
#define restrict __restrict
#define _Alignas(Size)
static_assert(sizeof(void*)==sizeof(void(*)(void)),"");
#pragma warning(disable:4201)
#endif

#define uPURES_DLL_IMPORT_ __declspec(dllimport)//only for DLL usage
#define uTHRP_MACRO_DEFINE_
#include <thrpure.h>
#include <stdio.h>
#include <stdlib.h>

static _Bool My_Process_(const void *const);//function for task example
typedef const struct { const int Period,Repeat;const char Msg[32]; }MY_TASK;//task argument holder

int main(void)
#define My_Do_(Flag,Oper) do{if((Flag)==(ThrP.Flag->Success))(Flag)=(Oper);else return(EXIT_FAILURE);}while(0)
{
	const size_t QueueSpace=1024;//internal queue space - 1KB
	thrp_qu *Qu[2]={NULL,NULL};//queue object table
	int Flag=ThrP.Flag->Success;//thread flag
	
	My_Do_(Flag,ThrP.Qu.Create_(ThrP.UM,NULL,Qu+0,QueueSpace));//create queue 0
	My_Do_(Flag,ThrP.Qu.Create_(ThrP.UM,NULL,Qu+1,QueueSpace));//create queue 1
	
	My_Do_(Flag,ThrP_Qu_Push_(Qu+0,ThrP.Task.Sleep_,const int,+10));
	My_Do_(Flag,ThrP_Qu_Push_(Qu+1,ThrP.Task.Sleep_,const int,+10));

	My_Do_(Flag,ThrP_Qu_Push_(Qu+0,ThrP.Task.Print_,const char[8],"[Fine]"));
	My_Do_(Flag,ThrP_Qu_Push_(Qu+1,ThrP.Task.Print_,const char[12],"[thank you]"));

	My_Do_(Flag,ThrP_Qu_Push_(Qu+0,My_Process_,MY_TASK,.Repeat=+3,.Period=+250,.Msg="Hi, there!"));
	My_Do_(Flag,ThrP_Qu_Push_(Qu+1,My_Process_,MY_TASK,.Repeat=+3,.Period=+250,.Msg="Who are you?"));
	My_Do_(Flag,ThrP_Qu_Push_(Qu+0,My_Process_,MY_TASK,.Repeat=+5,.Period=+500,.Msg="I'm Fine, thank you."));
	My_Do_(Flag,ThrP_Qu_Push_(Qu+1,My_Process_,MY_TASK,.Repeat=+5,.Period=+500,.Msg="Nice to meet you, Fine."));
	
	My_Do_(Flag,ThrP_Qu_Push_(Qu+0,ThrP.Task.Sleep_,const int,+750));
	My_Do_(Flag,ThrP_Qu_Push_(Qu+1,ThrP.Task.Sleep_,const int,+750));
	
	My_Do_(Flag,ThrP.Qu.Wait_(Qu+0));//synchronize queue 0
	My_Do_(Flag,ThrP.Qu.Wait_(Qu+1));//synchronize queue 1

	My_Do_(Flag,ThrP.Qu.Delete_(Qu+0));//delete queue 0
	My_Do_(Flag,ThrP.Qu.Delete_(Qu+1));//delete queue 1
	
	return ((Flag==ThrP.Flag->Success)?(EXIT_SUCCESS):(EXIT_FAILURE));
}
#undef My_Do_

static _Bool My_Process_(const void *const Arg)//receive a task
{
	MY_TASK Task=*((MY_TASK*)(Arg));//task argument holder
	const struct othrpack_signal Sign=*(ThrP.Signal);//signal table
	
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
