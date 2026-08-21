#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
    Processos (Criação e Hierarquia)

    O código abaixo tenta criar uma estrutura onde um processo pai gera dois filhos, e cada filho imprime seu PID.
    No entanto, o programador cometeu um erro clássico na lógica do fork().

    Tarefa:

        Identifique o erro lógico que faz com que o código crie mais processos do que o pretendido 
        (ou processos "netos" indesejados).

        Corrija o código dentro do bloco for para que apenas o processo pai original crie os dois filhos.
*/



int main() {
    pid_t pid;
    for (int i = 0; i < 2; i++) {
        pid = fork();
        
        if (pid >= 0) {
            if (pid == 0) {
                printf("\nProcesso %d, filho de %d", getpid(), getppid());
                exit(0);
            }
        } else {
            perror("\nErro!");
            exit(1);
        }
    }

    // Espera os filhos terminarem
    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }
    return 0;
}