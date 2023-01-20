#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

FILE *erro;
FILE *hist;

// construcao de um numero:
typedef struct no
{
    int valor;
    struct no *prox;
    struct no *ant;
} NoNumero;

typedef struct listaNumero
{
    char sinal;
    NoNumero *inicio;
} Numero;

// construcao do historico
typedef struct no_operacao
{
    // a e b sao entradas, c eh saida
    Numero *a;
    Numero *b;
    Numero *c;
    char operacao;
    struct no_operacao *prox;

} NoOperacao;

typedef struct listaHistorico
{
    NoOperacao *inicio;
} Historico;

void criarLogs()
{
    hist = fopen("historico.txt", "w+");
    erro = fopen("log.txt", "w+");
    fclose(erro);
    fclose(hist);
}
// funcoes Numero:
Numero *criar()
{
    Numero *l = (Numero *)malloc(sizeof(Numero));
    if (l == NULL)
        return NULL;
    l->inicio = NULL;
    return l;
}

int listaVazia(Numero *l)
{
    if (l == NULL)
    {
        logErro(-2);
        return 2;
    }
    if (l->inicio == NULL)
        return 0;
    return 1;

}

int inserirInicio(Numero *l, int it)
{
    if (l == NULL)
    {
        logErro(-2);
        return 2;
    }
    NoNumero *no = (NoNumero *)malloc(sizeof(NoNumero));
    no->valor = it;
    no->prox = l->inicio;
    no->ant = NULL;
    if (l->inicio != NULL)
        l->inicio->ant = no;
    l->inicio = no;

    return 0;
}

int inserirFim(Numero *l, int it)
{
    if (l == NULL)
    {
        logErro(-2);
        return 2;
    }
    if (listaVazia(l) == 0)
        return inserirInicio(l, it);
    NoNumero *noLista = l->inicio;
    while (noLista->prox != NULL)
        noLista = noLista->prox;
    NoNumero *no = (NoNumero *)malloc(sizeof(NoNumero));
    no->valor = it;
    no->prox = NULL;
    no->ant = noLista;
    noLista->prox = no;

    return 0;
}

void limpar(Numero *l)
{
    l->sinal = ' ';
    while (listaVazia(l) != 0)
        removerInicio(l);
}

void mostrar(Numero *l)
{
    int i, j;
    if (l != NULL)
    {
        NoNumero *noLista = l->inicio;
        if (l->sinal == '-')
            printf("%c", l->sinal);
        while (noLista != NULL)
        {
            printf("%d", noLista->valor);
            noLista = noLista->prox;
        }
        printf("\n");
    }
}

int removerFim(Numero *l)
{
    if (l == NULL)
    {
        logErro(-2);
        return 2;
    }
    if (listaVazia(l) == 0)
        return 1;
    NoNumero *noLista = l->inicio;
    while (noLista->prox != NULL)
        noLista = noLista->prox;
    if (noLista->ant == NULL)
        l->inicio = NULL;
    else
        noLista->ant->prox = NULL;
    free(noLista);

    return 0;
}

int removerInicio(Numero *l)
{
    if (l == NULL)
    {
        logErro(-2);
        return 2;
    }
    if (listaVazia(l) == 0)
        return 1;
    NoNumero *noLista = l->inicio;
    l->inicio = noLista->prox;
    if (l->inicio != NULL)
        l->inicio->ant = NULL;

    free(noLista);
    return 0;
}

// funcoes historico:
Historico *criarHistorico()
{
    Historico *l = (Historico *)malloc(sizeof(Historico));
    l->inicio = NULL;
    return l;
}

int historicoVazio(Historico *l)
{
    if (l == NULL)
    {
        logErro(-2);
        return 2;
    }
    if (l->inicio == NULL)
        return 0;


    return 1;
}

