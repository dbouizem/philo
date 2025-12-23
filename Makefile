NAME = philo
BONUS_NAME = philo_bonus

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

BONUS_SRCS =	src_bonus/main_bonus.c \
				src_bonus/parsing_bonus.c \
				src_bonus/init_bonus.c \
				src_bonus/time_bonus.c \
				src_bonus/utils_bonus.c \
				src_bonus/monitor_bonus.c \
				src_bonus/actions_bonus.c \
				src_bonus/routine_bonus.c \
				src_bonus/print_bonus.c \
				src_bonus/cleanup_bonus.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) successfully created!$(RESET)"

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
	@echo "$(GREEN)🎁 $(BONUS_NAME) successfully created!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✓$(RESET) Compiling $<"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(YELLOW)🗑️  obj/ directory removed$(RESET)"

clean_bonus: clean
	@echo "$(YELLOW)🗑️  Bonus cleanup done$(RESET)"

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "$(YELLOW)🗑️  $(NAME) removed$(RESET)"
	@echo "$(YELLOW)🗑️  $(BONUS_NAME) removed$(RESET)"

fclean_bonus: fclean
	@echo "$(YELLOW)🗑️  Full bonus cleanup done$(RESET)"

re: fclean all

.PHONY: all bonus clean clean_bonus fclean fclean_bonus re
