#include <stdio.h>

int main() {
    int num;

    printf("Contagem progressiva de 1 a 100:\n");

    for (num = 1; num <= 100; num++) {
        printf("%3d ", num);

        if (num % 10 == 0) {
            printf("\n");
        }
    }

return 0;
}