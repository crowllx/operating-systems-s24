#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Winston Shine
// Operating Systems
// Lab week 5

void string_trim(char *input) {
  char *tmp = strdup(input);
  size_t size = strlen(input);
  size_t start = 0;
  size_t end = size - 1;

  while (start < size && isspace(input[start])) {
    start++;
  }
  while (end > 0 && isspace(input[end])) {
    end--;
  }
  int i = 0;
  for (start; start < end + 1; start++) {
    input[i] = tmp[start];
    i++;
  }
  input[i] = '\0';
}

char *get_args(char *input) {
  size_t len = strlen(input);
  size_t split = 0;
  while (split < len && !isspace(input[split])) {
    split++;
  }
  size_t args_start = split;
  while (args_start < len && isspace(input[args_start])) {
    args_start++;
  }
  input[split] = '\0';

  char *args = input + args_start * sizeof(char);
  /* printf("%p\n", input); */
  /* printf("%p\n", args); */
  return args;
}
int main(int argc, char *argv[]) {
  char buf[80];

  while (1) {
    // get cmd
    fgets(buf, sizeof(buf), stdin);
    string_trim(buf);

    char *args = get_args(buf);

    pid_t p = fork();

    if (p < 0) {
      perror("fork failed");
      return 1;
    } else if (p == 0) {
      // child
      execlp(buf, args);
    } else {
      waitpid(p, NULL, 0);
    }
  }

  return 0;
}
