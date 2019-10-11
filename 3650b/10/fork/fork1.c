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

    printf("Hi, I'm %d, child of %d\n", opid, opar);

    if ((cpid = fork())) {
        // In the parent
        int pid1 = getpid();
        int par1 = getppid();
        printf("[P] Hi, I'm %d, child of %d\n", pid1, par1);
        printf("[P] New child is %d\n", cpid);

        int st;
        waitpid(cpid, &st, 0);
        printf("Child status = %d\n", st);
    }
    else {
        // In the child
        int pid1 = getpid();
        int par1 = getppid();
        printf("[C] Hi, I'm %d, child of %d\n", pid1, par1);

        execlp("echo", "echo", "hello", "from", "echo", NULL);
        printf("finished exec");
        return 2;
    }

    printf("All done.\n");

    return 0;
}
