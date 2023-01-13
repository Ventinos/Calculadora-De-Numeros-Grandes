#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

FILE *erro;
FILE *hist;

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
    erro=fopen("log.txt","a+");
    fclose(erro);
    fclose(hist);
}
//funcoes Numero:
Numero *criar()
{
    Numero *l = (Numero*)malloc(sizeof(Numero));
    if(l==NULL)
        fprintf(erro,"\nERRO AO CRIAR NUMERO");
    fprintf(erro,"\nNumero Criado");
    l->inicio = NULL;
    return l;
}

int listaVazia(Numero *l)
{
    
    if (l == NULL)
    {
        fprintf(erro,"\nNumero Nulo em listaVazia");
        return 2;
    } 
    if (l->inicio == NULL) return 0;
    return 1;
}

int inserirInicio(Numero *l, int it) {
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
    return 0;
}

int inserirFim(Numero *l, int it)
{
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
    int i,j;
    if (l != NULL)
    {
        NoNumero *noLista = l->inicio;
        if(l->sinal=='-')
            printf("%c",l->sinal);
        while (noLista != NULL)
        {
            /*if(noLista->ant!=NULL)
            {
                for(i=10;i<=100;i=i*10)
                {
                    y--;
                    if((noLista->valor)==0)
                    {
                        for(j=0;j<5;j++)
                        {
                            printf("0");
                        }
                        i=1000;
                    }
                    else if((noLista->valor)<i)
                    {
                        for(j=0;j<y;j++)
                        {
                            printf("0");
                        }
                        i=1000;
                    }
                }
            }
            y=6;*/
            printf("%d",noLista->valor);
            noLista = noLista->prox;
        }
        printf("\n");
    }
}

int removerFim(Numero *l)
{
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
    return 0;
}

int removerInicio(Numero *l) 
{
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
    if (l == NULL)
    {
        fprintf(erro,"\nHistorico Nulo em historicoVazio");
        return 2;
    } 
    if (l->inicio == NULL) return 0;

    return 1;
}

int inserirFimHistorico(Historico *l, Numero *n1, Numero *n2, Numero *n3, char op)
{
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
    copia(no->a, n1);
    copia(no->b, n2);
    copia(no->c, n3);
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
    return 0;
}

int removerFimHistorico(Historico *l)
{
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
        scanf("%1d",&userInputA);
        inserirFim(a,userInputA);
        userInputA=0;
        teste=getc(stdin);
    }
    fflush(stdin);
    if(a->sinal!='-')
        a->sinal='+';
    printf("\nA=");
    //corrige(a);
    mostrar(a);

    printf("\nInsira a operacao:");
    scanf("%c",&operacao);
    fflush(stdin);

    lixo = getc(stdin);
    printf("\nInsira o Segundo Numero: ");
    teste=getc(stdin);
    while(teste!='\n')
    {
        if(teste=='-')
            b->sinal='-';

        else
            ungetc(teste,stdin);

        scanf("%1d",&userInputA);
        inserirFim(b,userInputA);
        userInputA=0;
        teste=getc(stdin);
    }
    fflush(stdin);
    if(b->sinal!='-')
        b->sinal='+';
    printf("\nB=");
    //corrige(b);
    mostrar(b);
    //printf("\n\n\n%c %c",a->sinal,b->sinal);

    switch (operacao)
    {

        case '+':
        {
            c=soma(h,a,b);
            printf("\nsoma feita!");
            printf("\no resultado da soma eh:");
            mostrar(c);
            break;
        }
        case '-':
        {
            c = subtracao(h,a,b);
            printf("\nsubtracao feita!");
            printf("\no resultado da subtracao eh:");
            mostrar(c);
            break;
        }
        case '*':
        {
            //r = multiplicacao(h,a,b,c);
            if(r==0)
            {
                printf("\nmultiplicacao feita!");
                printf("\no resultado da multiplicacao eh:");
                mostrar(c);
            }
            if(r==1)
                printf("ero");
            break;
        }
        case '/':
        {
            r = divisao(h,a,b,c);
            if(r==0)
            {
                printf("\ndivisao feita!");
                printf("\no resultado da divisao eh:");
                mostrar(c);
            }
            break;
        }
        default:
            printf("\noperacao invalida!ERRO!");
            return -1;
            break;
    }
    
}

