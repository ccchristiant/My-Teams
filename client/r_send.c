/*
** EPITECH PROJECT, 2022
** r_send.c
** File description:
** r_send
*/

#include "client.h"

bool r_send(res_t *pckg, char **uuid)
{
    if (strcmp(pckg->send.user_uuid, *uuid) != 0)
        client_event_private_message_received(pckg->send.user_uuid,
        pckg->send.message_body);
    return false;
}
