#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("kill: usage: %s <pid>\n", argv[0]);
        exit(-1);
    }

    pid_t pid = atoi(argv[1]);
    if (kill(pid, SIGINT) < 0) {   /* send signal to pid */
        printf("kill: No such process\n");   /* return -1 if error */
    }

    return 0;
}