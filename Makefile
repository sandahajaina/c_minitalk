CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = minitalk

$(NAME) : 
		@cd libft && make bonus
		@cd ft_printf && make
		$(CC) $(CFLAGS) mandatory/server.c libft/libft.a ft_printf/libftft_printf.a -o server
		$(CC) $(CFLAGS) mandatory/client.c ft_printf/libftft_printf.a -o client

all : $(NAME)

clean :
		@cd libft && make clean
		@cd ft_printf && make clean
		rm -f server.o client.o

fclean : clean
		@cd libft && make fclean
		@cd ft_printf && make fclean
		rm -f client server

re : fclean all

.PHONY: all clean fclean re