#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//                          (principal)
//                               |
//              +----------------+--------------+
//              |                               |
//           filho_1                         filho_2
//              |                               |
//    +---------+-----------+          +--------+--------+
//    |         |           |          |        |        |
// neto_1_1  neto_1_2  neto_1_3     neto_2_1 neto_2_2 neto_2_3

// ~~~ printfs  ~~~
//      principal (ao finalizar): "Processo principal %d finalizado\n"
// filhos e netos (ao finalizar): "Processo %d finalizado\n"
//    filhos e netos (ao inciar): "Processo %d, filho de %d\n"

// Obs:
// - netos devem esperar 5 segundos antes de imprmir a mensagem de finalizado (e terminar)
// - pais devem esperar pelos seu descendentes diretos antes de terminar

int main(int argc, char** argv) {
    pid_t pid; 

    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            return 1;
        }

        if(pid == 0) {
            printf("Processo %d, filho de %d", getpid(), getppid());

            for (int j = 0; j < 3; j++) {
                pid_t neto = fork();

                if(neto==0) {
                    printf("Processo %d, filho de %d", getpid(), getppid());
                    sleep(5);
                    printf("Processo %d finalizado\n", getpid());
                    exit(0);        
                }
            }

            for (int k = 0; k < 3; k++) {
                wait(NULL);
            }
            printf("Processo %d finalizado", getpid());
            exit(0);
        } 
    }


    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }
    
    printf("Processo principal %d finalizado\n", getpid());    
    return 0;
}
