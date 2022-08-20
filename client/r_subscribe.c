/*
** EPITECH PROJECT, 2022
** r_subscribe.c
** File description:
** r_subscribe
*/

#include "client.h"

bool r_subscribe(res_t *pckg, char **uuid)
{
    (void)uuid;
    client_print_subscribed(pckg->subscribe.user_uuid,
    pckg->subscribe.team_uuid);
    return false;
}
