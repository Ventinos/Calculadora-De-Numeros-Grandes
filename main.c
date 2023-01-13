#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "lista.h"

int main()
{
    char op;
    char l; //lixo
    char *n1, *n2;
    criarLogs();
    Numero *A=criar();
    Numero *B=criar();
    Numero *C=criar();
    Historico *historico=criarHistorico();

    printf("\nEscolha uma das opcoes a baixo:\n");
    printf("A- Comecar operacao nova\n");
    printf("B- Limpar historico\n");
    printf("C- Exibir Historico de operacoes\n");
    printf("X- Encerrar o programa\n\n");

	scanf("%c", &op);
    scanf("%c", &l);
	op = toupper(op);
	fflush(stdin);

    while(op != 'X')
	{
		printf("\n");

	    switch(op)
	    {
            case 'A':
                //funcao de comecar nova operacao aqui
                opcaoA(A, B, C, historico);
                limpar(A);
                limpar(B);
                limpar(C);
                printf("\nOperacao Realizada!");
                break;

            case 'B':
                //funcao de limpar queue das operacoes aqui
                limparHistorico(historico);
                printf("\nClear Realizado!");
                break;

            case 'C':
                //funcao de mostrar historico
                mostrarHistorico(historico);
                printf("\nHistorico Exibido");
                break;

            case 'X':
                return 0;
            default:
                fprintf(stderr,"\nINPUT INVALIDO!");
		}

        printf("\nEscolha uma das opcoes a baixo:\n");
        printf("A- Comecar operacao nova\n");
        printf("B- Limpar historico\n");
        printf("C- Exibir Historico de operacoes\n");
        printf("X- Encerrar\n\n");

		scanf("%c", &op);
        scanf("%c", &l);
		op = toupper(op);
		fflush(stdin);
	}
	
    return 0; 
}