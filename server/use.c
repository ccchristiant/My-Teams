/*
** EPITECH PROJECT, 2022
** use.c
** File description:
** use
*/

#include "server.h"

void reset_tmps(client_t **clts, int fd)
{
    clts[fd]->tmp_team = NULL;
    clts[fd]->tmp_thread = NULL;
    clts[fd]->tmp_channel = NULL;
}

bool use(core_t *core, client_t **clts, int fd, char **args)
{
    (void)core;
    int len = 0;

    reset_tmps(clts, fd);
    if (args == NULL) {
        return false;
    } else {
        for (; args[len] != NULL; len++);
        if (len >= 1)
            clts[fd]->tmp_team = strdup(args[0]);
        if (len >= 2)
            clts[fd]->tmp_channel = strdup(args[1]);
        if (len == 3)
            clts[fd]->tmp_thread = strdup(args[2]);
    }
    return false;
}
