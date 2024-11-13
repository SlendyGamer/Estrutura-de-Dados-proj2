#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "arvores.h"

int main()
{
    setlocale(LC_ALL,"portuguese");
    FILE *file, *newFile;
    char line[90];
    Info info;
    Arv* A = criaArv();
    if (A == NULL)
    {
        printf("erro");
    }

    file = fopen("Dados.txt", "r");
    //newFile = fopen("novosDados.txt", "w");

    if (file == NULL)
    {
        printf("arquivo antigo nao encontrado");
        return 2;
    }
    //else if (newFile == NULL)
    //{
    //    printf("arquivo novo nao criado");
    //    return 2;
    //}
    else
    {
        int n;

        if (fgets(line,sizeof(line), file) != NULL)
        {
        sscanf(line, "%d", &n);
        }
        //printf("%d\n", n);
        while (fgets(line,sizeof(line), file) != NULL)
        {
            sscanf(line, "%d %39[^\n] %d %24[^\n] %f", &info.matricula, info.nome, &info.idade, info.cargo, &info.salario);
            insereArv(A, info);
            //printf("escaneado: %d  %s  %d  %s %.2f\n", info.matricula, info.nome, info.idade, info.cargo, info.salario); //sucesso
            //fprintf(newFile, "%d %s %d %s %.2f\n", int1, string1, int2, string2, float1);
            //n--;
        }
        ImprimeArv(A);
        fclose(file);
        liberaArv(A);
        //fclose(newFile);
        printf("sucesso");
    }
}
