NAME = minishell

RESET = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[93m
CYAN = \033[96m

SOURCE = Src/main.c Src/parser.c Src/utils.c Src/executor.c Src/pr_checker.c Src/commands.c \
Src/command_aux.c Src/pipes.c Src/init.c Src/signals.c builtins/env_utils.c builtins/echo.c builtins/cd.c builtins/env.c \
builtins/exit.c builtins/export.c builtins/pwd.c builtins/utils.c builtins/cd_utils.c builtins/cd_utils2.c builtins/unset.c \
builtins/export_utils.c builtins/sort_env.c builtins/echo_split.c builtins/echo_utils.c Src/history.c \
get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

INCLUDE = Inc/minishell.h

LIBFT_LIB =  libft/libft.a
SILENCE = --no-print-directory
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
READLINE = -lreadline

OBJS = $(SOURCE:.c=.o)

%.o: %.c Makefile $(INCLUDE)
	@echo "$(YELLOW)$(BOLD)Compiling $(RESET)$(CYAN)$<$(RESET)"
	@${CC} -c ${CFLAGS} -I /$(INCLUDE) $< -o $@

all:  sub_make $(NAME)

$(NAME): ${OBJS} $(INCLUDE) Inc/structures.h Makefile
	@echo "$(YELLOW)Creating executable...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) $(READLINE)
	@echo "$(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)$(BOLD)created!$(RESET)"

sub_make:
	@make -C libft $(SILENCE)

clean:
	@echo "$(YELLOW)$(BOLD)Cleaning object files...$(RESET)"
	@make clean -C libft $(SILENCE)
	@rm -f $(OBJS)
	@echo "$(RED)$(BOLD)Object files removed!$(RESET)"

fclean: clean
	@echo "$(YELLOW)$(BOLD)Cleaning trash...$(RESET)"
	@make fclean -C libft $(SILENCE)
	@rm $(NAME)
	@echo "$(RED)$(BOLD)Trash removed!$(RESET)"

re:     fclean all

.PHONY: all clean fclean sub_make
