# Thread 

- Basic unit of program execution flow. It resides in context of a process.
- A process has atleast one thread. -- main thread.

- Fork point -- Instance when a new thread is created.
- Parent thread -- creator of a new thread
- Child thread -- created thread

- If main thread terminates then all the child threads terminates.

- Race condition : after the forking point, which thread is going to get executed
that's indeterministic. This is called as race condition.

- Methods for thread termination
1. pthred_exit() call by the thread. (child thread will keep running in this way if parent exit)
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
When a thread is created it can be started in two modes. joinable or detachable. if a thread is crated using joinable mode, then on returning or pthread_exit() it will notify main thread or parent thread, which may or may not be waiting for the further process using pthread_join() call. Resource will only get released if jonable thread joins the main thread. So, right way to program is use pthred join for waiting on joinable thread. 
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
thread waiting in while for network packet or user Input
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
Code — CR is made up of several instructions. if global or static data is being used then this locking is used.

Object - Data locking
When there are chances that out of many particular DS will be shared then that data structure will have mutex within and Threads will lock that per DS mutex and use it in the CR.
Make sure this DS is not memcopied as mutex is one of its member. Otherwise behaviour would be undefined.
if there is an utility of removing node from list, and this utility can be called from multiple thread with same or different lists as an input,
so if list is same then data locking is required, if different lists are used then it's not critical section, as access is not happening to same object.

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

* Theread cancellation requests are sent by the thread residing in the same process.

Thread cancellation can be of two types
1. Async cancellation
- request of cancellation is delivered to the OS. OS enqueue the request and deliever to the target thread when it gets time.
- there will be time difference between request submission and request execution.
2. Deferred cancellation

* Making a thread cancellable
threads can be cancellable but need to define while creating the thread or can be set by pthread_setcancelthread -- PTHREAD_CANCEL_ENABLE and mode of cancellation -- PTHREAD_CANCEL_ASYNCHRONOUS in pthread_setcanceltype() -- can be set in the thread function. these APIs do not take the thread_id as args. so whoever call this api will become cancellable thread.

pthread_cancle will help only if thread is cancellable to cancle the thread.

* Problems with Async cancellation
1. Resource leaking -- not releasing file descriptors and heap memory.
solution to this problem is using cleanup handlers.
2. cause invariants -- corruption in data structures
suppose thread was working on a linkedlist and modifying it and if it terminates, list will be inconsistent state or invariant.
cancelling thread while it has initiated the system call. systecall gets terminated and it may lead to kernel corruption or issues.
3. deadlocks -- mutex left locked and left for forever as thread died.
Mutex is locked and then thread terminates. horrible thing will happen if someone try to lock this acquired mutex.
2nd and 3rd problems can be avoided using cancellation points.(only Deferred cancellation).

* POSIX provides interface called thread cleanup handlers to prevent the resource leaking.
(void)(* cleanup_handlers)(void *)
only after return of these clean-up handlers threads can terminate.
Way to call these cleanup function

//Thread1(){
//    ...
//    pthread_cleanup_push(f1, arg1);
//    ...
//    pthread_cleanup_push(f2, arg2);
//    ...
//    ...
//    ...
//    pthread_cleanup_pop(0); // developer has to pop the stack incase thread doesn't
//    pthread_cleanup_pop(0); // get any cancel request and terminate naturally.
//}

* passing n = 0 in pop call means just pop out the cleanup handler from stack.
* passing n = ~0 means pop out and also call the handler.

* pthread_cleanup_push() and pop() are nothing but macros.
and hence, your thread function should have push and pop counts same.
e.g.
//Thread1(){
//    ...
//    {
//      some code here from push(f1)
//    ...
//    {
//      some code here from push(f2)
//    ...
//    ...
//    ...
//      some code here from push(f2)
//    }
//      some code here from push(f2)
//    }
//}

* pthread_exit() also invoke the clean up functions but not when thread exit with virture of `return` statement.
better to always handle exit with pthread_exit() call rather than normal return in a thread function or
use goto statement to jump on pop() calls.

* Deferred cancellation
Method to control as to which point in the execution flow of the thread , the thread is allowed to be cancelled.
Used to handle the problem of invariants.

* Cancellation points -- instrurcutions at which a thread can be cancelled.
Developer decides to put the cancellation point.

e.g. suppose at point p1 cancellation request has come.
//Thread1(){
//    ...
//    p1
//    ...
//    ...
//    p2
//    ...
//    ...
//    ...
//    p3  // pthread_testcancel() 
//        // cancallation point. -- Test if any cancellation request is pending or not.
//        // if yes then invoke the clean up handlers and cancel the thread.
//    ...
//    ...
//    ...
//}
    
* Choose Cancellation point wisely that we don't face issue of RL/Variants/Deadlocks.

* Semaphores
Usage : resource allocatin among multiple requesters.
e.g. Invited 13 Guests on party, but party hall has capacity of 10G.
3G will be in waiting list. if any from 10 entered guest will leave the hall
then waiting list will be checked and 1G will be allowed to enter.
        ----------------
