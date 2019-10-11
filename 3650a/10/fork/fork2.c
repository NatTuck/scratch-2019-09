#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int
main(int _ac, char* _av[])
{
    int opid = getpid();
    int opar = getppid();
    int cpid;

    printf("Hi I'm %d, child of %d\n", opid, opar);

    if ((cpid = fork())) {
        // Parent
        int st;
        waitpid(cpid, &st, 0);
        printf("Child exited with status = %d\n", st);
    }
    else {
        // Child
        execlp("echo", "echo", "in", "subprocess", NULL);
        printf("Never get here.\n");
    }

    printf("We're done.\n");

    return 0;
}
