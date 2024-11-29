#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "arvores.h"

int main()
{
    setlocale(LC_ALL,"portuguese");
    int select, n, i = 0, buscaMatricula;
    FILE *dataFile, *mainFile, *newFile;
    char linha[90], buffer[40];
    Info dado;
    NoArv *busca;
    Arv *A = arv_Criar();
    if (A == NULL)
    {
        printf("erro de alocamento\n");
        exit(2);
    }

    mainFile = fopen("DadosSave.txt", "a +"); //a tem espa�o entre +??
    if (mainFile == NULL)
    {
        printf("\n\tdados salvos n�o encontrados, inicializando nova �rvore:\n");
    }
    else
    {
        printf("aqui inicializarei a arvore com os dados j� salvos\n");
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
                 "\t6:\tBuscar por funcion�rio mais novo e mais velho;\n"
                 "\t7:\tVisualisar dados registrados no sistema;\n\n"
                 "\t0:\tSalvar e sair do programa.");
        select = -1;
        scanf("%d", &select);
        fflush(stdin);
        switch(select)
        {
            case 1:
                printf("\n\tdigite o nome do arquivo(se estiver na mesma pasta) ou ent�o o caminho para o arquivo:\t");
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
                        arv_Inserir(A, dado);
                        printf("%d escaneado: %d  %s  %d  %s %.2f\n", i, dado.matricula, dado.nome, dado.idade, dado.cargo, dado.salario); //sucesso
                        //fprintf(newFile, "%d %s %d %s %.2f\n", int1, string1, int2, string2, float1);
                    }
                    printf("inserido %d dados\n", i);
                }

                break;
            case 2:
                printf("atualizar\n");
                fflush(stdin);
                busca = editaNoArv(A->raiz, buscaMatricula);
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
                arv_Inserir(A, dado);
                break;
            case 4:
                if (arv_Vazia(A))
                {
                    printf("\n\tarvore vazia\t");
                }
                else
                {
                    printf("\n\tdigite a matricula do usuario que deseja remover:\t");
                    scanf("%d", &buscaMatricula);
                    arv_Remover(A, buscaMatricula);
                }
                break;
            case 5:
                printf("\n\tDigite a matricula do usuario que deseja procurar:\t");
                scanf("%d", &buscaMatricula);
                busca = buscaArv(A->raiz, buscaMatricula);
                if (busca != NULL)
                {
                    imprimeInfo(busca);
                }
                break;
            case 6:
                printf("Achar mais novo e mais velho\n");
                break;
            case 7:
                break;
            case 8:
                if (arv_Vazia(A))
                {
                    printf("\n\tarvore vazia\t");
                }
                else
                {
                    printf("\n1 - pre, 2 - in, 3 - pos\n\n");
                    scanf("%d", &select);
                    switch(select)
                    {
                    case 1: //pre
                        ImprimeArv(A, 1);
                        break;
                    case 2: //in
                        ImprimeArv(A, 2);
                        break;
                    case 3: //pos
                        ImprimeArv(A, 3);
                        break;
                    }
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
    arv_Liberar(A);
    return 0;
}
