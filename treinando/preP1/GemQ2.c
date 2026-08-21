#include <pthread.h>
#include <math.h>

#define N_THREADS 4
#define T 1000000
double vetor[T];

typedef struct {
    int inicio;
    int fim;
} intervalo_t;

void* thread_func(void* arg) {
    intervalo_t* inter = (intervalo_t*) arg;
    // (A) Implemente o loop que processa a fatia do vetor:
    for (int i = __________; i < __________; i++) {
        vetor[i] = sqrt(vetor[i]) * 1.5;
    }
    return NULL;
}

int main() {
    pthread_t threads[N_THREADS];
    intervalo_t intervalos[N_THREADS];
    
    for (int i = 0; i < N_THREADS; i++) {
        // (B) Calcule os limites de cada thread:
        intervalos[i].inicio = i * (T / N_THREADS);
        intervalos[i].fim = ________________________;
        
        // (C) Crie a thread passando o intervalo:
        pthread_create(____________________________);
    }
    // ... joins omitidos
}