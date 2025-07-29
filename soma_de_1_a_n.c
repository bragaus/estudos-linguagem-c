#include <stdio.h>

int main() {
    int num, n, soma = 0;

    printf("Digite um numero inteiro: ");
    scanf("%d", &n);

    for (num = 1; num <= n; num++) {
        soma = num + soma;
    }

    printf("A soma dos numeros de 1 a %d = %d\n", n, soma);

return 0;
}