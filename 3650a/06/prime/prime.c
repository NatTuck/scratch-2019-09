
// Print the N'th prime number.

// The plan:
//  - Allocate an array to store N primes.
//  - Pre-load first 3 primes.
//  - A number x is prime if it's not divisible by any prime up to sqrt(x)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long
sqrt_up(long xx)
{
    return (long)ceil(sqrt(xx));
}

int
is_prime(long* primes, long xx)
{
    for (long ii = 1; primes[ii] <= sqrt_up(xx); ++ii) {
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
    long primes[nn];
    /*
    for (long ii = 0; ii < nn; ++ii) {
        primes[ii] = 0;
    }
    */
   
    0[primes] = 2;  // primes[0] = *(primes + 0) = *(0 + primes) = 0[primes]
    1[primes] = 3;
    2[primes] = 5;

    for (long ii = 3; ii < nn; ++ii) {
        long guess = (ii-1)[primes] + 2;

        while (!is_prime(primes, guess)) {
            guess += 2;
        }

        primes[ii] = guess;
    }

    return primes[nn - 1];
}

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        puts("Usage:\n  ./prime N\n");
        return 1;
    }

    long nn = atol(argv[1]);
    long pp = prime(nn);

    printf("Prime %ld is %ld\n", nn, pp);

    return 0;
}





