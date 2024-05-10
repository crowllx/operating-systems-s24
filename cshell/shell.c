#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// Winston Shine
// Operating Systems

#define DELIMS " \t\n\a\r"
enum Operator { STDOUT, REDIRECT_STDIN, REDIRECT_STDOUT, PIPE };

char **tokenize(char *line, size_t *count) {
    char **tokens = malloc(sizeof(char *) * 20);

    char *tok = strtok(line, DELIMS);

    while (tok != NULL && *count < 20) {
        tokens[*count] = tok;
        (*count)++;
        tok = strtok(NULL, DELIMS);
    }
    tokens[*count] = NULL;
    return tokens;
}
enum Operator check_ops(char *token) {
    if (strcmp(token, "|") == 0) {
        return PIPE;
    } else if (strcmp(token, "<") == 0) {
        return REDIRECT_STDIN;
    } else if (strcmp(token, ">") == 0) {
        return REDIRECT_STDOUT;
    } else {
        return STDOUT;
    }
}

void execute_piped(char *argv[], int *prev_pfd) {
    int pfds[2];

    if (pipe(pfds) < 0) {
        perror("pipe failed");
        exit(-1);
    }
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(-1);
    } else if (pid == 0) {
        if (prev_pfd != STDIN_FILENO) {
            dup2(*prev_pfd, STDIN_FILENO); // previous pipe -> stdin
            close(*prev_pfd);
        }
        dup2(pfds[1], STDOUT_FILENO); // stdout -> new pipe
        close(pfds[1]);
        close(pfds[0]);

        execvp(argv[0], argv);
        perror("execvp error");
        exit(-1);
    } else {
        close(pfds[1]);
        *prev_pfd = pfds[0]; // save read end;
    }
}
void execute(char *argv[], int *prev_pfd) {
    pid_t pid = fork();
    printf("%d\n", pid);
    if (pid == 0) {
        if (prev_pfd != STDIN_FILENO) {
            dup2(*prev_pfd, STDIN_FILENO); // previous pipe -> stdin
            close(*prev_pfd);
        }
        execvp(argv[0], argv);
        perror("execvp err");
        exit(0);
    } else {
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    char buf[80];

    while (1) {
        fgets(buf, 80, stdin);
        char *line = buf;
        size_t tok_count = 0;
        char **tokens = tokenize(line, &tok_count);
        enum Operator op = STDOUT;
        size_t token_idx = 0;
        int prev_pfd, pfd[2];
        char **cmds[20];
        cmds[0] = tokens;
        int cmds_count = 1;

        // break commands in to null terminated lists of arguments
        while (token_idx < tok_count) {
            printf("token: %s\n", tokens[token_idx]);
            op = check_ops(tokens[token_idx]);
            if (op != STDOUT) {
                tokens[token_idx] = NULL;
                cmds[cmds_count] = &tokens[token_idx + 1];
                cmds_count++;
            }
            token_idx++;
        }

        // execute commands
        size_t i = 0;
        while (i < cmds_count - 1) {
            execute_piped(cmds[i], &prev_pfd);
            i++;
        }
        execute(cmds[cmds_count - 1], &prev_pfd);
    }

    return 0;
}
