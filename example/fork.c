#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    pid_t childpid;

    childpid = fork();

    if (childpid < 0) {   /* cannot allocate new process */
        printf("fork failed\n");
    } else if (childpid == 0) {   /* child process */
        printf("(pid=%d) I'm child, I will sleep for 3 seconds\n", getpid());
        sleep(3);
    } else {   /* parent process */
        pid_t pid = getpid();
        printf("(pid=%d) I'm parent, and my child's pid is %d\n", pid, childpid);

        int status;
        waitpid(childpid, &status, 0);   /* wait for child process terminated */
        printf("(pid=%d) My child has been terminated\n", pid);
    }

    return 0;
}