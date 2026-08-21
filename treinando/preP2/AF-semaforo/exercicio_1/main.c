#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

FILE* out;
sem_t sem_a;
sem_t sem_b;
pthread_mutex_t mutex;

int diff = 0;

void *thread_a(void *args) {
    int i = 0;
    int iters = *(int*)args;

    while(i < iters) {
	//      +---> arquivo (FILE*) destino
	//      |    +---> string a ser impressa
	//      v    v
        sem_wait(&sem_a);

        

        pthread_mutex_lock(&mutex);

        if (diff == 1) {
            pthread_mutex_unlock(&mutex);
            sem_post(&sem_a);
            continue;
        }

        fprintf(out, "A");
        // Importante para que vocês vejam o progresso do programa
        // mesmo que o programa trave em um sem_wait().
        fflush(stdout);

        diff++;
        i++;

        pthread_mutex_unlock(&mutex);

        sem_post(&sem_b);
    }
    return NULL;
}

void *thread_b(void *args) {
    int iters = *(int*)args;
    int i = 0;

    while (i < iters) {
        sem_wait(&sem_b);

        pthread_mutex_lock(&mutex);

        if (diff == -1) {
            pthread_mutex_unlock(&mutex);
            sem_post(&sem_b);
            continue;
        }

        fprintf(out, "B");
        fflush(stdout);
        
        diff--;
        i++;

        pthread_mutex_unlock(&mutex);

        sem_post(&sem_a);
    }
    return NULL;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: %s [ITERAÇÕES]\n", argv[0]);
        return 1;
    }
    int iters = atoi(argv[1]);
    srand(time(NULL));
    out = fopen("result.txt", "w");

    pthread_t ta, tb;

    pthread_mutex_init(&mutex, NULL);

    sem_init(&sem_a, 0, 1);
    sem_init(&sem_b, 0, 1);

    // Cria threads
    pthread_create(&ta, NULL, thread_a, &iters);
    pthread_create(&tb, NULL, thread_b, &iters);

    // Espera pelas threads
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    //Imprime quebra de linha e fecha arquivo
    fprintf(out, "\n");
    fclose(out);

    sem_destroy(&sem_a);
    sem_destroy(&sem_b);
    pthread_mutex_destroy(&mutex);

    return 0;
}
