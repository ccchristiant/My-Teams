/*
** EPITECH PROJECT, 2022
** users.c
** File description:
** users
*/

#include "server.h"

bool users(core_t *core, client_t **clts, int fd, char **args)
{
    (void)core;
    (void)args;
    res_t pckg;

    pckg.command = 3;
    pckg.users.nb = 0;
    for (int i = 0; i < FD_SETSIZE; i++)
        if (clts[i]->name != NULL) {
            strcpy(pckg.users.users[pckg.users.nb].user_uuid, clts[i]->uuid);
            strcpy(pckg.users.users[pckg.users.nb].user_name, clts[i]->name);
            pckg.users.users[pckg.users.nb].user_status = clts[i]->logged;
            pckg.users.nb += 1;
        }
    write(fd, &pckg, sizeof(res_t));
    return false;
}
