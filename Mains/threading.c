#ifdef _MSC_BUILD
#define _Alignas(Size)
#define restrict __restrict
#pragma warning(disable:4201)
static_assert(sizeof(void*)==sizeof(void(*)(void)),"");
#endif

#define _PURES_DLL_IMPORT_ __declspec(dllimport)
#include <thrpure.h>
#include <stdio.h>

typedef const struct { const char *const Msg;const int Period,Repeat; }MY_TASK;
static _Bool _My_Process_(const void *const Arg);

int main(void)
#define _My_Do_(Flag,Oper) if(Flag)return(Flag);else do{(Flag)=(Oper);}while(0)
{
	const char NameA[]="[Fine]",NameB[]="[thank you]";
	const size_t QueueBytes=1024;
	thrp_qu *Qu[2]={NULL,NULL};
	int Flag=ThrP.Flag->Success;

	if(Flag)
		puts("ThrP.Flag->Success != 0");
	else;

	_My_Do_(Flag,ThrP.Qu.Create_(Qu+0,QueueBytes));
	_My_Do_(Flag,ThrP.Qu.Create_(Qu+1,QueueBytes));

	_My_Do_(Flag,ThrP.Qu.Push_(Qu+0,ThrP.Task.Print_,NameA,sizeof(NameA)));
	_My_Do_(Flag,ThrP.Qu.Push_(Qu+1,ThrP.Task.Print_,NameB,sizeof(NameB)));
	
	_My_Do_(Flag,ThrP.Qu.Push_(Qu+0,_My_Process_,&(MY_TASK){.Repeat=3,.Period=250,.Msg="Hi, there!"},sizeof(MY_TASK)));
	_My_Do_(Flag,ThrP.Qu.Push_(Qu+1,_My_Process_,&(MY_TASK){.Repeat=3,.Period=250,.Msg="Who are you?"},sizeof(MY_TASK)));
	_My_Do_(Flag,ThrP.Qu.Push_(Qu+0,_My_Process_,&(MY_TASK){.Repeat=5,.Period=500,.Msg="I'm Fine, thank you."},sizeof(MY_TASK)));
	_My_Do_(Flag,ThrP.Qu.Push_(Qu+1,_My_Process_,&(MY_TASK){.Repeat=5,.Period=500,.Msg="Nice to meet you, Fine."},sizeof(MY_TASK)));

	_My_Do_(Flag,ThrP.Qu.Wait_(Qu+0));
	_My_Do_(Flag,ThrP.Qu.Wait_(Qu+1));

	_My_Do_(Flag,ThrP.Qu.Delete_(Qu+1));
	_My_Do_(Flag,ThrP.Qu.Delete_(Qu+0));

	return Flag;
}
#undef _My_Do_

static _Bool _My_Process_(const void *const Arg)
{
	MY_TASK *const Task=Arg;

	for(int Count=0;Count<Task->Repeat;Count++)
		if(ThrP.Task.Sleep_(&(Task->Period))==ThrP.Signal->Continue)
			if(printf("[%3d ms] [%d/%d] %s\r\n",Task->Period,Count,Task->Repeat,Task->Msg)<0)
				return ThrP.Signal->Break;
			else
				continue;
		else
			return ThrP.Signal->Break;

	return ThrP.Signal->Continue;
}
