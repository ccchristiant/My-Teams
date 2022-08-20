/*
** EPITECH PROJECT, 2022
** check.c
** File description:
** check
*/

#include "server.h"

bool check_subscribed(core_t *core, client_t **clts, int fd)
{
    team_t *tmp_team;
    client_t *tmp_clt;

    TAILQ_FOREACH(tmp_team, &core->teams_head, teams) {
        if (strcmp(tmp_team->team_uuid, clts[fd]->team->team_uuid) == 0) {
            TAILQ_FOREACH(tmp_clt, &tmp_team->clients_head, clients)
                if (strcmp(tmp_clt->uuid, clts[fd]->uuid) == 0)
                    return true;
            break;
        }
    }
    send_error(fd, UNAUTHORIZED, NULL);
    return false;
}

bool check_thread(client_t **clts, int fd)
{
    thread_t *tmp_thread;

    TAILQ_FOREACH(tmp_thread, &clts[fd]->channel->threads_head, threads)
        if (strcmp(tmp_thread->thread_uuid, clts[fd]->tmp_thread) == 0) {
            clts[fd]->thread = tmp_thread;
            return true;
        }
    send_error(fd, UNKNOWN_THREAD, clts[fd]->tmp_thread);
    return false;
}

bool check_channel(client_t **clts, int fd)
{
    channel_t *tmp_channel;

    TAILQ_FOREACH(tmp_channel, &clts[fd]->team->channels_head, channels)
        if (strcmp(tmp_channel->channel_uuid, clts[fd]->tmp_channel) == 0) {
            clts[fd]->channel = tmp_channel;
            return true;
        }
    send_error(fd, UNKNOWN_CHANNEL, clts[fd]->tmp_channel);
    return false;
}

bool check_team(core_t *core, client_t **clts, int fd)
{
    team_t *tmp_team;

    TAILQ_FOREACH(tmp_team, &core->teams_head, teams)
        if (strcmp(tmp_team->team_uuid, clts[fd]->tmp_team) == 0) {
            clts[fd]->team = tmp_team;
            return true;
        }
    send_error(fd, UNKNOWN_TEAM, clts[fd]->tmp_team);
    return false;
}
