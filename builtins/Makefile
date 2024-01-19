# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 10:43:27 by bautrodr          #+#    #+#              #
#    Updated: 2024/01/19 15:15:52 by bautrodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = built_ins.a

SRCS = cd.c \
	   echo.c \
	   env.c \
	   env_utils.c \
	   pwd.c \
	   export.c \
	   exit.c \
	   utils.c \
	   unset.c
INCLUDE_LIBFT = ../libft/libft.a
LIBFT_DIR = ../libft
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -o a.out

all: $(NAME)

%.o:%.c Makefile
	$(CC) $(FLAGS) -I ./ -c $< -o $@

$(NAME): $(OBJS) Makefile ../Inc/minishell.h ../Inc/structures.h $(LIBFT_DIR)/libft.h
	make -C $(LIBFT_DIR)
	ar rcs $(NAME) $(OBJS)
clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
