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
        while (no->prox != NULL)
        {
            no = no->prox;
        }

        novono = (tlista *)malloc(sizeof(tlista));
        novono->reg = reg;
        novono->prox = NULL;

        no->prox = novono;
    }
}

tlista *lst_interseccao(tlista *lista1, tlista *lista2)
{
    tlista *resul = NULL;
    tlista *aux;

    if(lista1 == NULL){
        return lista2;
    }
    if (lista2 == NULL){
        return lista1;
    }

    while (lista1 != NULL)
    {
        aux = lista2;
        /* compara cada elemento da segunda lista com a primeira encontrada */
        while (aux != NULL)
        {
            /* se for interseccao, adiciona no resultado */
            if (strcmp((((tmunicipio *)lista1->reg)->codigo_ibge), (((tmunicipio *)aux->reg)->codigo_ibge)) == 0)
            {
                lst_insere(&resul, aux->reg);
            }
            aux = aux->prox;
        }

        lista1 = lista1->prox;
    }

    return resul;
}

void lst_imprime(tlista *lista, thash h)
{
    tlista *aux = lista;
    tmunicipio *resul;
    char busca[8];
    printf("%-12s | %-30s | %-10s | %-10s | %-6s | %-3s | %-5s | %-3s | %-3s\n",
           "Codigo IBGE", "Nome", "Latitude", "Longitude",
           "Capital", "Codigo UF", "ID SIAFI", "DDD", "Fuso Horario");

    while (aux->prox != NULL)
    {
        strcpy(busca, (((tmunicipio *)aux->reg)->codigo_ibge));
        resul = hash_busca(h, busca);
        municipio_printa(*resul);
        aux = aux->prox;
    }
    strcpy(busca, (((tmunicipio *)aux->reg)->codigo_ibge));
    resul = hash_busca(h, busca);
    municipio_printa(*resul);
}
