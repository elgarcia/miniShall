# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elias <elias@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 16:51:29 by bautrodr          #+#    #+#              #
#    Updated: 2024/05/09 12:15:59 by tuta             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RESET = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[93m
CYAN = \033[96m

BUILTINS = builtins/cd/cd.c builtins/cd/cd_utils.c builtins/cd/cd_utils2.c \
		   builtins/echo/echo.c builtins/echo/echo_utils.c \
		   builtins/env/env.c builtins/env/env_utils.c \
		   builtins/exit/exit.c builtins/exit/exit_utils.c\
		   builtins/export/export.c builtins/export/export_utils.c builtins/export/export_utils2.c \
		   builtins/pwd/pwd.c \
		   builtins/unset/unset.c \
		   builtins/utils/utils.c builtins/utils/sort_env.c 

SOURCE = Src/main.c Src/init.c \
		 Src/Lexer/parser.c Src/Lexer/expansor.c Src/Lexer/expansor_utils.c Src/Lexer/parser_aux.c Src/Lexer/parser_aux_2.c \
		 Src/Lexer/split_words.c Src/Lexer/word_quotes.c \
		 Src/Executor/executor.c Src/Executor/pr_checker.c Src/Executor/commands.c Src/Executor/executor_aux2.c \
		 Src/Executor/command_aux.c Src/Executor/pipes.c Src/Executor/executor_aux.c Src/Executor/pr_checker_aux.c \
		 Src/Utils/utils.c get_next_line/get_next_line.c \
		 get_next_line/get_next_line_utils.c Src/Utils/auxiliar_functions.c \
		 Src/Utils/quotes.c Src/Utils/utils2.c Src/Utils/envp.c Src/Utils/auxiliar_functions2.c \
		 Src/Utils/exit_error.c \
		 Src/History/history.c Src/History/history_utils.c \
		 Src/Signals/signals.c

INCLUDE = Inc/

HEADER = $(INCLUDE)structures.h $(INCLUDE)minishell.h

LIBFT_LIB =  libft/libft.a
SILENCE = --no-print-directory
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
READLINE = -lreadline

OBJS = $(SOURCE:.c=.o) $(BUILTINS:.c=.o)

%.o: %.c Makefile $(HEADER)
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} -c ${CFLAGS} -I ./$(INCLUDE) $< -o $@
	
all:  sub_make $(NAME)

$(NAME): ${OBJS} $(HEADER) Makefile
	@echo ""
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
	@rm -f $(NAME)
	@rm -f ".history"
	@echo "$(RED)$(BOLD)Trash removed!$(RESET)"

re:     fclean all

.PHONY: all clean fclean sub_make re
