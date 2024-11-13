#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "arvores.h"

int main()
{
    int select;

    do
    {
        select = -1;
        scanf("%d", &select);
        fflush(stdin);
        switch(select)
        {
            case 1:
                printf("inserir\n");
                break;
            case 2:
                printf("atualizar\n");
                break;
            case 3:
                printf("incluir\n");
                break;
            case 4:
                printf("remover\n");
                break;
            case 5:
                printf("buscar\n");
                break;
            case 6:
                printf("buscar mais novo e mais velho\n");
                break;
            case 7:
                printf("imprimir tudo\n");
                break;
            case 0:
                printf("finalizar\n");
                break;
            default:
                printf("error\n\n");
                break;
            }
    } while (select != 0);
    return 0;
}
