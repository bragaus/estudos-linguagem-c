#include <stdio.h>

int main() {
    int num;

    printf("Digite um numero: ");
    scanf("%d", &num);

    if (num % 2 == 0) {
        printf("Esse numero e par!\n");
    } else {
        printf("Esse numero e impar!\n");
    }
    return 0;
}