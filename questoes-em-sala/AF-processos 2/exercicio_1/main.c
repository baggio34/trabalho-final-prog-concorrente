#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//       (pai)
//         |
//    +----+----+
//    |         |
// filho_1   filho_2

// ~~~ printfs  ~~~
// pai (ao criar filho): "Processo pai criou %d\n"
//    pai (ao terminar): "Processo pai finalizado!\n"
//  filhos (ao iniciar): "Processo filho %d criado\n"

// Obs:
// - pai deve esperar pelos filhos antes de terminar!

int main(int argc, char **argv) {

  // ....

  /*************************************************
   * Dicas:                                        *
   * 1. Leia as intruções antes do main().         *
   * 2. Faça os prints exatamente como solicitado. *
   * 3. Espere o término dos filhos                *
   *************************************************/

  pid_t pid; // pid_t é um tipo de dado referente ao id do processo, aqui estou
             // criando o processo pai

  for (int i = 0; i <= 1; i++) { // roda 2 vezes
    pid = fork(); // a cada iteração do loop cria um novo pid, ou seja, cria o
                  // filho a partir do pai, o filho é duplicata do pai

    if (pid >= 0) { // se pid é positivo criou o processo com sucesso

      if (pid == 0) { // processo filho
        printf("Processo filho %d criado\n", getpid());
        exit(0); // encerra o processo e retorna sucesso
      } else {   // processo pai (pid > 0)
        printf("Processo pai criou %d\n", pid);
      }
    } else { // criação falhou
      printf("\nO processo não pode ser criado");
      return 1; // retorna falha
    }
  }

  // Processo pai aguarda o encerramento dos 2 filhos
  for (int i = 0; i < 2; i++) {
    wait(NULL);
  }

  printf("Processo pai finalizado!\n");

  // retorna sucesso
  return 0;
}