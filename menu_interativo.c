#include <stdio.h>

int main() {
    int resp;

    do {
        printf("====== MENU ======\n");
        printf("Escolha uma opcao:\n");
        printf("1 - Opcao A\n2 - Opcao B\n3 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &resp);

        if (resp == 1) {
            printf("Voce escolheu a opcao A!\n\n");
        } else if(resp == 2) {
            printf("Voce escolheu a opcao B!\n\n");
        } else if(resp != 3) {
            printf("Opcao invalida! Tente novamente.\n\n");
        }

    } while (resp != 3);

    printf("Saindo do Menu...\n");

return 0;
}