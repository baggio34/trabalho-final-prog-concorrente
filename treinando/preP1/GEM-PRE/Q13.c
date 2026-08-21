/*
    Você deve completar um código onde 5 threads tentam escrever 10 mensagens cada em um "servidor de log" (representado por uma variável global e um printf).

    Sem o Mutex, as mensagens podem sair embaralhadas.

    Com o Mutex, cada thread deve conseguir escrever sua mensagem inteira sem interrupção.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Variáveis Globais
int mensagens_enviadas = 0;
// TODO: Declare aqui o seu mutex
pthread_mutex_t trava;

void* tarefa_log(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 10; i++) {
        // --- INÍCIO DA REGIÃO CRÍTICA ---
        // TODO: Bloqueie o mutex aqui
        pthread_mutex_lock(&trava);

        mensagens_enviadas++;
        printf("Thread #%d escrevendo log %d... [Total: %d]\n", id, i+1, mensagens_enviadas);
        
        // Simulando um processamento rápido
        usleep(1000); 

        // TODO: Desbloqueie o mutex aqui
        pthread_mutex_unlock(&trava);
        // --- FIM DA REGIÃO CRÍTICA ---
        
        usleep(1000); // Pausa fora da região crítica para dar chance a outras threads
    }

    free(arg);
    return NULL;
}

int main() {
    pthread_t threads[5];

    // TODO: Inicialize o mutex aqui
    pthread_mutex_init(&trava, NULL);

    for (int i = 0; i < 5; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        // TODO: Crie as threads chamando a função 'tarefa_log'
        pthread_create(&threads[i], NULL, tarefa_log, id);
    }

    for (int i = 0; i < 5; i++) {
        // TODO: Aguarde a finalização das threads
        pthread_join(threads[i], NULL);
    }

    // TODO: Destrua o mutex aqui
    pthread_mutex_destroy(&trava);

    printf("\nFim da execução. Total de mensagens: %d\n", mensagens_enviadas);
    return 0;
}