watiing |               |               party hall == shared resource
list    |               |               Guest == threads competing for the resource.
--------                ------------
 3G           10G           
--------                ------------
        |               |
        |  party hall   |
        ----------------

* Mutex vs Semaphore

        Mutex (Permit number == 1)                  Semaphore ( PN == n )

C.S  ------------------------------         --------------------------------

        only 1 execution unit                   n execution units or threads
         or thread at a time                        at a time permitted.

C.S  ------------------------------         --------------------------------

* Mutex is the special case of semaphore and sometimes also referred as
binary semaphore.
Semaphore allows user to decide permit numbers wherease mutex doesn't allow.

* Semaphore allows multiple threads to run inside CR/CS at a time.
this may lead to problem of invariants. so developer has to be very
cautious that CS/CR is as such that, being executed by multiple threads
at a time won't make any issue. //re-entrant code????!!!

* semaphore APIs
1. sem_t sem;
/* Declare semaphore variable */
2. sem_init(sem_t * sem, int pshared, int permit_counter);
/* Initialise semaphore variable */
set pshared = 0 for threads, for precess give ~0 value.
3. sem_wait(sem_t * sem);
/* block calling thread or process if semaphore is not available */
4. sem_post(sem_t * sem);
/*  signal the blocked theread on semaphore */
5. sef_destroy(sem_t * sem);
/* destroy the thrad after use */

* Working of semaphore

       Semaphore ( PN == n )
     
        sem_wait(&sem) // Unconditionally decrease PC by 1 and allow if PC >= 0 and blcok if PC<0 the thread/process.
 --------------------------------

     n execution units or threads
         at a time permitted.

        sem_post(&sem) // Unconditionally increament PC by 1 and send signal to thread waiting on sem_wait() call, if any.
 --------------------------------
If any thread is waiting on the sem receives the signal from thread relaseing semaphore will simply enters the CS without 
touching the permit count. // this will help to level the count which was changed when sem_wait() was called by blocked thread.

* PC = 1 means mutx == semaphore with just one difference.
semaphore can be released by different thread.
Semaphore uses signaling mechanism, where as mutex doesn't.
which thread enters the CS will only exit after releasing mutex, where as for semaphore this is not true.

* Semaphore are also used for preocess synchronization

thread 1 init a vairable 'X' and it has to be used by 2nd thread or process
only after its initialization.

time 

t1        1st thread/process        2nd thread/process
t2          sem_wait(&sem)                .......
                 .....                    .......
