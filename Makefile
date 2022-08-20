##
## EPITECH PROJECT, 2022
## Makefile NWP
## File description:
## makefile NWP
##

SRC_SERVER		=	server/main.c 				\
					server/launch_server.c		\
					server/run_server.c			\
					server/accept_client.c		\
					server/manage_client.c		\
					server/tools.c				\
					server/help.c				\
					server/login.c				\
					server/logout.c				\
					server/users.c				\
					server/user.c				\
					server/send_msg.c			\
					server/messages.c			\
					server/subscribe.c			\
					server/subscribed.c			\
					server/unsubscribe.c		\
					server/use.c				\
					server/create.c				\
					server/check.c				\
					server/check_exists.c		\
					server/create_sub.c			\
					server/list.c				\
					server/list_sub.c			\
					server/info.c				\
					server/info_sub.c			\
					server/send_error.c			\

SRC_CLIENT		=	client/main.c				\
					client/launch_cli.c			\
					client/run_cli.c			\
					client/protocol.c			\
					client/tools.c				\
					client/response.c			\
					client/r_help.c				\
					client/r_login.c			\
					client/r_logout.c			\
					client/r_users.c			\
					client/r_user.c				\
					client/r_send.c				\
					client/r_messages.c			\
					client/r_subscribe.c		\
					client/r_subscribed.c		\
					client/r_unsubscribe.c		\
					client/r_use.c				\
					client/r_create.c			\
					client/r_list.c				\
					client/r_info.c				\
					client/r_error.c			\

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

NAME_SERVER	=	myteams_server

NAME_CLIENT =	myteams_cli

CC	=	gcc

CPPFLAGS	=	-I include/

LDFLAGS		=	-L libs/myteams/

LDLIBS		=	-lmyteams -luuid

all:	myteams

myteams:	$(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER):	$(OBJ_SERVER)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME_SERVER) $(SRC_SERVER)
	
$(NAME_CLIENT):	$(OBJ_CLIENT)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME_CLIENT) $(SRC_CLIENT)

clean:
	rm -rf $(OBJ_SERVER) $(OBJ_CLIENT)

fclean:	clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re:	fclean all

.PHONY: all clean fclean re
