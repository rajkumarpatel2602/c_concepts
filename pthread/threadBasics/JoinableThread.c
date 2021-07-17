#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>        /* for using POSIX threads */
#include <unistd.h>     /* for pause() and sleep() */


/* Prototype for the thread must be
 * (void *) (*thread_fn) (void *)
 */

pthread_t pthread2;
pthread_t pthread3;

void *
cb_thread_fn (void *args)
{

    int *input_num = (int *) args;

    int count = 0;
    while (count < *input_num)
    {
        printf ("Inside child thread : %d\n", count);
        sleep (1);
        count++;
    }

    void *result = (int *)calloc(1, sizeof(int));
    *(int *)result = (*input_num) * (*input_num);
    free(input_num);
    return result;

}


void
thread_create (pthread_t *pthread, int val)
{

    int *num = calloc(1, sizeof(int));

    *num = val;

    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(
            &attr,
            PTHREAD_CREATE_JOINABLE);/* for detachable PTHREAD_CREATE_DETACHED */

    pthread_create (
        pthread,
        &attr,
        cb_thread_fn,
        (void *) num);
}


int
main (int argc, char **argv)
{
    void *thread_ret;

    thread_create (&pthread2, 2);
    thread_create (&pthread3, 10);
    pthread_join (pthread2, &thread_ret);           // do not terminate main thread.
    if(thread_ret != NULL){
        printf("Retruned value from thread 2 is : %d\n", *(int *)thread_ret);
        free(thread_ret);
    }
    pthread_join (pthread3, &thread_ret);           // do not terminate main thread.
    if(thread_ret != NULL){
         printf("Retruned value from thread 3 is : %d\n", *(int *)thread_ret);
        free(thread_ret);
    }
    return 0;
}
