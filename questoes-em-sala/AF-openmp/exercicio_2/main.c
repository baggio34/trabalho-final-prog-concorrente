#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>


/*
    O maior problema era o paralelismo aninhado: tínhamos um #pragma dentro de outro, o que fazia o sistema criar 
    threads demais para tarefas simples, gerando um gargalo desnecessário. Além disso, a forma como estávamos acessando 
    a matriz right (loop i-j-k) forçava a CPU a saltar endereços na memória, gerando muitos cache misses e deixando o 
    acesso muito lento, não aproveitando dos benefícios da cache.

    O que nós ajustamos:

        Removemos o paralelismo interno: Agora usamos apenas um nível de paralelismo no loop mais externo, 
        o que é muito mais leve para o processador.

        Reordenamos os loops para i-k-j: Com o j por dentro, a leitura da memória ficou sequencial (linha a linha), 
        o que permite à CPU aproveitar muito melhor a cache como comentado anteriormente.

        Ajustamos o escalonamento: Trocamos o schedule(dynamic, 1) por schedule(static). 
        Como a carga de trabalho na multiplicação de matrizes é fixa e previsível, o static é muito mais eficiente, 
        pois elimina o custo de gerenciar filas dinâmicas de tarefas, que era outra fonte de lentidão no código original.

        Melhoramos a estrutura: Adicionamos uma variável temporária temp para evitar acessos repetitivos à matriz da 
        esquerda durante o cálculo interno.

    Com essas mudanças, o código ficou muito mais eficiente e, principalmente, garante que o cálculo seja feito sem 
    conflitos de concorrência ou variáveis sobrescritas indevidamente.
*/

void init_matrix(double* m, int rows, int columns) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            m[i*columns+j] = i + j;
}


void mult_matrix(double* out, double* left, double *right, 
                 int rows_left, int cols_left, int cols_right) {
    
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < rows_left; ++i) {
        // Altera a ordem para i-k-j (o loop 'k' vem antes do 'j')
        for (int k = 0; k < cols_left; ++k) {
            double temp = left[i * cols_left + k]; // Valor fixo da linha
            for (int j = 0; j < cols_right; ++j) {
                // Agora o acesso ao 'right' e ao 'out' é sequencial (linha a linha)
                out[i * cols_right + j] += temp * right[k * cols_right + j];
            }
        }
    }
}

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s tam_matriz\n", argv[0]);
        return 1;
    }
    int sz = atoi(argv[1]);
    double* a = malloc(sz*sz*sizeof(double));
    double* b = malloc(sz*sz*sizeof(double));
    double* c = calloc(sz*sz, sizeof(double));

    init_matrix(a, sz, sz);
    init_matrix(b, sz, sz);

    //          c = a * b
    mult_matrix(c,  a,  b, sz, sz, sz);
    
    /* ~~~ imprime matriz ~~~ */
    char tmp[32];
    int max_len = 1;
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            int len = sprintf(tmp, "%ld", (unsigned long)c[i*sz+j]);
            max_len = max_len > len ? max_len : len;
        }
    }
    char fmt[16];
    if (snprintf(fmt, 16, "%%s%%%dld", max_len) < 0) 
        abort();
    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) 
            printf(fmt, j == 0 ? "" : " ", (unsigned long)c[i*sz+j]);
        printf("\n");
    }

    free(a);
    free(b);
    free(c);

    return 0;
}
