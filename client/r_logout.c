/*
** EPITECH PROJECT, 2022
** r_logout.c
** File description:
** r_logout
*/

#include "client.h"

bool r_logout(res_t *pckg, char **uuid)
{
    client_event_logged_out(pckg->login.user_uuid, pckg->login.user_name);
    if (strcmp(pckg->login.user_uuid, *uuid) != 0)
        return false;
    return true;
}
