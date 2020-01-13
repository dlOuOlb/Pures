# Pures Documentation

## Build Guide

A standard C18 compiler (with thread and safety support) is required. For the more details, see the library headers.

### [Headers](./Headers) [#](http://github.com/dlOuOlb/Pures/tree/master/Headers)

- [strpure.h](./Headers/strpure.h) [#](http://github.com/dlOuOlb/Pures/tree/master/Headers/strpure.h) - about inflexible string
- [thrpure.h](./Headers/thrpure.h) [#](http://github.com/dlOuOlb/Pures/tree/master/Headers/thrpure.h) - about task queue
- [timpure.h](./Headers/timpure.h) [#](http://github.com/dlOuOlb/Pures/tree/master/Headers/timpure.h) - about time value

### [Sources](./Sources) [#](http://github.com/dlOuOlb/Pures/tree/master/Sources)

- [strpure.c](./Sources/strpure.c) [#](http://github.com/dlOuOlb/Pures/tree/master/Sources/strpure.c)
- [thrpure.c](./Sources/thrpure.c) [#](http://github.com/dlOuOlb/Pures/tree/master/Sources/thrpure.c)
- [timpure.c](./Sources/timpure.c) [#](http://github.com/dlOuOlb/Pures/tree/master/Sources/timpure.c)

Do not build the below files directly, which are a private header and a template. Just put them in the same folder with the above files.

- [stdpain.h](./Sources/stdpain.h) [#](http://github.com/dlOuOlb/Pures/tree/master/Sources/stdpain.h)
- [strpain.c](./Sources/strpain.c) [#](http://github.com/dlOuOlb/Pures/tree/master/Sources/strpain.c)

## Library Usage

### ThrPure

#### Task Queue Examples

For the more detailed example, see [this](./Mains/threading.c) [#](http://github.com/dlOuOlb/Pures/blob/master/Mains/threading.c).

##### ThrP_Qu: Creation and Deletion

```c
// assign null, specifying it needs to be allocated
thrp_qu *Qu = NULL;

// allocate 1KB with the default allocater
int Flag = ThrP.Qu.Create_( ThrP.UM, NULL, &Qu, 1024 );

// handle the possible error, e.g.
// if( Flag == ThrP.Flag->Success ); else return EXIT_FAILURE;

/* do your job... */

// wait for all tasks to be processed
Flag = ThrP.Qu.Wait_( &Qu );
/* handle the possible error */

// deallocate the space
Flag = ThrP.Qu.Delete_( &Qu );
/* handle the possible error */
```

##### ThrP_Qu: Enqueueing and Synchronization

```c
// enqueue a user task A into the queue A
Flag = ThrP.Qu.Push_( &QuA, User_Func_A_, sizeof( UserArgA ), &UserArgA );
/* handle the possible error */

// enqueue a user task B into the queue B
Flag = ThrP.Qu.Push_( &QuB, User_Func_B_, sizeof( UserArgB ), &UserArgB );
/* handle the possible error */

// synchronize the queues
Flag = ThrP.Qu.Wait_( &QuA );
/* handle the possible error */
Flag = ThrP.Qu.Wait_( &QuB );
/* handle the possible error */
```

#### Mutex Examples

##### ThrP_Mu: Creation and Deletion

```c
// assign null, specifying it needs to be allocated
thrp_mu *Mu = NULL;

// allocate the space with the default allocater
int Flag = ThrP.Mu.Create_( ThrP.UM, NULL, &Mu );

// handle the possible error, e.g.
// if( Flag == ThrP.Flag->Success ); else return EXIT_FAILURE;

/* do your job... */

// deallocate the space
Flag = ThrP.Mu.Delete_( &Mu );
/* handle the possible error */
```

##### ThrP_Mu: Locking and Unlocking

```c
// wait and lock
Flag = ThrP.Mu.Take_( &Mu, true );
/* handle the possible error */

// mutate the state
UserObj->Num++;

// unlock without waiting
Flag = ThrP.Mu.Give_( &Mu, false );
/* handle the possible error */
```

Or just simply, with an abusive [macro](./Headers/thrpure.h#L180-L182) [#](http://github.com/dlOuOlb/Pures/tree/master/Headers/thrpure.h#L180-L182)

```c
// wait, lock, do, unlock
ThrP_Mu_Lock_Do_( Flag, &Mu )
	UserObj->Num++;
```
