/*
** EPITECH PROJECT, 2022
** create_sub.c
** File description:
** create_sub
*/

#include "server.h"

void create_reply(client_t **clts, int fd, char **args)
{
    reply_t *tmp = malloc(sizeof(reply_t));
    res_t pckg;
    client_t *tmp_clt;

    tmp->team_uuid = strdup(clts[fd]->team->team_uuid);
    tmp->thread_uuid = strdup(clts[fd]->thread->thread_uuid);
    tmp->user_uuid = strdup(clts[fd]->uuid);
    tmp->timestamp = time(NULL);
    tmp->reply_body = strdup(args[0]);
    TAILQ_INSERT_TAIL(&clts[fd]->thread->replies_head, tmp, replies);
    pckg.command = 11;
    pckg.context = REPLY;
    server_event_reply_created
    (tmp->thread_uuid, tmp->user_uuid, tmp->reply_body);
    strcpy(pckg.reply.team_uuid, tmp->team_uuid);
    strcpy(pckg.reply.thread_uuid, tmp->thread_uuid);
    strcpy(pckg.reply.user_uuid, tmp->user_uuid);
    pckg.reply.reply_timestamp = tmp->timestamp;
    strcpy(pckg.reply.reply_body, tmp->reply_body);
    TAILQ_FOREACH(tmp_clt, &clts[fd]->team->clients_head, clients)
        write(tmp_clt->cl_sock, &pckg, sizeof(res_t));
}

void create_thread(client_t **clts, int fd, char **args)
{
    thread_t *tmp = malloc(sizeof(thread_t));
    res_t pckg;
    uuid_t uuid;
    client_t *tmp_clt;

    tmp->channel_uuid = strdup(clts[fd]->channel->channel_uuid);
    uuid_generate(uuid);
    tmp->thread_uuid = malloc(sizeof(char) * UUID_LENGTH);
    uuid_unparse(uuid, tmp->thread_uuid);
    tmp->user_uuid = strdup(clts[fd]->uuid);
    tmp->timestamp = time(NULL);
    tmp->thread_title = strdup(args[0]);
    tmp->thread_body = strdup(args[1]);
    TAILQ_INIT(&tmp->replies_head);
    TAILQ_INSERT_TAIL(&clts[fd]->channel->threads_head, tmp, threads);
    pckg.command = 11;
    pckg.context = THREAD;
    server_event_thread_created(tmp->channel_uuid, tmp->thread_uuid,
    tmp->user_uuid, tmp->thread_title, tmp->thread_body);
    strcpy(pckg.thread.thread_uuid, tmp->thread_uuid);
    strcpy(pckg.thread.user_uuid, tmp->user_uuid);
    pckg.thread.thread_timestamp = tmp->timestamp;
    strcpy(pckg.thread.thread_title, tmp->thread_title);
    strcpy(pckg.thread.thread_body, tmp->thread_body);
    TAILQ_FOREACH(tmp_clt, &clts[fd]->team->clients_head, clients)
        write(tmp_clt->cl_sock, &pckg, sizeof(res_t));
}

void create_channel(client_t **clts, int fd, char **args)
{
    channel_t *tmp = malloc(sizeof(channel_t));
    res_t pckg;
    uuid_t uuid;
    client_t *tmp_clt;

    tmp->team_uuid = strdup(clts[fd]->team->team_uuid);
    uuid_generate(uuid);
    tmp->channel_uuid = malloc(sizeof(char) * UUID_LENGTH);
    uuid_unparse(uuid, tmp->channel_uuid);
    tmp->user_uuid = strdup(clts[fd]->uuid);
    tmp->channel_name = strdup(args[0]);
    tmp->channel_description = strdup(args[1]);
    TAILQ_INIT(&tmp->threads_head);
    TAILQ_INSERT_TAIL(&clts[fd]->team->channels_head, tmp, channels);
    pckg.command = 11;
    pckg.context = CHANNEL;
    server_event_channel_created
    (tmp->team_uuid, tmp->channel_uuid, tmp->channel_name);
    strcpy(pckg.channel.channel_uuid, tmp->channel_uuid);
    strcpy(pckg.channel.user_uuid, tmp->user_uuid);
    strcpy(pckg.channel.channel_name, tmp->channel_name);
    strcpy(pckg.channel.channel_description, tmp->channel_description);
    TAILQ_FOREACH(tmp_clt, &clts[fd]->team->clients_head, clients)
        write(tmp_clt->cl_sock, &pckg, sizeof(res_t));
}

void create_team(core_t *core, client_t **clts, int fd, char **args)
{
    team_t *tmp = malloc(sizeof(team_t));
    res_t pckg;
    uuid_t uuid;

    uuid_generate(uuid);
    tmp->team_uuid = malloc(sizeof(char) * UUID_LENGTH);
    uuid_unparse(uuid, tmp->team_uuid);
    tmp->user_uuid = strdup(clts[fd]->uuid);
    tmp->team_name = strdup(args[0]);
    tmp->team_description = strdup(args[1]);
    TAILQ_INIT(&tmp->channels_head);
    TAILQ_INIT(&tmp->clients_head);
    TAILQ_INSERT_TAIL(&core->teams_head, tmp, teams);
    pckg.command = 11;
    pckg.context = TEAM;
    server_event_team_created(tmp->team_uuid, tmp->team_name, tmp->user_uuid);
    strcpy(pckg.team.team_uuid, tmp->team_uuid);
    strcpy(pckg.team.user_uuid, tmp->user_uuid);
    strcpy(pckg.team.team_name, tmp->team_name);
    strcpy(pckg.team.team_description, tmp->team_description);
    for (int i = 0; i < FD_SETSIZE; i++)
        if (clts[i]->name != NULL && clts[i]->logged == 1)
            write(clts[i]->cl_sock, &pckg, sizeof(res_t));
}
