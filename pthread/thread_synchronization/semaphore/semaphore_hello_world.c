#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* for posix threads*/
#include <semaphore.h> /* for semaphore use*/
#include <errno.h> /* for global error number */
#include <unistd.h> /*  for sleep() and pause() kind calls */

#define NR_THREAD 5
#define PERMIT_COUNT 2

sem_t sem;

pthread_t threads[NR_THREAD];

// thread callback function which has critical section.
void thread_cb_fun(void *arg){
    int i =0;
    char *thread_name = (char *)arg;

    sem_wait(&sem);

    printf("%s ENTERED\n", thread_name);

    // CS starts here
    for(i=0; i<NR_THREAD; i++){
        printf("%s is executing in CS!!!\n", thread_name);
        sleep(1);
    }
    // CS ends here

    printf("%s EXITING\n", thread_name);

    sem_post(&sem);
}

// helper function to create threads.
void
thread_create(pthread_t *thread_handle, void *arg){

    int rc = pthread_create(thread_handle, NULL, thread_cb_fun, arg);
    if(rc != 0){
        printf("Error: Thread creation failed!\n");
        exit(0);
    }
}

// Entry point of the program
int main(int argc, void **argv){

    sem_init(&sem, 0, PERMIT_COUNT);

    thread_create(&threads[0], "thread1");
    thread_create(&threads[1], "thread2");
    thread_create(&threads[2], "thread3");
    thread_create(&threads[3], "thread4");
    thread_create(&threads[4], "thread5");

    int i;
    for(i=0; i<NR_THREAD; i++){
        pthread_join(threads[i], NULL);
    }
    // before exit destroy the semaphore
    sem_destroy(&sem);
    return 0;
}
