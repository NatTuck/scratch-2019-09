#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void
check_rv(int rv)
{
    if (rv == -1) {
        perror("fail");
        exit(1);
    }
}

int
main(int _ac, char* _av[])
{
    int rv;
    char msg[] = "Hello, pipe\n";

    int pipe_fds[2];
    rv = pipe(pipe_fds);
    check_rv(rv);

    int p_read = pipe_fds[0];
    int p_write = pipe_fds[1];
    int cpid;

    if ((cpid = fork())) {
        check_rv(cpid);
        close(p_read);

        rv = write(p_write, msg, strlen(msg));
        check_rv(rv);
    }
    else {
        close(p_write);

        char temp[100];
        while (1) {
            rv = read(p_read, temp, 100);
            check_rv(rv);
            temp[rv] = 0;
            if (rv == 0) {
                break;
            }
        }

        rv = write(1, temp, strlen(temp));
        check_rv(rv);
    }

    return 0;
}
