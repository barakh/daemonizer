#include "daemonizer.h"

void _start_daemon(
    int pipe_write,
    char * const argv[]
) {
    int pid;
    if ( -1 == (pid = fork()) ) {
        /* FIXME: what this should be it was "return -1" 
         * but this fucntion return void 
         * should it stay the fix exit(-1)
         * or it should be return? */
        exit(-1);
    }
    if( pid != 0 ) {
        /* Parent */
        write(pipe_write, &pid, sizeof(pid));
        close(pipe_write);
    } else {
        /* Child  */
        close(pipe_write);
        execv(argv[0], argv);
    }
    exit(EXIT_SUCCESS); 
}

/* wrapper for the vdaemonize function */
int daemonize(
    int fds[3],
    ...
) {
    int ret;
    va_list args;
    va_start(args, fds);
    ret = vdaemonize(fds, (char**)args);
    va_end(args);
    return ret;
}

/* Run the specified process as daemon 
* Use fds as stdin, stdout and stderr  
*/
int vdaemonize ( 
    int fds[3],
    char * const argv[]
) {
    int pid_pipe[2] = {-1, -1}; 
    int pid = -1;
    int daemon_pid = -1;
    int i;

    if ( -1 == pipe(pid_pipe) ) 
        goto cleanup;

    if ( -1 == (pid = fork()) ) 
        goto cleanup;

    if( pid == 0 ) {
        /* Child  */
        close(pid_pipe[0]);
        /* Set stdin stdout and stderr */
        for (i = 0;i < 3; i++) {
            dup2(fds[i], i);
        }
        _start_daemon(pid_pipe[1], argv);
    }

    /* Parent */
    close(pid_pipe[1]);
    read(pid_pipe[0], &daemon_pid, sizeof(daemon_pid));
    close(pid_pipe[0]);

cleanup:
    for (i = 0;i < 2;i++) {
        if ( pid_pipe[i] != -1)
            close(pid_pipe[i]);
    }
    return daemon_pid;
}

