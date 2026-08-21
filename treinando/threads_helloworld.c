#include <pthread.h>
#include <stdio.h>

void * print_helloworld(void *arg) {
    pthread_t tid = pthread_self();
    printf("\nHello world from thread number %d\n", (unsigned int) tid);
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    pthread_t thread;
    pthread_create(&thread, NULL, print_helloworld, NULL);
    pthread_join(thread, NULL);
    return 0;
}