#include <stdio.h>

int
main(int _ac, char* _av[])
{
    FILE* thing1 = fopen("thing.txt", "w");
    fprintf(thing1, "Hello, thing\n");
    fclose(thing1);

    char temp[80];
    FILE* thing2 = fopen("thing.txt", "r");
    fgets(temp, 80, thing2);
    fclose(thing2);

    fprintf(stdout, "%s", temp);

    return 0;
}
