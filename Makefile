NAME = minitalk
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIENT_FILE = mandatory/client.c
SERVER_FILE = mandatory/server.c

CLIENT_BONUS = bonus/client_bonus.c
SERVER_BONUS = bonus/server_bonus.c

CLIENT_EXEC = client
SERVER_EXEC = server
CLIENT_BONUS_EXEC = client_bonus
SERVER_BONUS_EXEC = server_bonus

all : $(NAME)

$(NAME) : $(CLIENT_EXEC) $(SERVER_EXEC)

$(CLIENT_EXEC) : ft_printf/libftprintf.a $(CLIENT_FILE)
	$(CC) $(CFLAGS) $(CLIENT_FILE) -Lft_printf -lftprintf -o $(CLIENT_EXEC)

$(SERVER_EXEC) : ft_printf/libftprintf.a libft/libft.a $(SERVER_FILE)
	$(CC) $(CFLAGS) $(SERVER_FILE) -Lft_printf -lftprintf -Llibft -lft -o $(SERVER_EXEC)

client_bonus : ft_printf/libftprintf.a $(CLIENT_BONUS)
	$(CC) $(CFLAGS) $(CLIENT_BONUS) -Lft_printf -lftprintf -o $(CLIENT_BONUS_EXEC)

server_bonus : ft_printf/libftprintf.a libft/libft.a $(SERVER_BONUS)
	$(CC) $(CFLAGS) $(SERVER_BONUS) -Lft_printf -lftprintf -Llibft -lft -o $(SERVER_BONUS_EXEC)

libft/libft.a :
	$(MAKE) -C libft bonus

ft_printf/libftprintf.a :
	$(MAKE) -C ft_printf

bonus : client_bonus server_bonus

clean :
	rm -f $(CLIENT_EXEC) $(SERVER_EXEC) $(CLIENT_BONUS_EXEC) $(SERVER_BONUS_EXEC)
	$(MAKE) -C libft clean
	$(MAKE) -C ft_printf clean

fclean : clean
	$(MAKE) -C libft fclean
	$(MAKE) -C ft_printf fclean

re : fclean all

.PHONY: all clean fclean re bonus