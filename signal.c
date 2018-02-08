#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#include "main.h"

static void sHandleSignal(int signo)
{
    printf("Handling signal %d - thread id %d\n", signo, pthread_self( ));

    if (pthread_self( ) != 1)
    {
        printf("Sending signal to main thread...\n");
        pthread_kill(1, signo);
        printf("Calling pthread_exit - thread %d\n", pthread_self( ));
	pthread_exit(NULL);
    }

    /* Close the pipe. */
    ClosePipe( );

    printf("Calling real exit - thread %d\n", pthread_self( ));
    exit(0);
}

void InstallSignalHandler(void)
{
    struct sigaction sigact, 
                     sigactold;

    printf("Installing SIGTERM signal handler...\n");

    sigemptyset(&sigact.sa_mask);
    sigact.sa_handler = (void (*)()) sHandleSignal;
    sigact.sa_flags = 0;

    sigaction(SIGTERM, &sigact, &sigactold);

    return;
}
