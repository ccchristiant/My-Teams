/*
** EPITECH PROJECT, 2022
** tools.c
** File description:
** tools
*/

#include "server.h"

char *af_ret(char *tmp)
{
    return (strchr(tmp, '\n') + 1);
}

void free_double_tab(char **tab)
{
    if (tab != NULL) {
        for (int i = 0; tab[i] != NULL; i++)
            free(tab[i]);
        free(tab);
    }
}

char *concat(const char *s1, const char *s2)
{
    char *res = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));

    strcpy(res, s1);
    strcat(res, s2);
    return res;
}
