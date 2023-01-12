#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

static FILE *erro;
static FILE *hist;

//construcao de um numero:
typedef struct no
{
    int valor;
    struct no *prox;
    struct no *ant;
}NoNumero;

typedef struct listaNumero
{
    char sinal;
    NoNumero *inicio;
}Numero;

//construcao do historico
typedef struct no_operacao
{
    //a e b sao entradas, c eh saida
    Numero *a;
    Numero *b;
    Numero *c;
    char operacao;
    struct no_operacao *prox;

}NoOperacao;

typedef struct listaHistorico
{
    NoOperacao *inicio;
}Historico;

void criarLogs()
{
    hist=fopen("historico.txt","w+");
    erro=fopen("log.txt","w+");
    fclose(erro);
    fclose(hist);
}

//funcoes Numero:
Numero *criar()
{
    erro=fopen("log.txt","a+");
    fprintf(erro,"\nNumero Criado");
    Numero *l = (Numero*)malloc(sizeof(Numero));
    l->inicio = NULL;
    return l;
}

int listaVazia(Numero *l)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if (l == NULL)
    {
        fprintf(erro,"\nNumero Nulo em listaVazia");
        return 2;
    }
    if (l->inicio == NULL) return 0;
    fclose(hist);
    fclose(erro);
    return 1;
}

int inserirInicio(Numero *l, int it) {
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if (l == NULL)
    {
        fprintf(erro,"\nNumero Nulo em inserirInicio");
        return 2;
    }
    NoNumero *no = (NoNumero *)malloc(sizeof(NoNumero));
    no->valor = it;
    no->prox = l->inicio;
    no->ant = NULL;
    if (l->inicio != NULL)
        l->inicio->ant = no;
    l->inicio = no;
    fclose(hist);
    fclose(erro);
    return 0;
}

int inserirFim(Numero *l, int it)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if (l == NULL)
    {
        fprintf(erro,"\nNumero Nulo em inserirFim");
        return 2;
    }
    if (listaVazia(l) == 0)
        return inserirInicio(l,it);
    NoNumero *noLista = l->inicio;
    while (noLista->prox != NULL)
        noLista = noLista->prox;
    NoNumero *no = (NoNumero*)malloc(sizeof(NoNumero));
    no->valor = it;
    no->prox = NULL;
    no->ant = noLista;
    noLista->prox = no;
    fclose(hist);
    fclose(erro);
    return 0;
}

void limpar(Numero *l)
{
    l->sinal = ' ';
    while (listaVazia(l) != 0)
        removerFim(l);
}

void mostrar(Numero *l)
{
    int y=5;
    if (l != NULL)
    {
        NoNumero *noLista = l->inicio;
        if(l->sinal=='-')
        printf("%c",l->sinal);
        while (noLista != NULL)
        {
            if(noLista->ant!=NULL)
            {
                for(int i=10;i<=100000;i=i*10)
                {
                    if((noLista->valor)<i)
                    {
                        for(int i=0;i<y;i++)
                        {
                            printf("0");
                        }
                        break;
                    }
                    y--;
                }
            }
            printf("%d",noLista->valor);
            noLista = noLista->prox;
        }
        printf("\n");
    }
}

int removerFim(Numero *l)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if (l == NULL)
    {
        fprintf(erro,"\nNumero Nulo em removerFim");
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
    fclose(hist);
    fclose(erro);
    return 0;
}

int removerInicio(Numero *l)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if (l == NULL)
    {
        fprintf(erro,"\nNumero Nulo em removerInicio");
        return 2;
    }
    if (listaVazia(l) == 0)
        return 1;
    NoNumero *noLista = l->inicio;
    l->inicio = noLista->prox;
    if (l->inicio != NULL)
        l->inicio->ant = NULL;
    free(noLista);
    fclose(hist);
    fclose(erro);
    return 0;
}

//funcoes historico:
Historico *criarHistorico()
{
    Historico *l = (Historico*)malloc(sizeof(Historico));
    l->inicio = NULL;
    return l;
}

int historicoVazio(Historico *l)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if (l == NULL)
    {
        fprintf(erro,"\nHistorico Nulo em historicoVazio");
        return 2;
    }
    if (l->inicio == NULL) return 0;
    fclose(hist);
    fclose(erro);
    return 1;
}

