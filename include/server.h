/*
** EPITECH PROJECT, 2022
** server.h
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "../libs/myteams/logging_server.h"
    #include "structures.h"

typedef struct core {
    fd_sets_t fd_sets;
    TAILQ_HEAD(, team) teams_head;
} core_t;

typedef struct team {
    char *team_uuid;
    char *user_uuid;
    char *team_name;
    char *team_description;
    TAILQ_ENTRY(team) teams;
    TAILQ_HEAD(, channel) channels_head;
    TAILQ_HEAD(, client) clients_head;
} team_t;

typedef struct channel {
    char *team_uuid;
    char *channel_uuid;
    char *user_uuid;
    char *channel_name;
    char *channel_description;
    TAILQ_ENTRY(channel) channels;
    TAILQ_HEAD(, thread) threads_head;
} channel_t;

typedef struct thread {
    char *channel_uuid;
    char *thread_uuid;
    char *user_uuid;
    time_t timestamp;
    char *thread_title;
    char *thread_body;
    TAILQ_ENTRY(thread) threads;
    TAILQ_HEAD(, reply) replies_head;
} thread_t;

typedef struct reply {
    char *team_uuid;
    char *thread_uuid;
    char *user_uuid;
    time_t timestamp;
    char *reply_body;
    TAILQ_ENTRY(reply) replies;
} reply_t;

typedef struct message {
    char *sender_uuid;
    char *receiver_uuid;
    time_t timestamp;
    char *message_body;
    TAILQ_ENTRY(message) messages;
} message_t;

typedef struct client {
    SOCKADDR_IN sv_sa_in;
    int cl_sock;
    SOCKADDR_IN cl_sa_in;
    int cl_sa_size;
    char *tmp;
    char *cmd;

    int logged;
    char *uuid;
    char *name;
    char *tmp_team;
    team_t *team;
    char *tmp_channel;
    channel_t *channel;
    char *tmp_thread;
    thread_t *thread;
    TAILQ_ENTRY(client) clients;
    TAILQ_HEAD(, message) messages_head;
} client_t;

typedef bool (*f_ptr) (core_t *, client_t **, int, char **);

typedef struct command {
    char *nm;
    int ln;
    f_ptr f;
} command_t;

int launch_server(int port);
void run_server(core_t *, client_t **, int);

void accept_client(client_t *, int);

bool manage_client(core_t *, client_t **, int, char *);
char *af_ret(char *);
void free_double_tab(char **);

bool help(core_t *, client_t **, int, char **);
bool login(core_t *, client_t **, int, char **);
bool logout(core_t *, client_t **, int, char **);
bool users(core_t *, client_t **, int, char **);
bool user(core_t *, client_t **, int, char **);
bool send_msg(core_t *, client_t **, int, char **);
bool messages(core_t *, client_t **, int, char **);
bool subscribe(core_t *, client_t **, int, char **);
bool subscribed(core_t *, client_t **, int, char **);
bool unsubscribe(core_t *, client_t **, int, char **);
bool use(core_t *, client_t **, int, char **);
bool create(core_t *, client_t **, int, char **);
bool list(core_t *, client_t **, int, char **);
bool info(core_t *, client_t **, int, char **);

void send_error(int, error_type_t, char *);
bool check_thread(client_t **, int);
bool check_channel(client_t **, int);
bool check_team(core_t *, client_t **, int);
bool check_subscribed(core_t *, client_t **, int);
bool check_thread_exists(client_t **, int, char *);
bool check_channel_exists(client_t **, int, char *);
bool check_team_exists(core_t *, int, char *);
void create_reply(client_t **, int, char **);
void create_thread(client_t **, int, char **);
void create_channel(client_t **, int, char **);
void create_team(core_t *, client_t **, int, char **);
void list_reply(client_t **, int);
void list_thread(client_t **, int);
void list_channel(client_t **, int);
void list_team(core_t *, int);
void info_thread(client_t **, int);
void info_channel(client_t **, int);
void info_team(client_t **, int);
void info_user(client_t **, int);

#endif /* !SERVER_H_ */
