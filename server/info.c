/*
** EPITECH PROJECT, 2022
** info.c
** File description:
** info
*/

#include "server.h"

bool i_thread(core_t *core, client_t **clts, int fd)
{
    if (clts[fd]->tmp_thread != NULL) {
        if (!check_team(core, clts, fd) || !check_channel(clts, fd) ||
            !check_thread(clts, fd) || !check_subscribed(core, clts, fd))
            return true;
        info_thread(clts, fd);
        return true;
    }
    return false;
}

bool i_channel(core_t *core, client_t **clts, int fd)
{
    if (clts[fd]->tmp_channel != NULL) {
        if (!check_team(core, clts, fd) || !check_channel(clts, fd) ||
            !check_subscribed(core, clts, fd))
            return true;
        info_channel(clts, fd);
        return true;
    }
    return false;
}

bool i_team(core_t *core, client_t **clts, int fd)
{
    if (clts[fd]->tmp_team != NULL) {
        if (!check_team(core, clts, fd) || !check_subscribed(core, clts, fd))
            return true;
        info_team(clts, fd);
        return true;
    }
    return false;
}

bool info(core_t *core, client_t **clts, int fd, char **args)
{
    (void)args;
    if (i_thread(core, clts, fd))
        return false;
    if (i_channel(core, clts, fd))
        return false;
    if (i_team(core, clts, fd))
        return false;
    info_user(clts, fd);
    return false;
}
