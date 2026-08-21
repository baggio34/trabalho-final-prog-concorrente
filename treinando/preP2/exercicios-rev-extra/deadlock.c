#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex_servidorA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_servidorB = PTHREAD_MUTEX_INITIALIZER;

void transferir_dados(pthread_mutex_t* origem, pthread_mutex_t* destino, const char* nome_origem, const char* nome_destino) {

    if (origem < destino) {
        pthread_mutex_lock(origem);
        printf("Travou %s. Aguardando %s...\n", nome_origem, nome_destino);

        sleep(1); // Simula atraso na rede, forçando o deadlock
        
        pthread_mutex_lock(destino);
    } else {
        pthread_mutex_lock(destino);
        printf("Travou %s. Aguardando %s...\n", nome_origem, nome_destino);

        sleep(1);
        pthread_mutex_lock(origem);
    }

    printf("Transferindo dados de %s para %s...\n", nome_origem, nome_destino);

    if (origem < destino) {
        pthread_mutex_unlock(destino);
        pthread_mutex_unlock(origem);
    } else {
        pthread_mutex_unlock(origem);
        pthread_mutex_unlock(destino);
    }
}

void* rotina_servidorA(void* arg) {
    transferir_dados(&mutex_servidorA, &mutex_servidorB, "Servidor A", "Servidor B");
    return NULL;
}

void* rotina_servidorB(void* arg) {
    transferir_dados(&mutex_servidorB, &mutex_servidorA, "Servidor B", "Servidor A");
    return NULL;
}

int main() {
    pthread_t tA, tB;
    pthread_create(&tA, NULL, rotina_servidorA, NULL);
    pthread_create(&tB, NULL, rotina_servidorB, NULL);
    
    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    
    printf("Transferências concluídas sem deadlock!\n");
    return 0;
}