int inserirFimHistorico(Historico *l, Numero *n1, Numero *n2, Numero *n3, char op)
{
    if (l == NULL)
    {
        logErro(-2);
        return 2;
    }
    NoOperacao *noLista = l->inicio;
    if (noLista != NULL)
    {
        while (noLista->prox != NULL)
            noLista = noLista->prox;
    }

    NoOperacao *no = (NoOperacao *)malloc(sizeof(NoOperacao));
    no->a = criar();
    no->b = criar();
    no->c = criar();
    copia(no->a, n1);
    copia(no->b, n2);
    copia(no->c, n3);
    no->operacao = op;

    if (noLista->prox == NULL)
    {
        noLista->prox = no;
    }
    else
    {
        no->prox = noLista->prox;
        noLista->prox = no;
    }

    return 0;
}

int removerFimHistorico(Historico *l)
{
    if (l == NULL)
    {
        logErro(-2);
        return 2;
    }
    if (historicoVazio(l) == 0)
        return 1;

    NoOperacao *noAuxiliar = NULL;
    NoOperacao *noLista = l->inicio;

    while (noLista->prox != NULL)
    {
        noAuxiliar = noLista;
        noLista = noLista->prox;
    }

    if (noAuxiliar == NULL)
        l->inicio = NULL;
    else
        noAuxiliar->prox = NULL;

    free(noLista);

    return 0;
}

void limparHistorico(Historico *l)
{
    while (historicoVazio(l) != 0)
        removerFimHistorico(l);
}

void mostrarHistorico(Historico *l)
{
    // nao testei mas acho que faz sentido
    // mo trampo namoral
    if (l != NULL)
    {
        printf("Historico:\n");
        NoOperacao *noLista = l->inicio;

        while (noLista != NULL)
        {
            mostrar(noLista->a);
            printf(" %c ", noLista->operacao);
            mostrar(noLista->b);
            printf(" = ");
            mostrar(noLista->c);
            printf("\n");
            noLista = noLista->prox;
        }
        printf("\n");
    }
}

// se quiser me chama no zap que eu explico, ta funcionando perfeitamente, so eh meio foda de entender.
int opcaoA(Numero *a, Numero *b, Numero *c, Historico *h)
{
    if (a == NULL || b == NULL || c == NULL || h == NULL)
    {
        logErro(-2);
        return 2;
    }

    int r;
    int userInputA;
    char teste;
    char lixo;
    char operacao;
    printf("\nInsira o Primeiro Numero: ");
    teste = getc(stdin);
    while (teste != '\n')
    {
        if (teste == '-')
            a->sinal = '-';
        else
            ungetc(teste, stdin);
        scanf("%1d", &userInputA);
        inserirFim(a, userInputA);
        userInputA = 0;
        teste = getc(stdin);
    }
    fflush(stdin);
    if (a->sinal != '-')
        a->sinal = '+';
    printf("\nA=");
    corrige(a);
    mostrar(a);

    printf("\nInsira a operacao:");
    scanf("%c", &operacao);
    fflush(stdin);

    lixo = getc(stdin);
    printf("\nInsira o Segundo Numero: ");
    teste = getc(stdin);
    while (teste != '\n')
    {
        if (teste == '-')
            b->sinal = '-';

        else
            ungetc(teste, stdin);

        scanf("%1d", &userInputA);
        inserirFim(b, userInputA);
        userInputA = 0;
        teste = getc(stdin);
    }
    fflush(stdin);
    if (b->sinal != '-')
        b->sinal = '+';
    printf("\nB=");
    corrige(b);
    mostrar(b);
    // printf("\n\n\n%c %c",a->sinal,b->sinal);
    switch (operacao)
    {

    case '+':
    {
        c = soma(h, a, b);
        printf("\nsoma feita!");
        printf("\no resultado da soma eh:");
        mostrar(c);
        
        break;
    }
    case '-':
    {
        c = subtracao(h, a, b);
        printf("\nsubtracao feita!");
        printf("\no resultado da subtracao eh:");
        mostrar(c);
        
        break;
    }
    case '*':
    {
        c = multiplicacao(h, a, b);
        printf("\nmultiplicacao feita!");
        printf("\no resultado da multiplicacao eh:");
        mostrar(c);
        
        break;
    }
    case '/':
    {
        Numero *res = criar();
        c = divisao(h, a, b, res);
        printf("\ndivisao feita!");
        printf("\no resultado da divisao eh:");
        mostrar(c);
        printf("\no resto da divisao eh:");
        mostrar(res);
        limpar(res);
        break;
    }
    default:
        printf("\noperacao invalida!ERRO!");
        return -1;
        break;
    }
    mostrarOperacao(a,b,c);

    return 0;
}

