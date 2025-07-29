#include <stdio.h>

int main() {
    int num, cont = 0;

    printf("Contagem regressiva de 100 a 1:\n");

    for (num = 100; num > 0; num--) {
        printf("%3d ", num);
        cont++;

        if (cont % 10 == 0) {
            printf("\n");
        }
    }
    
return 0;
}