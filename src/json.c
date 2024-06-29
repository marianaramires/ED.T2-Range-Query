#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lib.h"

char *trata(char *string)
{
    char *pt = strstr(string, ":");
    pt = pt + 2;
    char *virgula = strchr(pt, ',');
    if (virgula)
        *virgula = '\0';

    return pt;
}

void trata_aspas(char *string, char *sem_aspas)
{
    char aspas[500];
    int j = 0;
    strcpy(aspas, trata(string));
    for (int i = 0; aspas[i] != '\0'; i++)
    {
        if (aspas[i] != '"')
        {
            sem_aspas[j++] = aspas[i];
        }
    }
    sem_aspas[j] = '\0';
}