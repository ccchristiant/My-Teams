/*
** EPITECH PROJECT, 2022
** messages.c
** File description:
** messages
*/

#include "server.h"

bool matching_msg(client_t **clts, message_t *tmp_msg, int fd, int i)
{
    return ((strcmp(tmp_msg->sender_uuid, clts[fd]->uuid) == 0 &&
    strcmp(tmp_msg->receiver_uuid, clts[i]->uuid) == 0) ||
    (strcmp(tmp_msg->sender_uuid, clts[i]->uuid) == 0 &&
    strcmp(tmp_msg->receiver_uuid, clts[fd]->uuid) == 0));
}

bool messages(core_t *core, client_t **clts, int fd, char **args)
{
    (void)core;
    res_t pckg;
    message_t *tmp_msg;

    if (args == NULL)
        return false;
    for (int i = 0; i < FD_SETSIZE; i++)
        if (clts[i]->uuid != NULL && strcmp(clts[i]->uuid, args[0]) == 0) {
            pckg.command = 6;
            pckg.messages.nb = 0;
            TAILQ_FOREACH(tmp_msg, &clts[i]->messages_head, messages) {
                if (matching_msg(clts, tmp_msg, fd, i)) {
                    strcpy(pckg.messages.messages[pckg.messages.nb].user_uuid, tmp_msg->sender_uuid);
                    pckg.messages.messages[pckg.messages.nb].timestamp = tmp_msg->timestamp;
                    strcpy(pckg.messages.messages[pckg.messages.nb].message_body, tmp_msg->message_body);
                    pckg.messages.nb += 1;
                }
            }
            write(fd, &pckg, sizeof(res_t));
            return false;
        }
    send_error(fd, UNKNOWN_USER, args[0]);
    return false;
}
