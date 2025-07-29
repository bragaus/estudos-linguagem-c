#include <stdio.h>

int main() {
    int num;

    do {
        printf("========== Validacao de Entrada ==========\n");
        printf("Digite um numero entre 1 e 5 para entrar:");
        scanf("%d", &num);

        if (num < 1 || num > 5) {
            printf("Entrada Invalida! Tente novamente.\n\n");
        }
    } while(num < 1 || num > 5);

    printf("Entrada Valida! Voce digitou: %d\n", num);

    return 0;
}