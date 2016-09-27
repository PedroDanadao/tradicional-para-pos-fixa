/*  
    ALUNO: PEDRO AUGUSTO ANADÃO CORREIA DE MORAES
    DISCIPLINA: ALGORITMOS E ESTRUTURAS DE DADOS
    EP4   DATA: 14/07/2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  essa struct recebera um operador da exprecao que vai ser 
//  transformada em notacao pos fixa e será um item da pilha de operadores
typedef struct EXPRESSAO
{
    char caractere;

    struct EXPRESSAO *prox;
}expressao;

//  essa será a raiz da arvore
typedef struct RAIZ
{
    oper *atual;
}root;

//  struct da arvore da operacao
//  ela pode receber tanto um inteiro(operando) quando um caractere(operador)
typedef struct OPERACAO
{
    float operando;
    
    char operador;
    
    struct OPERACAO *esq;
    struct OPERACAO *dir;
}oper;

// pilha de arvores que vao ser criadas para a operacao
typedef struct pilha_arvores
{
    oper *no_atual;
    
    struct pilha_arvores *prox;
}p_a;


int bem_formada(char *s);

void empilha_expressao(char c, expressao *ini);
void desempilha_expressao(expressao *ini);
void imprime_expressao(int x, char *npf, expressao *ini);
int imprime_expressao_toda(int x, char *npf, expressao *ini);
char *n_p_f(char *expr);

void monta_arvore(char *expr, root *raiz);
void cria_no(char c, p_a *ini, root *raiz);
void empilha_arvore(oper *no, p_a *ini);
void desempilha_arvore(p_a *ini);
float calcula(oper *no);
void libera_arvore(oper *no);

float computa(char *expr);

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main()
{
    FILE *data;
    data = fopen("exp.dat", "r");
    
    char *expr = malloc(30 * sizeof(char));
    
    while(fscanf(data, "%s", expr) != EOF){
        if(bem_formada(expr))
            printf("RESULATDO = %f\n\n", computa(expr));
            
        else printf("%s mal formada\n\n", expr);
    }
    
    fclose(data);
    
    return 0;
}

float computa(char *expr)
{
    root *raiz = malloc(sizeof(root));
    raiz -> atual = NULL;
    char *expr2 = n_p_f(expr);
    float resultado;
    
    monta_arvore(expr2, raiz);
    
    resultado = calcula(raiz -> atual);
    libera_arvore(raiz -> atual);
    
    return resultado;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* essa função recebe um ponteiro para uma string e devolve 1 caso os parenteses dessa string etiverem
bem formados. 
ex. (a+b) devolve 1, enquanto que ((a+b) ou (a+b)) devolve 0 */
int bem_formada(char *s)
{
    char *pilha;//essa string vai servir para empilhar os '('
    int t, N, i;
    
    N = strlen(s);
    pilha = malloc(N * sizeof(char));
    t = 0;
    
    for(i = 0; s[i] != '\0'; ++i){//percorre a string s
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
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//----------------------------------------------------------------------------------------------
/* essa funcao recebe uma string que é a expressao a ser calculada e devolve 
essa expressao na forma de notacao pós fixa */
char *n_p_f(char *expr)
{
    int i, j = 0, N;
    N = strlen(expr);// N eh o tamanho da string
    char t[N + 1];//    t  tem o tamanho da string + 1
    char *npf = malloc(N * sizeof(char));//     npf será a expressao em notacao pós fixa
    expressao *comeco = malloc(sizeof(expressao));//    comeco de uma pilha de caracteres
    comeco -> prox = NULL;
    
    t[0] = '(';//   serve como caractere verificador para a funçao imprime_expressao_toda
    for(i = 0; i < N; i++)// aqui eu copio a string recebida para t
        t[i + 1] = expr[i];
    
    for(i = 0; i < N; i++){
        if(t[i] == '(')
            empilha_expressao(t[i], comeco);
        
        else if(t[i] == ')')
            j = imprime_expressao_toda(j, npf, comeco);
            
        else if( (t[i] == '-' || t[i] == '+') && (comeco -> prox -> caractere == '*' || comeco -> prox -> caractere == '/') ){
            j = imprime_expressao_toda(j, npf, comeco);
            empilha_expressao(t[i], comeco);
        }
        
        else if( (t[i] == '*' || t[i] == '/') && (comeco -> prox -> caractere == '*' || comeco -> prox -> caractere == '/') ){
            imprime_expressao(j, npf, comeco);
            empilha_expressao(t[i], comeco);
            j++;
        }
        
        else if( (t[i] == '+' || t[i] == '-') && (comeco -> prox -> caractere == '+' || comeco -> prox -> caractere == '-') ){
            imprime_expressao(j, npf, comeco);
            empilha_expressao(t[i], comeco);
            j++;
        }
        
        else if(t[i] == '+' || t[i] == '-' || t[i] == '*' || t[i] == '/')
            empilha_expressao(t[i], comeco);
        
        else npf[j++] = t[i];
    }
    
    j = imprime_expressao_toda(j, npf, comeco);// caso sobre algo da pilha de operadores a ser impresso
    npf[j] = '\0';//    garante que a notacao pos fixa tenha fim em npf[j]
    
    printf("%s = %s\n", expr, npf);
    return npf;
}

//essa funcao recebe um cractere e o empilha com topo da pilha de operadores
void empilha_expressao(char c, expressao *ini)
{
    expressao *nova = malloc(sizeof(expressao));//  cria um novo item para a pilha de operadores
    nova -> caractere = c;//    atribui c ao caractere do novo item

    nova -> prox = ini -> prox;
    ini -> prox = nova;
}

//essa funcao apenas retira o item que está no topo da pilha de operadores
void desempilha_expressao(expressao *ini)
{
    expressao *tmp;
    
    tmp = ini -> prox;
    ini -> prox = tmp -> prox;
    
    free(tmp);
}

//  essa funcao recebe um inteiro, uma string e o inicio da pilha de operadores.
//  ela entao atribui à posicao x da string o caractere que está
//  no topo da pilha. feito isso a funcao encerra ao desmpilha o item no topo da pilha
void imprime_expressao(int x, char *npf, expressao *ini)
{
    expressao *tmp;
    
    tmp = ini -> prox;
    npf[x] = tmp -> caractere;
    
    desempilha_expressao(ini);
}

//  essa funcao recebe um inteiro, uma string e o topo da pilha de operadores.
//  ela então imprime na string(a partir da posicao x) os caracteres da pilha
//  até que o topo da pilha seja igual a '('
int imprime_expressao_toda(int x, char *npf, expressao *ini)
{
    while(ini -> prox != NULL && ini -> prox -> caractere != '('){
        npf[x++] = ini -> prox -> caractere;
        
        desempilha_expressao(ini);//    sempre desempilha o topo da pilha ao final 
    }
    
    if(ini -> prox != NULL)
        desempilha_expressao(ini);//    desempilha '('
    
    return x;// devolve x para que a string continue recebendo caracteres a partir da posicao certa
}
//----------------------------------------------------------------------------------------------


//**********************************************************************************************
/*  essa funcao recebe a expressao em forma de notacao pos fixa, assim como a raiz da arvore.
    e cria uma arvore a partir da expressao, onde os nós pais sao os operadores e as folhas sao os operandos */
void monta_arvore(char *expr, root *raiz)
{
    p_a *comeco = malloc(sizeof(p_a));//    cria uma pilha de arvores
    comeco -> prox = NULL;
    comeco -> no_atual = NULL;
    
    int i;
    
    for(i = 0; expr[i] != '\0'; i++)//  precorre a string da expressao
        cria_no(expr[i], comeco, raiz);
    
}

//  essa funcao recebe um caractere, o inicio da pilha de arvores e a raiz da arvore
//  ela entao cria um nó que vai armazenar o  caractere recebido
void cria_no(char c, p_a *ini, root *raiz)
{
    oper *no = malloc(sizeof(oper));//  cria o nó
    if(c == '+' || c == '-' || c == '*' || c == '/'){// armazena no nó o caractere caso ele seja um operador
        no -> operador = c;
        no -> dir = ini -> prox -> no_atual;//  ponteiro da direita é o nó do topo da pilha de árvores
        desempilha_arvore(ini);//   dempilha o nó do topo da pilha de arvores
        no -> esq = ini -> prox -> no_atual;//  ponteiro da direita é o nó do topo da pilha de árvores
        desempilha_arvore(ini);//   dempilha o nó do topo da pilha de arvores
        
        empilha_arvore(no, ini);// empilha a sub-arvore criada acima
        raiz -> atual = no;//   a raiz passa a apontar para o nó criado
    }
    
    else{//     caso o caractere recebido seja um operando
        float x;//  cria uma variavel float
        printf("digite o valor de %c ", c);//   pede ao usuario o valor da variavel x
        scanf("%f", &x);
        
        no -> operando = x;//   atribui ao nó criado o valor de x
        no -> dir = NULL;// todos os operandos vao ser folhas
        no -> esq = NULL;// entao seus ponteiros para itens da esquerda e da direita serao NULOS
        empilha_arvore(no, ini);//  empilha o nó criado na pilha de arvores
    }
}

//  recebe um nó da arvore e o inicio da pilha de arvores
//  empilha o nó na pilha de arvores
void empilha_arvore(oper *no, p_a *ini)
{
    p_a *nova = malloc(sizeof(p_a));
    nova -> no_atual = no;
    
    nova -> prox = ini -> prox;
    ini -> prox = nova;
}

//  essa funçao recebe o inicio da pilha de arvores e desempilha item no topo
void desempilha_arvore(p_a *ini)
{
    p_a *tmp = ini -> prox;
    ini -> prox = tmp -> prox;
    
    free(tmp);
}

//  essa funcao vai receber(inicialmente) o nó da raiz da arvore de operacoes
//  e vai realizar recursivamente os calculos da arvore
float calcula(oper *no)
{
    if(no -> esq == NULL && no -> dir == NULL)//    caso o nó seja uma folha(operando)
        return no -> operando;//    a funcao devolve o valor do operando do nó
    
    else{
        if(no -> operador == '+')// caso o operador do nó seja '+'
            return calcula(no -> esq) + calcula(no -> dir);// devolve a soma entre o valor final da esquerda com o valor da direita 
        
        else if(no -> operador == '-')// caso o operador do nó seja '-'
            return calcula(no -> esq) - calcula(no -> dir);// devolve a subtracao entre o valor final da esquerda com o valor da direita 
        
        else if(no -> operador == '*')// caso o operador do nó seja '*'
            return calcula(no -> esq) * calcula(no -> dir);// devolve a multiplicacao entre o valor final da esquerda com o valor da direita 
        
        else if(no -> operador == '/')// caso o operador do nó seja '/'
            return calcula(no -> esq) / calcula(no -> dir);// devolve a divisao entre o valor final da esquerda com o valor da direita 
    }
}

//  essa funcao recebe(inicialmente) o nó da raiz da arvore de operacoes
//  ela vai 
void libera_arvore(oper *no)
{
    if(no -> esq != NULL && no -> dir != NULL){
        libera_arvore(no -> esq);
        libera_arvore(no -> dir);
    }
    free(no);
}
//****************************************************************************************
