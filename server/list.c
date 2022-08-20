/*
** EPITECH PROJECT, 2022
** list.h
** File description:
** list
*/

#include "server.h"

bool l_reply(core_t *core, client_t **clts, int fd)
{
    if (clts[fd]->tmp_thread != NULL) {
        if (!check_team(core, clts, fd) || !check_channel(clts, fd) ||
            !check_thread(clts, fd) || !check_subscribed(core, clts, fd))
            return true;
        list_reply(clts, fd);
        return true;
    }
    return false;
}

bool l_thread(core_t *core, client_t **clts, int fd)
{
    if (clts[fd]->tmp_channel != NULL) {
        if (!check_team(core, clts, fd) || !check_channel(clts, fd) ||
            !check_subscribed(core, clts, fd))
            return true;
        list_thread(clts, fd);
        return true;
    }
    return false;
}

bool l_channel(core_t *core, client_t **clts, int fd)
{
    if (clts[fd]->tmp_team != NULL) {
        if (!check_team(core, clts, fd) || !check_subscribed(core, clts, fd))
            return true;
        list_channel(clts, fd);
        return true;
    }
    return false;
}

bool list(core_t *core, client_t **clts, int fd, char **args)
{
    (void)args;
    if (l_reply(core, clts, fd))
        return false;
    if (l_thread(core, clts, fd))
        return false;
    if (l_channel(core, clts, fd))
        return false;
    list_team(core, fd);
    return false;
}
