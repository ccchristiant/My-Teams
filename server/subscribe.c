/*
** EPITECH PROJECT, 2022
** subscribe.c
** File description:
** subscribe
*/

#include "server.h"

bool subscribe(core_t *core, client_t **clts, int fd, char **args)
{
    res_t pckg;
    team_t *tmp_team;

    if (args == NULL)
        return false;
    TAILQ_FOREACH(tmp_team, &core->teams_head, teams)
        if (strcmp(tmp_team->team_uuid, args[0]) == 0) {
            pckg.command = 7;
            TAILQ_INSERT_TAIL(&tmp_team->clients_head, clts[fd], clients);
            server_event_user_subscribed(tmp_team->team_uuid, clts[fd]->uuid);
            strcpy(pckg.subscribe.user_uuid, clts[fd]->uuid);
            strcpy(pckg.subscribe.team_uuid, tmp_team->team_uuid);
            write(fd, &pckg, sizeof(res_t));
            return false;
        }
    send_error(fd, UNKNOWN_TEAM, args[0]);
    return false;
}