/*int corrige(Numero *l)
{
    
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
        for(i=10;i<=100;i=i*10)//i é fator de correçao de algarismo, que tb verifica o limite do valor de nonum(se for menor que 10^6, precisa de correçao)
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
    
    return 0;
}*/

int tamanho(Numero *l)
{
    
    if(l==NULL)
    {
        fprintf(erro,"\nNumero Nulo em tamanho");
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
    
    return i;
}

int copia(Numero *l, Numero *r)
{
    if(l==NULL || r==NULL)
    {
        fprintf(erro,"\nNumero Nulo em copia");
        return -1;
    }
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

Numero *soma(Historico *l, Numero *n1, Numero *n2)
{
    if(l==NULL)
    {
        fprintf(erro,"\nHistorico Nulo em soma");
        return NULL;
    }
    if(n1==NULL || n2==NULL)
    {
        fprintf(erro,"\nNumero Nulo em soma");
        return NULL;
    } 
    if (listaVazia(n1) == 0) return NULL;
    if (listaVazia(n2) == 0) return NULL;
    Numero *n3 = criar();
    
    if(tamanho(n1)==1)
    {
        if(n1->inicio->valor==0)
        {
            copia(n2,n3);
            inserirFimHistorico(l,n1,n2,n3,'+');
            fclose(hist);
            fclose(erro);
            return n3;
        }
    }
    
    if(tamanho(n2)==1)
    {
        if(n2->inicio->valor==0)
        {
            copia(n1,n3);
            inserirFimHistorico(l,n1,n2,n3,'+');
            fclose(hist);
            fclose(erro);
            return n3;
        }
    }

    if((n1->sinal=='-')&&(n2->sinal=='+')) return subtracao(l,n1,n2);
    if((n1->sinal=='+')&&(n2->sinal=='-')) return subtracao(l,n1,n2);
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

    printf("\n");
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

    NoNumero *c = n3->inicio;
    while(c->prox != NULL)
        c = c->prox;

    while(c!=NULL)
    {
        if(c->valor>=10)
        {
            c->valor = (c->valor)%10;
            if(c->ant!=NULL)
                (c->ant)->valor = (c->ant)->valor + 1;
            else
                inserirInicio(n3,1);
        }
        c = c->ant;
    }
    //inserirFimHistorico(l,n1,n2,n3,'+');
    /*NoNumero *m1=n1->inicio;
    while(m1!=NULL)
    {
        fprintf(erro,"\n%d ");
        m1=m1->prox;
    }
    fprintf(hist,"+");
    m1=n2->inicio;
    while(m1!=NULL)
    {
        fprintf(erro," %d");
        m1=m1->prox;
    }
    fprintf(erro,"=");
    m1=n3->inicio;
    while(m1!=NULL)
    {
        fprintf(erro," %d");
        m1=m1->prox;
    }*/
    return n3;
}

Numero *subtracao(Historico *l, Numero *n1, Numero *n2)
{
    
    if(l==NULL)
    {
        fprintf(erro,"\nHistorico Nulo em subtracao");
        return NULL;
    }
    if(n1==NULL || n2==NULL)
    {
        fprintf(erro,"\nNumero Nulo em subtracao");
        return NULL;
    } 
    if (listaVazia(n1) == 0) return NULL;
    if (listaVazia(n2) == 0) return NULL;
    Numero *n3 = criar();

    if((n1->sinal=='-')&&(n2->sinal=='+'))
    {
        n2->sinal = '-';
        n3 = soma(l,n1,n2);
        n2->sinal = '+';
        return n3;
    }
    if((n1->sinal=='+')&&(n2->sinal=='-'))
    {
        n2->sinal = '+';
        n3 = soma(l,n1,n2);
        n2->sinal = '-';
        return n3;
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
            return subtracao(l,n2,n1);
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
                    return subtracao(l,n2,n1);
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
            return subtracao(l,n2,n1);
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
                    return subtracao(l,n2,n1);
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
                (aux1->prox)->valor = (aux1->prox)->valor + 10;
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

    //inserirFimHistorico(l,n1,n2,n3,'-');
    /*printf("\nRESULTADO: ");
    mostrar(n3);*/
    return n3;
}
/*
int multiplicacao(Historico *l, Numero *n1, Numero *n2, Numero *n3)
{
    
    if(l==NULL)
    {
        fprintf(erro,"\nHistorico Nulo em multiplicacao");
        return 4;
    }
    if(n1==NULL || n2==NULL)
    {
        fprintf(erro,"\nNumero Nulo em multiplicacao");
        return 2;
    }
    limpar(n3);
    if (listaVazia(n1) == 0) return 1;
    if (listaVazia(n2) == 0) return 1;
    int y,z,i=0,j=0;
    NoNumero *a = n1->inicio;
    NoNumero *b = n2->inicio;
    //NoNumero *a1 = (NoNumero *)malloc(sizeof(NoNumero));
    Numero *res1 = criar();
    Numero *res0 = criar();
    Numero *help1 = criar();
    Numero *help = criar();
    Numero *help2 = criar();
    Numero *aux = criar();
    NoNumero *noLista = aux->inicio;

    inserirInicio(res0,0);

    while(b->prox != NULL)
        b = b->prox;
    
    res1 = n1;
    soma(l,n1,n2,n3);
    
    while(b!=NULL)
    {
        while(a->prox != NULL)
            a = a->prox;
        //printf("%d",a->valor);
        while(a!=NULL)
        {
            y = (b->valor)%1000;
            z = (b->valor)/1000;
            inserirInicio(aux,y*(a->valor));
            inserirInicio(aux,z*(a->valor));
            noLista = aux->inicio;//noLista==TuT                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
            noLista = noLista->prox;
            y = (noLista->valor)/1000;
            noLista->valor = (noLista->valor)%1000;
            (noLista->ant)->valor = (noLista->ant)->valor + y;
            //corrige(aux);
            while(noLista!=NULL)
            {
                if(noLista->valor>1000000)
                {
                    noLista->valor = (noLista->valor)%1000000;
                    if(noLista->ant!=NULL)
                        (noLista->ant)->valor = (noLista->ant)->valor + 1;
                    else
                        inserirInicio(n3,1);
                }
                noLista = noLista->ant;
            }
            if(j>0)
            {
                for(int y = 0;y<j;y++)
                {
                    inserirFim(aux,0);
                }
            }
            if(j==0)
            {
                copia(aux,help);
            }
            else
            {
                soma(l,help,aux,help1);
                removerFimHistorico(l);
                copia(help1,help);
                limpar(help1);
            }
            limpar(aux);
            j++;
            a = a->ant;
        }
        j=0;
        if(i>0)
        {
            for(int y=0;y<i;y++)
                inserirFim(help,0);
        }
        if(i==0)
        {
            copia(help,res1);
        }
        else
        {
            soma(l,help,res1,help2);
            removerFimHistorico(l);
            copia(help2,res1);
            limpar(help2);
        }
        limpar(help);
        i++;
        b = b->ant;
    }
    copia(res1,n3);
    if((n1->sinal=='+')&&(n2->sinal=='+')) n3->sinal='+';
    if((n1->sinal=='-')&&(n2->sinal=='+')) n3->sinal='-';
    if((n1->sinal=='+')&&(n2->sinal=='-')) n3->sinal='-';
    if((n1->sinal=='-')&&(n2->sinal=='-')) n3->sinal='+';
    inserirFimHistorico(l,n1,n2,n3,'*');
    
    return 0;
}*/

int divisao(Historico *l, Numero *n1, Numero *n2, Numero *n3)
{
    
    if(l==NULL)
    {
        fprintf(erro,"\nHistorico Nulo em divisao");
        return 4;
    }
    if(n1==NULL || n2==NULL)
    {
        fprintf(erro,"\nNumero Nulo em divisao");
        return 2;
    } 
    if (historicoVazio(l) == 0) return 1;
    //coisinhas da operacao
    inserirFimHistorico(l,n1,n2,n3,'/');
    
    return 0;
}