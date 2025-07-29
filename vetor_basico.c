#include <stdio.h>

int main() {
    int vetor[5], i;

    for (i = 0; i < 5; i++) {
        printf("Digite um valor para a posicao %d: ", i);
        scanf("%d", &vetor[i]);
    }

    printf("\n====== Valores do vetor ======\n");

    for (i = 0; i < 5; i++) {
        printf("vetor[%d] = %d\n", i, vetor[i]);
    }

    return 0;
}