#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// Winston Shine
// Operating Systems

#define DELIMS " \t\n\a\r"
#define prompt_color "\x1b[35m"
#define bold "\x1b[1m"
#define color_end "\x1b[0m"

enum Operator { NONE, STDOUT, REDIRECT_STDIN, REDIRECT_STDOUT, PIPE };

void prompt() { printf(prompt_color bold "\n> " color_end); }

// break given command in to null terminated lists of strings split on
// whitespace
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

// execute a command and redirect its stdout to a pipe
int execute_piped(char *argv[], int *prev_pfd) {
    int pfds[2];
    printf("*** PIPED ***\n");
    int status;
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
        wait(&status);
    }
    return status;
}

// TODO: allow redirections that precede pipes
// execute a command and either redirect a file to its STDIN
// or redirect its STDOUT to a file
int execute_redirect(char *argv[], int *prev_pfd, char *fp, enum Operator op) {
    int status;
    printf("*** REDIRECT ***\n");

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(-1);
    } else if (pid == 0) {
        if (op == REDIRECT_STDOUT) {
            if (prev_pfd != STDIN_FILENO) {
                dup2(*prev_pfd, STDIN_FILENO); // previous pipe -> stdin
                close(*prev_pfd);
            }
            int fd = open(fp, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (fd < 0) {
                perror("error on open: ");
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } else if (op == REDIRECT_STDIN) {
            int fd = open(fp, O_RDONLY);
            if (fd < 0) {
                perror("error on open: ");
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        execvp(argv[0], argv);
        perror("error on execvp");
        exit(-1);
    } else {
        wait(&status);
    }
    return status;
}

int execute(char *argv[], int *prev_pfd) {
    printf("*** EXEC ***\n");
    int status;
    pid_t pid = fork();
    if (pid == 0) {
        if (prev_pfd != STDIN_FILENO) {
            dup2(*prev_pfd, STDIN_FILENO); // previous pipe -> stdin
            close(*prev_pfd);
        }
        execvp(argv[0], argv);
        perror("execvp err");
        exit(0);
    } else {
        wait(&status);
    }
    return status;
}

int main(int argc, char *argv[]) {
    char buf[80];

    while (1) {
        prompt();
        fgets(buf, 80, stdin);
        char *line = buf;
        size_t tok_count = 0;
        char **tokens = tokenize(line, &tok_count);
        enum Operator op = STDOUT;
        size_t token_idx = 0;
        int prev_pfd, pfd[2];
        size_t next_cmd = 0;
        int prev_status = 0;

        while (token_idx < tok_count) {
            printf("token: %s\n", tokens[token_idx]);
            op = check_ops(tokens[token_idx]);
            switch (op) {
            case PIPE:
                tokens[token_idx] = NULL;
                printf("tokens: %p, cmd: %p, op: %d\n", tokens,
                       tokens[next_cmd], op);
                printf("cmd: %s arg1: %s\n", tokens[next_cmd],
                       tokens[next_cmd + 1]);
                prev_status = execute_piped(&tokens[next_cmd], &prev_pfd);
                next_cmd = token_idx + 1;
                break;
            case REDIRECT_STDIN:
            case REDIRECT_STDOUT:
                tokens[token_idx] = NULL;
                char *fp = tokens[token_idx + 1];
                prev_status =
                    execute_redirect(&tokens[next_cmd], &prev_pfd, fp, op);
                next_cmd = token_idx + 2;
                token_idx++;
                break;
            default:
                break;
            }
            token_idx++;
        }
        // execute last command
        printf("tokens: %p, cmd: %p\n", tokens, tokens[next_cmd]);
        printf("cmd: %s arg1: %s\n", tokens[next_cmd], tokens[next_cmd + 1]);
        if (tokens[next_cmd] != NULL) {
            prev_status = execute(&tokens[next_cmd], &prev_pfd);
        }
        if (prev_pfd != STDIN_FILENO) {
            printf("PREV closed\n");
            close(prev_pfd);
        }
        free(tokens); // can i do this without re mallocing/freeing each loop?
    }

    return 0;
}
