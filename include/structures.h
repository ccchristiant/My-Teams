/*
** EPITECH PROJECT, 2022
** structures.h
** File description:
** structures
*/

#ifndef STRUCTURES_H_
    #define STRUCTURES_H_

    #include <time.h>
    #include <sys/queue.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <uuid/uuid.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <unistd.h>
    #include <string.h>

    #define UUID_LENGTH 37
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

static const int TOT_LEN =
    (MAX_NAME_LENGTH + MAX_DESCRIPTION_LENGTH + MAX_BODY_LENGTH + 3);

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

typedef struct fd_sets {
    fd_set r_fds;
    fd_set r_fds_save;
    fd_set w_fds;
    fd_set w_fds_save;
} fd_sets_t;

typedef struct team_res {
    char team_uuid[UUID_LENGTH];
    char user_uuid[UUID_LENGTH];
    char team_name[MAX_NAME_LENGTH];
    char team_description[MAX_DESCRIPTION_LENGTH];
} team_res_t;

typedef struct channel_res {
    char channel_uuid[UUID_LENGTH];
    char user_uuid[UUID_LENGTH];
    char channel_name[MAX_NAME_LENGTH];
    char channel_description[MAX_DESCRIPTION_LENGTH];
} channel_res_t;

typedef struct thread_res {
    char thread_uuid[UUID_LENGTH];
    char user_uuid[UUID_LENGTH];
    time_t thread_timestamp;
    char thread_title[MAX_NAME_LENGTH];
    char thread_body[MAX_BODY_LENGTH];
} thread_res_t;

typedef struct reply_res {
    char team_uuid[UUID_LENGTH];
    char thread_uuid[UUID_LENGTH];
    char user_uuid[UUID_LENGTH];
    time_t reply_timestamp;
    char reply_body[MAX_BODY_LENGTH];
} reply_res_t;

typedef struct help_res {
    char buffer[MAX_BODY_LENGTH];
} help_res_t;

typedef struct login_res {
    char user_uuid[UUID_LENGTH];
    char user_name[MAX_NAME_LENGTH];
} login_res_t;

typedef struct logout_res {
    char user_uuid[UUID_LENGTH];
    char user_name[MAX_NAME_LENGTH];
} logout_res_t;

typedef struct user_res {
    char user_uuid[UUID_LENGTH];
    char user_name[MAX_NAME_LENGTH];
    int user_status;
} user_res_t;

typedef struct users_res {
    int nb;
    user_res_t users[FD_SETSIZE];
} users_res_t;

typedef struct send_res {
    char user_uuid[UUID_LENGTH];
    time_t message_timestamp;
    char message_body[MAX_BODY_LENGTH];
} send_res_t;

typedef struct message_res {
    char user_uuid[UUID_LENGTH];
    time_t timestamp;
    char message_body[MAX_BODY_LENGTH];
} message_res_t;

typedef struct messages_res {
    int nb;
    message_res_t messages[100];
} messages_res_t;

typedef struct subscribe_res {
    char user_uuid[UUID_LENGTH];
    char team_uuid[UUID_LENGTH];
} subscribe_res_t;

typedef struct subscribed_team_res {
    int nb;
    team_res_t teams[100];
} subscribed_team_res_t;

typedef struct subscribed_res {
    int argument;
    union {
        users_res_t users;
        subscribed_team_res_t teams;
    };
} subscribed_res_t;

typedef struct unsubscribe_res {
    char user_uuid[UUID_LENGTH];
    char team_uuid[UUID_LENGTH];
} unsubscribe_res_t;

typedef enum context {
    TEAM = 0,
    CHANNEL,
    THREAD,
    REPLY,
    USER
} context_t;

typedef enum error_type {
    UNKNOWN_TEAM = 0,
    UNKNOWN_CHANNEL,
    UNKNOWN_THREAD,
    UNKNOWN_USER,
    UNAUTHORIZED,
    ALREADY_EXIST
} error_type_t;

typedef struct error_res {
    error_type_t type;
    char uuid[UUID_LENGTH];
} error_res_t;

typedef struct res {
    int command;
    context_t context;
    union {
        help_res_t help;
        login_res_t login;
        logout_res_t logout;
        users_res_t users;
        user_res_t user;
        send_res_t send;
        messages_res_t messages;
        subscribe_res_t subscribe;
        subscribed_res_t subscribed;
        unsubscribe_res_t unsubscribe;
        team_res_t team;
        channel_res_t channel;
        thread_res_t thread;
        reply_res_t reply;
        error_res_t error;
    };
} res_t;

#endif /* !STRUCTURES_H_ */
