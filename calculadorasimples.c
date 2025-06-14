#include <stdio.h>

int main() {
    int num1, num2, adic, subt, mult, div, resto;

    printf("Digite um numero inteiro: ");
    scanf("%d", &num1);

    printf("Digite outro numero inteiro: ");
    scanf("%d", &num2);

    adic = num1 + num2;
    subt = num1 - num2;
    mult = num1 * num2;
    div = num1 / num2;
    resto = num1 % num2;

    printf("%d + %d = %d \n", num1, num2, adic);
    printf("%d - %d = %d \n", num1, num2, subt);
    printf("%d x %d = %d \n", num1, num2, mult);
    printf("%d / %d = %d \n", num1, num2, div);
    printf("O resto da divisao entre %d e %d = %d \n", num1, num2, resto);

    return 0;

}