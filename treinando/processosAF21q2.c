/*
    Author: Gabriel Augusto Baggio Varnier
    Date: April 7th, 2026
*/

/*
    Questão: Você deve escrever um programa C em que:

    - O processo principal crie 2 processos filhos.

    - Cada um dos processos filhos deve, por sua vez, criar mais três processos.

    - Cada processo filho (tanto do processo principal quanto dos criados no passo anterior) 
        deve imprimir "Processo XXX, filho de YYY", onde XXX é o PID do processo em questão e YYY 
        o PID do processo que o criou (use as funções getpid() e getppid() para isso).

    - Os processos netos (filhos dos filhos do processo principal) devem, após imprimir esta mensagem, 
        aguardar 5 segundos antes de terminar (use a função sleep() para isso) 

    - Os processos que criaram filhos devem aguardar que seus filhos terminem de executar (utilize a função wait()).

    - Todos os processos filhos devem imprimir, ao finalizar, "Processo XXX finalizado", 
        onde XXX é o PID do processo em questão. O processo principal deve imprimir "Processo principal XXX finalizado", 
        onde XXX é o PID do processo principal.

*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {
    pid_t pid; //cria o processo principal

    // cria 2 filhos
    for (int i = 0; i < 2; i++) {
        pid = fork(); // cria uma duplicata do pai (filho) a cada loop

        if (pid >= 0) { //se pid é positivo criou o processo com sucesso
            if (pid == 0) { //processo filho
                printf("\nProcesso %d, filho de %d\n\n", getpid(), getppid());

                //cada filho cria 3 filhos (netos)
                for (int i = 0; i < 3; i++) {
                    pid_t neto = fork(); //mesma lógica, 3 duplicatas do filho (netos)

                    if (neto == 0) { //processo neto
                        printf("\nProcesso %d, filho de %d. (neto)\n\n", getpid(), getppid());
                        sleep(5); //espera 5 segundos para finalizar o processo
                        printf("Processo %d finalizado. (neto)\n", getpid());
                        exit(0); //processo finalziado com sucesso (neto)
                    }
                }

                //espera os 3 netos
                for (int j = 0; j < 3; j++) {
                    wait(NULL);
                }       
                printf("Processo %d finalizado. (neto)\n", getpid());
                exit(0);


            } else { //processo pai
                printf("\nProcesso pai criou %d\n", pid);
            }
            
        } else {
            printf("\nO processo não pode ser criado");
            return 1;
        }
    }

     // processo principal espera os 2 filhos
    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }

    printf("Processo principal %d finalizado\n", getpid());

    return 0; //retorna sucesso

}