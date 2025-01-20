NAME			=	minitalk
SERVER			=	server
SERVER_SRC		=	server.c
CLIENT			=	client
CLIENT_SRC		=	client.c
UTILS_SRC		=	utils.c
CC				=	cc
RM 				=	rm -rf
CFLAGS			=	-Wall -Werror -Wextra

all : $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER) :
	$(CC) $(CFLAGS) $(SERVER_SRC) $(UTILS_SRC) -o $(SERVER)

$(CLIENT) :
	$(CC) $(CFLAGS) $(CLIENT_SRC) $(UTILS_SRC) -o $(CLIENT)

clean :
	$(RM) $(SERVER) $(CLIENT)

fclean :
	$(RM) $(SERVER) $(CLIENT)

re : fclean all

.PHONY: all clean fclean re
