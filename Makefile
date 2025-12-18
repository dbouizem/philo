NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

OBJ_DIR = obj

SRCS =	main.c \
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

BONUS_SRCS =	src_bonus/main_bonus.c \
				src_bonus/parsing_bonus.c \
				src_bonus/init_bonus.c \
				src_bonus/time_bonus.c \
				src_bonus/utils_bonus.c \
				src_bonus/monitor_bonus.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))


GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) créé avec succès !$(RESET)"

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
	@echo "$(GREEN)🎁 $(BONUS_NAME) créé avec succès !$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✓$(RESET) Compilation de $<"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(YELLOW)🗑️  Dossier obj/ supprimé$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)🗑️  $(NAME) supprimé$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
