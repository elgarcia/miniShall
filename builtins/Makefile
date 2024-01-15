# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 10:43:27 by bautrodr          #+#    #+#              #
#    Updated: 2024/01/15 10:55:02 by bautrodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = built_ins

SRCS = cd.c \
	   echo.c \
	   env.c \
	   env_utils.c \
	   pwd.c \
	   main.c
INCLUDE_LIBFT = ../libft/libft.a
LIBFT_DIR = ../libft
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

.c.o:
	$(CC) -c $< -o $@

$(NAME): $(OBJS) Makefile ../Inc/built_ins.h $(LIBFT_DIR)/libft.h
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
