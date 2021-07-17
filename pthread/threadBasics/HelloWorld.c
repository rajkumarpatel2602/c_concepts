#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>		/* for using POSIX threads */
#include <unistd.h>		/* for pause() and sleep() */


/* Prototype for the thread must be
 * (void *) (*thread_fn) (void *)
 */
void *
cb_thread_fn (void *args)
{

  char *input = (char *) args;

  while (1)
    {
      printf ("Inside child thread : %s\n", input);
      sleep (1);
    }

}


void
thread1_create ()
{
  pthread_t pthread1;		//create handle for the thread.

  static char *thread_input1 = "I'm thread one";	// Has to be static or on heap

  //fork point for main thread.
  /* do not give input from stack
     because calling function will get retruned */
  int rc =
    pthread_create (&pthread1, NULL, cb_thread_fn, (void *) thread_input1);

  if (rc != 0)
    {
      printf ("Thread created failed with error code : %d", rc);
    }
}


int
main (int argc, char **argv)
{
  thread1_create ();
  pause ();			// do not terminate main thread.
  return 0;
}
