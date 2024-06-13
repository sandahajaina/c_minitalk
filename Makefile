NAME = minitalk
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIENT_FILE = mandatory/client.c
SERVER_FILE = mandatory/server.c

CLIENT_BONUS = bonus/client_bonus.c
SERVER_BONUS = bonus/server_bonus.c

all : $(NAME)

$(NAME) : client server

client : ft_printf $(CLIENT_FILE)
		$(CC) $(CFLAGS) $(CLIENT_FILE) ft_printf/libftprintf.a -g -o client

server : $(SERVER_FILE) ft_printf libft
		$(CC) $(CFLAGS) $(SERVER_FILE) ft_printf/libftprintf.a libft/libft.a -g -o server

client_bonus : ft_printf $(CLIENT_BONUS)
		$(CC) $(CFLAGS) $(CLIENT_BONUS) ft_printf/libftprintf.a -g -o client_bonus

server_bonus : ft_printf libft $(SERVER_BONUS)
		$(CC) $(CFLAGS) $(SERVER_BONUS) ft_printf/libftprintf.a libft/libft.a -g -o server_bonus

libft :
		$(MAKE) bonus -C libft

ft_printf :
		$(MAKE) -C ft_printf

bonus : client_bonus server_bonus

clean :	
		rm -f client server client_bonus server_bonus
		$(MAKE) -C libft clean
		$(MAKE) -C ft_printf clean

fclean : clean
		$(MAKE) -C libft fclean
		$(MAKE) -C ft_printf fclean

re : fclean all

.PHONY: all clean fclean re bonus ft_printf libft