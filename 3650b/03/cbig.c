#include <stdio.h>


int
main(int argc, char* argv[])
{
    printf("argc = %d\n", argc);
    for (int ii = 0; ii < argc; ++ii) {
        printf("arg %d: %s\n", ii, argv[ii]);
    }
    return 0;
}


