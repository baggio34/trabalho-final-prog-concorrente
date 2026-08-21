/*
    Questão 3: Threads (Passagem de Parâmetros e Race Condition)

    O código tenta passar o valor de i para cada thread. Como &i aponta para o mesmo endereço que muda no loop, 
    ocorre uma condição de corrida no argumento.

    Tarefa: Corrija a criação das threads para que cada uma receba seu valor de ID (0, 1, 2, 3) de forma íntegra.
*/


#include <pthread.h>
#include <stdio.h>

void* tarefa(void* arg) {
    int id = *(int*)arg;
    printf("Thread ID recebido: %d\n", id);
    return NULL;
}

int main() {
    pthread_t threads[4];
    int ids[4]; // DICA: Use este array para salvar os valores

    for (int i = 0; i < 4; i++) {
        // TODO: Corrigir a passagem do parâmetro 'i'
        pthread_create(&threads[i], NULL, tarefa, &i);
    }

    for (int i = 0; i < 4; i++) pthread_join(threads[i], NULL);
    return 0;
}