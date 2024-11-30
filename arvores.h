#ifndef ARVORES_H_INCLUDED
#define ARVORES_H_INCLUDED

 typedef struct Info
 {
     int matricula;
     char nome[41];
     int idade;
     char cargo[26];
     float salario;
 }Info;

 typedef struct NoArvore
 {
     struct Info dado;
     struct NoArvore *esq;
     struct NoArvore *dir;
 }NoArv;


 typedef struct Arvore
 {
     NoArv *raiz;
 }Arv;

 /*
 arv_Criar() ok
 arv_Vazia() ok
 arv_Inserir() ok
 insereAux() ok
 arv_Remover() ok
 removeAux() ok
 arv_Liberar()
 */

 Arv* arv_Criar()
 {
        Arv *aux;
        aux = (Arv*)malloc(sizeof(Arv));
        aux->raiz = NULL;
        return aux;
 }

 void removeCR(char charVet[])
 {
     charVet[strcspn(charVet, "\r\n")] = 0;
 }

 int arv_Vazia(Arv* A)
 {
     if (A->raiz == NULL)
     {
         //printf("\narvore vazia!\n");
         return 1;
     }
     //printf("\narvore ocupada!\n");
     return 0;
 }

 NoArv* insereAux(NoArv *no, Info info)
 {
     int end_flag;
     NoArv *pai;
     NoArv *novo = (NoArv*)malloc(sizeof(NoArv));

     novo->dado.matricula = info.matricula;
     strcpy(novo->dado.nome, info.nome);
     novo->dado.idade = info.idade;
     strcpy(novo->dado.cargo, info.cargo);
     novo->dado.salario = info.salario;

     novo->esq = NULL;
     novo->dir = NULL;
     if (no == NULL)
     {
         return novo;
     }
     else
     {
         pai = no;
         end_flag = 0;
         while (end_flag != 1)
         {
             if (info.matricula > pai->dado.matricula)
             {
                 if (pai->dir != NULL)
                 {
                     pai = pai->dir;
                 }
                 else
                 {
                     pai->dir = novo;
                     end_flag = 1;
                 }
             }
             else if(info.matricula < pai->dado.matricula)
             {
                 if (pai->esq != NULL)
                 {
                     pai = pai->esq;
                 }
                 else
                 {
                     pai->esq = novo;
                     end_flag = 1;
                 }
             }
             else
             {
                 printf("matricula ja existente detectada, ignorando...\n");
                 end_flag = 1;
             }
         }
     }
     return no;
 }

 void arv_Inserir(Arv *A, Info info)
 {
     A->raiz = insereAux(A->raiz, info);
 }

 NoArv* removeAux(NoArv *pai, int matricula)
 {
     if (pai == NULL)
     {
         printf("\nnao existe matricula %d na arvore!\n", matricula);
     }
     else
     {
        if (matricula > pai->dado.matricula)
        {
            pai->dir = removeAux(pai->dir, matricula);
        }
        else
        {
            if (matricula < pai->dado.matricula)
            {
                pai->esq = removeAux(pai->esq, matricula);
            }
            else
            {
                if (pai->dir == NULL && pai->esq == NULL)
                {
                     free(pai);
                     pai = NULL; //por que?
                }
                else
                {
                    if (pai->esq == NULL)
                    {
                        NoArv *aux = pai;
                        pai = pai->dir;
                        free(aux);
                    }
                    else
                    {
                        if (pai->dir == NULL)
                        {
                            NoArv *aux = pai;
                            pai = pai->esq;
                            free(aux);
                        }
                        else
                        {
                            NoArv *aux;
                            aux = pai->esq;
                            while (aux->dir != NULL)
                            {
                                aux = aux->dir;
                            }
                            pai->dado.matricula = aux->dado.matricula;
                            aux->dado.matricula = matricula;
                            pai->esq = removeAux(pai->esq, matricula);
                        }
                    }
                }
            }
        }
    }
    return pai;
 }

 int setMatricula()
 {
     int matricula;
     do
        {
            printf("\n\tMatrícula:\n");
            printf("\\:\t");
            matricula = -1;
            fflush(stdin);
            if (scanf("%d", &matricula) != 1) {
                printf("\n\tErro\n\n");
            }
        } while (matricula <= 0 || matricula > 9999); //printar em formato 0000

     return matricula;
 }

 void setNome(char *nome)
 {
     char buffer[40];
     printf("\n\tNome:\n");
     printf("\\:\t");
     fflush(stdin);
     fgets(buffer, 38, stdin); //hmmm
     removeCR(buffer);
     strcpy(nome, buffer);
 }

 int setIdade()
 {
     int idade;
     do
        {
            printf("\n\tIdade:\n");
            printf("\\:\t");
            idade = -1;
            fflush(stdin);
            if (scanf("%d", &idade) != 1) {
                printf("\n\tErro\n\n");
            }
        } while (idade <= 0);

     return idade;
 }

 void setCargo(char *cargo, char nome[])
 {
     int select;
     do
        {
            select = -1;
            printf("\n\tDefina o cargo de %-40s\n", nome);
            printf("\t1 - ANALISTA DE SISTEMAS\n");
            printf("\t2 - ANALISTA DE SUPORTE\n");
            printf("\t3 - PROGRAMADOR\n");
            printf("\t4 - CONTADOR\n");
            printf("\t5 - ADMINISTRATIVO\n");
            printf("\t6 - GERENTE\n\n");
            printf("\\:\t");
            fflush(stdin);
            scanf("%d", &select);
            switch(select)
            {
                case 1:
                    strcpy(cargo, "ANALISTA DE SISTEMAS");
                    break;
                case 2:
                    strcpy(cargo, "ANALISTA DE SUPORTE");
                    break;
                case 3:
                    strcpy(cargo, "PROGRAMADOR");
                    break;
                case 4:
                    strcpy(cargo, "CONTADOR");
                    break;
                case 5:
                    strcpy(cargo, "ADMINISTRATIVO");
                    break;
                case 6:
                    strcpy(cargo, "GERENTE");
                    break;
                default:
                    printf("erro\n");
                    break;
            }
        } while (select < 1 || select > 6);
 }

 float setSalario()
 {
     float salario;
     do
        {
            printf("\n\tSalário:\n");
            printf("\\:\t");
            salario = -1;
            fflush(stdin);
            if (scanf("%f", &salario) != 1) {
                printf("erro\n");
            }
        } while(salario <= 0);
     return salario;
 }

 Arv* arv_Remover(Arv *A, int matricula)
 {
     NoArv *aux = A->raiz;
     if (aux->dado.matricula == matricula && (aux->dir == NULL && aux ->esq == NULL))
     {
         free(aux);
         //free(A);
         A->raiz=NULL;
         return A;
     }
     A->raiz = removeAux(A->raiz, matricula);
     return A;
 }



 NoArv* buscaArv(NoArv* pai, int matricula) {
     if (pai == NULL) {
         printf("\nNao existe matricula %d na arvore!\n", matricula);
         return NULL;
     }

     if (matricula > pai->dado.matricula)
     {
         return buscaArv(pai->dir, matricula);
     }
     else
     {
        if (matricula < pai->dado.matricula)
        {
            return buscaArv(pai->esq, matricula);
        }
        else
        {
             return pai;
        }
    }
 }

 NoArv* editaBuscaArv(NoArv* pai, int matricula) {
     if (pai == NULL) {
         printf("\nNao existe matricula %d na arvore!\n", matricula);
         return NULL;
     }
    printf("editabusca\n");
     if (matricula > pai->dado.matricula)
     {
         printf("dir\n");
         return editaBuscaArv(pai->dir, matricula);
     }
     else
     {
        if (matricula < pai->dado.matricula)
        {
            printf("esq\n");
            return editaBuscaArv(pai->esq, matricula);
        }
        else
        {
            printf("achou\n");
             int select;
        do
        {
            select = -1;
            printf("\n\to que deseja editar?\n");
            printf("\t1 - Nome\n");
            printf("\t2 - Idade\n");
            printf("\t3 - Cargo\n");
            printf("\t4 - Salario\n");
            fflush(stdin);
            scanf("%d", &select);

            switch(select)
            {
                case 1:
                    setNome(pai->dado.nome);
                    break;
                case 2:
                    pai->dado.idade = setIdade();
                    break;
                case 3:
                    setCargo(pai->dado.cargo, pai->dado.nome);
                    break;
                case 4:
                    pai->dado.salario = setSalario();
                    break;
                default:
                    printf("\n\tErro\n");
                    break;
            }
        } while (select <1 || select > 4);
        return pai;
        }
    }
 }



 void editaArv(Arv* pai, int matricula)
 {
    if (pai != NULL)
    {
        printf("editaarv\n");
        editaBuscaArv(pai->raiz, matricula);
    }
    else
    {
        //arvore vazia
    }

 }


