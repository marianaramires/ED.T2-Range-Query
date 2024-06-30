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

    /* avl */
    tarv arv_nome, arv_lat, arv_long, arv_cod, arv_ddd;
    avl_constroi(&arv_nome, cmp_nome);
    avl_constroi(&arv_lat, cmp_lat);
    avl_constroi(&arv_long, cmp_long);
    avl_constroi(&arv_cod, cmp_cod);
    avl_constroi(&arv_ddd, cmp_ddd);

    /* variaveis interface */
    int condicao = -1;
    char min_nome[50], max_nome[50];
    float min_lat, max_lat, min_long, max_long;
    int min_cod, max_cod, min_ddd, max_ddd;
    int flag[5];
    tlista *lstnome, *lstlat, *lstlong, *lstcod, *lstddd;

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

    while (condicao != 0)
    {
        printf("___________________________________________________________________________\n");
        printf("1 - Nova Consulta\n");
        printf("0 - Sair\n");
        scanf("%d", &condicao);

        switch (condicao)
        {
        case 1:
            printf("___________________________________________________________________________\n");
            printf("* Para buscar valores iguais, digite o mesmo valor duas vezes.\n");
            printf("Exemplo: Cidades com DDD == 67. Digite MIN: 67 e MAX: 67 *\n");

            printf("\nConsultar por NOME?\n");
            printf("1: Sim\n0: Não\n");
            scanf("%d", &flag[0]);
            if(flag[0] == 1){
                printf("MIN: ");
                scanf(" %[^\n]s", min_nome);
                printf("MAX: ");
                scanf(" %[^\n]s", max_nome);
                tmunicipio * bmin_nome = aloca_municipio("", min_nome, 0, 0, 0, 0, 0, 0, "");
                tmunicipio * bmax_nome = aloca_municipio("", max_nome, 0, 0, 0, 0, 0, 0, "");
                lstnome = range_query(&arv_nome, &arv_nome.raiz, bmin_nome, bmax_nome);
            } else{
                lstnome = NULL;
            }

            printf("\nConsultar por LATITUDE?\n");
            printf("1: Sim\n0: Não\n");
            scanf("%d", &flag[1]);
            if(flag[1] == 1){
                printf("MIN: ");
                scanf("%f", &min_lat);
                printf("MAX: ");
                scanf("%f", &max_lat);
            } else{
                lstlat = NULL;
            }

            printf("\nConsultar por LONGITUDE?\n");
            printf("1: Sim\n0: Não\n");
            scanf("%d", &flag[2]);
            if(flag[2] == 1){
                printf("MIN: ");
                scanf("%f", &min_long);
                printf("MAX: ");
                scanf("%f", &max_long);
            } else{
                lstlong = NULL;
            }

            printf("\nConsultar por CÓDIGO DE UF?\n");
            printf("1: Sim\n0: Não\n");
            scanf("%d", &flag[3]);
            if(flag[3] == 1){
                printf("MIN: ");
                scanf("%d", &min_cod);
                printf("MAX: ");
                scanf("%d", &max_cod);

                tmunicipio * bmin_cod = aloca_municipio("", "", 0, 0, 0, min_cod, 0, 0, "");
                tmunicipio * bmax_cod = aloca_municipio("", "", 0, 0, 0, max_cod, 0, 0, "");
                lstcod = range_query(&arv_cod, &arv_cod.raiz, bmin_cod, bmax_cod);
            } else{
                lstcod = NULL;
            }

            printf("\nConsultar por DDD?\n");
            printf("1: Sim\n0: Não\n");
            scanf("%d", &flag[4]);
            if(flag[4] == 1){
                printf("MIN: ");
                scanf("%d", &min_ddd);
                printf("MAX: ");
                scanf("%d", &max_ddd);

                tmunicipio * bmin_ddd = aloca_municipio("", "", 0, 0, 0, 0, 0, min_ddd, "");
                tmunicipio * bmax_ddd = aloca_municipio("", "", 0, 0, 0, 0, 0, max_ddd, "");
                lstddd = range_query(&arv_ddd, &arv_ddd.raiz, bmin_ddd, bmax_ddd);
            } else{
                lstddd = NULL;
            }

            printf("\n--- CIDADES ENCONTRADAS ---\n");
            tlista * resul1 = lst_interseccao(lstnome, lstlat);
            tlista * resul2 = lst_interseccao(resul1, lstlong);
            tlista * resul3 = lst_interseccao(resul2, lstcod);
            tlista * resul = lst_interseccao(resul3, lstddd);
            lst_imprime(resul, h);
            break;
        case 0:
            break;
        default:
            printf("Essa não é uma opção válida, digite novamente");
            break;
        }
    }

    fclose(arq);
    free(h.table);
    avl_destroi(arv_nome.raiz);
    avl_destroi(arv_lat.raiz);
    avl_destroi(arv_long.raiz);
    avl_destroi(arv_cod.raiz);
    avl_destroi(arv_ddd.raiz);
    return EXIT_SUCCESS;
}