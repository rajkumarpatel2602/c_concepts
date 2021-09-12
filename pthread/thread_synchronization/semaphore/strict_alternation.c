/******************************************************
 * write a program to create two threads and
 * in one thread print odd value and in second even upto
 * 20. print threase values in sequential manner.
 * Use semaphore for strict alternation.
 *
 * hint : use zero semaphore. ie sem_init(&sem, 0, 0);
 * ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* for posix threads*/
#include <semaphore.h> /* for semaphore use*/
#include <errno.h> /* for global error number */
#include <unistd.h> /*  for sleep() and pause() kind calls */

#define NR_THREAD 2
#define PERMIT_COUNT 0

#define USE_SLEEP 0

#if USE_SLEEP
// with sleep
sem_t sem;
#else
// without sleep
sem_t sem_1;
sem_t sem_2;
#endif

pthread_t threads[NR_THREAD];

#if USE_SLEEP
// using 1 semaphore
void thread_cb_print_odd(void *arg){
    int i = 1;//starting even
    while(i < 20){
        printf("%d\n", i);
        i += 2;
        sem_post(&sem);
        sleep(1);
    }
    pthread_exit(0);
}

void thread_cb_print_even(void *arg){
    int i = 2;//starting even
    while(i <= 20){
        sem_wait(&sem);
        printf("%d\n", i);
        i += 2;
        sleep(1);
    }
    pthread_exit(0);
}
#else
// using two zero semaphore
void thread_cb_print_odd(void *arg){
    int i = 1;//starting even
    while(i < 20){

        printf("%d\n", i);
        i += 2;
        sem_post(&sem_1);
        sem_wait(&sem_2);
    }
    pthread_exit(0);
}

void thread_cb_print_even(void *arg){
    int i = 2;//starting even
    while(i <= 20){
        sem_wait(&sem_1);
        printf("%d\n", i);
        i += 2;
        sem_post(&sem_2);
    }
    pthread_exit(0);
}
#endif

// Entry point of the program
int main(int argc, void **argv){

#if USE_SLEEP
    sem_init(&sem, 0, 0);// zero semaphore for pair of threads for strict alternation.
#else
    sem_init(&sem_1, 0, 0);// using two semaphore there's no need to sleep.
    sem_init(&sem_2, 0, 0);
#endif
    int rc = pthread_create(&threads[0], NULL, thread_cb_print_odd, "odd_thread");
    if(rc != 0){
        printf("Error: Thread1 creation failed!\n");
        exit(0);
    }
    rc = pthread_create(&threads[1], NULL, thread_cb_print_even, "even_thread");
    if(rc != 0){
        printf("Error: Thread2 creation failed!\n");
        exit(0);
    }

    int i;
    for(i=0; i<NR_THREAD; i++){
        pthread_join(threads[i], NULL);
    }
#if USE_SLEEP
    // before exit destroy the semaphore
    sem_destroy(&sem);
#else
    sem_destroy(&sem_1);
    sem_destroy(&sem_2);
#endif
    return 0;
}