int inserirFimHistorico(Historico *l, Numero *n1, Numero *n2, Numero *n3, char op)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if (l == NULL)
    {
        fprintf(erro,"\nHistorico Nulo em inserirFimHistorico");
        return 2;
    }
    NoOperacao *noLista = l->inicio;
    if(noLista!=NULL)
    {
        while (noLista->prox != NULL)
        noLista = noLista->prox;
    }

    NoOperacao *no = (NoOperacao*)malloc(sizeof(NoOperacao));
    no->a=criar();
    no->b=criar();
    no->c=criar();

    copia(n1,no->a);
    copia(n2,no->b);
    copia(n3,no->c);

    no->operacao = op;

    if(noLista==NULL)
    {
        no->prox = noLista;
        noLista = no;
    }
    else
    {
        no->prox = noLista->prox;
        noLista->prox = no;
    }
    fclose(hist);
    fclose(erro);
    return 0;
}

int removerFimHistorico(Historico *l)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if (l == NULL)
    {
        fprintf(erro,"\nHistorico Nulo em removerFimHistorico");
        return 2;
    }
    if (historicoVazio(l) == 0) return 1;

    NoOperacao *noAuxiliar = NULL;
    NoOperacao *noLista = l->inicio;

    while (noLista->prox != NULL)
    {
        noAuxiliar = noLista;
        noLista = noLista->prox;
    }

    if (noAuxiliar == NULL) l->inicio = NULL;
    else noAuxiliar->prox = NULL;

    free(noLista);
    fclose(hist);
    fclose(erro);
    return 0;
}

void limparHistorico(Historico *l)
{
    while (historicoVazio(l) != 0)
        removerFimHistorico(l);
}

void mostrarHistorico(Historico *l)
{
    //nao testei mas acho que faz sentido
    //mo trampo namoral
    if (l != NULL)
    {
       printf("Historico:\n");
       NoOperacao *noLista = l->inicio;

       while (noLista != NULL)
       {
          mostrar(noLista->a);
          printf(" %c ",noLista->operacao);
          mostrar(noLista->b);
          printf(" = ");
          mostrar(noLista->c);
          printf("\n");
          noLista = noLista->prox;
       }
       printf("\n");
    }
}

//se quiser me chama no zap que eu explico, ta funcionando perfeitamente, so eh meio foda de entender.
int opcaoA(Numero *a, Numero *b, Numero *c, Historico *h)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if(a==NULL || b==NULL || c==NULL || h==NULL)
    {
        fprintf(erro,"\nNumero Nulo em opcaoA");
        return 2;
    }

    int r;
    int userInputA;
    char teste;
    char lixo;
    char operacao;

    printf("\nInsira o Primeiro Numero: ");
    teste=getc(stdin);
    while(teste!='\n')
    {
        if(teste=='-')
            a->sinal='-';

        else
            ungetc(teste,stdin);

        scanf("%6d",&userInputA);
        inserirFim(a,userInputA);
        userInputA=0;
        teste=getc(stdin);
    }
    fflush(stdin);
    if(a->sinal!='-')
        a->sinal='+';
    printf("\nA=");
    corrige(a);
    mostrar(a);

    printf("\nInsira a operacao:");
    scanf("%c",&operacao);
    fflush(stdin);

    printf("\nInsira o Segundo Numero: ");
    teste=getc(stdin);
    while(teste!='\n')
    {
        if(teste=='-')
            b->sinal='-';

        else
            ungetc(teste,stdin);

        scanf("%6d",&userInputA);
        inserirFim(b,userInputA);
        userInputA=0;
        teste=getc(stdin);
    }
    fflush(stdin);
    if(b->sinal!='-')
        b->sinal='+';
    printf("\nB=");
    corrige(b);
    mostrar(b);
    //printf("\n\n\n%c %c",a->sinal,b->sinal);

    switch (operacao)
    {

        case '+':
            r = soma(h,a,b,c);
            if(r==0)
            {
                printf("\nsoma feita!");
                printf("\no resultado da soma eh:");
                mostrar(c);
            }
            break;
        case '-':
            r = subtracao(h,a,b,c);
            if(r==0)
            {
                printf("\nsubtracao feita!");
                printf("\no resultado da subtracao eh:");
                mostrar(c);
            }
            break;

        case '*':
            r = multiplicacao(h,a,b,c);
            if(r==0)
            {
                printf("\nmultiplicacao feita!");
                printf("\no resultado da multiplicacao eh:");
                mostrar(c);
            }
            if(r==1)
                printf("ero");
            break;

        case '/':
            r = divisao(h,a,b,c);
            if(r==0)
            {
                printf("\ndivisao feita!");
                printf("\no resultado da divisao eh:");
                mostrar(c);
            }
            break;

        default:
            printf("\noperacao invalida!ERRO!");
            return -1;
            break;
    }
    fclose(hist);
    fclose(erro);

}

