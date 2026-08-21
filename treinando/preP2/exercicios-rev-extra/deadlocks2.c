#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
pthread_mutex_t garfos[N];

void* filosofo(void* arg) {
    int i = *((int*)arg);
    
    while(1) {
        // 1. Pensar
        printf("Filósofo %d pensando", i);
        sleep(1);
        
        if (i == N - 1) {
            pthread_mutex_lock(&garfos[(i+1)%N]);
            pthread_mutex_lock(&garfos[i]);
        } else {
            pthread_mutex_lock(&garfos[i]);
            pthread_mutex_lock(&garfos[(i+1)%N]);
        }


    
        
        
        // 3. Comer
        printf("Filósofo %d comendo", i);
        sleep(1);
        
        // 4. Devolver os garfos
        // Dica: Use pthread_mutex_unlock(&garfos[i]);

        pthread_mutex_unlock(&garfos[(i+1)%N]);
        pthread_mutex_unlock(&garfos[i]);

        printf("Filósofo %d saindo", i);
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    // TODO: Inicializar os N mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&garfos[i], NULL);
    }
    
    // TODO: Criar as N threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, filosofo, &ids[i]);
    }

    // TODO: Join das threads
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }


    return 0;
}