void imprimeInfo(NoArv* pai)
{
    printf("\nMatricula: %04d", pai -> dado.matricula);
    printf("\nNome: %-38s", pai -> dado.nome);
    printf("\nIdade: %d", pai -> dado.idade);
    printf("\nCargo: %-23s", pai -> dado.cargo);
    printf("\nSalario: R$%.2f", pai -> dado.salario);
}

 void ImprimeAuxPre(NoArv* nA)
 {
    if (nA != NULL)
     {
        printf("%04d  %-38s  %d  %-23s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
        ImprimeAuxPre(nA->dir);
        ImprimeAuxPre(nA->esq);
     }
 }

 void ImprimeAuxIn(NoArv* nA)
 {
    if (nA != NULL)
     {
        ImprimeAuxIn(nA->dir);
        printf("%04d  %-38s  %d  %-23s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
        ImprimeAuxIn(nA->esq);
     }
 }

 void ImprimeAuxPos(NoArv* nA)
 {
    if (nA != NULL)
     {
        ImprimeAuxPos(nA->dir);
        ImprimeAuxPos(nA->esq);
        printf("%04d  %-38s  %d  %-23s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
     }
 }

 void ImprimeArv(Arv *A, int type)
 {
     if (!arv_Vazia(A))
     {
         NoArv *nA = A->raiz;
         printf("Matricula Nome\t\t\tIdade\tcargo\t\tsalario\n");
         switch(type)
         {
         case 1: //pre

             printf("%04d  %-38s  %d  %-23s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
             ImprimeAuxPre(nA->dir);
             ImprimeAuxPre(nA->esq);
             break;
         case 2: //in
             ImprimeAuxIn(nA->dir);
             printf("%04d  %-38s  %d  %-23s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
             ImprimeAuxIn(nA->esq);
             break;
         case 3: //pos
             ImprimeAuxPos(nA->dir);
             ImprimeAuxPos(nA->esq);
             printf("%04d  %-38s  %d  %-23s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
             break;
         default:
             break;
         }
     }
 }

 NoArv* maiorMenorAux(NoArv *A, NoArv** maior, NoArv** menor)
 {
     if (A != NULL)
     {
         if (A->dado.idade > (*maior)->dado.idade)
         {
             *maior = A;
         }
         else if (A->dado.idade < (*menor)->dado.idade)
         {
             *menor = A;
         }
         maiorMenorAux(A->dir, maior, menor);
         maiorMenorAux(A->esq, maior, menor);
     }

 }

 void arv_MaiorMenorIdade(Arv *A, NoArv** maior, NoArv** menor)
 {
     if (!arv_Vazia(A))
     {
         *maior = A->raiz;
         *menor = A->raiz;
         maiorMenorAux(A->raiz->dir, maior, menor);
         maiorMenorAux(A->raiz->esq, maior, menor);
     }
 }

 void arv_FiltrarCargo(NoArv* A, char cargo[])
 {
     if (A != NULL)
     {
         if (strncmp(cargo, A->dado.cargo, strlen(cargo)) == 0)
         {
             printf("func");
             imprimeInfo(A);
             printf("\n");
         }
         arv_FiltrarCargo(A->dir, cargo);
         arv_FiltrarCargo(A->esq, cargo);
     }
 }

 NoArv* liberaAux(NoArv* nA, FILE* dataFile)
 {
    if (nA != NULL)
     {
         liberaAux(nA->dir, dataFile);
         liberaAux(nA->esq, dataFile);
         fprintf(dataFile, "%04d %-38s %d %-23s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
         free(nA);
         printf("no liberado\n");
     }
     return NULL;
 }

 Arv* arv_Liberar(Arv *A, int n)
 {
     if (!arv_Vazia(A))
     {
         FILE* dataFile = fopen("DadosSalvos.txt", "w");
         if (dataFile == NULL)
         {
             printf("\n\terro de salvamento\n");
         }
         else
         {
            fprintf(dataFile, "%d\n", n);
            A->raiz = liberaAux(A->raiz, dataFile);
            printf("tudo liberado\n");
            fclose(dataFile);
         }
     return A;
     }
 }

#endif // ARVORES_H_INCLUDED
