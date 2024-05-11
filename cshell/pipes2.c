#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {

    int prev_pfd, pfds[2];
    int status;

    int ret = pipe(pfds);
    if (ret < 0) {
        perror("pipe errror");
        exit(0);
    }

    pid_t p = fork();
    if (p < 0) {
        perror("fork failed");
        exit(-1);
    } else if (p == 0) {
        // write to pipe
        dup2(pfds[1], STDOUT_FILENO);
        close(pfds[1]);
        close(pfds[0]);
        char *args[] = {"ls", "-la", NULL};
        execvp(args[0], args);
        perror("exec err");
        exit(0);
    } else {
        close(pfds[1]);
        wait(&status);
        char buf[1024];
        int n;
        n = read(pfds[0],buf, 1024);
        perror("read:");
        printf("Parent: \n%s\n%d\n", buf, n);
    }

    pid_t p2 = fork();
    if (p2 < 0) {
        perror("fork failed: ");
        exit(0);
    } else if (p2 ==0) {
        int n;
        char buf[1024];
        n = read(pfds[0],buf, 1024);
        perror("read:");
        printf("child: \n%s\n%d\n", buf, n);
        exit(0);
    }
    return 0;
}
