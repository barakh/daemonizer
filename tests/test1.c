#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>

#include "../daemonizer.h"

#define TMP_FILE_NAME "blabla.tmp"
#define PATTREN "blablablablabla\n"

void main(void)
{
    int fds[3] = {0};
    int read_fds[2] = {0};
    int write_fds[2] = {0};
    char read_buffer[100] = {0};
    int result = 0;
    int daemon_pid = -1;


    result = pipe(read_fds);
    if (0 != result) {
        printf("pipe failed\n");
        return;
    }
    
    result = pipe(write_fds);
    if (0 != result) {
        printf("pipe failed\n");
        return;
    }

    fds[0] = write_fds[0];
    fds[1] = read_fds[1];
    fds[2] = read_fds[1];

    daemon_pid = daemonize(fds, "cat");
    if(daemon_pid == -1) {
        printf("Daemon initialization failed\n");
        return;
    }
    if(kill(daemon_pid, 0) == -1) {
        printf("Daemon died unexpectedly\n");
        return;
    }

    result = write(write_fds[1], PATTREN, strlen(PATTREN));
    if (0 > result) {
        printf("write failed\n");
        return;
    }

    result = read(read_fds[0], read_buffer, strlen(PATTREN));
    if (0 > result) {
        printf("read failed\n");
        return;
    }

    /* it's not the best choice to use readline but i am lazy */
    strncmp(PATTREN, read_buffer, strlen(PATTREN)); 
}
