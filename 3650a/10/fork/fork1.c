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
        int pid1 = getpid();
        int par1 = getppid();
        printf("[P] Hello, I'm %d, child of %d\n", pid1, par1);
        printf("[P] New child is %d\n", cpid);

        int st;
        waitpid(cpid, &st, 0);
        printf("I found the number %d\n", st);
    }
    else {
        // Child
        int pid1 = getpid();
        int par1 = getppid();
        printf("[C] Hello, I'm %d, child of %d\n", pid1, par1);
        return 1;
    }

    printf("We're done.\n");

    return 0;
}
