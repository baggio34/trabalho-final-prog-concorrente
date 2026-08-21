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


int main(int argc, char** argv) {
    pid_t pid;  // cria o pai

    for (int i = 0; i < 2; i++) {     // criar 2 filhos  
        pid = fork();                 // cria o filho com fork

        if (pid >= 0) {               // se o pid for >= 0 deu certo
            if (pid == 0) {           // pid == 0 é processo criado
                printf("Filho %d", getpid());  // getpid para capturar o pid do processo atual
                exit(0);                // exit com sucesso
            } else {                    // se o pid é maior que 0 é o processo pai, e ele é igual ao pid do filho
                printf("Processo pai criou %d", pid);   // pid == pid do filho gerado
            }
        } else {        // deu erro
            printf("\nO processo não foi criado");
            return 1;       // return com erro
        }
    }

    for (int i = 0; i < 2; i++) {
        wait(NULL); // espera os dois filhos encerrarem
    }

    printf("Processo pai finalizado");  // pai finalizado

    return 0;       // retorna sucesso
}
