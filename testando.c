#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct expressao
{
    char caractere;

    struct expressao *prox;
}expressao;

int main()
{
    FILE *data;
    data = fopen("data.txt", "r");

    char *esp = malloc(30 * sizeof(char));

    while(fscanf(data, "%s", esp) != EOF)
        printf("%s\n", esp);

    fclose(data);

    return 0;
}
