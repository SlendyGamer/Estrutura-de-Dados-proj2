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
 criaArv() ok
 vaziaArv() ok
 insereArv() ok
 insereAux() ok
 removeArv() ok
 removeAux() ok
 liberaArv()
 */

 Arv* criaArv()
 {
        Arv *aux;
        aux = (Arv*)malloc(sizeof(Arv));
        aux->raiz = NULL;
        return aux;
 }

 int vaziaArv(Arv* A)
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
         }
     }
     return no;
 }

 void insereArv(Arv *A, Info info)
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



 Arv* removeArv(Arv *A, int matricula)
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


void imprimeInfo(NoArv* pai)
{
    printf("\nMatricula: %d", pai -> dado.matricula);
    printf("\nNome: %-39s", pai -> dado.nome);
    printf("\nIdade: %d", pai -> dado.idade);
    printf("\nCargo: %-24s", pai -> dado.cargo);
    printf("\nSalario: %.2f", pai -> dado.salario);
}

 void ImprimeAuxPre(NoArv* nA)
 {
    if (nA != NULL)
     {
        printf("%d  %-39s  %d  %-24s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
        ImprimeAuxPre(nA->dir);
        ImprimeAuxPre(nA->esq);
     }
 }

 void ImprimeAuxIn(NoArv* nA)
 {
    if (nA != NULL)
     {
        ImprimeAuxIn(nA->dir);
        printf("%d  %-39s  %d  %-24s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
        ImprimeAuxIn(nA->esq);
     }
 }

 void ImprimeAuxPos(NoArv* nA)
 {
    if (nA != NULL)
     {
        ImprimeAuxPos(nA->dir);
        ImprimeAuxPos(nA->esq);
        printf("%d  %-39s  %d  %-24s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
     }
 }

 void ImprimeArv(Arv *A, int type) //mudar nome para pre order
 {
     if (!vaziaArv(A))
     {
         NoArv *nA = A->raiz;
         switch(type)
         {
         case 1: //pre

             printf("%d  %-39s  %d  %-24s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
             ImprimeAuxPre(nA->dir);
             ImprimeAuxPre(nA->esq);
             break;
         case 2: //in
             ImprimeAuxIn(nA->dir);
             printf("%d  %-39s  %d  %-24s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
             ImprimeAuxIn(nA->esq);
             break;
         case 3: //pos
             ImprimeAuxPos(nA->dir);
             ImprimeAuxPos(nA->esq);
             printf("%d  %-39s  %d  %-24s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
             break;
         default:
             break;
         }
     }
 }

 NoArv* liberaAux(NoArv* nA)
 {
    if (nA != NULL)
     {
         liberaAux(nA->dir);
         liberaAux(nA->esq);
         free(nA);
         printf("no liberado\n");
     }
     return NULL;
 }

 Arv* liberaArv(Arv *A)
 {
     if (!vaziaArv(A))
     {
         A->raiz = liberaAux(A->raiz);
         printf("tudo liberado\n");
     }
     return A;
 }

#endif // ARVORES_H_INCLUDED
