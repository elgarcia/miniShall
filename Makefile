NAME = minishell

SOURCE = Src/main.c Src/parser.c Src/utils.c Src/executor.c Src/pr_checker.c Src/commands.c \
Src/command_aux.c Src/pipes.c Src/init.c Src/signals.c builtins/env_utils.c builtins/echo.c builtins/cd.c builtins/env.c \
builtins/exit.c builtins/export.c builtins/pwd.c builtins/utils.c builtins/cd_utils.c builtins/unset.c \
builtins/export_utils.c builtins/sort_env.c builtins/echo_split.c
INCLUDE = Inc/minishell.h

LIBFT_LIB =  libft/libft.a
SILENCE = --no-print-directory
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
READLINE = -lreadline

OBJS = $(SOURCE:.c=.o)

%.o: %.c Makefile $(INCLUDE)
	@echo "Compiling $<..."
	@${CC} -c ${CFLAGS} -I $(INCLUDE) $< -o $@

all:  sub_make $(NAME)

$(NAME): ${OBJS} $(INCLUDE) Makefile
	@echo "Creating executable..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) $(READLINE)
	@echo "$(NAME) created!"

sub_make:
	@make -C libft $(SILENCE)

clean:
	@echo "Cleaning object files..."
	@make clean -C libft $(SILENCE)
	@rm -f $(OBJS)
	@echo "Object files removed!"

fclean: clean
	@echo "Cleaning trash..."
	@make fclean -C libft $(SILENCE)
	@rm $(NAME)
	@echo "Trash removed!"

re:     fclean all

.PHONY: all clean fclean sub_make
