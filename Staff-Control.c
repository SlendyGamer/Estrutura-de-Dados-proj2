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
    FILE *dataFile, *mainFile, *newFile;
    char linha[90], buffer[40];
    Info dado;
    NoArv *busca, *maior, *menor;
    Arv *A = arv_Criar();
    if (A == NULL)
    {
        printf("\terro de alocação\n");
        exit(2);
    }

    mainFile = fopen("DadosSalvos.txt", "r+"); //a tem espaï¿½o entre +??
    if (mainFile == NULL)
    {
        printf("\n\tdados salvos não encontrados, inicializando nova árvore vazia!\n");
    }
    else
    {

        dataFile = fopen("DadosSalvos.txt", "r");
                if (dataFile == NULL)
                {
                    printf("\n\tarquivo nao encontrado\n");
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
                        //printf("%d escaneado: %d  %s  %d  %s %.2f\n", i, dado.matricula, dado.nome, dado.idade, dado.cargo, dado.salario); //sucesso
                        //fprintf(newFile, "%d %s %d %s %.2f\n", int1, string1, int2, string2, float1);
                    }
                    printf("\n\t%d dados escaneados\n", i);
                    i = 0;
                    fclose(dataFile);
                }

    }

    do
    {
        printf("\n\tStaff Control v.1.0:\n\n"
                 "\tO que deseja?\n\n"
                 "\t1:\tCarregar novos dados de um arquivo no sistema;\n"
                 "\t2:\tAtualizar dado do sistema;\n"
                 "\t3:\tIncluir novo dado no sistema;\n"
                 "\t4:\tRemover dado do sistema;\n"
                 "\t5:\tBuscar por dado no sistema;\n"
                 "\t6:\tAchar funcionário mais novo e mais velho;\n"
                 "\t7:\tVisualisar dados registrados no sistema;\n\n"
                 "\t0:\tSalvar e sair do programa.\n\n");
                 printf("\\:\t");
        select = -1;
        scanf("%d", &select);
        fflush(stdin);
        //limpar tela
        switch(select)
        {
            case 1:
                printf("\n\tdigite o nome do arquivo(se estiver na mesma pasta) ou então o caminho para o arquivo:\n");
                printf("\\:\t");
                fgets(buffer, 39, stdin);
                removeCR(buffer);
                fflush(stdin);
                dataFile = fopen(buffer, "r");
                if (dataFile == NULL)
                {
                    printf("\n\tarquivo nao encontrado\n");
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
                        //printf("%d escaneado: %d  %s  %d  %s %.2f\n", i, dado.matricula, dado.nome, dado.idade, dado.cargo, dado.salario); //sucesso
                        //fprintf(newFile, "%d %s %d %s %.2f\n", int1, string1, int2, string2, float1);
                    }
                    printf("\n\t%d dados escaneados\n", i);
                    i = 0;
                }
                    fclose(dataFile);

                break;


            case 2:
                printf("\n\tDigite a matrícula do funcionario que deseja alterar:\n");
                printf("\\:\t");
                fflush(stdin);
                buscaMatricula = setMatricula();
                printf("\n%d\n", buscaMatricula);
                editaArv(A, buscaMatricula);
                break;


            case 3:
                printf("\n\tdigite as informações de quem deseja adicionar:\n");

                dado.matricula = setMatricula();
                setNome(dado.nome);
                dado.idade = setIdade();
                setCargo(dado.cargo, dado.nome);
                dado.salario = setSalario();

                arv_Inserir(A, dado);
                n++;
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
                    n--;
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
                if (!arv_Vazia(A))
                {
                arv_MaiorMenorIdade(A, &maior, &menor);
                imprimeInfo(maior);
                imprimeInfo(menor);
                }
                break;
            case 7:
                if (!arv_Vazia(A))
                {
                    do
                    {
                        select = -1;
                        printf("defina o cargo de %-40s\n", dado.nome);
                        printf("1 - ANALISTA DE SISTEMAS\n");
                        printf("2 - ANALISTA DE SUPORTE\n");
                        printf("3 - PROGRAMADOR\n");
                        printf("4 - CONTADOR\n");
                        printf("5 - ADMINISTRATIVO\n");
                        printf("6 - GERENTE\n");
                        fflush(stdin);
                        scanf("%d", &select);
                        switch(select)
                        {
                            case 1:
                                arv_FiltrarCargo(A->raiz, "ANALISTA DE SISTEMAS");
                                break;
                            case 2:
                                arv_FiltrarCargo(A->raiz, "ANALISTA DE SUPORTE");
                                break;
                            case 3:
                                arv_FiltrarCargo(A->raiz, "PROGRAMADOR");
                                break;
                            case 4:
                                arv_FiltrarCargo(A->raiz, "CONTADOR");
                                printf("teste");
                                break;
                            case 5:
                                arv_FiltrarCargo(A->raiz, "ADMINISTRATIVO");
                                break;
                            case 6:
                                arv_FiltrarCargo(A->raiz, "GERENTE");
                                break;
                            default:
                                printf("erro\n");
                                break;
                        }
                    } while (select < 1 || select > 6);
                }

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
    arv_Liberar(A, n);
    return 0;
}
