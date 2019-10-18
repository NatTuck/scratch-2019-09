
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>


int
main(int _ac, char* _av[])
{
    int* xs = malloc(10 * sizeof(int));

    for (int ii = 0; ii < 10; ++ii) {
        xs[ii] = ii;
    }

    int cpid;
    if ((cpid = fork())) {
        sleep(1);

        printf("mutating array\n");
        for (int ii = 0; ii < 10; ++ii) {
            xs[ii] = 100 * ii;
        }

        waitpid(cpid, 0, 0);
    }
    else {
        printf("Printing array 1:\n");
        for (int ii = 0; ii < 10; ++ii) {
            printf("%d ", xs[ii]);
        }
        printf("\n");

        sleep(2);

        printf("Printing array 2:\n");
        for (int ii = 0; ii < 10; ++ii) {
            printf("%d ", xs[ii]);
        }
        printf("\n");
    }

    free(xs);

    return 0;
}
