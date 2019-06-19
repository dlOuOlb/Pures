#include <thrpure.h>
#include <stdio.h>

static thrp_mu *_GlobalLocker;

struct _my_task
{
	const char *Msg;
	int Period;
	int Repeat;
};
typedef struct _my_task my_task;
typedef const struct _my_task MY_TASK;

static _Bool _My_Process_(const void *const Arg)
{
	THRPACK *const _ThrP=ThrP_();
	MY_TASK *const Task=Arg;

	for(int Count=0;Count<Task->Repeat;Count++)
		if(_ThrP->Task.Sleep_(&(Task->Period))==_ThrP->Signal.Continue)
		{
			if(_ThrP->Mu.Take_(_GlobalLocker)==_ThrP->Flag.Success);//Mutex Lock
			else return _ThrP->Signal.Break;//Mutex Lock Failure

			printf("[%3d ms] [%d/%d] %s\r\n",Task->Period,Count,Task->Repeat,Task->Msg);

			if(_ThrP->Mu.Give_(_GlobalLocker)==_ThrP->Flag.Success);//Mutex Unlock
			else return _ThrP->Signal.Break;//Mutex Unlock Failure
		}
		else return _ThrP->Signal.Break;

	return _ThrP->Signal.Continue;
}

int main(void)
{
	const size_t QueueBytes=1024;
	THRPACK *const _ThrP=ThrP_();
	thrp_qu *Qu[2];
	my_task TaskHolder;
	int Flag;

	_GlobalLocker=_ThrP->Mu.Create_();

	Qu[0]=_ThrP->Qu.Create_(QueueBytes);
	Qu[1]=_ThrP->Qu.Create_(QueueBytes);

	TaskHolder.Msg="Hi, there!";
	TaskHolder.Period=250;
	TaskHolder.Repeat=3;
	Flag=_ThrP->Qu.Push_(Qu[0],_My_Process_,&TaskHolder,sizeof(my_task));

	TaskHolder.Msg="Who are you?";
	Flag=_ThrP->Qu.Push_(Qu[1],_My_Process_,&TaskHolder,sizeof(my_task));

	TaskHolder.Msg="I'm Fine, thank you.";
	TaskHolder.Period=500;
	TaskHolder.Repeat=5;
	Flag=_ThrP->Qu.Push_(Qu[0],_My_Process_,&TaskHolder,sizeof(my_task));

	TaskHolder.Msg="Nice to meet you, Fine.";
	Flag=_ThrP->Qu.Push_(Qu[1],_My_Process_,&TaskHolder,sizeof(my_task));

	Flag=_ThrP->Qu.Wait_(Qu[0]);
	Flag=_ThrP->Qu.Wait_(Qu[1]);

	Flag=_ThrP->Qu.Delete_(Qu+1);
	Flag=_ThrP->Qu.Delete_(Qu+0);

	Flag=_ThrP->Mu.Delete_(&_GlobalLocker);

	return Flag;
}
