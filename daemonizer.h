
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int daemonize(
    int fds[3],
    ...
);

int vdaemonize ( 
    int fds[3],
    char * const argv[]
) ;
