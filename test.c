#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvores.h"

int main(){
    Arv* A = criaArv();
    Info info;
    if (A == NULL)
    {
        printf("erro");
    }
    info.matricula = 4453;
    strcpy(info.nome, "gabriel");
    info.idade = 4;
    strcpy(info.cargo, "foda");
    info.salario = 123.123;

    ImprimeArv(A);

    insereArv(A, info);

    ImprimeArv(A);

    liberaArv(A);

    vaziaArv(A);

    free(A);

}
