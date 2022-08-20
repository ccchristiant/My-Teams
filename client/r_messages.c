/*
** EPITECH PROJECT, 2022
** r_messages.c
** File description:
** r_messages
*/

#include "client.h"

bool r_messages(res_t *pckg, char **uuid)
{
    (void)uuid;
    for (int i = 0; i < pckg->messages.nb; i++) {
        client_private_message_print_messages(
        pckg->messages.messages[i].user_uuid,
        pckg->messages.messages[i].timestamp,
        pckg->messages.messages[i].message_body);
    }
    return false;
}
