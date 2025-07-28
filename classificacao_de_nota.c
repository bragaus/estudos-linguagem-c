#include <stdio.h>

int main() {
    float nota;

    printf("Digite a sua nota final: ");
    scanf("%f", &nota);

    if(nota >= 9.0) {
        printf("Excelente! Aprovado(a).\n");
    } else if(nota >= 7.0) {
        printf("Aprovado(a)!\n");
    } else if(nota >= 4.0) {
        printf("Em Recuperacao.\n");
    } else {
        printf("Reprovado(a).\n");
    }

    return 0;
}