int corrige(Numero *l)
{
    if (l == NULL)
    {
        logErro(-2);
        return 2;
    }
    if (listaVazia(l) == 0)
        return 1;
    int i, j;
    if(tamanho(l)>1)
    {   
        while (l->inicio->valor == 0)
        {
            removerInicio(l);
        }
    }

    return 0;
}

int tamanho(Numero *l)
{

    if (l == NULL)
    {
        logErro(-2);
        return -1;
    }

    if (listaVazia(l) == 0)
        return 0;

    int i = 1;

    NoNumero *nolista = l->inicio;

    while (nolista->prox != NULL)
    {
        i++;
        nolista = nolista->prox;
    }

    return i;
}

int copia(Numero *l, Numero *r)
{
    if (l == NULL || r == NULL)
    {
        logErro(-2);
        return -1;
    }
    limpar(r);
    NoNumero *no = l->inicio;
    while (no != NULL)
    {
        inserirFim(r, no->valor);
        no = no->prox;
    }
    r->sinal = l->sinal;

    return 0;
}

// funcoes operacoes diversas
// processo q eu pensei pras operacoes:a gnt recebe da main o historico criado la, os numeros(ja criado e formado) e a operacao que o usuario digita, e assim é gerado uma lista do tipo Numero que é o resultado da operacao.
// no fim tudo seria inserido no historico
// B)

Numero *soma(Historico *l, Numero *n1, Numero *n2)
{
    if (l == NULL)
    {
        
        return NULL;
    }
    if (n1 == NULL || n2 == NULL)
    {
        logErro(-2);
        return NULL;
    }
    if (listaVazia(n1) == 0)
    {
        return NULL;
    }
        
    if (listaVazia(n2) == 0)
        return NULL;
    Numero *n3 = criar();

    if (tamanho(n1) == 1)
    {
        if (n1->inicio->valor == 0)
        {
            copia(n2, n3);
            // inserirFimHistorico(l,n1,n2,n3,'+');
            return n3;
        }
    }

    if (tamanho(n2) == 1)
    {
        if (n2->inicio->valor == 0)
        {
            copia(n1, n3);
            // inserirFimHistorico(l,n1,n2,n3,'+');
            return n3;
        }
    }

    if ((n1->sinal == '-') && (n2->sinal == '+'))
    {
        n1->sinal = '+';
        n3 = subtracao(l, n1, n2);
        n3->sinal = '-';
        n1->sinal = '-';
        return n3;
    }

    if ((n1->sinal == '+') && (n2->sinal == '-'))
    {
        n2->sinal = '+';
        n3 = subtracao(l, n1, n2);
        n2->sinal = '-';
        return n3;
    }

    if ((n1->sinal == '-') && (n2->sinal == '-'))
        n3->sinal = '-';
    else
        n3->sinal = '+';
    int y;

    NoNumero *a = n1->inicio;
    NoNumero *b = n2->inicio;

    while (a->prox != NULL)
        a = a->prox;

    while (b->prox != NULL)
        b = b->prox;

    while ((a != NULL) && (b != NULL))
    {
        y = a->valor + b->valor;
        inserirInicio(n3, y);
        a = a->ant;
        b = b->ant;
    }

    if (a == NULL)
    {
        while (b != NULL)
        {
            inserirInicio(n3, b->valor);
            b = b->ant;
        }
    }

    if (b == NULL)
    {
        while (a != NULL)
        {
            inserirInicio(n3, a->valor);
            a = a->ant;
        }
    }

    NoNumero *c = n3->inicio;
    while (c->prox != NULL)
        c = c->prox;

    while (c != NULL)
    {
        if (c->valor >= 10)
        {
            c->valor = (c->valor) % 10;
            if (c->ant != NULL)
                (c->ant)->valor = (c->ant)->valor + 1;
            else
                inserirInicio(n3, 1);
        }
        c = c->ant;
    }
    // inserirFimHistorico(l,n1,n2,n3,'+');

    return n3;
}

