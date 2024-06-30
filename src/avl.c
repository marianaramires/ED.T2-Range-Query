#include<stdio.h>
#include<stdlib.h>
#include "../include/lib.h"

int max(int a,int b){
    return a>b?a:b;
}

int altura(tnode *arv){
    int ret;
    if (arv==NULL){
        ret = -1;
    }else{
        ret = arv->h;
    }
    return ret;
}

void avl_constroi(tarv *parv, double (*cmp)(void *, void *)){
    parv->raiz = NULL;
    parv->cmp = cmp;
}

void avl_insere(tarv *parv, tnode ** ppnode, tnode *pai, void *reg){
    if (*ppnode == NULL){
        *ppnode = (tnode *) malloc(sizeof(tnode));
        (*ppnode)->lista = NULL;
        lst_insere(&(*ppnode)->lista, reg);
        (*ppnode)->pai = pai;
        (*ppnode)->esq = NULL;
        (*ppnode)->dir = NULL;
        (*ppnode)->h = 0;

    }else if(parv->cmp((*ppnode)->lista->reg, reg) > 0){
        avl_insere(parv, &(*ppnode)->esq, *ppnode, reg);
    }else if(parv->cmp((*ppnode)->lista->reg, reg) < 0){
        avl_insere(parv, &(*ppnode)->dir, *ppnode, reg);
    } else{
        lst_insere(&(*ppnode)->lista, reg);
    }

    (*ppnode)->h = max(altura((*ppnode)->esq),altura((*ppnode)->dir)) + 1;
    _avl_rebalancear(ppnode);
}



void _rd(tnode **parv){
    tnode * y = *parv; 
    tnode * x = y->esq;
    tnode * A = x->esq;
    tnode * B = x->dir;
    tnode * C = y->dir;

    y->esq = B; 
    x->dir = y;
    *parv  = x;
    y->h = max(altura(B),altura(C)) + 1;
    x->h = max(altura(A),altura(y)) + 1;
}

void _re(tnode **parv){
    tnode * x = *parv; 
    tnode * y = x->dir;
    tnode * A = x->esq;
    tnode * B = y->esq;
    tnode * C = y->dir;

    x->dir = B;
    y->esq = x; 
    *parv  = y;
    x->h = max(altura(A),altura(B)) + 1;
    y->h = max(altura(x),altura(C)) + 1;
}

void _avl_rebalancear(tnode **parv){
    int fb;
    int fbf;
    tnode * filho;
    fb = altura((*parv)->esq) - altura((*parv)->dir);

    if (fb  == -2){
        filho = (*parv)->dir;
        fbf = altura(filho->esq) - altura(filho->dir);
        if (fbf <= 0){ /* Caso 1  --> ->*/
            _re(parv);
        }else{   /* Caso 2  --> <-*/
            _rd(&(*parv)->dir);
            _re(parv);
        }
    }else if (fb == 2){  
        filho = (*parv)->esq;
        fbf = altura(filho->esq) - altura(filho->dir);
        if (fbf >=0){ /* Caso 3  <-- <-*/
            _rd(parv);
        }else{  /* Caso 4  <-- ->*/
            _re(&(*parv)->esq);
            _rd(parv);
        }
    }
}

tnode ** percorre_esq(tnode ** arv){
    tnode * aux = *arv;
    if (aux->esq  == NULL){
        return arv;
    }else{
        while (aux->esq->esq != NULL)
            aux = aux->esq;
        return &(aux->esq);
    }
}

/* tree-sucessor do cormen */
tnode ** avl_sucessor(tnode **x){
    if((*x)->dir != NULL){
        return percorre_esq(&(*x)->dir);
    }

    tnode *y = (*x)->pai;
    while (y != NULL && *x == y->dir){
        *x = y;
        y = y->pai;
    }

    return &(*x)->pai;
}

void avl_destroi(tnode *parv){
    if (parv!=NULL){
        avl_destroi(parv->esq);
        avl_destroi(parv->dir);
        free(parv);
    }
}