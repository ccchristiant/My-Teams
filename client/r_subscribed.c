/*
** EPITECH PROJECT, 2022
** r_subscribed.c
** File description:
** r_subscribed
*/

#include "client.h"

bool r_subscribed(res_t *pckg, char **uuid)
{
    (void)uuid;
    if (pckg->subscribed.argument == 0) {
        for (int i = 0; i < pckg->subscribed.teams.nb; i++) {
            client_print_teams(pckg->subscribed.teams.teams[i].team_uuid,
            pckg->subscribed.teams.teams[i].team_name,
            pckg->subscribed.teams.teams[i].team_description);
        }
    } else {
        for (int i = 0; i < pckg->subscribed.users.nb; i++) {
            client_print_users(pckg->subscribed.users.users[i].user_uuid,
            pckg->subscribed.users.users[i].user_name,
            pckg->subscribed.users.users[i].user_status);
        }
    }
    return false;
}
