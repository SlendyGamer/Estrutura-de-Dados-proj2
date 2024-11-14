#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "arvores.h"

int main()
{
    int select, n, i = 0, buscaMatricula;
    FILE *dataFile, *mainFile, *newFile;
    char linha[90], buffer[40];
    Info dado;
    Arv *A = criaArv();
    if (A == NULL)
    {
        printf("erro de alocamento\n");
        exit(2);
    }

    mainFile = fopen("DadosSave.txt", "a +"); //a tem espaço entre +??
    if (mainFile == NULL)
    {
        printf("\n\tdados salvos não encontrados, inicializando nova árvore:\n");
    }
    else
    {
        printf("aqui inicializarei a arvore com os dados já salvos\n");
    }

    do
    {
        printf("\n\tStaff Control v.1.0:\n\n"
                 "\tO que deseja?\n"
                 "\t1:\tCarregar novos dados de um arquivo no sistema;\n"
                 "\t2:\tAtualizar dado do sistema;\n"
                 "\t3:\tIncluir novo dado no sistema;\n"
                 "\t4:\tRemover dado do sistema;\n"
                 "\t5:\tBuscar por dado no sistema;\n"
                 "\t6:\tBuscar por funcionário mais novo e mais velho;\n"
                 "\t7:\tVisualisar dados registrados no sistema;\n\n"
                 "\t0:\tSalvar e sair do programa.");
        select = -1;
        scanf("%d", &select);
        fflush(stdin);
        switch(select)
        {
            case 1:
                printf("\n\tdigite o nome do arquivo(se estiver na mesma pasta) ou então o caminho para o arquivo:\t");
                gets(buffer);
                dataFile = fopen(buffer, "r +");
                if (dataFile == NULL)
                {
                    printf("arquivo nao encontrado\n");
                }
                else
                {
                    if (fgets(linha,sizeof(linha), dataFile) != NULL)
                    {
                        sscanf(linha, "%d", &n);
                    }
                    while (fgets(linha,sizeof(linha), dataFile) != NULL)
                    {
                        i++;
                        sscanf(linha, "%d %39[^\n] %d %24[^\n] %f", &dado.matricula, dado.nome, &dado.idade, dado.cargo, &dado.salario);
                        insereArv(A, dado);
                        printf("%d escaneado: %d  %s  %d  %s %.2f\n", i, dado.matricula, dado.nome, dado.idade, dado.cargo, dado.salario); //sucesso
                        //fprintf(newFile, "%d %s %d %s %.2f\n", int1, string1, int2, string2, float1);
                    }
                    printf("inserido %d dados\n", i);
                }

                break;
            case 2:
                printf("atualizar\n");
                break;
            case 3:
                scanf("%d", &dado.matricula);
                fflush(stdin);
                gets(buffer);
                fflush(stdin);
                strcpy(dado.nome, buffer);
                scanf("%d", &dado.idade);
                fflush(stdin);
                gets(buffer);
                fflush(stdin);
                strcpy(dado.cargo, buffer);
                scanf("%f", &dado.salario);
                fflush(stdin);
                insereArv(A, dado);
                break;
            case 4:
                if (vaziaArv(A))
                {
                    printf("\n\tarvore vazia\t");
                }
                else
                {
                    printf("\n\tdigite a matrícula do usuário que deseja remover:\t");
                    scanf("%d", &buscaMatricula);
                    removeArv(A, buscaMatricula);
                }
                break;
            case 5:
                printf("buscar\n");
                break;
            case 6:
                printf("Achar mais novo e mais velho\n");
                break;
            case 7:
                if (vaziaArv(A))
                {
                    printf("\n\tarvore vazia\t");
                }
                else
                {
                    ImprimeArv(A);
                }
                break;
            case 0:
                printf("finalizar\n");
                break;
            default:
                printf("error\n\n");
                break;
            }
    } while (select != 0);
    liberaArv(A);
    return 0;
}
