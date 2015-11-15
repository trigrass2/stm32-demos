
/** from http://www.amparo.net/ce155/thread-ex.html */

/* Includes */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */

#include <leds.h>

/* prototype for thread routine */
void print_message_function ( void *ptr );
void print_message_function_threadsafe ( void* ptr );

/* struct to hold data to be passed to a thread
   this shows how multiple data items can be passed to a thread */
typedef struct str_thdata
{
    int thread_no;
    char message[100];
} thdata;

pthread_mutex_t mutex;

int main()
{
    pthread_t thread1;
    pthread_t thread2;  /* thread variables */
    thdata data1;
    thdata data2;         /* structs to be passed to threads */

    flash_led(LED1);

    /* initialize data to pass to thread 1 */
    data1.thread_no = 1;
    strcpy(data1.message, "Hello!");

    /* initialize data to pass to thread 2 */
    data2.thread_no = 2;
    strcpy(data2.message, "Hi!");

    /* create threads 1 and 2 */
    pthread_create (&thread1, NULL, (void *) &print_message_function, (void *) &data1);
    pthread_create (&thread2, NULL, (void *) &print_message_function, (void *) &data2);

    /* Main block now waits for both threads to terminate, before it exits
       If main block exits, both threads exit, even if the threads have not
       finished their work */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("done!\n");

    pthread_mutex_init(&mutex, NULL);

    while(1)
    {
        pthread_create (&thread1, NULL, (void *) &print_message_function_threadsafe, (void *) &data1);
        pthread_create (&thread2, NULL, (void *) &print_message_function_threadsafe, (void *) &data2);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        sleep(1);
    }
    pthread_mutex_destroy(&mutex);

    /* exit */
    exit(0);
} /* main() */

/**
 * print_message_function is used as the start routine for the threads used
 * it accepts a void pointer
 * the printfs MAY write over each other, that is multithreading.
**/
void print_message_function ( void *ptr )
{
    thdata *data;
    data = (thdata *) ptr;  /* type cast to a pointer to thdata */

    printf("Thread %d says %s \n", data->thread_no, data->message);
    /* do the work */

    pthread_exit(0); /* exit */
} /* print_message_function ( void *ptr ) */

/**
 * print_message_function is used as the start routine for the threads used
 * it accepts a void pointer
 * the printfs MAY NOT write over each other, that is multithreading with mutexes.
**/
void print_message_function_threadsafe ( void* ptr )
{
    pthread_mutex_lock(&mutex);

    thdata *data;
    data = (thdata *) ptr;  /* type cast to a pointer to thdata */

    printf("Safe Thread %d says %s \n", data->thread_no, data->message);

    pthread_mutex_unlock(&mutex);

    pthread_exit(0); /* exit */
} /* print_message_function ( void *ptr ) */

