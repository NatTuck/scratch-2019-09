#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <assert.h>

int
main(int argc, char* argv[])
{
    int rv;
    DIR* wd = opendir(".");

    struct dirent* ent;
    struct stat st;

    while ((ent = readdir(wd))) {
        char* name = ent->d_name;
        rv = stat(name, &st);
        assert(rv != -1);

        printf("%s\t%07o\t%ld\n", name, st.st_mode, st.st_size);
    }

    closedir(wd);
    return 0;
}