int corrige(Numero *l)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if(l==NULL)
    {
        fprintf(erro,"\nNumero Nulo em corrige");
        return 2;
    }
    if(listaVazia(l)==0) return 1;
    int i,j;
    NoNumero *nonum = l->inicio;
    while(nonum->prox != NULL)
        nonum = nonum->prox;

    //printf("\nno antes: %d",nonum->valor);
    NoNumero *aux = nonum->ant;
    while(aux != NULL)//aux é o anterior de nonum, se aux é NULL, é pq o nonum é o primeiro no da lista
    {
        for(i=10;i<=100000;i=i*10)//i é fator de correçao de algarismo, que tb verifica o limite do valor de nonum(se for menor que 10^6, precisa de correçao)
        {
            if(nonum->valor==(nonum->valor)%i)
            {
                j=(aux->valor)%10;//pega o ultimo algarismo do no anterior
                aux->valor=(aux->valor)/10;//corrige questões de classe numerica
                nonum->valor=(nonum->valor) + j*i;//insere o algarismo do no anterior no no atual, multiplicando ele pelo fator de correçao de classe do algarismo
            }
        }
        nonum = nonum->ant;
        aux = aux->ant;
    }

    //while(nonum->prox != NULL)
    //    nonum = nonum->prox;

    //printf("\nno depois: %d",nonum->valor);
    //printf("\n\n\n");
    fclose(hist);
    fclose(erro);
    return 0;
}

int tamanho(Numero *l)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if(l==NULL)
    {
        fprintf(erro,"\nNumero Nulo em opcaoA");
        return -1;
    }
    if(listaVazia(l)==0) return 0;
    int i=1;
    NoNumero *nolista = l->inicio;
    while(nolista->prox!=NULL)
    {
        i++;
        nolista=nolista->prox;
    }
    fclose(hist);
    fclose(erro);
    return i;
}

int copia(Numero *l, Numero *r)
{
    limpar(r);
    NoNumero *no = l->inicio;
    while(no!=NULL)
    {
        inserirFim(r,no->valor);
        no = no->prox;
    }
    r->sinal = l->sinal;
    return 0;
}

//funcoes operacoes diversas
//processo q eu pensei pras operacoes:a gnt recebe da main o historico criado la, os numeros(ja criado e formado) e a operacao que o usuario digita, e assim é gerado uma lista do tipo Numero que é o resultado da operacao.
//no fim tudo seria inserido no historico
//B)

int soma(Historico *l, Numero *n1, Numero *n2, Numero *n3)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if(l==NULL)
    {
        fprintf(erro,"\nHistorico Nulo em soma");
        return 4;
    }
    if(n1==NULL || n2==NULL || n3==NULL)
    {
        fprintf(erro,"\nNumero Nulo em somaAlt");
        return 2;
    }
    if (listaVazia(n1) == 0) return 1;
    if (listaVazia(n2) == 0) return 1;

    if(tamanho(n1)==1)
    {
        if(n1->inicio->valor==0)
        {
            copia(n2,n3);
            printf("\nRESULTADO: ");
            mostrar(n3);
            inserirFimHistorico(l,n1,n2,n3,'+');
            fclose(hist);
            fclose(erro);
            return 0;
        }
    }

    if(tamanho(n2)==1)
    {
        if(n2->inicio->valor==0)
        {
            copia(n1,n3);
            printf("\nRESULTADO: ");
            mostrar(n3);
            inserirFimHistorico(l,n1,n2,n3,'+');
            fclose(hist);
            fclose(erro);
            return 0;
        }
    }

    if((n1->sinal=='-')&&(n2->sinal=='+')) return subtracao(l,n1,n2,n3);
    if((n1->sinal=='+')&&(n2->sinal=='-')) return subtracao(l,n1,n2,n3);
    if((n1->sinal=='-')&&(n2->sinal=='-')) n3->sinal='-';
    else n3->sinal='+';
    int y;
    NoNumero *a = n1->inicio;
    NoNumero *b = n2->inicio;

    while(a->prox != NULL)
        a = a->prox;

    while(b->prox != NULL)
        b = b->prox;

    while((a!=NULL)&&(b!=NULL))
    {
        y = a->valor + b->valor;
        inserirInicio(n3,y);
        a = a->ant;
        b = b->ant;
    }

    if(a==NULL)
    {
        while(b!=NULL)
        {
            inserirInicio(n3,b->valor);
            b = b->ant;
        }
    }

    if(b==NULL)
    {
        while(a!=NULL)
        {
            inserirInicio(n3,a->valor);
            a = a->ant;
        }
    }

    //correção do resultado
    NoNumero *c = n3->inicio;
    while(c->prox != NULL)
        c = c->prox;

    while(c!=NULL)
    {
        if(c->valor>1000000)
        {
            c->valor = (c->valor)%1000000;
            if(c->ant!=NULL)
                c->ant = c->ant + 1;
            else
                inserirInicio(n3,1);
        }
        c = c->ant;
    }
    /*printf("\nRESULTADO: ");
    mostrar(n3);*/
    inserirFimHistorico(l,n1,n2,n3,'+');
    fclose(hist);
    fclose(erro);
    return 0;
}

