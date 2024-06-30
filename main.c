#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "include/lib.h"

double cmp_nome(void *a, void *b){
    return strcasecmp((*((tmunicipio *)a)).nome,(*((tmunicipio *)b)).nome);
}

double cmp_lat(void *a, void *b){
    return ((*((tmunicipio *)a)).latitude - (*((tmunicipio *)b)).latitude);
}

double cmp_long(void *a, void *b){
    return ((*((tmunicipio *)a)).longitude - (*((tmunicipio *)b)).longitude);
}

double cmp_cod(void *a, void *b){
    return ((*((tmunicipio *)a)).codigo_uf - (*((tmunicipio *)b)).codigo_uf);
}

double cmp_ddd(void *a, void *b){
    return ((*((tmunicipio *)a)).ddd - (*((tmunicipio *)b)).ddd);
}

int main()
{
    /* hash */
    thash h;
    hash_constroi(&h, 11003, get_cod);

    /* variaveis para manipulacao json */
    char c[500], sem_aspas[500], codigo_ibge[10], nome[40];
    float latitude, longitude;
    int capital, codigo_uf, siafi_id, ddd;
    char fuso_horario[40];
    FILE *arq;
    arq = fopen("municipios.json", "r");
    char busca[8];
    int condicao = -1;
    int vizinhos;

    /* avl */
    tarv arv_nome, arv_lat, arv_long, arv_cod, arv_ddd;
    avl_constroi(&arv_nome, cmp_nome);
    avl_constroi(&arv_lat, cmp_lat);
    avl_constroi(&arv_long, cmp_long);
    avl_constroi(&arv_cod, cmp_cod);
    avl_constroi(&arv_ddd, cmp_ddd);

    fgets(c, 100, arq); // lixo
    while (!feof(arq))
    {
        fgets(c, 100, arq); // lixo

        if (strchr(c, ']') != NULL)
            break;

        // codigo_ibge
        fgets(c, 500, arq);
        strcpy(codigo_ibge, trata(c));

        // nome
        fgets(c, 500, arq);
        trata_aspas(c, sem_aspas);
        strcpy(nome, sem_aspas);

        // latitude
        fgets(c, 500, arq);
        latitude = atof(trata(c));

        // longitude
        fgets(c, 500, arq);
        longitude = atof(trata(c));

        // capital
        fgets(c, 500, arq);
        capital = atoi(trata(c));

        // codigo_uf
        fgets(c, 500, arq);
        codigo_uf = atoi(trata(c));

        // siafi_id
        fgets(c, 500, arq);
        siafi_id = atoi(trata(c));

        // ddd
        fgets(c, 500, arq);
        ddd = atoi(trata(c));

        // fuso horario
        fgets(c, 500, arq);
        trata_aspas(c, sem_aspas);
        strcpy(fuso_horario, sem_aspas);

        fgets(c, 100, arq); // lixo

        hash_insere(&h, aloca_municipio(codigo_ibge, nome, latitude, longitude, capital,
                                        codigo_uf, siafi_id, ddd, fuso_horario));
        avl_insere(&arv_nome, &arv_nome.raiz, NULL, aloca_municipio(codigo_ibge, nome, 0, 0, 0,
                                        0, 0, 0, ""));
        avl_insere(&arv_lat, &arv_lat.raiz, NULL, aloca_municipio(codigo_ibge, "", latitude, 0, 0,
                                        0, 0, 0, ""));
        avl_insere(&arv_long, &arv_long.raiz, NULL, aloca_municipio(codigo_ibge, "", 0, longitude, 0,
                                        0, 0, 0, ""));
        avl_insere(&arv_cod, &arv_cod.raiz, NULL, aloca_municipio(codigo_ibge, "", 0, 0, 0,
                                        codigo_uf, 0, 0, ""));
        avl_insere(&arv_ddd, &arv_ddd.raiz, NULL, aloca_municipio(codigo_ibge, "", 0, 0, 0,
                                        0, 0, ddd, ""));
    }

    tmunicipio *search = hash_busca(h, "5002704");
    municipio_printa(*search);

    printf("RAIZ NOME\n");
    municipio_printa((*((tmunicipio *)arv_nome.raiz->lista->reg)));
    printf("RAIZ LAT\n");
    municipio_printa((*((tmunicipio *)arv_lat.raiz->lista->reg)));
    printf("RAIZ LONG\n");
    municipio_printa((*((tmunicipio *)arv_long.raiz->lista->reg)));
    printf("RAIZ COD\n");
    municipio_printa((*((tmunicipio *)arv_cod.raiz->lista->reg)));
    printf("RAIZ DDD\n");
    municipio_printa((*((tmunicipio *)arv_ddd.raiz->lista->reg)));

    fclose(arq);
    free(h.table);
    avl_destroi(arv_nome.raiz);
    avl_destroi(arv_lat.raiz);
    avl_destroi(arv_long.raiz);
    avl_destroi(arv_cod.raiz);
    avl_destroi(arv_ddd.raiz);
    return EXIT_SUCCESS;
}