t3               .....                  sem_wait(&sem);// make sure x is initialised.
                 .....                  while (X){
                 .....                    .......
                 .....                    .......
            set X = Value;                .......                  
                 .....                    .......
t4          sem_post(&sem)                .......

* Strict alternation
Strict alternation is the way of doing work using a pair of threads in alternate manner.
Strict alternation uses zero semaphore for its application.
e.g. sem_init(&sem, 0 , 0);
always post is bound to happen by a starting thread and making other thread wait for post by started thread.


semaphores can be used by
conditional variables and mutex. 

types of semaphores
1. unnamed and -- sync between threads and related processes // fork and named pipe and for threads
2. named semaphores. // used for unrelated process -- also for related.

mutex and CV are used for threads of the same process.
unnamed semaphores are used for threads and related processes
named semaphores are used for threads and related-unreleated processes.

semaphores
1. weak -- semaphore not gaurantee that all threads blocks on it will get CS and CPU at somepoint then that semaphore is called weak semaphore. -- bounded waiting is required to reduce starvation of threads. // T1, T2, T3 waiting to enter. - signal --> T1 in CS. T4, T2, T3 in waiting. - signale --> T4 enters and T5, T2, T3 in waiting. 
T2 and T3 are starving due to randomness in choosing the thread to get enter in CS on signal reception.
2. strong -- implement FIFO for unblocking thread. and hence system would have bounded waiting -- finite amount of waiting time. it gaurantee that all the threads will get CS at some point.

conditional variables :
allows us to have the finer control over taking the decision on when and which competing thread should be unblocked/resumed.
i.e. thread T1 is waiting on the empty queue for the element to get populated in the queue.

Mutex look like:
pthread_mutex_lock(&laptop->mutex);
// enjoy laptop
pthread_mutex_unlock(&laptop->mutex);

CV look like:
pthread_mutex_lock(&laptop->mutex);
if(conditions(laptop has internet connection)){
    wait(&cv, &laptop->mutex);
}
pthread_mutex_unlock(&laptop->mutex);

CV uses mutex internally.

Mutex can block on mutex availability only.
CV can block based on user variable or user defined condition's matching. on matting the condition it can also wake-up the thread waiting for the resource.

Advanced thread sync schemes are implemented using mutex + CV :
semaphores, monitors, producers-consumers, dinning philosopher, thread scheduler, wait queues, barriers, etc.

Mutex is all about Mutual exclusion
and CV is about checking if conditions are met or not. if met then only allow acces otherwise block the call. CV + Mutex always used together.
CV is used for co-ordination between threads. pthread_cond_wait is used to block thread if condition is not met. pthread_cond_signal is used to signal blocked thread.

Aquiring CV :
1. lock the mutex : pthrad_mutex_lock(&mutex);
2. wait on cv : pthread_cond_wait(&cv, &mutex); // mutex is released internally and then thread  wait on CV to get signalled by someother thread.


relasing CV :
1. lock the mutex : pthrad_mutex_lock(&mutex);
2. signal the conditional variable (cv): pthread_cond_signal(&cv); // sends the signal to CV
3. CV on signal, make the receiving thread awake -- and moved to ready state and wait for mutex release from signaling therad.
4. signalling thread releases the mutex : pthrad_mutex_unlock(&mutex); // making the signalled thread in execution.
5. As mutex is again made available, receiving thread will acquire the mutex and will do its work happily.

T1 :

pthread_mutex_t mutex;
pthread_cond_t cv;

pthread_mutex_init(&mutex, NULL);
pthread_cond_init(&cv, NULL);

....
printf("T1 is going to be blocked by wait call!\n");
pthread_mutex_lock(&mutex);
// may have predicate here
// if(queue_empty()){ // use while() to avoid spurious wakeups.
pthread_cond_wait(&cv, &mutex);// make the thread halt and mutex release internally.
// predicate block may end here. predicate is used to check the state of the resource.
// Execute your CR.
printf("T1 got awakened on singal from T2");
pthread_mutex_unlock(&mutex);
....


T2:
....
printf("T2 is going to signal T1!\n");
pthread_mutex_lock(&mutex);
pthread_cond_signale(&cv);// signal the T1 and make the thread in ready state. suppos T1 is now in ready state and T3 is also there is makeing predicate condition go false then, it will be a suprious wakeup for thread T1.
pthread_mutex_unlock(&mutex);
....

Producer and consumer dealing with a single queue can be impletemeted using CV and mutex very effectively.

- Spurious wakeups
When a thread is unblocked by signal, may resume execution due to a reason which is no more valid.


pseudo codes for producer consumer probelm.

consumer :

pthread_mutex_lock(&mutex) // 1. get lock
while(!predicate()){ // while to make sure we check predicate again after getting pthread_cond_signal()
    pthread_cond_wait(&cv, &mutex); // 2. release the lock and go into wait state as condition is not met
                                    // 5. wake up as cond_signal arrived and go from blocked to ready to run state.
                                    // 7. acquire lock internally and proceed for data structure access.
}
execute_cr_code_or_ds(); // 8. working on shared queue may be the ds.
pthread_mutex_unlock(&mutex) // 9. lock the thread again 

producer :

pthread_mutex_lock(&mutex) // 3. get the lock as it's released by consumer
if(predicate()){
    execute_cr_code_or_ds(); // do work
    pthread_cond_signal(&cv); // 4. signal the consumer waiting thread
}
pthread_mutex_unlock(&mutex) // 6. release the lock

// consumer - producer problem scenario
https://www.udemy.com/course/multithreading_parta/learn/lecture/24815736#overview 

- CV is associated with mutex and predicate
many cv can be associated with one mutex at a time.
but, one cv can not be associated with more than 1 mutex at a time.

Mutex is the property of resource always.
CV can be property of the shared resource or the thread. // if cv is property of shared resource or say just one cv for multiple thread,
then signaling thread will use this single cv to awake the thread, but which waiting thread will be awaken, that's totally depending on scheduler.
// supposed all thread has their own CVs(CV1, CV2, CV3 for example.). then there will be no dilemma in unblocking the thread using signal. because signallling thread will give specific cv name as arg to pthread_cond_signal(&CVx), giving developer the choice to deal with threads as he or she wants.
in other words, if threads share same CV then that CV becomes the property of resource, otherwise it will be peroperty of thread itself.

- pthead_cond_broadcast(&cv);
this api will signal all the threads and work run each blocked thread 1 by 1.
basically it helps programmer to write just 1 statement instead of 3 in case 3 threads are blocked and each waiting for pthread_cond_signal() call.

* Spin lock
- same as mutex, except one thing. it will not get blocked, rather will keep on executing nop operation, and hence context switching will not happen, as it does in mutex case.
- context switch is the concept of context swapping out from scheduler, but if one thread is in CR, and other thread comes and if it tries to acquire, this thread will be put to block stage.
- in case of spin lock, if incoming thread t2 is waiting for t1 to release the resource, it will keep on executing thread t2 with NOP instruction and will not be swapped out.
- pthread_spin_lock()
- pthread_spin_unlock()


PROBLEM encountered sofar
1. accessing hall with 10Guest capacity
2. producer - consumer problme with 2 producer and 2 consumer
3. strict alternation
4. listerner threads // server threads
5. write a program to print odd and even number by 2 threads. (zero semaphore to avoid race condition)
   
ALL THREAD SYNCRONIZATION DS ARE CONSRUCTED USING MUTEX AND CONDITIONAL VARIABLES
thread barriers, thread scheduler, thread pools, thread monitors, wait queues and semaphores are created using mutex and conditional variable.
