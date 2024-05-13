#include <assert.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// Winston Shine
// Operating Systems

#define prompt_color "\x1b[35m"
#define bold "\x1b[1m"
#define color_end "\x1b[0m"

#define DELIMS " \t\n\a\r"
#define MAX_CMDS 10
#define MAX_TOKENS 20

enum Op { EXEC, PIPE, AND, OR };
struct Command {
    char **args;
    int op;
    int status;
    pid_t pid;
    char *file_in;
    char *file_out;
    int outfile_mode;
    int read_pfd;
};

void prompt() { printf(prompt_color bold "\n> " color_end); }

void print_cmd(struct Command *cmd) {
    printf("argv: ");
    size_t i = 0;
    while (cmd->args[i] != NULL) {
        printf("%s ", cmd->args[i]);
        i++;
    }
    printf("\nop: %d\n", cmd->op);
    printf("append: %d\n", cmd->outfile_mode);
    printf("file in: %s\n", cmd->file_in);
    printf("file out: %s\n", cmd->file_out);
    printf("pid: %d\n", cmd->pid);
}

void change_dir(struct Command *cmd) {
    /* print_cmd(cmd); */
    char *path;
    if (cmd->args[1] == NULL || strcmp(cmd->args[1], "~") == 0) {
        path = getenv("HOME");
    } else {
        path = cmd->args[1];
    }

    if (chdir(path) < 0) {
        perror("cd");
    }
}

char **build_args() {
    char **args = malloc(sizeof(char *) * MAX_TOKENS);
    for (size_t i = 0; i < MAX_TOKENS; i++) {
        args[i] = NULL;
    }
    return args;
}

void parse_commands(char *line, size_t *count, struct Command *cmds) {
    char *tok = strtok(line, DELIMS);
    while (*count < MAX_CMDS && tok != NULL) {
        char **args = build_args();
        cmds[*count].args = args;
        cmds[*count].op = EXEC;
        cmds[*count].status = 0;
        cmds[*count].pid = 0;
        cmds[*count].file_in = NULL;
        cmds[*count].file_out = NULL;
        cmds[*count].outfile_mode = 0;
        cmds[*count].read_pfd = -1;
        size_t i = 0;
        while (tok != NULL && i < MAX_TOKENS) {
            args[i] = tok;
            if (strcmp(tok, "|") == 0) {
                args[i] = NULL;
                cmds[*count].op = PIPE;
                tok = strtok(NULL, DELIMS);
                break;
            } else if (strcmp(tok, "<") == 0) {
                args[i] = NULL;
                cmds[*count].file_in = strtok(NULL, DELIMS);
            } else if (strcmp(tok, ">") == 0) {
                args[i] = NULL;
                cmds[*count].file_out = strtok(NULL, DELIMS);
                cmds[*count].outfile_mode = O_WRONLY | O_TRUNC | O_CREAT;
            } else if (strcmp(tok, ">>") == 0) {
                args[i] = NULL;
                cmds[*count].file_out = strtok(NULL, DELIMS);
                cmds[*count].outfile_mode = O_WRONLY | O_APPEND | O_CREAT;
            }
            i++;
            tok = strtok(NULL, DELIMS);
        }
        (*count)++;
    }
}
void exec_cmd(struct Command *cmd, int *prev_pfd, int pfds[2]) {

    int rval = pipe(pfds);
    if (rval < 0) {
        perror("pipe");
        exit(0);
    }
    /* printf("new pipe fds: %d, %d\n\n", pfds[0], pfds[1]); */

    if (strcmp(cmd->args[0], "cd") == 0) {
        change_dir(cmd);
        return;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(0);
    } else if (pid == 0) {
        // redirect STDIN, either from file or from previous commands pipe
        if (cmd->file_in != NULL) {
            int fd = open(cmd->file_in, O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        } else if (*prev_pfd > 0) {
            dup2(*prev_pfd, STDIN_FILENO);
            close(*prev_pfd);
        }

        // redirect STDOUT
        if (cmd->file_out != NULL) {
            int fd = open(cmd->file_out, cmd->outfile_mode, 0644);
            if (fd < 0) {
                perror("open");
                exit(0);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } else if (cmd->op == PIPE) {
            dup2(pfds[1], STDOUT_FILENO); // stdout -> pipe write end
            close(pfds[0]);
            close(pfds[1]);
        }

        // execute cmd
        execvp(cmd->args[0], cmd->args);
        perror(cmd->args[0]);
        exit(0);
    } else {
        cmd->pid = pid;
        *prev_pfd = pfds[0]; // save read end of pipe for next process
        close(pfds[1]);
    }
}
int main(int argc, char *argv[]) {
    char buf[80];

    while (1) {
        prompt();
        fgets(buf, 80, stdin);
        char *line = buf;
        size_t cmd_count = 0;
        int exit_flag = -1;
        struct Command cmds[MAX_CMDS];

        // needs free
        parse_commands(line, &cmd_count, cmds);

        // debug
        /* for (int i = 0; i < cmd_count; i++) { */
        /*     print_cmd(&cmds[i]); */
        /* } */

        // execute loop
        int prev_pfd = -1;
        int pfds[cmd_count][2];
        for (size_t i = 0; i < cmd_count; i++) {
            pfds[cmd_count][0] = 0;
            pfds[cmd_count][1] = 0;
            cmds[i].read_pfd = prev_pfd;
            if (strcmp(cmds[i].args[0], "exit") == 0) {
                exit_flag = 0;
            } else {
                exec_cmd(&cmds[i], &prev_pfd, pfds[i]);
            }
        }

        // clean up
        for (int i = 0; i < cmd_count; i++) {
            waitpid(cmds[i].pid, &cmds[i].status, 0);
        }
        for (int i = 0; i < cmd_count; i++) {
            if (fcntl(pfds[i][0], F_GETFL) != -1) {
                close(pfds[i][0]);
            }
            free(cmds[i].args);
        }

        if (exit_flag == 0) {
            break;
        }
    }
    return 0;
}
