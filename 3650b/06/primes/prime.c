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

int
is_prime(long* primes, long xx)
{
    for (long ii = 0; primes[ii] <= sqrt_up(xx); ++ii) {
        long pp = *(primes + ii);   // primes[ii]
        if ((xx % pp) == 0) {
            return 0;
        }
    }
    return 1;
}


long
prime(long nn)
{
    long primes[nn + 1];
    for (long ii = 0; ii < nn; ++ii) {
        primes[ii] = 0;
    }

    0[primes] = 2; // 0[primes]=*(0 + primes)=*(primes + 0)=primes[0]
    1[primes] = 3;
    2[primes] = 5;

    for (long ii = 3; ii < (nn + 1); ++ii) {
        long guess = primes[ii - 1] + 1;

        while (!is_prime(primes, guess)) {
            guess++;
        }

        primes[ii] = guess;
    }

    return primes[nn];
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



