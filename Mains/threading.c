#ifdef _MSC_BUILD
#define restrict __restrict
#endif

#include "thrpure.h"
#include <stdio.h>

typedef const struct { const char *const Msg;const int Period;const int Repeat; }MY_TASK;

static _Bool _My_Process_(const void *const Arg);

int main(void)
{
#define _My_Do_(Flag,Oper) if(Flag)return(Flag);else do{(Flag)=(Oper);}while(0)
	THRPACK T=*ThrP_();
	const char NameA[]="[Fine]",NameB[]="[thank you]";
	const size_t QueueBytes=1024;
	thrp_qu *Qu[2]={NULL,NULL};
	int Flag=T.Flag.Success;
	
	if(Flag)
		puts("ThrP.Flag.Success != 0");
	else;

	_My_Do_(Flag,T.Qu.Create_(Qu+0,QueueBytes));
	_My_Do_(Flag,T.Qu.Create_(Qu+1,QueueBytes));

	_My_Do_(Flag,T.Qu.Push_(Qu+0,(thrp_p_)(T.Task.Print_),NameA,sizeof(NameA)));
	_My_Do_(Flag,T.Qu.Push_(Qu+1,(thrp_p_)(T.Task.Print_),NameB,sizeof(NameB)));
	
	_My_Do_(Flag,T.Qu.Push_(Qu+0,_My_Process_,&(MY_TASK){.Repeat=3,.Period=250,.Msg="Hi, there!"},sizeof(MY_TASK)));
	_My_Do_(Flag,T.Qu.Push_(Qu+1,_My_Process_,&(MY_TASK){.Repeat=3,.Period=250,.Msg="Who are you?"},sizeof(MY_TASK)));
	_My_Do_(Flag,T.Qu.Push_(Qu+0,_My_Process_,&(MY_TASK){.Repeat=5,.Period=500,.Msg="I'm Fine, thank you."},sizeof(MY_TASK)));
	_My_Do_(Flag,T.Qu.Push_(Qu+1,_My_Process_,&(MY_TASK){.Repeat=5,.Period=500,.Msg="Nice to meet you, Fine."},sizeof(MY_TASK)));

	_My_Do_(Flag,T.Qu.Wait_(Qu+0));
	_My_Do_(Flag,T.Qu.Wait_(Qu+1));

	_My_Do_(Flag,T.Qu.Delete_(Qu+1));
	_My_Do_(Flag,T.Qu.Delete_(Qu+0));

	return Flag;
#undef _My_Do_
}

static _Bool _My_Process_(const void *const Arg)
{
	THRPACK T=*ThrP_();
	MY_TASK *const Task=Arg;

	for(int Count=0;Count<Task->Repeat;Count++)
		if(T.Task.Sleep_(&(Task->Period))==T.Signal.Continue)
			if(printf("[%3d ms] [%d/%d] %s\r\n",Task->Period,Count,Task->Repeat,Task->Msg)<0)
				return T.Signal.Break;
			else
				continue;
		else
			return T.Signal.Break;

	return T.Signal.Continue;
}
