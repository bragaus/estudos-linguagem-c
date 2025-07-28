#include <stdio.h>

int main() {
    float temp1, temp2;

    printf("Digite uma temperatura em graus Celsius: ");
    scanf("%f", &temp1);

    temp2 = temp1 * 1.8 + 32;

    printf("A temperatura em Fahrenheit = %.2f\n", temp2);

    return 0;
}