Numero *subtracao(Historico *l, Numero *n1, Numero *n2)
{
    if (l == NULL)
    {
        return NULL;
    }
    if (n1 == NULL || n2 == NULL)
    {
        logErro(-2);
        return NULL;
    }
    if (listaVazia(n1) == 0)
        return NULL;
    if (listaVazia(n2) == 0)
        return NULL;
    Numero *n3 = criar();
    int j = 0;
    if ((n1->sinal == '-') && (n2->sinal == '+'))
    {
        n2->sinal = '-';
        n3 = soma(l, n1, n2);
        n2->sinal = '+';
        return n3;
    }
    if ((n1->sinal == '+') && (n2->sinal == '-'))
    {
        n2->sinal = '+';
        n3 = soma(l, n1, n2);
        n2->sinal = '-';
        return n3;
    }

    if ((n1->sinal == '+') && (n2->sinal == '+'))
    {
        int n = tamanho(n1);
        int m = tamanho(n2);
        if (n > m)
        {
            n3->sinal = '+';
        }
        else if (n < m)
        {
            n3 = subtracao(l, n2, n1);
            n3->sinal = '-';
            return n3;
        }
        else
        {
            NoNumero *no1 = n1->inicio;
            NoNumero *no2 = n2->inicio;

            while (no1 != NULL)
            {
                if (no1->valor > no2->valor)
                {
                    n3->sinal = '+';
                    break;
                }
                else if (no1->valor < no2->valor)
                {
                    n3 = subtracao(l, n2, n1);
                    n3->sinal = '-';
                    return n3;
                }
                else
                {
                    n3->sinal = '+';
                    j++;
                }
                no1 = no1->prox;
                no2 = no2->prox;
            }
            if ((j == m) && (j == n))
            {
                inserirInicio(n3, 0);
                return n3;
            }
        }
    }

    if ((n1->sinal == '-') && (n2->sinal == '-'))
    {
        int n = tamanho(n1);
        int m = tamanho(n2);
        if (n > m)
        {
            n3->sinal ='-';
        }
        else if (n < m)
        {
            n3 = subtracao(l, n2, n1);
            n3->sinal = '+';
            return n3;
        }
        else
        {
            NoNumero *no1 = n1->inicio;
            NoNumero *no2 = n2->inicio;

            while (no1 != NULL)
            {
                if (no1->valor > no2->valor)
                {
                    n3->sinal = '-';
                    break;
                }
                else if (no1->valor < no2->valor)
                {
                    n3 = subtracao(l, n2, n1);
                    n3->sinal = '+';
                    return n3;
                }
                else
                {
                    n3->sinal = '+';
                    j++;
                }
                no1 = no1->prox;
                no2 = no2->prox;
            }
            if ((j == m) && (j == n))
            {
                inserirInicio(n3, 0);
                return n3;
            }
        }
    }
    char sin;
    if (tamanho(n1) == 1)
    {
        if (n1->inicio->valor == 0)
        {
            sin = n3->sinal;
            copia(n2, n3);
            n3->sinal = sin;
            // inserirFimHistorico(l,n1,n2,n3,'+');
            fclose(hist);
            return n3;
        }
    }

    if (tamanho(n2) == 1)
    {
        if (n2->inicio->valor == 0)
        {
            copia(n1, n3);
            // inserirFimHistorico(l,n1,n2,n3,'+');
            fclose(hist);
    

            return n3;
        }
    }

    Numero *naux1 = criar();
    copia(n1,naux1);

    NoNumero *no1 = n1->inicio;
    NoNumero *no2 = n2->inicio;

    while (no1->prox != NULL)
        no1 = no1->prox;

    while (no2->prox != NULL)
        no2 = no2->prox;

    NoNumero *aux1 = no1->ant;
    NoNumero *cteant = no1->ant;

    int i = 1, y;
    while (no1 != NULL && no2 != NULL)
    {
        if ((no2->valor) > (no1->valor))
        {
            while ((aux1 != NULL) && (aux1->valor == 0))
            {
                i++;
                aux1 = aux1->ant;
            }
            for (int y = 0; y < i; y++)
            {
                aux1->valor = aux1->valor - 1;
                (aux1->prox)->valor = (aux1->prox)->valor + 10;
                aux1 = aux1->prox;
            }
        }
        aux1 = cteant;
        y = no1->valor - no2->valor;
        inserirInicio(n3, y);
        no1 = no1->ant;
        if (no1 != NULL)
        {
            aux1 = aux1->ant;
            cteant = aux1;
        }
        no2 = no2->ant;
    }

    if (no1 == NULL)
    {
        while (no2 != NULL)
        {
            inserirInicio(n3, no2->valor);
            no2 = no2->ant;
        }
    }

    if (no2 == NULL)
    {
        while (no1 != NULL)
        {
            inserirInicio(n3, no1->valor);
            no1 = no1->ant;
        }
    }

    while ((n3->inicio)->valor == 0)
    {
        if (n3->inicio->prox == NULL)
            break;
        removerInicio(n3);
    }

    //inserirFimHistorico(l,n1,n2,n3,'-');

    copia(naux1,n1);
    return n3;
}

