#include <unistd.h>
#include <stdio.h>

void main() {
    for (int i = 0; i < 4; i++) {
        printf("\nLOOP EXTERNO");
        if (fork() != 0) { 
            printf("\nFORK != 0");
            for (int j=i; j < 4; j++) {
                printf("\nLOOP INTERNO");
                if (fork() == 0) {
                    printf("\nIF INTERNO FORK == 0");
                    break;
                }
            }
            break;
        }
    }
}