/*
** EPITECH PROJECT, 2022
** unsubscribe.c
** File description:
** unsubscribe
*/

#include "server.h"

bool unsubscribe(core_t *core, client_t **clts, int fd, char **args)
{
    res_t pckg;
    team_t *tmp_team;
    client_t *tmp_clt;

    if (args == NULL)
        return false;
    TAILQ_FOREACH(tmp_team, &core->teams_head, teams)
        if (strcmp(tmp_team->team_uuid, args[0]) == 0) {
            TAILQ_FOREACH(tmp_clt, &tmp_team->clients_head, clients)
                if (strcmp(tmp_clt->uuid, clts[fd]->uuid) == 0) {
                    pckg.command = 9;
                    TAILQ_REMOVE(&tmp_team->clients_head, tmp_clt, clients);
                    free(tmp_clt);
                    server_event_user_unsubscribed
                    (tmp_team->team_uuid, clts[fd]->uuid);
                    strcpy(pckg.unsubscribe.user_uuid, clts[fd]->uuid);
                    strcpy(pckg.unsubscribe.team_uuid, tmp_team->team_uuid);
                    write(fd, &pckg, sizeof(res_t));
                    return false;
                }
            return false;
        }
    send_error(fd, UNKNOWN_TEAM, args[0]);
    return false;
}
