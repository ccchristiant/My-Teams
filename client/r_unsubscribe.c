/*
** EPITECH PROJECT, 2022
** r_unsubscribe.c
** File description:
** r_unsubscribe
*/

#include "client.h"

bool r_unsubscribe(res_t *pckg, char **uuid)
{
    (void)uuid;
    client_print_unsubscribed(pckg->unsubscribe.user_uuid,
    pckg->unsubscribe.team_uuid);
    return false;
}
