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
     if (A->raiz == NULL || A == NULL)
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

 NoArv* removeAux(NoArv *pai, Info info)
 {
     if (pai == NULL)
     {
         printf("\nnao existe matricula %d na arvore!\n", info.matricula);
     }
     else
     {
        if (info.matricula > pai->dado.matricula)
        {
            pai->dir = removeAux(pai->dir, info);
        }
        else
        {
            if (info.matricula < pai->dado.matricula)
            {
                pai->esq = removeAux(pai->esq, info);
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
                            aux->dado.matricula = info.matricula;
                            pai->esq = removeAux(pai->esq, info);
                        }
                    }
                }
            }
        }
    }
    return pai;
 }



 Arv* removeArv(Arv *A, Info info)
 {
     NoArv *aux = A->raiz;
     if (aux->dado.matricula == info.matricula && (aux->dir == NULL && aux ->esq == NULL))
     {
         free(aux);
         //free(A);
         A->raiz=NULL;
         return A;
     }
     A->raiz = removeAux(A->raiz, info);
     return A;
 }

 void ImprimeAux(NoArv* nA)
 {
    if (nA != NULL)
     {
         printf("%d  %s  %d  %s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
         ImprimeAux(nA->dir);
         ImprimeAux(nA->esq);
     }
 }

 void ImprimeArv(Arv *A)
 {
     if (!vaziaArv(A))
     {
         NoArv *nA = A->raiz;
         printf("%d  %s  %d  %s %.2f\n", nA->dado.matricula, nA->dado.nome, nA->dado.idade, nA->dado.cargo, nA->dado.salario);
         ImprimeAux(nA->dir);
         ImprimeAux(nA->esq);
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
