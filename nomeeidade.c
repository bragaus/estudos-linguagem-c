#include <stdio.h>

int main() {
    char name[50];
    int age;

    printf("Qual e o seu nome? ");
    fgets(name, sizeof(name), stdin);

    name[strcspn(name, "\n")] = '\0';

    printf("Qual e a sua idade? ");
    scanf("%d", &age);

    printf("Ola, %s! Voce tem %d anos.\n",name,age);

    return 0;
}