int subtracao(Historico *l, Numero *n1, Numero *n2, Numero *n3)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if(l==NULL)
    {
        fprintf(erro,"\nHistorico Nulo em subtracao");
        return 4;
    }
    if(n1==NULL || n2==NULL || n3==NULL)
    {
        fprintf(erro,"\nNumero Nulo em somaAlt");
        return 2;
    }
    if (listaVazia(n1) == 0) return 1;
    if (listaVazia(n2) == 0) return 1;

    if((n1->sinal=='-')&&(n2->sinal=='+'))
    {
        n2->sinal = '-';
        soma(l,n1,n2,n3);
        n2->sinal = '+';
        return 0;
    }
    if((n1->sinal=='+')&&(n2->sinal=='-'))
    {
        n2->sinal = '+';
        soma(l,n1,n2,n3);
        n2->sinal = '-';
        return 0;
    }

    if((n1->sinal=='+')&&(n2->sinal=='+'))
    {
        int n = tamanho(n1);
        int m = tamanho(n2);
        if(n>m)
        {
            if(n3->sinal != '-')
                n3->sinal = '+';
        }
        else if(n<m)
        {
            n3->sinal = '-';
            return subtracao(l,n2,n1,n3);
        }
        else
        {
            NoNumero *no1 = n1->inicio;
			NoNumero *no2 = n2->inicio;

			while(no1 != NULL)
			{
				if(no1->valor > no2->valor)
				{
                    if(n3->sinal != '-')
					    n3->sinal = '+';
					break;
				}
				else if(no1->valor < no2->valor)
				{
					n3->sinal = '-';
                    return subtracao(l,n2,n1,n3);
				}
                else
                {
                    n3->sinal = '+';
                    inserirInicio(n3,0);
                }
				no1 = no1->prox;
				no2 = no2->prox;
			}
        }
    }

    if((n1->sinal=='-')&&(n2->sinal=='-'))
    {
        int n = tamanho(n1);
        int m = tamanho(n2);
        if(n>m)
        {
            if(n3->sinal != '+') n3->sinal = '-';
        }
        else if(n<m)
        {
            n3->sinal = '+';
            return subtracao(l,n2,n1,n3);
        }
        else
        {
            NoNumero *no1 = n1->inicio;
			NoNumero *no2 = n2->inicio;

			while(no1 != NULL)
			{
				if(no1->valor > no2->valor)
				{
                    if(n3->sinal != '+')
					    n3->sinal = '-';
					break;
				}
				else if(no1->valor < no2->valor)
				{
					n3->sinal = '+';
                    return subtracao(l,n2,n1,n3);
				}
                else
                {
                    n3->sinal = '+';
                    inserirInicio(n3,0);
                }
				no1 = no1->prox;
				no2 = no2->prox;
			}
        }
    }

    NoNumero *no1 = n1->inicio;
    NoNumero *no2 = n2->inicio;

    while(no1->prox != NULL)
        no1 = no1->prox;

    while(no2->prox != NULL)
        no2 = no2->prox;
    NoNumero *aux1 = no1->ant;
    int i = 1,y;
    while(no1!=NULL && no2!=NULL)
    {
        if((no2->valor)>(no1->valor))
        {
            while(aux1!=NULL && aux1->valor == 0)
            {
                i++;
                aux1 = aux1->ant;
            }
            for(int y=0;y<i;y++)
            {
                aux1->valor = aux1->valor - 1;
                (aux1->prox)->valor = (aux1->prox)->valor + 1000000;
                aux1 = aux1->prox;
            }
        }
        y = no1->valor - no2->valor;
        inserirInicio(n3,y);
        no1 = no1->ant;
        if(no1!=NULL)
            aux1 = aux1->ant;
        no2 = no2->ant;
    }

    if(no1==NULL)
    {
        while(no2!=NULL)
        {
            inserirInicio(n3,no2->valor);
            no2=no2->ant;
        }
    }

    if(no2==NULL)
    {
        while(no1!=NULL)
        {
            inserirInicio(n3,no1->valor);
            no1 =  no1->ant;
        }
    }

    while((n3->inicio)->valor == 0)
    {
        if(n3->inicio->prox==NULL) break;
        removerInicio(n3);
    }

    inserirFimHistorico(l,n1,n2,n3,'-');
    /*printf("\nRESULTADO: ");
    mostrar(n3);*/
    fclose(hist);
    fclose(erro);
    return 0;
}

