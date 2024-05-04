#include <stdlib.h>
int main(int argc, char *argv[]) {

    int *arr = malloc(sizeof(int) * 100);
    arr[100] = 0;
    arr[15] = 3;



    printf("index 1: %d\n index 15: %d\n", arr[100], arr[15]);
    return 0;
}
