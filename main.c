#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>

#include "main.h"

void *tmain(void *arg)
{
    printf("THREAD: Entering - thread id %d\n", pthread_self( ));

    printf("THREAD: Sleeping - thread id %d\n", pthread_self( ));

    sleep(60);

    printf("THREAD: Returning - thread id %d\n", pthread_self( ));
}

int main(int argc, char **argv)
{
    long status;

    pthread_t thread;

    printf("MAIN: Entering - thread id %d\n", pthread_self( ));

    /* Create our thread. */
    if ((status = pthread_create(&thread, NULL, tmain, NULL)) != 0)
    {
        misLogError("pthread_create: %s", strerror(errno));
        exit(1);
    }

    InstallSignalHandler( );

    /* Create a pipe that we will eventually read on. */
    CreatePipe( );

    printf("MAIN: Reading from the pipe - thread id %d\n", pthread_self( ));

    /* Read data from the pipe. */
    ReadPipe( );

    printf("MAIN: Exiting - thread id %d\n", pthread_self( ));
}
