NAME = minitalk
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIENT = mandatory/client.c
SERVER = mandatory/server.c

CLIENT_BONUS = bonus/client_bonus.c
SERVER_BONUS = bonus/server_bonus.c

$(NAME) : client server

all : $(NAME)

client : ft_printf $(CLIENT)
		$(CC) $(CFLAGS) $(CLIENT) ft_printf/libftprintf.a -g -o client

server : $(SERVER) ft_printf libft
		$(CC) $(CFLAGS) $(SERVER) ft_printf/libftprintf.a libft/libft.a -g -o server

client_bonus : ft_printf $(CLIENT_BONUS)
		$(CC) $(CFLAGS) $(CLIENT_BONUS) ft_printf/libftprintf.a -g -o client

server_bonus : ft_printf libft $(SERVER_BONUS)
		$(CC) $(CFLAGS) $(SERVER_BONUS) ft_printf/libftprintf.a libft/libft.a -g -o server

libft :
		$(MAKE) bonus -C libft

ft_printf :
		$(MAKE) -C ft_printf

bonus : clean_bonus client_bonus server_bonus

clean :	
		rm -f client server
		$(MAKE) -C libft clean
		$(MAKE) -C ft_printf clean

clean_bonus :
		rm -f client server

fclean : clean
		$(MAKE) -C libft fclean
		$(MAKE) -C ft_printf fclean

re : fclean all

.PHONY: all clean fclean re bonus ft_printf libft 