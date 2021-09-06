# Thread 

- Basic unit of program execution flow. It resides in context of a process.
- A process has atleast one thread. -- main thread.

- Fork point -- Instance when a new thread is created.
- Parent thread -- creator of a new thread
- Child thread -- created thread

- If main thread terminates then all the child threats terminates.

- Race condition : after the forking point, which thread is going to get executed
that's indeterministic. This is called as race condition.

- Methods for thread termination
1. pthred_exit() call by the thread. (child thread will keep running in this way)
2. Exit of thread function. (return 0 in main 
will kill child threads as process is ending itself.)
3. Cancellation request from other thread.

- Thread function's input arg must be static or residing on heap, as after forking
thread creating function may return and stack-frame will get destoryed.

- Prototyp for the thread function : (void * )( * thread_fn) (void * input_args);

- Reosurce sharing :

* OS allocates resources to threads : 
1. Memory -- so that thread may use heap via calloc, malloc
2. CPU -- so that threads get scheduled
3. Hardware 

- OS considers all threads as sibligs. there's no parent-child relationshipe.
if one thread dies then that has no impact on anyother threads.
    -- when main thread dies, then all child thread also die as process is getting
    terminated. if main exits with pthread_exit() then there's no impact on child
    threads. This is the exception to above statement.

- Multiple threads of a process shares same addess virtual space of the process.
-- Threads of same process, share heap, open file descriptors, sockets, global vars.
-- stack memory is not shared. each thread has mutually exclusive stack memeory.

- What is schedulable? -- kernel only schedule threads, not processes.
-- However, if any thread gives SEG-FAULT or some error then process
(and all threads within) gets killed.
-- A signal is delivered per process, not per thread.

------------------------ section 2 ---------------------------------

CONTEXT SWITCHING, CONCURRENCY AND PARALLELISM

- *Concurrency* : one task at a time and task switiching(i.e. round robin)
all tasks will be in progression.
example : 3 well-digger with single drilling tool.
work in progression for all. At a time only one can work.

- *Parallelism* : all tasks work in parallel at any given instance.
example  : 3 well-digggers with their personal drilling tool.
work in progression for all. At a time All 3 can work. No context switching.

