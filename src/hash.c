#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../include/lib.h"
#define SEED 0x12345678

char *get_cod(void *reg)
{
    return (*((tmunicipio *)reg)).codigo_ibge;
}

char *get_nome(void *reg)
{
    return (*((tmunicipio *)reg)).nome;
}

void *aloca_municipio(char *codigo_ibge, char *nome, float latitude, float longitude,
                      int capital, int codigo_uf, int siafi_id, int ddd, char *fuso_horario)
{
    tmunicipio *municipio = malloc(sizeof(tmunicipio));
    strcpy(municipio->codigo_ibge, codigo_ibge);
    strcpy(municipio->nome, nome);
    municipio->latitude = latitude;
    municipio->longitude = longitude;
    municipio->capital = capital;
    municipio->codigo_uf = codigo_uf;
    municipio->siafi_id = siafi_id;
    municipio->ddd = ddd;
    strcpy(municipio->fuso_horario, fuso_horario);

    return municipio;
}

uint32_t hashf(const char *str, uint32_t h)
{
    /* One-byte-at-a-time Murmur hash
    Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp */
    for (; *str; ++str)
    {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}

uint32_t hash_duplo(uint32_t h, int max, int i)
{
    int hash = h + (i * ((h % (max - 1)) + 1));
    return abs(hash % max);
}

int hash_insere(thash *h, void *bucket)
{
    uint32_t hash = hashf(h->get_key(bucket), SEED);
    int pos = hash % (h->max);
    int i = 0;
    // verifica se a tabela esta cheia
    if (h->max == (h->size + 1))
    {
        free(bucket);
        return EXIT_FAILURE;
    }
    else
    { // faz a insercao
        while (h->table[pos] != 0)
        {
            i++;
            if (h->table[pos] == h->deleted)
                break;
            pos = hash_duplo(hash, h->max, i);
        }
        h->table[pos] = (uintptr_t)bucket;
        h->size += 1;
    }
    return EXIT_SUCCESS;
}

int hash_constroi(thash *h, int nbuckets, char *(*get_key)(void *))
{
    h->table = calloc(sizeof(void *), nbuckets);
    if (h->table == NULL)
    {
        return EXIT_FAILURE;
    }
    h->max = nbuckets;
    h->size = 0;
    h->get_key = get_key;
    h->deleted = (uintptr_t) & (h->size);
    return EXIT_SUCCESS;
}

void municipio_printa(tmunicipio municipio)
{
    printf("%-12s | %-30s | %-10s | %-10s | %-6s | %-3s | %-5s | %-3s | %-3s\n",
           "Codigo IBGE", "Nome", "Latitude", "Longitude",
           "Capital", "Codigo UF", "ID SIAFI", "DDD", "Fuso Horario");

    printf("%-12s | %-30s | %-10f | %-10f | %-6d | %-3d | %-5d | %-3d | %-3s\n",
           municipio.codigo_ibge, municipio.nome, municipio.latitude,
           municipio.longitude, municipio.capital, municipio.codigo_uf,
           municipio.siafi_id, municipio.ddd, municipio.fuso_horario);
}

void *hash_busca(thash h, const char *key)
{
    uint32_t hash = hashf(key, SEED);
    int pos = hash % (h.max);
    int i = 0;
    void *ret = NULL;
    while (h.table[pos] != 0 && ret == NULL)
    {
        if (strcmp(h.get_key((void *)h.table[pos]), key) == 0)
        {
            ret = (void *)h.table[pos];
        }
        i++;
        pos = hash_duplo(hash, h.max, i);
    }
    return ret;
}

void *hash_busca_nome(thash h, const char *key, int *cont)
{
    uint32_t hash = hashf(key, SEED);
    int pos = hash % (h.max);
    int i = 0;
    void *ret = NULL;
    while (h.table[pos] != 0)
    {
        if (strcmp(h.get_key((void *)h.table[pos]), key) == 0)
        {
            (*cont)++;
            municipio_printa(*(tmunicipio *)h.table[pos]);
            ret = (void *)h.table[pos];
        }
        i++;
        pos = hash_duplo(hash, h.max, i);
    }
    return ret;
}