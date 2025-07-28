#include <stdio.h>

int main() {
    float base, altura, area;

    printf("Digite o valor da base de um retangulo: ");
    scanf("%f", &base);

    printf("Digite o valor da altura de um retangulo: ");
    scanf("%f", &altura);

    area = base * altura;

    printf("A area do retangulo = %.2f\n", area);

    return 0;
}