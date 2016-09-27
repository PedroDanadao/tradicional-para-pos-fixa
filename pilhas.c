#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct CONTAS
{
    char *conta;

    struct CONTAS *prox;
}cnt;

typedef struct EXPRECAO
{
    char caractere[2];

    struct EXPRECAO *prox;
}exprecao;


int bem_formada(char s[]);
void calcula(char s[]);
void cont_insere(char expr[], cnt *ini);
void cont_esvazia(cnt *ini);
void imprime(cnt *ini);

//""""""""""""""""""""""""""""""""""""""
int main()
{
    char esp[20] = "(((a(bc))))";
    //char *esp = malloc(sizeof(char));

    printf("%d", bem_formada(esp));
}
//""""""""""""""""""""""""""""""""""""""

//++++++++++++++++++++++++++++++++++++++
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

    free(pilha);
    return t == 0;
}
//++++++++++++++++++++++++++++++++++++++

//--------------------------------------
void calcula(char s[])
{
    cnt *inicial = malloc(sizeof());
    inicial -> prox = NULL;


}
//--------------------------------------

void n_p_f(char s[])
{
    int i, j = 0, N;
    N = strlen(s);
    char npf;
    exprecao *comeco = malloc(sizeof(exprecao));
    comeco -> prox = NULL;

    for(i = 0; i < N; i++){
        if(s[i] == '(')
            empilha_exprecao(s[i], comeco)

        else if(s[i] == ')'){
            while(comeco -> prox != '('){
                imprime_exprecao(npf, j, comeco);
                j++;
            }
            retira_exprecao(comeco);
        }

        else if( (s[i] == '-' || s[i] == '+') && (comeco -> prox -> caractere == '*' || comeco -> prox -> caractere == '/') ){
            while(comeco -> prox -> caractere != '(' && comeco -> prox != NULL){
                imprime_exprecao(npf, j, comeco);
                j++;
            }
            if(comeco -> prox -> caractere == '(')
                retira_exprecao(comeco);
            empilha_exprecao(s[i], comeco);
        }

        else if( (s[i] == '*' || s[i] == '/') && (comeco -> prox -> caractere == '*' || comeco -> prox -> caractere == '/') ){
            imprime_exprecao(npf, j, comeco);
            empilha_exprecao(s[i], comeco);
            j++;
        }

        else if( (s[i] == '+' || s[i] == '-') && (comeco -> prox -> caractere == '+' || comeco -> prox -> caractere == '-') ){
            imprime_exprecao(npf, j, comeco);
            empilha_exprecao(s[i], comeco);
            j++;
        }

        else if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
            empilha(s[i], comeco);

        else npf[j++] = s[i];
    }

    while(comeco -> prox != NULL){
        imprime_exprecao(npf, j, comeco);
        j++;
    }
}

void empilha_exprecao(char c[], exprecao *ini)
{
    exprecao *nova = malloc(sizeof(exprecao));
    nova caractere = c;

    nova -> prox = ini -> prox;
    ini -> prox = nova;
}

void imprime_exprecao(char npf[], int x, exprecao *ini)
{
    exprecao *tmp;
    char c[2];

    tmp = ini -> prox;
    ini -> prox = tmp -> prox;

    npf[x] = tmp caractere;
    free(tmp);
}

void retira_exprecao(exprecao *ini)
{
    exprecao *tmp;

    tmp = ini -> prox;
    ini -> prox = tmp -> prox;

    free(tmp);
}

void cont_insere(char expr[], cnt *ini)
{
    cnt *nova = malloc(sizeof(cnt));
    nova -> conta = expr;
    cnt *tmp = ini -> prox;

    while(tmp -> prox != NULL)
        tmp = tmp -> prox;

    nova -> prox = tmp -> prox;
    tmp -> prox = nova;
}

void cont_esvazia(cnt *ini)
{
    cnt *tmp1, *tmp2;
    tmp1 = ini -> prox;

    while(tmp1 != NULL){
        tmp2 = tmp1;
        tmp1 = tmp1 -> prox;
        free(tmp2);
    }
}

void imprime(cnt *ini)
{
    cnt *tmp = ini -> prox;
    while(tmp != NULL)
        printf("%s ", tmp -> conta);
}
