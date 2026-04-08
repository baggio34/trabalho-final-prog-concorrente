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
    pid_t pid; //pid_t é um tipo de dado referente ao id do processo, aqui estou criando o processo pai

    for (int i = 0; i <= 1; i++) { // roda 2 vezes
        pid = fork(); // a cada iteração do loop cria um novo pid, ou seja, cria o filho a partir do pai, o filho é duplicata do pai

        if (pid >= 0) { //se pid é positivo criou o processo com sucesso

            if (pid == 0) { //processo filho
                printf("\nProcesso filho %d criado\n\n", getpid());
                exit(0); // encerra o processo e retorna sucesso
            } else { //processo pai (pid > 0)
                printf("\nProcesso pai criou %d\n", pid);
            }
        } else { //criação falhou
            printf("\nO processo não pode ser criado");
            return 1; //retorna falha
        }
    }

    // Processo pai aguarda o encerramento dos 2 filhos
    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }

    printf("\n\nProcesso pai finalizado!\n");
    
    // retorna sucesso
    return 0;
    
}