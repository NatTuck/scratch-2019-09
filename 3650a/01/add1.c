
long 
add1(long x)
{
    return x + 1;
}

int 
main(int argc, char* argv[])
{
    long a = 5;
    long b = add1(a);
    printf("%ld + 1 = %ld\n", a, b);
    return 0;
}
