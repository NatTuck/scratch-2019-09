#include <stdio.h>


int
main(int _argc, char* _argv[])
{
    printf("sizeof(char) = %ld\n", sizeof(char));
    printf("sizeof(short) = %ld\n", sizeof(short));
    printf("sizeof(int) = %ld\n", sizeof(int));
    printf("sizeof(long) = %ld\n", sizeof(long));
    printf("sizeof(long long) = %ld\n", sizeof(long long));

    printf("sizeof(float) = %ld\n", sizeof(float));
    printf("sizeof(double) = %ld\n", sizeof(double));

    printf("sizeof(char*) = %ld\n", sizeof(char*));
    printf("sizeof(long*) = %ld\n", sizeof(long*));
    printf("sizeof(float*) = %ld\n", sizeof(float*));

    printf("sizeof(void*) = %ld\n", sizeof(void*));
    printf("sizeof(void) = %ld\n", sizeof(void));

    float nn;
    float* nnp = &nn;
    printf("&nn = %lx\n", (unsigned long)(nnp));
    
    float* nnq = nnp + 5;
    printf("&(nn) + 5 = %lx\n", (unsigned long)(nnq));

    return 0;
}


