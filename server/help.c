/*
** EPITECH PROJECT, 2022
** help.c
** File description:
** help
*/

#include "server.h"

bool help(core_t *core, client_t **clts, int fd, char **args)
{
    (void)core;
    (void)clts;
    (void)args;
    res_t pckg;

    pckg.command = 0;
    strcpy(pckg.help.buffer, "/help\
    \n/login [\"user_name\"]\
    \n/logout\
    \n/users\
    \n/user [\"user_uuid\"]\
    \n/send [\"user_uuid\"] [\"message_body\"]\
    \n/messages [\"user_uuid\"]\
    \n/subscribe [\"team_uuid\"]\
    \n/subscribed ?[\"team_uuid\"]\
    \n/unsubscribe [\"team_uuid\"]\
    \n/use ?[\"team_uuid\"] ?[\"channel_uuid\"] ?[\"thread_uuid\"]\
    \n/create\
    \n/list\
    \n/info\n");
    write(fd, &pckg, sizeof(res_t));
    return false;
}
