#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("fifo: usage: %s [-c/-w/-r] <fifo_name>\n", argv[0]);
        exit(0);
    }

    if (strcmp(argv[1], "-c") == 0) {
        if (mkfifo(argv[2], 0666) < 0) {   /* create a fifo */
            perror("mkfifo failed");
        } else {
            printf("mkfifo successed\n");
            exit(0);
        }
    } else if (strcmp(argv[1], "-r") == 0) {
        int fd;
        fd = open(argv[2], O_RDONLY);   /* open a special file */
        char buf[1024];
        int len;
        while ((len = read(fd, buf, sizeof(buf))) > 0) {   /* operate as a file */
            printf("Read %d byte(s): %s", len, buf);
            memset(buf, 0, sizeof(buf));
        }
    } else if (strcmp(argv[1], "-w") == 0) {
        int fd;
        fd = open(argv[2], O_WRONLY);
        char buf[1024];
        while (1) {
            memset(buf, 0, sizeof(buf));
            fgets(buf, sizeof(buf), stdin);
            write(fd, buf, strlen(buf));
        }
    }
    
    return 0;
}