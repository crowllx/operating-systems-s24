#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int count = 0;
pthread_mutex_t lock;

void *increment() {
    pthread_mutex_lock(&lock);
    count++;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char *argv[]) {
    struct timeval tv;
    time_t start;
    gettimeofday(&tv, NULL);
    start = tv.tv_sec;
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    while (count < 100000) {
        pthread_create(&thread1, NULL, increment, NULL);
        pthread_create(&thread2, NULL, increment, NULL);
        pthread_create(&thread3, NULL, increment, NULL);
    }
    gettimeofday(&tv, NULL);
    time_t end;
    end = tv.tv_sec;

        
    printf("start: %ld\n end: %ld\n duration: %ld\n", start, end, end - start);

    return 0;
}
