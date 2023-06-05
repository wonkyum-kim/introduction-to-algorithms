#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int res = 0;

void *fibonacci_thread(void *arg) {
    int n = *(int*)arg;
    if (n <= 1) {
        res += n;
    } else {
        pthread_t threads[2];
        int n1 = n - 1;
        int n2 = n - 2;
        pthread_create(&threads[0], NULL, fibonacci_thread, (void*)(&n1));
        pthread_create(&threads[1], NULL, fibonacci_thread, (void*)(&n2));
        for (int i = 0; i < 2; ++i) {
            pthread_join(threads[i], NULL);
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;

    int n = 8;

    pthread_create(&thread, NULL, fibonacci_thread, (void*)&n);
    pthread_join(thread, NULL);
    printf("%d\n", res);

    return 0;
}
