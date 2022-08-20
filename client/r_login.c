/*
** EPITECH PROJECT, 2022
** r_login.c
** File description:
** r_login
*/

#include "client.h"

bool r_login(res_t *pckg, char **uuid)
{
    client_event_logged_in(pckg->login.user_uuid, pckg->login.user_name);
    if (*uuid == NULL)
        *uuid = strdup(pckg->login.user_uuid);
    return false;
}
