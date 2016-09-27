#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct EXPRECAO
{
    char *caractere;

    struct EXPRECAO *prox;
}exprecao;

int bem_formada(char s[]);

int main()
{
    int i;
    char *esp = malloc(2 * sizeof(char));
    esp[0] = 'a';
    char esp2[3];
    esp2[0] = *esp;
    //for(i = 0; i < 5; i++)
        //esp[i] = 'a';
    //exprecao *comeco = malloc(sizeof(exprecao));
    //comeco -> prox = NULL;
    //comeco -> caractere = esp;
    //empilha_exprecao(esp, comeco);

    printf("%s", esp2);
}

int bem_formada(char s[])
{
    char *pilha, *expr;
    int t, u, N, i;

    N = strlen(s);
    pilha = malloc(N * sizeof(char));
    t = 0;

    for(i = 0; s[i] != '\0'; ++i){
        if(s[i] == '(')
            pilha[t++] = s[i];

        else if(s[i] == ')'){
            if(pilha[t - 1] == '(')
                --t;

            else
                return 0;
        }
    }

    //printf("%s", pilha);
    free(pilha);
    return t == 0;
}
