/*
** EPITECH PROJECT, 2022
** client.c
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <signal.h>
    #include "../libs/myteams/logging_client.h"
    #include "structures.h"

typedef struct protocol {
    char *nm;
    int ln;
    char *cd;
} protocol_t;

typedef bool (*g_ptr) (res_t *, char **);

typedef struct response {
    int cmd;
    g_ptr g;
} response_t;

int launch_cli(const char *, int);

void run_cli(fd_sets_t *, int);
void protocol(int, char *, char **, char **);
char *af_ret(char *);
char *free_double_tab(char **);
char *concat(const char *, const char *);

bool response(int, char **);

bool r_help(res_t *, char **);
bool r_login(res_t *, char **);
bool r_logout(res_t *, char **);
bool r_users(res_t *, char **);
bool r_user(res_t *, char **);
bool r_send(res_t *, char **);
bool r_messages(res_t *, char **);
bool r_subscribe(res_t *, char **);
bool r_subscribed(res_t *, char **);
bool r_unsubscribe(res_t *, char **);
bool r_use(res_t *, char **);
bool r_create(res_t *, char **);
bool r_list(res_t *, char **);
bool r_info(res_t *, char **);
bool r_error(res_t *, char **);

#endif /* !CLIENT_H_ */
