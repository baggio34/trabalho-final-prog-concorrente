#include <stdio.h>
#include <omp.h>

#define SIZE 1000

void aplicar_filtro(double entrada[SIZE][SIZE], double saida[SIZE][SIZE]) {
    // TODO: Paralelize este loop duplo. 
    // Dica: Como cada célula da saída depende apenas da entrada, é um problema "embarrassingly parallel".
    #pragma omp parallel for collapse(2)
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            saida[i][j] = (entrada[i-1][j] + entrada[i+1][j] + entrada[i][j-1] + entrada[i][j+1]) / 4.0;
        }
    }
}