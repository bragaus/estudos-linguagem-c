#include <stdio.h>

int main() {
    int idade;

    printf("Quantos anos voce tem? ");
    scanf("%d", &idade);

    if (idade >= 18) {
        printf("Voce e maior de idade!\n");
    } else {
        printf("Voce e menor de idade!\n");
    }

    return 0;
}