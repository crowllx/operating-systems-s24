#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        char *argsv[3];
        argsv[0] = "-a";
        argsv[1] = ".";
        argsv[2] = NULL;
        int v_exit = execv("/bin/ls", argsv);

    } else {
        int l_exit = execl("/bin/ls", "/bin/ls", "-l", NULL);
    }
}