int multiplicacao(Historico *l, Numero *n1, Numero *n2, Numero *n3)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if(l==NULL)
    {
        fprintf(erro,"\nHistorico Nulo em multiplicacao");
        return 4;
    }
    if(n1==NULL || n2==NULL || n3==NULL)
    {
        fprintf(erro,"\nNumero Nulo em somaAlt");
        return 2;
    }
    if (listaVazia(n1) == 0) return 1;
    if (listaVazia(n2) == 0) return 1;

    if(tamanho(n1)==1)
    {
        if(n1->inicio->valor==0)
        {
            copia(n1,n3);
            inserirFimHistorico(l,n1,n2,n3,'+');
            fclose(hist);
            fclose(erro);
            return 0;
        }
    }

    if(tamanho(n2)==1)
    {
        if(n2->inicio->valor==0)
        {
            copia(n2,n3);
            inserirFimHistorico(l,n1,n2,n3,'+');
            fclose(hist);
            fclose(erro);
            return 0;
        }
    }

    Numero *res0 = criar();
    Numero *res1 = criar();
    Numero *res2 = criar();

    inserirInicio(res2,2);
    inserirInicio(res1,1);
    inserirInicio(res0,0);

    Numero *j=criar();
    Numero *k=criar();
    Numero *m=criar();
    Numero *nx=criar();
    inserirFim(j,0);
    inserirFim(m,0);
    inserirFim(k,0);
    Numero *nr=criar();
    inserirFim(nr,0);


    copia(n1,j);
    removerFimHistorico(l);

    copia(n2,m);
    removerFimHistorico(l);

    soma(l,n1,n1,nx);
    removerFimHistorico(l);
    limpar(n1);

    subtracao(l,n2,res2,k);
    removerFim(k);
    removerFimHistorico(l);
    limpar(n2);

    copia(k,n2);
    removerFimHistorico(l);
    limpar(k);

    while(n2->inicio->valor!=0)
    {
        soma(l,j,nx,n1);
        limpar(nx);

        copia(n1,nx);
        removerFimHistorico(l);
        limpar(n1);

        subtracao(l,n2,res1,k);
        removerFimHistorico(l);
        limpar(n2);

        copia(k,n2);
        removerFimHistorico(l);
        limpar(k);
    }

    if((j->sinal=='+')&&(m->sinal=='+')) nx->sinal='+';
    if((j->sinal=='-')&&(m->sinal=='+')) nx->sinal='-';
    if((j->sinal=='+')&&(m->sinal=='-')) nx->sinal='-';
    if((j->sinal=='-')&&(m->sinal=='-')) nx->sinal='+';

    copia(nx,n3);
    inserirFimHistorico(l,n1,j,n3,'*');
    return 0;
}

int divisao(Historico *l, Numero *n1, Numero *n2, Numero *n3)
{
    hist=fopen("historico.txt","a+");
    erro=fopen("log.txt","a+");
    if(l==NULL)
    {
        fprintf(erro,"\nHistorico Nulo em divisao");
        return 4;
    }
    if(n1==NULL || n2==NULL || n3==NULL)
    {
        fprintf(erro,"\nNumero Nulo em divisao");
        return 2;
    }
    if (historicoVazio(l) == 0) return 1;
    //coisinhas da operacao
    inserirFimHistorico(l,n1,n2,n3,'/');
    fclose(hist);
    fclose(erro);
    return 0;
}
