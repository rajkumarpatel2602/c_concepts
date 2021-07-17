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
There's no need to joining on exit of child thread. and no need to block parent thread using pthred_join. resources are released as soon as thread terminates.
-- No need to return result to main thread. It donesn't notify parent thread.
