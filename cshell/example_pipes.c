#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int fd[2];

    pipe(fd);

    pid_t p = fork();
    int status= 0;
    if (p < 0) {
        exit(-1);
    } else if (p == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        char* args[] = { "ls", "-la", NULL};
        execvp(args[0], args);
    } else {
        wait(&status);
    }
    printf("%d",status);
    p = fork();

    if (p < 0) {
        exit(-1);
    } else if (p == 0) {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        char* args[] = { "grep", "shell", NULL};
        execvp(args[0], args);
    } else {
        close(fd[0]);
        close(fd[1]);
        wait(&status);
    }
    printf("%d",status);
    return 0;
}
