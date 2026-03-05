NAME				=	minitalk
SERVER				=	server
SERVER_SRC			=	server.c
CLIENT				=	client
CLIENT_SRC			=	client.c
UTILS_SRC			=	utils.c
SERVER_BONUS		=	server_bonus
SERVER_BONUS_SRC	=	server_bonus.c
CLIENT_BONUS		=	client_bonus
CLIENT_BONUS_SRC	=	client_bonus.c
CC					=	cc
RM 					=	rm -rf
CFLAGS				=	-Wall -Werror -Wextra

all : $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER) :
	$(CC) $(CFLAGS) $(SERVER_SRC) $(UTILS_SRC) -o $(SERVER)

$(CLIENT) :
	$(CC) $(CFLAGS) $(CLIENT_SRC) $(UTILS_SRC) -o $(CLIENT)

bonus : $(CLIENT_BONUS) $(SERVER_BONUS)

$(SERVER_BONUS) :
	$(CC) $(CFLAGS) $(SERVER_BONUS_SRC) $(UTILS_SRC) -o $(SERVER_BONUS)

$(CLIENT_BONUS) :
	$(CC) $(CFLAGS) $(CLIENT_BONUS_SRC) $(UTILS_SRC) -o $(CLIENT_BONUS)

clean :
	$(RM) $(SERVER) $(CLIENT)

fclean :
	$(RM) $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

re : fclean all

.PHONY: all bonus clean fclean re
