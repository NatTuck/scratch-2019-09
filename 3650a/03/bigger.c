#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("give one number as argument\n");
        return 1;
    }

    int xx = atoi(argv[1]);

    printf("%d + 1 = %d\n", xx, xx + 1);

    return 0;
}


