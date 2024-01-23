# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 12:05:58 by bautrodr          #+#    #+#              #
#    Updated: 2024/01/23 22:49:49 by bautrodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_fprintf.a

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[1;33m
NC = \033[0m  

CHECKMARK = ✔️
CROSSMARK = ❌

SRCS = ./srcs/check_format.c \
	   ./srcs/ft_putchar.c \
	   ./srcs/ft_putnbr.c \
	   ./srcs/print_str.c \
	   ./srcs/to_hex.c \
	   ./srcs/unsigned_int.c \
	   ./srcs/ft_printf.c \
	   ./srcs/print_address.c

FLAGS = -Wall -Wextra -Werror -MMD 
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
CC = gcc

all: $(NAME)
	@echo "$(GREEN)$(CHECKMARK) El programa se ha compilado con éxito.$(NC)"

%.o:%.c Makefile includes/ft_printf.h
	$(CC) $(FLAGS) -I ./ -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	@echo "$(YELLOW)Limpiando los archivos object y dependencias...$(NC)"
	@rm -f $(OBJS) $(DEPS)
	@echo "$(GREEN)$(CHECKMARK) Limpieza completa.$(NC)"

fclean: clean
	@echo "$(YELLOW)Eliminando el ejecutable...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(CHECKMARK) Ejecutable eliminado.$(NC)"

re: fclean all
	@echo "$(YELLOW)Recompilando...$(NC)"
	@echo "$(GREEN)$(CHECKMARK) Recompilación completa.$(NC)"

-include $(DEPS)

.PHONY: all clean fclean re
