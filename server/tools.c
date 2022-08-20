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
