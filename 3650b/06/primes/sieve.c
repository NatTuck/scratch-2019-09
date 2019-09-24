#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Usage:
//    ./prime N   - find the N'th prime number

// Examples:
//    ./prime 0    => 2
//    ./prime 2    => 5
//    ./prime 4    => 11

// Algorithm:
//  - List of primes: [2]
//  - For each x number above list, check if it is divisible
//    by primes up to sqrt(x)
//  - If it's prime, it goes in list.
//  - Continue to N.

long
sqrt_up(long xx)
{
    return (long)ceil(sqrt(xx));
}

long
prime(long nn)
{
    long mm = nn + 3;
    char* nums = calloc(1, mm * mm );

    for (long ii = 2; ii <= mm; ++ii) {
        if (nums[ii]) {
            continue;
        }
        for (long jj = 2 * ii; jj <= (mm * mm); jj += ii) {
            nums[jj] = 1;
        }
    }

    long count = 0;
    for (long ii = 2; ii <= (mm * mm); ++ii) {
        if (nums[ii] == 0) {
            if (count == nn) {
                //free(nums);
                return ii;
            }
            count += 1;
        }
    } 

    abort();
}

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        puts("Usage:\n\t./primes N");
        return 1;
    }

    long nn = atol(argv[1]);
    long pp = prime(nn);

    printf("Prime #%ld is %ld\n", nn, pp);

    return 0;
}



