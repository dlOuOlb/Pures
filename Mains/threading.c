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

static thrp_mu *_GlobalLocker=NULL,**const GlobalLocker=&_GlobalLocker;
static _Bool _My_Process_(const void *const Arg);

#define _My_Do_(Flag,Oper) do{if(Flag){return(Flag);}else{(Flag)=(Oper);}}while(0)

int main(void)
{
	const size_t QueueBytes=1024;
	THRPACK *const _ThrP=ThrP_();
	thrp_qu *Qu[2]={NULL,NULL};
	my_task _TaskHolder,*const TaskHolder=&_TaskHolder;
	int Flag=_ThrP->Flag.Success;

	if(Flag)
	{
		printf("ThrP.Flag.Success != 0\r\n");
		return Flag;
	}

	Flag=_ThrP->Mu.Create_(GlobalLocker);

	Flag=_ThrP->Qu.Create_(Qu+0,QueueBytes);
	Flag=_ThrP->Qu.Create_(Qu+1,QueueBytes);

	TaskHolder->Repeat=3;
	TaskHolder->Period=250;
	TaskHolder->Msg="Hi, there!";
	_My_Do_(Flag,_ThrP->Qu.Push_(Qu+0,_My_Process_,TaskHolder,sizeof(my_task)));

	TaskHolder->Msg="Who are you?";
	_My_Do_(Flag,_ThrP->Qu.Push_(Qu+1,_My_Process_,TaskHolder,sizeof(my_task)));

	TaskHolder->Repeat=5;
	TaskHolder->Period=500;
	TaskHolder->Msg="I'm Fine, thank you.";
	_My_Do_(Flag,_ThrP->Qu.Push_(Qu+0,_My_Process_,TaskHolder,sizeof(my_task)));

	TaskHolder->Msg="Nice to meet you, Fine.";
	_My_Do_(Flag,_ThrP->Qu.Push_(Qu+1,_My_Process_,TaskHolder,sizeof(my_task)));

	_My_Do_(Flag,_ThrP->Qu.Wait_(Qu+0));
	_My_Do_(Flag,_ThrP->Qu.Wait_(Qu+1));

	_My_Do_(Flag,_ThrP->Qu.Delete_(Qu+1));
	_My_Do_(Flag,_ThrP->Qu.Delete_(Qu+0));

	_My_Do_(Flag,_ThrP->Mu.Delete_(GlobalLocker));

	return Flag;
}

static _Bool _My_Process_(const void *const Arg)
{
	THRPACK *const _ThrP=ThrP_();
	MY_TASK *const Task=Arg;

	for(int Count=0;Count<Task->Repeat;Count++)
		if(_ThrP->Task.Sleep_(&(Task->Period))==_ThrP->Signal.Continue)
		{
			if(_ThrP->Mu.Take_(GlobalLocker,true)==_ThrP->Flag.Success);	//Mutex Lock
			else return _ThrP->Signal.Break;								//Something Wrong

			printf("[%3d ms] [%d/%d] %s\r\n",Task->Period,Count,Task->Repeat,Task->Msg);

			if(_ThrP->Mu.Give_(GlobalLocker,false)==_ThrP->Flag.Busy);		//Mutex Unlock
			else return _ThrP->Signal.Break;								//Something Wrong
		}
		else return _ThrP->Signal.Break;

	return _ThrP->Signal.Continue;
}
