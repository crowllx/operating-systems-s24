#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int execute_cmd(char *argv[], enum Operator flag, int *pipe, char *fp) {

    pid_t pid = fork();

    if (pid < 0) {
        perror("Failed to fork");
    } else if (pid == 0) {
        char args[80];
        size_t i = 1;
        while (argv[i] != NULL) {
            strcat(args, argv[i]);
            i++;
        }
        printf("%s\n%s\n", argv[0], args);
        execvp(argv[0], argv);
    } else {
        waitpid(NULL);
    }

    return 0;
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
        int pipe_fd[2];
        pipe(pipe_fd);

        char **cmd = tokens;
        while (token_idx < tok_count) {
            op = check_ops(tokens[token_idx]);
            if (op != STDOUT && token_idx < tok_count - 1) {
                tokens[token_idx] = NULL;
                file_path = tokens[token_idx + 1];
                status = execute_cmd(cmd, op, pipe_fd, file_path);
                token_idx++;
                cmd += token_idx;
            }
            token_idx++;
            printf("%p\n",cmd);
        }
        status = execute_cmd(cmd, op, pipe_fd, file_path);
        cmd++;
    }

    return 0;
}
