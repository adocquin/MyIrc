##
## Makefile for my_irc in /home/docqui_a/PSU_2015_myirc
##
## Made by Avel Docquin
## Login   <docqui_a@epitech.net>
##
## Started on  Tue May 17 02:44:45 2016 Avel Docquin
## Last update Sun Jun  5 11:47:58 2016 Avel Docquin
##

CC = gcc

CFLAGS = -Wall -Werror -Wextra -Ofast

RM = rm -rf

SERVER = server

SERVER_SRC = src/server/main.c \
	src/server/server.c \
	src/server/client.c \
	src/server/misc.c \
	src/server/handle.c \
	src/server/orders.c \
	src/server/orders2.c \
	src/server/orders3.c \
	src/server/socket.c \
	src/server/reply.c \
	src/server/reply2.c \
	src/server/parser.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)

$(SERVER): $(SERVER_OBJ)
	$(CC) -o $(SERVER) $(SERVER_OBJ) $(CFLAGS)

CLIENT = client

CLIENT_SRC = src/client/main.c \
	src/client/client.c \
	src/client/misc.c \
	src/client/parser.c \
	src/client/control.c \
	src/client/infos.c \
	src/client/connection.c \
	src/client/commands.c \
	src/client/init_func_tab.c \
	src/client/socket.c	

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

$(CLIENT): $(CLIENT_OBJ)
		$(CC) -o $(CLIENT) $(CLIENT_OBJ) $(CFLAGS)

all: $(SERVER) $(CLIENT)

clean:
	$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)

fclean:	clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

run: re
	valgrind ./$(SERVER) 4242

crun: re
	valgrind ./$(CLIENT)

.PHONY:	all clean fclean re run crun