Numero *multiplicacao(Historico *l, Numero *n1, Numero *n2)
{
    Numero *n3 = criar();
    if (l == NULL)
    {
        return NULL;
    }
    if (n1 == NULL || n2 == NULL)
    {
        logErro(-2);
        return NULL;
    }
    if (listaVazia(n1) == 0)
        return NULL;
    if (listaVazia(n2) == 0)
        return NULL;
    int y, z, i = 0, j = 0;
    NoNumero *a = n1->inicio;
    NoNumero *b = n2->inicio;
    NoNumero *c = (NoNumero *)malloc(sizeof(NoNumero));
    NoNumero *a1 = (NoNumero *)malloc(sizeof(NoNumero));
    Numero *res1 = criar();
    Numero *res0 = criar();
    Numero *help1 = criar();
    Numero *help = criar();
    Numero *aux = criar();

    inserirInicio(res0, 0);
    inserirInicio(help, 0);

    if (tamanho(n1) == 1)
    {
        if (n1->inicio->valor == 0)
        {
            inserirFim(n3,0);
            // inserirFimHistorico(l,n1,n2,n3,'+');
            fclose(hist);
    

            return n3;
        }
        else if (n1->inicio->valor == 1)
        {
            copia(n2,n3);
            if ((n1->sinal == '+') && (n2->sinal == '+'))
                n3->sinal = '+';
            if ((n1->sinal == '-') && (n2->sinal == '+'))
                n3->sinal = '-';
            if ((n1->sinal == '+') && (n2->sinal == '-'))
                n3->sinal = '-';
            if ((n1->sinal == '-') && (n2->sinal == '-'))
                n3->sinal = '+';
            // inserirFimHistorico(l,n1,n2,n3,'+');
            fclose(hist);
    

            return n3;
        }
    }

    if (tamanho(n2) == 1)
    {
        if (n2->inicio->valor == 0)
        {
            inserirFim(n3,0);
            // inserirFimHistorico(l,n1,n2,n3,'+');
            fclose(hist);
    

            return n3;
        }
        else if (n2->inicio->valor == 1)
        {
            copia(n1,n3);
            if ((n1->sinal == '+') && (n2->sinal == '+'))
                n3->sinal = '+';
            if ((n1->sinal == '-') && (n2->sinal == '+'))
                n3->sinal = '-';
            if ((n1->sinal == '+') && (n2->sinal == '-'))
                n3->sinal = '-';
            if ((n1->sinal == '-') && (n2->sinal == '-'))
                n3->sinal = '+';
            // inserirFimHistorico(l,n1,n2,n3,'+');
            fclose(hist);
    

            return n3;
        }
    }

    while (b->prox != NULL)
        b = b->prox;
    // printf("%d\n",b->valor);
    while (a->prox != NULL)
        a = a->prox;
    a1 = a;
    // printf("\n\n%d\n\n",a1->valor);

    while (b != NULL)
    {
        a = a1;
        // printf("%d\n",a->valor);
        while (a != NULL)
        {
            // gerar uma linha da multiplicação
            y = (b->valor) * (a->valor);
            inserirInicio(aux, y);
            if ((j > 0) && (aux->inicio->valor != 0))
            {
                for (int y = 0; y < j; y++)
                {
                    inserirFim(aux, 0);
                }
            }
            c = aux->inicio; // nao precisa de loop pq so o inicio de aux tem valor relevante

            if (c->valor >= 10)
            {
                z = (c->valor) / 10;
                c->valor = (c->valor) % 10;
                inserirInicio(aux, z);
            }
            // printf("help = %d",help->inicio->valor);
            res1 = soma(l, aux, help);
            // removerFimHistorico;
            copia(res1, help);
            limpar(res1);
            limpar(aux);
            j++;
            a = a->ant;
        }
        // gerar a soma das linhas da multiplicação
        j = 0;
        if ((i > 0) && (help->inicio->valor != 0))
        {
            for (int y = 0; y < i; y++)
                inserirFim(help, 0);
        }
        help1 = soma(l, help, res0);
        // removerFimHistorico;
        copia(help1, res0);
        limpar(help1);
        limpar(help);
        inserirInicio(help, 0);
        i++;
        b = b->ant;
    }
    copia(res0, n3);
    if ((n1->sinal == '+') && (n2->sinal == '+'))
        n3->sinal = '+';
    if ((n1->sinal == '-') && (n2->sinal == '+'))
        n3->sinal = '-';
    if ((n1->sinal == '+') && (n2->sinal == '-'))
        n3->sinal = '-';
    if ((n1->sinal == '-') && (n2->sinal == '-'))
        n3->sinal = '+';
    // inserirFimHistorico(l,n1,n2,n3,'*');

    return n3;
}

