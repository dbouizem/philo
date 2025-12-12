NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

OBJ_DIR	= obj

SRCS =	main.c \
		parsing.c \
		tools.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) créé avec succès !$(RESET)"

$(OBJ_DIR)/%.o: %.c philo.h
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✓$(RESET) Compilation de $<"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(YELLOW)🗑️  Dossier obj/ supprimé$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)🗑️  $(NAME) supprimé$(RESET)"

re: fclean all

.PHONY: all clean fclean re