- *Singularism* : Two or more task are present, 
but context switch is not allowed until first task completes.
No progression, And at a time only one can work.[Number of resources doesn't really matter]
No context switching. Doesn't really exist in practical world. used in some embedded system
which have one mini CPU.

Time in parallelism << Time in singularism < Time in concurrency case.

Concurrency doesn't give speed but progression.
Parallelism gives speed and progression both. but it demands hardware resource.

- Context switched tasks will wait in *ready queue*.

- Why do we need concurrency?
suppose we have 100 threads to run and we have just 4 CPU cores.
Complete Parallism for all threads is not possible. 
So 4 threads will work in parallel fashion but remaining threads will
use CPU resource in concurrent fashion via context switching.
25/CPU will get allocated. and 25 threads(1 group) will run in concurrent fashion.
So, parallism and concurrency co-exist.

-- Threads in same group will work in concurrent fashion.
-- Threads in different group will work in parallel fashion.
-- If only parallelism is present then, 96 threads would starve. that's not desired.
-- Having concurrency alone is also a bad idea, as threads has to fight for single
resource and context switch is a costly operation.
-- So concurrency and parallelism both are required.

- Thread requirement
-- when process wants to handle multiple requests in parallel.[TCP server, jwellery shop owner, etc.  -- when delgation is possible.]
-- when multiple things need to be tackled in concurrency.

- Why thread is a lightweight process?
-- thread uses, process(main thread's) almost all the pre-existing resources. SO OS doesn't have to create isolated execution environment.
-- Page table, sockets, shared libs(already loaded while running the process)
-- deletion will also be easy, as it doesn't need to reclaim all resources. Contex switching is also faster.[Thread switching]. whereas switching between two process or threads of two different processes is costlier.

- Overlapping work?
-- if T1 is doing W1 and if T2 is doing W2, and both works are working on the same datastructures within a process(global or heap memory), then two threads will be overlapping threads and may require thread syncronization.

-- Parallelism achieved --  non-overlapping threads, different CPUs
-- Concurrency achieved -- overlapping or non-overlapping threads, same CPU.

- *Joinable threads*
When a thread is created it can be started in two modes. joinable or detachable. if a thread is crated using joinable mode, then on returning or pthread_exit() it will notify main thread or parent thread, which may or may not be waiting for the further process suing pthread_join() call. Resource will only get released if jonable thread joins the main thread. So, right way to program is use pthred join for waiting on joinable thread. 
-- Joinable can also be converted to detachable and vice-versa.
-- By default threads are joinable threads.
-- Joinee thread or parent thread may also collect return values from joinable.

- *Detached Thread*
There's no need to joining on exit for child thread. and no need to block parent thread using pthred_join. resources are released as soon as thread terminates.
-- No need to return result to main thread. It donesn't notify parent thread.

-- If a joinable thread is terminating then it will signal any threads who is waiting using pthread_join() api.
-- Thread can wait for the joinable thread only. Thread can not wait for detached thread.

- What is map-reduce?
programming conecpt based on divide and conquere paradigm.
-- mapper -- worker threads
-- reducer thread -- moderator thread or a thread which waits on mappers.

- When to use joinable thread?
-- if a thread is supposed to notify the parent or other thread, or it requires to return result to some other thread.

- When to use detached thread?
-- Independent worker which is not supposed to notify or provide results to anyone, then such threads should be made detached while creation.
-- when nobody care about thread's death.
e.g. -- All infinite loop threads.
thread waiting in while for netowrk packet or user Input
-- TCP server's worker thread working with tcp clients, mostly.

- Thread communincations
-- All IPCs can be used. i.e. sockets, MQ, Shared memory, Pipes.
-- Callbacks, and function pointers. Because, this is faster, no data transfer but transfer of computation. No kernel resource requirements or supports, and completely run in user-space.

- Notification function chain model
-- publisher -- who generates data
-- subscriber -- who owns method to operate on
-- notification -- calling a function pointer or callback.
-- TOC -- transfer of computations -- activity of TOC is callback registration.

- What is Notification chain?
-- It is an architectural concept(communication pattern) and used to notify multiple subscribers for the events they are interested in. It's a design patterns.
-- Event generator -- publishers
-- Party which gets notified on events -- subscribers.
-- one pub and multiple subs.
-- pub/sub can be threads in same process, threads in different processes, could be different processes on different machines or different software parts of a huge stack.
-- pub pushes event to the subs.
-- sub may register or de-register for the events on their will.

- Publisher are the owner of some data source. e.g. routing table as data source.
- subs are the applications or software piece which is interested in data source owned by the publiser.


- Notification chain is a linkedList of the topics of subscribers' interest as the key and callbacks provided by the subs to get invoked while the key(topic) gets some update.It is a database or linkedList maintained by the publisher.



* What is critical section?
Code using shared data structures
Heap, static, socket, global vars

* what are Conflicting operations?
RW and WW

* What is Thread synchronization?
Its a technique to prevent concurrent access to shared resources by several threads.

* what is Mutex?
Tool for thread synschronization.
Mutual exclusion.
e.g. Key and bank locker

code
`
Pthread_mutex_t mutexOb;
Pthreas_mutex_lock(&mutexOb)
CR
Pthread_mutex_unlock(&mutexOb)
`

* Points to remember
- If mutexOb is acquired then other threads trying to lock it will get blocked.
- Thread who owns the mutex must not intentionally die. As mutex will not be free ever. And deadlock will occur.
- Bigger the CR or CS,
- Larger the time threads has to wait.
- Locking and unlocking adds the cpu overheads.

* Rules.
- If T1 locks then, it only has to unlock.
- If mutex is locked by 1 thread then others trying to lock or acquire will go into blocked state.
- Unlocking/locking an already unlocked/locked mutex will result in undefined behaviour/seld-deadloacked.
- LIFO order of locking and unlocking mutex.

* Locking types
Code and object locking
Code — CR is made up of several instructions.

Object - Data locking
When there are chances that out of many particular DS will be shared then that data structure will have mutex within and Threads will lock that per DS mutex and use it in the CR.
Make sure this DS is not memcopied as mutex is one of its member. Otherwise behaviour would be undefined.

* Deadlocks
Necessary Conditions
-- Mutual exclusion : only one thread can be in CR or use resource which are not shareable at a single instance.
-- Hold and wait : a resource is holding atleast one resource and waiting on other resource.
-- No preemption : a resource can not be taken away from the resource unless thread release the resource.
-- Circular wait : a set of threads are waiting for resources in ciruclar fashion.

* Order of mutex acquisition matters
If thread 1 is acquiring mutex1 first and mutex2 second, then other thread should have same order of mutex
acqusition in its execution path. ie. mutex1 followed by mutex2. otherwise (mutex2 followed by mutex1) will
create deadlock condition.

//T1 executes
foo1(){
    lock(&m1)
    // do something
    lock(&m2)
}

// T2 executes
foo2(){
    lock(&m2)
    // do something
    lock(&m1)
}

* 
