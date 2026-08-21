#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

//                 (main)
//                    |
//    +----------+----+------------+
//    |          |                 |
// worker_1   worker_2   ....   worker_n

// ~~~ argumentos (argc, argv) ~~~
// ./program n_threads

// ~~~ printfs  ~~~
// main thread (após término das threads filhas): "Contador: %d\n"
// main thread (após término das threads filhas): "Esperado: %d\n"

// Obs:
// - pai deve criar n_threds (argv[1]) worker threads
// - cada thread deve incrementar contador_global (operador ++) n_loops vezes
// - pai deve esperar pelas worker threads  antes de imprimir!

/*
    Respostas das perguntas:

    1. Qual a relação entre n_threads e a diferença entre "Contador" e "Esperado"?
        R: Quanto maior o número de threads, maior tende a ser a diferença entre
        "Contador" e "Esperado". Isso acontece porque mais threads executando em
        paralelo aumentam a quantidade de acessos concorrentes à variável
        contador_global, intensificando a condição de corrida.

    2. Qual a relação entre n_loops e a diferença entre "Contador" e "Esperado"?
        R: Quanto maior o valor de n_loops, maior tende a ser a diferença,
        isso acontece porque o número total de incrementos cresce, aumentando
        a quantidade de vezes que ocorre acesso concorrente à variável global,
        o que aumenta a probabilidade de perda de incrementos e de erros comparando
        ao valor esperado.

    3. Existe alguma regra ou padrão na diferença entre "Contador" e "Esperado"?
        R: Não existe um valor fixo ou padrão determinístico para essa diferença,
        o resultado muda a cada execução, porque depende do escalonamento das
        threads pelo sistema operacional. No entanto, a tendência é que o valor
        do contador seja menor que o esperado devido à perda de incrementos
        causada pela condição de corrida.
*/

int contador_global = 0;    

void *increment(void *arg)
{
    int n_loops = *(int *)arg;
    for (int j = 0; j < n_loops; j++)
    {
        ++contador_global;
    }
    return NULL;    
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("n_threads é obrigatório!\n");
        printf("Uso: %s n_threads n_loops\n", argv[0]);
        return 1;
    }

    int n_threads = atoi(argv[1]);
    int n_loops = atoi(argv[2]);
    //...

    pthread_t threads[n_threads];

    for (int i = 0; i < n_threads; i++)
    {
        if (pthread_create(&threads[i], NULL, increment, &n_loops) != 0)
        {
            perror("Falha ao criar thread");
            return 1;
        }
    }

    for (int i = 0; i < n_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Contador: %d\n", contador_global);
    printf("Esperado: %d\n", n_threads * n_loops);
    return 0;
}
