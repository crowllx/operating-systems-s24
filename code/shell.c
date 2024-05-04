#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
    printf("%s", tmp);
    input[i] = '\0';
}
int main(int argc, char *argv[]) {
    char buf[80];

    while (1) {
        fgets(buf, sizeof(buf), stdin);
        string_trim(buf);
        printf("%s\n", buf);
    }

    return 0;
}
