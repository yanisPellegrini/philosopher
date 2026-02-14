NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
INCLUDES	= -I./includes

SRCS_DIR	= src
SRCS		= $(SRCS_DIR)/philo.c \
			  $(SRCS_DIR)/init.c \
			  $(SRCS_DIR)/uti.c \
			  $(SRCS_DIR)/actions.c \
			  $(SRCS_DIR)/routine.c \
			  $(SRCS_DIR)/monitor.c \
			  $(SRCS_DIR)/cleanup.c

OBJS		= $(SRCS:.c=.o)

# Colors
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiling: $<$(RESET)"

clean:
	@rm -f $(OBJS)
	@echo "$(RED)✗ Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)✗ $(NAME) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re