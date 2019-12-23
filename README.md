# Pures Documentation

## Build Guide

A standard C18 compiler (with thread and safety support) is required. For the more details, see [headers](./Headers) [#](http://github.com/dlOuOlb/Pures/tree/master/Headers).

### Sources

- strpure.c
- thrpure.c
- timpure.c

Do not build below files directly, which are a private header and a template. Just put them in the same folder with above files.

- stdpain.h
- strpain.c

### Headers

- strpure.h
- thrpure.h
- timpure.h

## Library Usage

### ThrPure

#### Task Queue Examples

For the more detailed example, see [this](./Mains/threading.c) [#](http://github.com/dlOuOlb/Pures/blob/master/Mains/threading.c).

##### Task Queue Creation and Deletion

```c
//assign null, specifying it is not initialized
thrp_qu *Qu = NULL;

//allocate 1KB with the default allocater
int Flag = ThrP.Qu.Create_( ThrP.UM, NULL, &Qu, 1024 );

//handle the possible error, e.g.
//if( Flag == ThrP.Flag->Success ); else return EXIT_FAILURE;

/* do your job... */

//wait for all tasks to be processed
Flag = ThrP.Qu.Wait_( &Qu );
/* handle the possible error */

//deallocate the space
Flag = ThrP.Qu.Delete_( &Qu );
/* handle the possible error */
```

##### Task Queue Enqueueing and Synchronization

```c
//enqueue a user task A into the queue A
Flag = ThrP.Qu.Push_( &QuA, User_Task_Func_A_, sizeof( UserTaskArgA ), &UserTaskArgA );
/* handle the possible error */

//enqueue a user task B into the queue B
Flag = ThrP.Qu.Push_( &QuB, User_Task_Func_B_, sizeof( UserTaskArgB ), &UserTaskArgB );
/* handle the possible error */

//synchronize the queues
Flag = ThrP.Qu.Wait_( &QuA );
/* handle the possible error */
Flag = ThrP.Qu.Wait_( &QuB );
/* handle the possible error */
```

#### Mutex Examples

##### Mutex Creation and Deletion

```c
//assign null, specifying it is not initialized
thrp_mu *Mu = NULL;

//allocate the space with the default allocater
int Flag = ThrP.Mu.Create_( ThrP.UM, NULL, &Mu );

//handle the possible error, e.g.
//if( Flag == ThrP.Flag->Success ); else return EXIT_FAILURE;

/* do your job... */

//deallocate the space
Flag = ThrP.Mu.Delete_( &Mu );
/* handle the possible error */
```

##### Mutex Locking and Unlocking

```c
//wait and lock
Flag = ThrP.Mu.Take_( &Mu, true );
/* handle the possible error */

//mutate the state
UserObj->Num++;

//unlock without waiting
Flag = ThrP.Mu.Give_( &Mu, false );
/* handle the possible error */
```
