#include <stdlib.h>

struct minha_st {
    int a;
    int b;
};


struct minha_st* cria_e_inicializa(int quantidade) {
    struct minha_st* ptr = (struct minha_st*) malloc(quantidade * sizeof(struct minha_st));
    return ptr;
};

void complementa_st (struct minha_st* ptr, int quantidade) {
    int i = 0;
    while (i < quantidade) {
        ptr[i].a = i;
        ptr[i].b = i;

        i = i + 1;
    };
};

void destroi_st (struct minha_st* ptr) {
    free(ptr);
    ptr = NULL;
};

int main() {
    struct minha_st *p = cria_e_inicializa(10);

    destroi_st(p);
}