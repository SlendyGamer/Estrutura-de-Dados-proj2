#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include "arvores.h"

int main()
{
    setlocale(LC_ALL,"portuguese");
    int select, n = 0, i = 0, buscaMatricula;
    FILE *dataFile;
    char linha[90], buffer[40];
    Info dado;
    NoArv *busca, *maior, *menor;
    Arv *A = arv_Criar();
    if (A == NULL)
    {
        printf("\tErro de alocaÁ„o\n");
        exit(2);
    }

    dataFile= fopen("DadosSalvos.txt", "r"); //a tem espaÔøΩo entre +??
    if (dataFile == NULL)
    {
        printf("\n\tdados salvos n„o encontrados, inicializando nova ·rvore vazia!\n");
    }
    else
    {
        printf("\n\tdados salvos encontrados, carregando dados!\n\n");
        if (fgets(linha,sizeof(linha), dataFile) != NULL)
        {
            sscanf(linha, "%d", &n);
        }
        while (fgets(linha,sizeof(linha), dataFile) != NULL)
        {
            i++;
            sscanf(linha, "%d %38[^\n] %d %23[^\n] %f", &dado.matricula, dado.nome, &dado.idade, dado.cargo, &dado.salario);
            arv_Inserir(A, dado);
        }
        printf("\n\t%d dados escaneados\n\n", i);
        i = 0;
        fclose(dataFile);

    }

    do
    {
        printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
        printf("\n\t\t\t>>>Staff Control<<<\n\n"
               "\t1:\tInserir novos funcion·rios por um arquivo;\n"
               "\t2:\tAtualizar funcion·rio do sistema;\n"
               "\t3:\tIncluir novo funcion·rio no sistema;\n"
               "\t4:\tRemover funcion·rio do sistema;\n"
               "\t5:\tBuscar por funcion·rio no sistema;\n"
               "\t6:\tAchar funcion·rio mais novo e mais velho;\n"
               "\t7:\tVisualisar funcion·rios de algum cargo;\n"
               "\t8:\tVisualisar todos os funcion·rios registrados;\n\n"
               "\t0:\tSalvar e sair do programa.\n");
        printf("\n\\:\t");
        select = -1;
        scanf("%d", &select);
        fflush(stdin);
        system("cls");
        switch(select)
        {
            case 1:
                printf("\n\tdigite o nome do arquivo(se estiver na mesma pasta) ou ent„o o caminho para o arquivo:\n");
                printf("\n\\:\t");
                fgets(buffer, 39, stdin);
                removeCR(buffer);
                fflush(stdin);
                dataFile = fopen(buffer, "r");
                if (dataFile == NULL)
                {
                    printf("\n\tArquivo nao encontrado\n");
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
                        sscanf(linha, "%d %38[^\n] %d %23[^\n] %f", &dado.matricula, dado.nome, &dado.idade, dado.cargo, &dado.salario);
                        arv_Inserir(A, dado);
                    }
                    printf("\n\t%d dados escaneados\n", i);
                    i = 0;
                }
                    fclose(dataFile);

                break;


            case 2:
                if (!arv_Vazia(A))
                {
                printf("\n\tDigite a matrÌcula do funcionario que deseja alterar:\n");
                fflush(stdin);
                buscaMatricula = setMatricula();
                editaArv(A, buscaMatricula);
                }
                else
                {
                    printf("\n\t¡rvore vazia\n");
                }
                break;


            case 3:
                printf("\n\tdigite as informaÁıes de quem deseja adicionar:\n");
                printf("\n\tN∫ de matrÌcula:\n");
                dado.matricula = setMatricula();

                printf("\n\tNome\n");
                setNome(dado.nome);

                printf("\n\tIdade de %-38s\n", dado.nome);
                dado.idade = setIdade();

                printf("\n\tCargo de %-38s\n", dado.nome);
                setCargo(dado.cargo);

                printf("\n\tSal·rio de %-38s\n", dado.nome);
                dado.salario = setSalario();

                arv_Inserir(A, dado);
                n++;
                break;


            case 4:
                if (arv_Vazia(A))
                {
                    printf("\n\t¡rvore vazia\n");
                }
                else
                {
                    printf("\n\tDigite a matrÌcula do usuario que deseja remover:\n");
                    printf("\n\\:\t");
                    scanf("%d", &buscaMatricula);
                    arv_Remover(A, buscaMatricula);
                    n--;
                }
                break;


            case 5:
                if (!arv_Vazia(A))
                {
                printf("\n\tDigite a matrÌcula que deseja buscar:\n");
                printf("\n\\:\t");
                scanf("%d", &buscaMatricula);
                busca = buscaArv(A->raiz, buscaMatricula);
                if (busca != NULL)
                {
                    printf("\n\tMatrÌcula | Nome\t\t\t\t  | Idade  | Cargo\t\t     | Sal·rio\n");
                    printf("\t----------------------------------------------------------------------------------------------\n");
                    imprimeInfo(busca);
                }
                }
                else
                {
                    printf("\n\t¡rvore vazia\n");
                }
                break;


            case 6:
                if (!arv_Vazia(A))
                {
                printf("\n\tMatrÌcula | Nome\t\t\t\t  | Idade  | Cargo\t\t     | Sal·rio\n");
                printf("\t----------------------------------------------------------------------------------------------\n");
                arv_MaiorMenorIdade(A, &maior, &menor);
                imprimeInfo(maior);
                imprimeInfo(menor);
                }
                else
                {
                    printf("\n\t¡rvore vazia\n");
                }
                break;
            case 7:
                if (!arv_Vazia(A))
                {
                    do
                    {
                        select = -1;
                        printf("\n\tQue cargo deseja filtrar?\n");
                        printf("\n\t1 - ANALISTA DE SISTEMAS\n");
                        printf("\n\t2 - ANALISTA DE SUPORTE\n");
                        printf("\n\t3 - PROGRAMADOR\n");
                        printf("\n\t4 - CONTADOR\n");
                        printf("\n\t5 - ADMINISTRATIVO\n");
                        printf("\n\t6 - GERENTE\n");
                        printf("\n\\:\t");
                        fflush(stdin);
                        scanf("%d", &select);
                        switch(select)
                        {
                            case 1:
                                printf("\n\tMatrÌcula | Nome\t\t\t\t  | Idade  | Cargo\t\t     | Sal·rio\n");
                                printf("\t----------------------------------------------------------------------------------------------\n");
                                arv_FiltrarCargo(A->raiz, "ANALISTA DE SISTEMAS");
                                break;
                            case 2:
                                printf("\n\tMatrÌcula | Nome\t\t\t\t  | Idade  | Cargo\t\t     | Sal·rio\n");
                                printf("\t----------------------------------------------------------------------------------------------\n");
                                arv_FiltrarCargo(A->raiz, "ANALISTA DE SUPORTE");
                                break;
                            case 3:
                                printf("\n\tMatrÌcula | Nome\t\t\t\t  | Idade  | Cargo\t\t     | Sal·rio\n");
                                printf("\t----------------------------------------------------------------------------------------------\n");
                                arv_FiltrarCargo(A->raiz, "PROGRAMADOR");
                                break;
                            case 4:
                                printf("\n\tMatrÌcula | Nome\t\t\t\t  | Idade  | Cargo\t\t     | Sal·rio\n");
                                printf("\t----------------------------------------------------------------------------------------------\n");
                                arv_FiltrarCargo(A->raiz, "CONTADOR");
                                break;
                            case 5:
                                printf("\n\tMatrÌcula | Nome\t\t\t\t  | Idade  | Cargo\t\t     | Sal·rio\n");
                                printf("\t----------------------------------------------------------------------------------------------\n");
                                arv_FiltrarCargo(A->raiz, "ADMINISTRATIVO");
                                break;
                            case 6:
                                printf("\n\tMatrÌcula | Nome\t\t\t\t  | Idade  | Cargo\t\t     | Sal·rio\n");
                                printf("\t----------------------------------------------------------------------------------------------\n");
                                arv_FiltrarCargo(A->raiz, "GERENTE");
                                break;
                            default:
                                printf("\n\tErro\n");
                                break;
                        }
                    } while (select < 1 || select > 6);
                }
                else
                {
                    printf("\n\t¡rvore vazia\n");
                }

                break;


            case 8:
                if (arv_Vazia(A))
                {
                    printf("\n\t¡rvore vazia\n");
                }
                else
                {
                    do
                    {
                        select = -1;
                        printf("\n\tSelecione o modo de impress„o:\n");
                        printf("\n\t1 - PrÈ-Order");
                        printf("\n\t2 - In-Order");
                        printf("\n\t3 - PÛs-Order\n");
                        printf("\n\\:\t");
                        fflush(stdin);
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
                        default:
                            printf("\n\tErro\n");
                            break;
                        }
                    } while (select < 1 || select > 6);
                }
                break;


            case 0:
                break;
            default:
                printf("\n\tErro\n");
                break;
            }
    } while (select != 0);
    arv_Liberar(A, n);
    return 0;
}
