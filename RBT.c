#include <stdio.h> 
#include <stdlib.h> 
#define MAX 20

typedef struct tnode{ 
    int chave; 
    int c; 
    struct tnode* anterior; 
    struct tnode* dir; 
    struct tnode* esq; 
} node; 

node* raiz = NULL; 

node* insereRN( node* raiz, node* aux) 
{ 
    if (raiz == NULL) 
        return aux;   
    if (aux->chave < raiz->chave){ 
        raiz->esq = insereRN(raiz->esq, aux); 
        raiz->esq->anterior = raiz; 
    } 
    else if (aux->chave > raiz->chave)  { 
        raiz->dir = insereRN(raiz->dir, aux); 
        raiz->dir->anterior = raiz; 
    } 
    return raiz; 
} 

void imprime( node *raiz) {
  if(raiz!=NULL) {
    printf("%d%c ",raiz->chave,raiz->c ? 'R' : 'N');
    imprime(raiz->esq);
    imprime(raiz->dir);
  }
} 
void rotadireita(node* aux) 
{ 
    printf("rotadireita");
    node* esquerda = aux->esq; 
    aux->esq = esquerda->dir; 
    if (aux->esq!=NULL) 
        aux->esq->anterior = aux; 
    esquerda->anterior = aux->anterior; 
    if (aux->anterior==NULL) 
        raiz = esquerda; 
    else if (aux==aux->anterior->esq) 
        aux->anterior->esq = esquerda; 
    else aux->anterior->dir = esquerda; 
    esquerda->dir = aux; 
    aux->anterior = esquerda; 
} 

void rotaesquerda(node* aux) 
{ 
    node* direita = aux->dir; 
    aux->dir = direita->esq; 
    if (aux->dir!=NULL) 
        aux->dir->anterior = aux; 
    direita->anterior = aux->anterior; 
    
    if (aux->anterior==NULL) 
        raiz = direita; 
    else if (aux == aux->anterior->esq) 
        aux->anterior->esq = direita; 
    else aux->anterior->dir = direita; 
    direita->esq = aux; 
    aux->anterior = direita;
}

void conserta( node* pt) 
{ 
    while ((pt != raiz) && (pt->c != 0) && (pt->anterior->c == 1))  { 
        node* anterior_pt = pt->anterior; 
        node* avo_pt = pt->anterior->anterior; 
        if (anterior_pt == avo_pt->esq){ 
            node* tio_pt = avo_pt->dir; 
            if (tio_pt != NULL && tio_pt->c == 1){ 
                avo_pt->c = 1; 
                anterior_pt->c = 0; 
                tio_pt->c = 0; 
                pt = avo_pt; 
            } 
            else{ 
                if (pt == anterior_pt->dir) { 
                    rotaesquerda(anterior_pt); 
                    pt = anterior_pt; 
                    anterior_pt = pt->anterior; 
                } 
                rotadireita(avo_pt); 
                int cor = anterior_pt->c; 
                anterior_pt->c = avo_pt->c; 
                avo_pt->c = cor; 
                pt  = anterior_pt; 
            } 
        } 

        else { 
            node* tio_pt = avo_pt->esq; 
            if ((tio_pt != NULL) && (tio_pt->c == 1)){ 
                    avo_pt->c = 1; 
                    anterior_pt->c = 0; 
                    tio_pt->c = 0; 
                    pt = avo_pt; 
                } 
            else { 
                if (pt == anterior_pt->esq) { 
                    rotadireita(anterior_pt); 
                    pt = anterior_pt; 
                    anterior_pt = pt->anterior; 
                } 
                rotaesquerda(avo_pt);  
                int cor = anterior_pt->c; 
                anterior_pt->c = avo_pt->c; 
                avo_pt->c = cor; 
                pt = anterior_pt;
            } 
        } 
    }raiz->c = 0; 
} 


int main() 
{  
    char entrada[MAX];
    int atual;
    int anterior;
    while(1){
        fgets(entrada, MAX ,stdin);
        atual = atoi(entrada); 
        if(atual == anterior){
            raiz->c = 1;
            if(raiz->dir&&raiz->dir->c==1)
            raiz->c = 0;
            if(raiz->esq&&raiz->esq->c==1)
            raiz->c = 0;
            break;  
        }
        node* aux = ( node*)malloc(sizeof( node));   
        aux->dir = NULL; 
        aux->esq = NULL; 
        aux->anterior = NULL; 
        aux->chave = atual; 
        aux->c = 1; 
        raiz = insereRN(raiz, aux);
        conserta(aux);
        anterior = atual;
    } 
    imprime(raiz); 
    return 0; 
}