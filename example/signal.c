#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int sigint_counter = 0;

void sigint_handler(int sig) {   /* handler body */
    sigint_counter++;
    if (sigint_counter > 3) {
        printf("Goodbye!\n");
        exit(0);
    } else {
        printf("SIGINT caught, %d more Control-C to exit!\n", 4 - sigint_counter);
    }
}

int main(int argc, char **argv) {
    pid_t childpid;

    struct sigaction sigint_action = {
        .sa_handler = &sigint_handler,
        .sa_flags = 0
    };
    sigemptyset(&sigint_action.sa_mask);
    sigaction(SIGINT, &sigint_action, NULL); 

    while(1) {
        sleep(1);
    }

    return 0;
}