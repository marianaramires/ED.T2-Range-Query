#include <stdio.h>
#include <stdlib.h>
#include "../include/lib.h"

void lst_insere(tlista **cabeca, void *reg)
{
    tlista *no;
    tlista *novono;

    /* lista vazia */
    if (*cabeca == NULL)
    {
        *cabeca = (tlista *)malloc(sizeof(tlista));
        (*cabeca)->reg = reg;
        (*cabeca)->prox = NULL;
    }
    else
    {
        /* percorre lista para inserir no final */
        no = *cabeca;
        while (no->prox != NULL){
            no = no->prox; 
        }

        novono = (tlista *)malloc(sizeof(tlista));
        novono->reg = reg;
        novono->prox = NULL;

        no->prox = novono;
    }
}