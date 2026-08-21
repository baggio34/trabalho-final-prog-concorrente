#include <sys/semaphore.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <stddef.h>




#define CONTINENTE  0               // Representa a cabeceira do continente
#define ILHA        1               // Representa a cabeceira da ilha
#define N_VEICULOS  20              // Máximo de veículos na ponte

sem_t sem_passar[2];                // Libera para entrar por uma cabeceira
pthread_mutex_t mtx_chegadas;       // Protege chegadas
int chegadas[2] = {0, 0};           // Quantos chegaram em uma cabeceira

void ponte_open() {
    // IMPLEMENTAR!
    sem_t semaforoContinente = sem_init(&sem_passar[0], 0, N_VEICULOS);
    sem_t semaforoIlha = sem_init(&sem_passar[1], 0, 0);
    pthread_mutex_init(&mtx_chegadas, NULL);
}

void ponte_entrar(int cabeceira) {
    // IMPLEMENTAR!
    sem_wait(&sem_passar[cabeceira]);
} 

void ponte_sair(int cabeceira) {
    // IMPLEMENTAR!
    pthread_mutex_lock(&mtx_chegadas);

    chegadas[cabeceira]++;

    if (chegadas[cabeceira] == N_VEICULOS) {
        chegadas[cabeceira] = 0;
        

        for (int i = 0; i < N_VEICULOS; i++) {
            sem_post(&sem_passar[cabeceira]);
        }
    }

    pthread_mutex_unlock(&mtx_chegadas);
}


