#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_PONTOS 10000000

int main() {
    int pontos_no_circulo = 0;
    double x, y;

    // TODO: Adicione a diretiva OpenMP correta aqui para paralelizar o for
    // Cuidado com a condição de corrida na variável pontos_no_circulo!
    
    #pragma omp parallel for reduction(+ : pontos_no_circulo) private(x,y)
    for (int i = 0; i < NUM_PONTOS; i++) {
        // Gerando valores entre -1.0 e 1.0 (simplificado para focar no OpenMP)
        // Nota: rand() puro não é thread-safe, use rand_r() em produção, 
        // mas para este exercício de diretivas, assuma que a semente é tratada.
        x = (double)rand() / RAND_MAX * 2.0 - 1.0;
        y = (double)rand() / RAND_MAX * 2.0 - 1.0;

        if (x * x + y * y <= 1.0) {
            pontos_no_circulo++;
        }
    }

    double pi = 4.0 * ((double)pontos_no_circulo / NUM_PONTOS);
    printf("Valor estimado de Pi: %f\n", pi);

    return 0;
}