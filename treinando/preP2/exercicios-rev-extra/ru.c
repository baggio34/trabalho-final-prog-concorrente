#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define TOTAL_ALUNOS 10
#define CAPACIDADE_RU 3

// TODO: Declare seu(s) semáforo(s) aqui

sem_t semaphore;

void* aluno_executa(void* arg) {
    int id = *((int*)arg);
    
    printf("[Aluno %d] Chegou na fila do RU.\n", id);
    
    // TODO: Sincronize a entrada. O aluno só pode passar se houver vaga.
    sem_wait(&semaphore);


    printf("[Aluno %d] ENTROU no RU e está comendo.\n", id);
    sleep(rand() % 3 + 1); // Comendo...
    printf("[Aluno %d] SAIU do RU.\n", id);
    
    // TODO: Sinalize que o aluno saiu e liberou uma vaga.
    sem_post(&semaphore);


    free(arg);
    return NULL;
}

int main() {
    pthread_t alunos[TOTAL_ALUNOS];
    
    // TODO: Inicialize seu semáforo aqui
    sem_init(&semaphore, 0, CAPACIDADE_RU);
    
    for (int i = 0; i < TOTAL_ALUNOS; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&alunos[i], NULL, aluno_executa, id);
    }
    
    for (int i = 0; i < TOTAL_ALUNOS; i++) {
        pthread_join(alunos[i], NULL);
    }
    
    // TODO: Destrua o semáforo
    sem_destroy(&semaphore);

    printf("Todos os alunos comeram. RU fechado!\n");
    return 0;
}