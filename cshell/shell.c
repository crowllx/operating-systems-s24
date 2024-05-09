#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int execute_cmd(char *argv[], enum Operator flag, int *fd, char *fp) {

    int status = 0;
    printf("cmd: %s\narg: %s\n", argv[0], argv[1]);
    pid_t pid = fork();
    if (pid < 0) {
        perror("Failed to fork\n");
    } else if (pid == 0) {
        if (flag == PIPE) {
            close(fd[0]);
            dup2(fd[1], 1);
            close(fd[1]);
        } else {
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
        }
        if (execvp(argv[0], argv) < 0) {
            printf("\nFailed to execute command.\n");
            exit(-1);
        }
        close(0);
        fflush(stdout);
        exit(0);
    } else {
        close(fd[1]);
        wait(NULL);
    }

    return status;
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
        char *file_path;
        int status;
        char **cmd = tokens;
        int fd[2];

        if (pipe(fd) < 0) {
            printf("failed to create pipe\n");
            return -1;
        }
        while (token_idx < tok_count) {
            op = check_ops(tokens[token_idx]);
            if (op != STDOUT && token_idx < tok_count - 1) {
                tokens[token_idx] = NULL;
                file_path = tokens[token_idx + 1];
                status = execute_cmd(cmd, op, fd, file_path);
                printf("%d\n", status);
                token_idx++;
                cmd += token_idx;
            }
            token_idx++;
        }
        status = execute_cmd(cmd, op, fd, file_path);
        close(fd[0]);
        cmd++;
    }

    return 0;
}
