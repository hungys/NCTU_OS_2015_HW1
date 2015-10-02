#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    pid_t childpid;
    int fd[2];

    pipe(fd); /* create a pipe */
    childpid = fork();

    if (childpid < 0) {
        printf("fork failed\n");
    } else if (childpid == 0) {
        dup2(fd[1], 1);   /* replace stdout */
        close(fd[0]);
        close(fd[1]);
        
        printf("HelloFromChild(pid=%d)!", getpid());   /* printf now writes to pipe */
    } else {
        dup2(fd[0], 0);   /* replace stdin */
        close(fd[0]);
        close(fd[1]);

        char buffer[32];
        scanf("%s", buffer);   /* scanf now reads from pipe */
        printf("(pid=%d) Received: %s\n", getpid(), buffer);

        int status;
        waitpid(childpid, &status, 0);
    }

    return 0;
}