/*
    Author: Gabriel Augusto Baggio Varnier
    Date: April 7th, 2026
*/

/*
    Questão: Você deve escrever um programa em C em que o processo pai crie 2 processos filhos (fork()). 

    Para cada processo filho criado, o processo pai deve imprimir "Processo pai criou XXX", 
    onde XXX é o PID do processo criado.

    Cada processo filho deve apenas imprimir "Processo filho XXX criado", 
    onde XXX é o PID do processo corrente (use a função getpid() para isso).

    O processo pai (e apenas ele) deve imprimir "Processo pai finalizado!", 
    somente após os filhos terminarem (use a função wait() para aguardar que os filhos terminem de executar).
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {
    pid_t pid;

    for (int i = 0; i <= 1; i++) {
        pid = fork();

        if (pid >= 0) { //se pid é positivo criou o processo

            if (pid == 0) { //processo filho
                printf("\nProcesso filho %d criado\n\n", getpid());
                exit(0);
            } else { //processo pai
                printf("\nProcesso pai criou %d\n", pid);
            }
        } else {
            printf("\nO processo não pode ser criado");
            return 1;
        }
    }

    wait(NULL);
    wait(NULL);

    printf("\n\nProcesso pai finalizado!\n");
    
    return 0;
    
}