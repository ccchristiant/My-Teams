/*
** EPITECH PROJECT, 2022
** user.c
** File description:
** user
*/

#include "server.h"

bool user(core_t *core, client_t **clts, int fd, char **args)
{
    (void)core;
    res_t pckg;

    if (args == NULL)
        return false;
    for (int i = 0; i < FD_SETSIZE; i++)
        if (clts[i]->uuid != NULL && strcmp(clts[i]->uuid, args[0]) == 0) {
            pckg.command = 4;
            strcpy(pckg.user.user_uuid, clts[i]->uuid);
            strcpy(pckg.user.user_name, clts[i]->name);
            pckg.user.user_status = clts[i]->logged;
            write(fd, &pckg, sizeof(res_t));
            return false;
        }
    send_error(fd, UNKNOWN_USER, args[0]);
    return false;
}
