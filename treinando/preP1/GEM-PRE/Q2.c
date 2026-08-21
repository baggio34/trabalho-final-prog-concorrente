/*
    Questão 2: Processos (O Problema da Cópia de Memória)

    Este código tenta usar uma variável global para contar quantas vezes o bloco foi executado por dois processos (Pai e Filho).
    O programador espera que o valor final seja 2.

    Tarefa:

        Corrija o código para que o Pai espere o Filho.

        Explique (ou comente no código) por que o contador no Pai ainda será 1 ao final
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int contador = 0; // Variável Global

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Erro");
        exit(1);
    }

    if (pid == 0) {
        contador++;
        printf("Filho: contador = %d\n", contador);
        exit(0);
    } else {
        // TODO: Esperar o filho
        wait(NULL);
        contador++;
        printf("Pai: contador = %d\n", contador);
    }
    return 0;
}

/*
    O contador permanecerá 1 porque processos tem memórias separadas e suas próprias cópias de variáveis, o que o filho altera
    não é visível ao pai
*/