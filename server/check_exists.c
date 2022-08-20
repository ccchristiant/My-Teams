/*
** EPITECH PROJECT, 2022
** check_exists.c
** File description:
** check_exists
*/

#include "server.h"

bool check_thread_exists(client_t **clts, int fd, char *arg)
{
    thread_t *tmp_thread;

    TAILQ_FOREACH(tmp_thread, &clts[fd]->channel->threads_head, threads)
        if (strcmp(tmp_thread->thread_title, arg) == 0) {
            send_error(fd, ALREADY_EXIST, NULL);
            return true;
        }
    return false;
}

bool check_channel_exists(client_t **clts, int fd, char *arg)
{
    channel_t *tmp_channel;

    TAILQ_FOREACH(tmp_channel, &clts[fd]->team->channels_head, channels)
        if (strcmp(tmp_channel->channel_name, arg) == 0) {
            send_error(fd, ALREADY_EXIST, NULL);
            return true;
        }
    return false;
}

bool check_team_exists(core_t *core, int fd, char *arg)
{
    team_t *tmp_team;

    TAILQ_FOREACH(tmp_team, &core->teams_head, teams)
        if (strcmp(tmp_team->team_name, arg) == 0) {
            send_error(fd, ALREADY_EXIST, NULL);
            return true;
        }
    return false;
}
