/*
** EPITECH PROJECT, 2022
** subscribed.c
** File description:
** subscribed
*/

#include "server.h"

void subscribed_users(core_t *core, int fd, char **args)
{
    res_t pckg;
    team_t *tmp_team;
    client_t *tmp_clt;

    TAILQ_FOREACH(tmp_team, &core->teams_head, teams)
        if (strcmp(tmp_team->team_uuid, args[0]) == 0) {
            pckg.command = 8;
            pckg.subscribed.argument = 1;
            pckg.subscribed.users.nb = 0;
            TAILQ_FOREACH(tmp_clt, &tmp_team->clients_head, clients) {
                strcpy(pckg.subscribed.users.users[pckg.subscribed.users.nb].user_uuid, tmp_clt->uuid);
                strcpy(pckg.subscribed.users.users[pckg.subscribed.users.nb].user_name, tmp_clt->name);
                pckg.subscribed.users.users[pckg.subscribed.users.nb].user_status = tmp_clt->logged;
                pckg.subscribed.users.nb += 1;
            }
            write(fd, &pckg, sizeof(res_t));
            return;
        }
    send_error(fd, UNKNOWN_TEAM, args[0]);
}

bool subscribed(core_t *core, client_t **clts, int fd, char **args)
{
    (void)clts;
    res_t pckg;
    team_t *tmp_team;

    if (args == NULL) {
        pckg.command = 8;
        pckg.subscribed.argument = 0;
        pckg.subscribed.teams.nb = 0;
        TAILQ_FOREACH(tmp_team, &core->teams_head, teams)
            if (!TAILQ_EMPTY(&tmp_team->clients_head)) {
                strcpy(pckg.subscribed.teams.teams[pckg.subscribed.teams.nb].team_uuid, tmp_team->team_uuid);
                strcpy(pckg.subscribed.teams.teams[pckg.subscribed.teams.nb].team_name, tmp_team->team_name);
                strcpy(pckg.subscribed.teams.teams[pckg.subscribed.teams.nb].team_description, tmp_team->team_description);
                pckg.subscribed.teams.nb += 1;
            }
        write(fd, &pckg, sizeof(res_t));
        return false;
    } else
        subscribed_users(core, fd, args);
    return false;
}
