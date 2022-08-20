/*
** EPITECH PROJECT, 2022
** logout.c
** File description:
** logout
*/

#include "server.h"

bool logout(core_t *core, client_t **clts, int fd, char **args)
{
    (void)core;
    (void)args;
    res_t pckg;

    pckg.command = 2;
    server_event_user_logged_out(clts[fd]->uuid);
    strcpy(pckg.logout.user_uuid, clts[fd]->uuid);
    strcpy(pckg.logout.user_name, clts[fd]->name);
    for (int i = 0; i < FD_SETSIZE; i++)
        if (clts[i]->name != NULL && clts[i]->logged == 1)
            write(i, &pckg, sizeof(res_t));
    clts[fd]->logged = 0;
    return true;
}
