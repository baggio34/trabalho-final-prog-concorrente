#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_IMPRESSORAS 3
#define NUM_DOCUMENTOS 10

// TODO: Defina seus semáforos aqui (contador de impressoras livres + fila)
sem_t sem_impressoras;

void* imprimir(void* arg) {
    int id = *((int*)arg);
    
    printf("[Doc %d] Aguardando impressora...\n", id);
    sem_wait(&sem_impressoras);
    
    printf("[Doc %d] IMPRIMINDO...\n", id);
    sleep(2); // Tempo de impressão
    
    printf("[Doc %d] Concluído.\n", id);
    // TODO: Libere a impressora
    sem_post(&sem_impressoras);
    return NULL;
}

int main() {
    pthread_t docs[NUM_DOCUMENTOS];
    int ids[NUM_DOCUMENTOS];
    
    // TODO: Inicialize os semáforos
    sem_init(&sem_impressoras, 0, NUM_IMPRESSORAS);

    for(int i=0; i<NUM_DOCUMENTOS; i++) {
        ids[i] = i;
        pthread_create(&docs[i], NULL, imprimir, &ids[i]);
    }
    for(int i=0; i<NUM_DOCUMENTOS; i++) pthread_join(docs[i], NULL);

    sem_destroy(&sem_impressoras);

    return 0;
}