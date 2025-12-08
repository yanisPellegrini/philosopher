NAME           	= philo

SRCS            =  src/philo.c
OBJ            = $(SRCS:.c=.o)

CFLAGS          =  -Werror -Wall -Wextra -I .

LIBFT       = libft/libft.a
LIBFT_INC   = libft

all:            $(NAME)

$(NAME): 		$(LIBFT) $(OBJ)
				 gcc -o $(NAME) $(OBJ) $(LIBFT) -lreadline

$(LIBFT):
	 $(MAKE) -C libft

%.o: %.c minishell.h
		gcc $(CFLAGS) -c $< -o $@

clean:
				rm -f $(OBJ)
				$(MAKE) -C libft clean

fclean:         clean
				rm -f $(NAME)
				$(MAKE) -C libft fclean

re:             fclean all
