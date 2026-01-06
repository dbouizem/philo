NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

OBJ_DIR = obj

SRCS =	src/main.c \
		src/parsing.c \
		src/print.c \
		src/utils.c \
		src/time.c \
		src/init.c \
		src/forks.c \
		src/cleanup.c \
		src/actions.c \
		src/routine.c \
		src/monitor.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully created!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✓$(RESET) Compiling $<"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(YELLOW)obj/ directory removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)$(NAME) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
