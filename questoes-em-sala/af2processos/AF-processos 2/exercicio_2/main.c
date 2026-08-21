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
// - netos devem esperar 5 segundos antes de imprmir a mensagem de finalizado (e
// terminar)
// - pais devem esperar pelos seu descendentes diretos antes de terminar

int main(int argc, char **argv) {

  // ....

  /*************************************************
   * Dicas:                                        *
   * 1. Leia as intruções antes do main().         *
   * 2. Faça os prints exatamente como solicitado. *
   * 3. Espere o término dos filhos                *
   *************************************************/

  pid_t pid; // cria o processo principal

  // cria 2 filhos
  for (int i = 0; i < 2; i++) {
    pid = fork(); // cria uma duplicata do pai (filho) a cada loop

    if (pid >= 0) {   // se pid é positivo criou o processo com sucesso
      if (pid == 0) { // processo filho
        printf("Processo %d, filho de %d\n", getpid(), getppid());

        // cada filho cria 3 filhos (netos)
        for (int i = 0; i < 3; i++) {
          fflush(stdout);
          pid_t neto = fork(); // mesma lógica, 3 duplicatas do filho (netos)

          if (neto == 0) { // processo neto
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            sleep(5); // espera 5 segundos para finalizar o processo
            printf("Processo %d finalizado\n", getpid());
            exit(0); // processo finalziado com sucesso (neto)
          }
        }

        // espera os 3 netos
        for (int j = 0; j < 3; j++) {
          wait(NULL);
        }
        printf("Processo %d finalizado\n", getpid());
        exit(0);
      }

    } else {
      return 1;
    }
  }

  // processo principal espera os 2 filhos
  for (int i = 0; i < 2; i++) {
    wait(NULL);
  }

  printf("Processo principal %d finalizado\n", getpid());
  return 0; // retorna sucesso
}