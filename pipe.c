#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>

#include "main.h"

int pipes[2];

void CreatePipe(void)
{
    printf("CreatePipe: Entering...\n");

    pipe(pipes);

    printf("CreatePipe: Returning...\n");
}

void ReadPipe(void)
{
    char buffer[256];

    int nfds;

    fd_set rfds, 
           efds;

    FD_ZERO(&rfds);
    FD_ZERO(&efds);

    FD_SET(pipes[0], &rfds);
    FD_SET(pipes[0], &efds);

printf("Selecting data...\n");
    /* Select data from the pipe. */
    nfds = select(pipes[1] + 1, &rfds, NULL, &efds, 0);

printf("Selected data - nfds %d\n", nfds);

    /* Read data from the pipe. */
printf("Reading data...\n");
    read(pipes[0], buffer, sizeof buffer);
}

void ClosePipe(void)
{
    printf("ClosePipe: Entering...\n");

    close(pipes[0]);

    printf("ClosePipe: Returning...\n");
}
