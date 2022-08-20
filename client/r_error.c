/*
** EPITECH PROJECT, 2022
** r_error.c
** File description:
** r_error
*/

#include "client.h"

bool r_error(res_t *pckg, char **uuid)
{
    (void)uuid;
    switch (pckg->error.type) {
        case UNKNOWN_TEAM:
            client_error_unknown_team(pckg->error.uuid);
            break;
        case UNKNOWN_CHANNEL:
            client_error_unknown_channel(pckg->error.uuid);
            break;
        case UNKNOWN_THREAD:
            client_error_unknown_thread(pckg->error.uuid);
            break;
        case UNKNOWN_USER:
            client_error_unknown_user(pckg->error.uuid);
            break;
        case UNAUTHORIZED:
            client_error_unauthorized();
            break;
        default:
            client_error_already_exist();
    }
    return false;
}
