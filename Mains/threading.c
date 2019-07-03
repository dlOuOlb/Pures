#ifdef _MSC_BUILD
#define restrict __restrict
#endif

#include <stdbool.h>
#include <stdio.h>
#include "thrpure.h"

struct _my_task
{
	const char *Msg;
	int Period;
	int Repeat;
};
typedef struct _my_task my_task;
typedef const struct _my_task MY_TASK;

static _Bool _My_Process_(const void *const Arg);

#define _My_Do_(Flag,Oper) do{if(Flag){return(Flag);}else{(Flag)=(Oper);}}while(0)

int main(void)
{
	const char NameA[]="[Fine]";
	const char NameB[]="[thank you]";
	const size_t QueueBytes=1024;
	THRPACK T=*ThrP_();
	thrp_qu *Qu[2]={NULL,NULL};
	my_task _TaskHolder,*const TaskHolder=&_TaskHolder;
	int Flag=T.Flag.Success;
	
	if(Flag)
	{
		puts("ThrP.Flag.Success != 0");

		return Flag;
	}

	_My_Do_(Flag,T.Qu.Create_(Qu+0,QueueBytes));
	_My_Do_(Flag,T.Qu.Create_(Qu+1,QueueBytes));

	_My_Do_(Flag,T.Qu.Push_(Qu+0,(thrp_p_)(T.Task.Print_),NameA,sizeof(NameA)));
	_My_Do_(Flag,T.Qu.Push_(Qu+1,(thrp_p_)(T.Task.Print_),NameB,sizeof(NameB)));
	_My_Do_(Flag,T.Task.Yield_(NULL));

	TaskHolder->Repeat=3;
	TaskHolder->Period=250;
	TaskHolder->Msg="Hi, there!";
	_My_Do_(Flag,T.Qu.Push_(Qu+0,_My_Process_,TaskHolder,sizeof(my_task)));

	TaskHolder->Msg="Who are you?";
	_My_Do_(Flag,T.Qu.Push_(Qu+1,_My_Process_,TaskHolder,sizeof(my_task)));

	TaskHolder->Repeat=5;
	TaskHolder->Period=500;
	TaskHolder->Msg="I'm Fine, thank you.";
	_My_Do_(Flag,T.Qu.Push_(Qu+0,_My_Process_,TaskHolder,sizeof(my_task)));

	TaskHolder->Msg="Nice to meet you, Fine.";
	_My_Do_(Flag,T.Qu.Push_(Qu+1,_My_Process_,TaskHolder,sizeof(my_task)));

	_My_Do_(Flag,T.Qu.Wait_(Qu+0));
	_My_Do_(Flag,T.Qu.Wait_(Qu+1));

	_My_Do_(Flag,T.Qu.Delete_(Qu+1));
	_My_Do_(Flag,T.Qu.Delete_(Qu+0));

	return Flag;
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
