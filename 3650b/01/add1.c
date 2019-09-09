long
add1(long x)
{
    return x + 1;
}

int
main(int argc, char* argv[])
{
    long x = 5;
    long y = add1(x);
    printf("%ld + 1 = %ld\n", x, y);
    return 0;
}


