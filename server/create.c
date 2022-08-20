/*
** EPITECH PROJECT, 2022
** create.c
** File description:
** create
*/

#include "server.h"

bool c_reply(core_t *core, client_t **clts, int fd, char **args)
{
    if (clts[fd]->tmp_thread != NULL) {
        if (!check_team(core, clts, fd) || !check_channel(clts, fd) ||
            !check_thread(clts, fd) || !check_subscribed(core, clts, fd))
            return true;
        create_reply(clts, fd, args);
        return true;
    }
    return false;
}

bool c_thread(core_t *core, client_t **clts, int fd, char **args)
{
    if (clts[fd]->tmp_channel != NULL) {
        if (!check_team(core, clts, fd) || !check_channel(clts, fd) ||
            !check_subscribed(core, clts, fd) ||
            check_thread_exists(clts, fd, args[0]))
            return true;
        create_thread(clts, fd, args);
        return true;
    }
    return false;
}

bool c_channel(core_t *core, client_t **clts, int fd, char **args)
{
    if (clts[fd]->tmp_team != NULL) {
        if (!check_team(core, clts, fd) || !check_subscribed(core, clts, fd) ||
            check_channel_exists(clts, fd, args[0]))
            return true;
        create_channel(clts, fd, args);
        return true;
    }
    return false;
}

void c_team(core_t *core, client_t **clts, int fd, char **args)
{
    if (check_team_exists(core, fd, args[0]))
        return;
    create_team(core, clts, fd, args);
}

bool create(core_t *core, client_t **clts, int fd, char **args)
{
    if (args == NULL)
        return false;
    if (c_reply(core, clts, fd, args))
        return false;
    if (!args[1])
        return false;
    if (c_thread(core, clts, fd, args))
        return false;
    if (c_channel(core, clts, fd, args))
        return false;
    c_team(core, clts, fd, args);
    return false;
}
