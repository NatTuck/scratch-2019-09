
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>


int
main(int argc, char* argv[])
{
    int cpid, rv;

    int pipes[2];
    rv = pipe(pipes);
    assert(rv != -1);

    // pipes[0] for reading
    // pipes[1] for writing

    if ((cpid = fork())) {
        assert(cpid != -1);

        // parent
        rv = close(pipes[1]);
        assert(rv != -1);

        char tmp[256];
        int  nn;

        do {
            nn = read(pipes[0], tmp, 256);
            assert(nn != -1);

            for (int ii = 0; ii < nn; ++ii) {
                if (tmp[ii] == 'e') {
                    tmp[ii] = 'E';
                }
            }

            rv = write(1, tmp, nn);
            assert(rv != -1);
        } while(nn != 0);

        int status;
        waitpid(cpid, &status, 0);
    }
    else {
        // child
        close(pipes[0]);
        close(1);

        rv = dup(pipes[1]);
        assert(rv != -1);
        rv = close(pipes[1]);
        assert(rv != -1);

        char* args[] = {"sort", "sample.txt", 0};
        execvp("sort", args);
        assert(0);
    }

    return 0;
}
