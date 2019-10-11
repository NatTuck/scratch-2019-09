#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

int
main(int _ac, char* _av[])
{
    int opid = getpid();
    int opar = getppid();
    int cpid;

    if ((cpid = fork())) {
        // In the parent
        int st;
        waitpid(cpid, &st, 0);
        printf("Child status = %d\n", st);
    }
    else {
        // In the child
        int fd = open("stdout.txt", O_CREAT | O_APPEND | O_WRONLY, 0644);
        close(1);
        dup(fd);
        close(fd);

        execlp("echo", "echo", "hello", "from", "echo", NULL);
    }

    return 0;
}
