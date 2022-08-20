/*
** EPITECH PROJECT, 2022
** send_msg.c
** File description:
** send_msg
*/

#include "server.h"

void res_to_sender_and_receiver(client_t **clts, int src_fd, int dst_fd,
message_t *tmp)
{
    res_t pckg;

    pckg.command = 5;
    strcpy(pckg.send.user_uuid, tmp->sender_uuid);
    pckg.send.message_timestamp = tmp->timestamp;
    strcpy(pckg.send.message_body, tmp->message_body);
    TAILQ_INSERT_TAIL(&clts[src_fd]->messages_head, tmp, messages);
    write(src_fd, &pckg, sizeof(res_t));
    server_event_private_message_sended
    (clts[src_fd]->uuid, clts[dst_fd]->uuid, tmp->message_body);
    TAILQ_INSERT_TAIL(&clts[dst_fd]->messages_head, tmp, messages);
    write(dst_fd, &pckg, sizeof(res_t));
}

bool send_msg(core_t *core, client_t **clts, int fd, char **args)
{
    (void)core;
    message_t *tmp;

    if (args == NULL || !args[1])
        return false;
    for (int i = 0; i < FD_SETSIZE; i++)
        if (clts[i]->uuid != NULL && strcmp(clts[i]->uuid, args[0]) == 0) {
            tmp = malloc(sizeof(message_t));
            tmp->sender_uuid = strdup(clts[fd]->uuid);
            tmp->receiver_uuid = strdup(clts[i]->uuid);
            tmp->timestamp = time(NULL);
            tmp->message_body = strdup(args[1]);
            res_to_sender_and_receiver(clts, fd, i, tmp);
            return false;
        }
    send_error(fd, UNKNOWN_USER, args[0]);
    return false;
}
