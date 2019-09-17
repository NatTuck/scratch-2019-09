#include <stdlib.h>
#include <stdio.h>

// Collatz Conjecture
//  - start with a number
//  - if it's even, take n/2
//  - if it's odd,  take 3*n+1
//  how many times repeat before get to 1?


long
iterate(long x)
{
    if (x % 2 == 0) {
        return x/2;
    }
    else {
        return 3*x + 1;
    }
}

int
main(int argc, char* argv[])
{
    long x = atol(argv[1]);

    long i = 0;

    while (x > 1) {
        printf("%ld\n", x);
        x = iterate(x);
        i++;
    }

    printf("i = %ld\n", i);
    return 0;
}






