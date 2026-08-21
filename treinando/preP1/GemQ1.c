#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


/*
    Cenário: 
        O código abaixo implementa um sistema simples onde duas threads trabalhadoras tentam 
        inserir elementos em um buffer global indexado por uma variável P. Do jeito que está escrito, 
        o código apresenta uma condição de corrida severa na variável P e no array buffer.

    Sua tarefa: 
        Identifique a região crítica e adicione os mecanismos de sincronização do padrão POSIX (pthread_mutex_t) 
        nos locais corretos para garantir a exclusão mútua sem gerar deadlocks.
*/



#define SIZE 100
char buffer[SIZE];
int P = 0;
pthread_mutex_t mutex;

void* trabalhadora(void* arg) {
    char caractere = *((char*) arg);
    for(int i = 0; i < 50; i++) {
        // --- Início do trecho problemático ---
        pthread_mutex_lock(&mutex);

        if (P < SIZE) {
            buffer[P] = caractere;
            P = P + 1;
        }
        
        pthread_mutex_unlock(&mutex);
        // --- Fim do trecho problemático ---
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;
    char c1 = 'A', c2 = 'B';

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, trabalhadora, &c1);
    pthread_create(&t2, NULL, trabalhadora, &c2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("Elementos inseridos no buffer: %d\n", P);
    return 0;
}