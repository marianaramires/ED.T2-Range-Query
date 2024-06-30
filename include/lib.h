#ifndef __LIB__
#define __LIB__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct _municipio
{
    char codigo_ibge[10];
    char nome[40];
    float latitude;
    float longitude;
    int capital;
    int codigo_uf;
    int siafi_id;
    int ddd;
    char fuso_horario[40];
} tmunicipio;

/* HASH */
typedef struct
{
    uintptr_t *table;
    int size;
    int max;
    char *(*get_key)(void *);
    uintptr_t deleted;
} thash;

char *get_cod(void *reg);
char *get_nome(void *reg);
void *aloca_municipio(char *codigo_ibge, char *nome, float latitude, float longitude,
int capital, int codigo_uf, int siafi_id, int ddd, char *fuso_horario);
uint32_t hashf(const char *str, uint32_t h);
uint32_t hash_duplo(uint32_t h, int max, int i);
int hash_insere(thash *h, void *bucket);
int hash_constroi(thash *h, int nbuckets, char *(*get_key)(void *));
void municipio_printa(tmunicipio municipio);
void *hash_busca(thash h, const char *key);
void *hash_busca_nome(thash h, const char *key, int *cont);

/* LISTA ENCADEADA */
typedef struct _tlista{
    void *reg;
    struct _tlista *prox;
}tlista;

void lst_insere(tlista **cabeca, void *reg);
void lst_imprime(tlista * lista, thash h);
tlista *lst_interseccao(tlista *lista1, tlista *lista2);

/* AVL */

typedef struct _node{
    tlista *lista;
    struct _node *pai;
    struct _node *esq;
    struct _node *dir;
    int h;
}tnode;

typedef struct _tarv{
    tnode *raiz;
    double (*cmp)(void * , void *);
} tarv;

void avl_constroi(tarv *parv, double (*cmp)(void *, void *));
void avl_insere(tarv *parv, tnode ** ppnode, tnode *pai, void *reg);
tnode ** avl_sucessor(tnode **ppnode);
tnode * avl_busca(tarv *parv, tnode **ppnode, void *busca);
tlista * range_query(tarv *parv, tnode **ppnode, void *busca1, void *busca2);
void avl_destroi(tnode * parv);

void _rd(tnode ** pparv);
void _re(tnode ** pparv);
void _avl_rebalancear(tnode ** pparv);

/* JSON */
char *trata(char *string);
void trata_aspas(char *string, char *sem_aspas);

#endif