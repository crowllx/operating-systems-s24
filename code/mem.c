#include <stdlib.h>
int main(int argc, char *argv[]) {

    char *arr = malloc(sizeof(char) * (int)argv[0]);
    int i = 0;

    while (1) {
        arr[i] = (char) "A";
    }
    return 0;
}