Numero *divisao(Historico *l, Numero *n1, Numero *n2, Numero *resto)
{
    if (l == NULL)
    {
        return NULL;
    }
    if (n1 == NULL || n2 == NULL)
    {
        logErro(-2);
        return NULL;
    }
    int i,j=0;
    Numero *n3 = criar();
    NoNumero *ptro = (NoNumero *)malloc(sizeof(NoNumero));
    Numero *seccao = criar();
    Numero *aux = criar();
    Numero *aux1 = criar();
    Numero *D = criar();
    inserirFim(D,1);
    int y = 1;
    i = diferenca(n1,n2);
    if(i==-1)
    {
        int n = tamanho(n2), m = tamanho(n1);
        seccao = cortaNumero(n1,n,ptro);
        if(m==n)
        {
            i = diferenca(seccao,n2);
            switch(i)
            {
                case 0://seccao == n2
                {
                    inserirFim(n3,1);
                    limpar(seccao);
                    inserirFim(seccao,0);
                    break;
                }
                case -1://seccao > n2
                {
                    while(i!=-2)
                    {
                        limpar(aux);
                        aux1 = multiplicacao(l,n2,D);
                        aux = subtracao(l,seccao,aux1);
                        i = diferenca(aux,n2);
                        limpar(aux1);
                        y++;
                        limpar(D);
                        inserirFim(D,y);
                    }
                    limpar(seccao);
                    copia(aux,seccao);
                    limpar(aux);
                    inserirFim(n3,y-1);
                    limpar(D);
                    break;
                }
            }
        }
        else
        {
        NoNumero *a = ptro;//nó imediatamente depois dos nós copiados para a secção.
        while(a!=NULL)
        {
            printf("seccao = ");
            mostrar(seccao);
            i = diferenca(seccao,n2);
            printf("seccao = ");
            mostrar(seccao);
            printf("n2 = ");
            mostrar(n2);
            printf("\ni = %d",i);
            switch(i)
            {
                case 0://seccao == n2
                {
                    printf("0");
                    inserirFim(n3,1);
                    limpar(seccao);
                    inserirFim(seccao,a->valor);
                    mostrar(seccao);
                    break;
                }
                case -2://seccao < n2
                {
                    printf("-2");
                    inserirFim(n3,0);
                    inserirFim(seccao,a->valor);
                    break;
                }
                case -1://seccao > n2
                {
                    printf("-1");
                    while(i!=-2)
                    {
                        limpar(aux);
                        aux1 = multiplicacao(l,n2,D);
                        aux = subtracao(l,seccao,aux1);
                        i = diferenca(aux,n2);
                        limpar(aux1);
                        y++;
                        limpar(D);
                        inserirFim(D,y);
                    }
                    limpar(seccao);
                    copia(aux,seccao);
                    limpar(aux);
                    inserirFim(seccao,a->valor);
                    inserirFim(n3,y-1);
                    y=1;
                    limpar(D);
                    inserirFim(D,y);
                    break;
                }
            }
            a = a->prox;
            if(a==NULL) printf("AAAAAAAAAA");
        }
        }
    }
    if(i==-2)
    {
        inserirFim(n3,0);
        copia(n1,resto);
        return n3;
    }
    if(i==0)
    {
        inserirFim(n3,1);
        inserirFim(resto,0);
        return n3;
    }
    if(i==-3)
    {
        return NULL;
    }
    // coisinhas da operacao
    corrige(n3);
    copia(seccao,resto);
    return n3;
}

