#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
    1. Desafio de Processos: A Árvore Genealógica

    Objetivo: Entender a hierarquia e o isolamento de memória do fork().

    Instruções:

        Crie um processo pai que gera dois filhos.

        O Filho 1 deve calcular o fatorial de 5 e exibir o resultado.

        O Filho 2 deve imprimir os primeiros 5 números da sequência de Fibonacci.

        O Pai deve esperar os dois terminarem e, ao final, imprimir o PID (Process ID) de cada um dos seus filhos.

        Dica de mestre: Use wait(NULL) ou waitpid() para sincronizar o pai com o término dos filhos.
*/

int fat(int n) {
    int acc = 1;
    for (int i = n; i > 0; i--) acc*=i;
    return acc;
}


int main() {
    pid_t pid;
    int i = 0;

    pid = fork();
    if (pid<0) exit(1);
    else {
        if(pid == 0) {
            fat(5);
            printf("\nFinalizou 1, pid: %d, filho de %d", getpid(), getppid());
            exit(0);
        } else {
            pid = fork();
            if (pid<0) exit(1);
            else {
                if (pid == 0) {
                    printf("\n\nFibo de 5 = 5\n");
                    printf("Finalizou 2, pid: %d, filho de %d", getpid(), getppid());
                    exit(0);
                }
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }

    printf("\n\n\nPai finalizou: %d", getpid());
}