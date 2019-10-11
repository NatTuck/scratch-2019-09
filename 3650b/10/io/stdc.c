#include <stdio.h>


int
main(int _ac, char* _av[])
{
    FILE* thing1 = fopen("thing.txt", "w");
    for (int ii = 0; ii < 10; ++ii) {
        fprintf(thing1, "Hello, thing.\n");
    }
    fclose(thing1);

    char temp[80];
    FILE* thing2 = fopen("thing.txt", "r");
    for (int ii = 0; ii < 10; ++ii) {
        fgets(temp, 80, thing2);
        fprintf(stdout, "%s", temp);
    }
    fclose(thing2);


    return 0;
}