int diferenca(Numero *a, Numero *b)
{
    if (listaVazia(a) == 0)
        return 1;
    if (listaVazia(b) == 0)
        return 1;
    NoNumero *no1 = a->inicio;
    NoNumero *no2 = b->inicio;
    int j = 0;
    int n = tamanho(a),m = tamanho(b);
    if(n>m)
        return -1;
    if(m>n)
        return -2;
    while (no1 != NULL)
    {
        if (no1->valor > no2->valor)
        {
            return -1;
        }
        else if (no1->valor < no2->valor)
        {
            return -2;
        }
        else
        {
            j++;
        }
        if((j==tamanho(a))&&(j==tamanho(b)))
            return 0;
        no1 = no1->prox;
        no2 = no2->prox;
    }
    return -3;
    //0 = iguais; -1 = a maior; -2 = b maior; -3 = erro.
}

//printa o numero passado no arquivo historico.txt, sim, esta funcionando.
int mostrarNumeroArquivo(Numero *a)
{
    hist=fopen("historico.txt","a");
    if(a==NULL)
    {
        logErro(-2);
        return -1;
    }

    NoNumero *no = a->inicio;
    if(a->sinal=='-')
        fprintf(hist,"%c",a->sinal);
    while(no!=NULL)
    {
        fprintf(hist,"%d",no->valor);
        no=no->prox;
    }
    fprintf(hist,"\n");


    fclose(hist);
    return 0;
}

/*falta so printar a operacao e o sinal de igual, salva as operacoes feitas no historico.txt
ta sendo chamada no opcaoA() dentro dos cases, parece ser uma boa pra gente usar.*/
int mostrarOperacao(Numero *a, Numero *b, Numero *c)
{
    hist=fopen("historico.txt","a");
    if(a==NULL || b==NULL || c==NULL)
    {
        logErro(-2);
        return -1;
    }
    fprintf(hist,"\n");
    mostrarNumeroArquivo(a);
    mostrarNumeroArquivo(b);
    mostrarNumeroArquivo(c);

    fclose(hist);
    return 0;
}

/*
    cortaNumero:
    supondo cortar 1234567, tirando os 3 primeiros elementos.
    essa função retornaria o Numero 123, e um ponteiro prx que apontaria pro nó do elemento de valor 4
*/
Numero *cortaNumero(Numero *a, int tam, NoNumero *prx)
{
    Numero *ret = criar();
    NoNumero *A = a->inicio;
    for(int i=0; i<tam; i++)
    {
        inserirFim(ret,A->valor);
        A = A->prox;
    }
    prx = A;
    return ret;
}

void logErro(int x)
{
    erro=fopen("log.txt","a+");
    if(x==-2)
        fprintf(erro,"\nNumero Nulo");
    if(x==-1)
        fprintf(erro,"\nHistorico Nulo");
    if(x==0)
        fprintf(erro,"Devolvendo resultado Nulo");
    fclose(erro);
}  