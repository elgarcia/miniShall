# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 10:11:46 by bautrodr          #+#    #+#              #
#    Updated: 2024/02/08 14:58:23 by bautrodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[93m
CYAN = \033[96m

NAME = libft.a

SRCS = ft_calloc.c \
	   ft_isdigit.c \
	   ft_memcpy.c \
	   ft_strdup.c \
	   ft_strlen.c \
	   ft_strtrim.c \
	   ft_isalnum.c \
	   ft_isprint.c \
	   ft_memmove.c \
	   ft_strjoin.c \
	   ft_strncmp.c \
	   ft_substr.c \
	   ft_atoi.c \
	   ft_isalpha.c \
	   ft_memchr.c \
	   ft_memset.c \
	   ft_strlcat.c \
	   ft_strnstr.c \
	   ft_tolower.c \
	   ft_bzero.c \
	   ft_isascii.c \
	   ft_memcmp.c \
	   ft_strchr.c \
	   ft_strlcpy.c \
	   ft_strrchr.c \
	   ft_toupper.c \
	   ft_split.c \
	   ft_itoa.c \
	   ft_strmapi.c \
	   ft_striteri.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_fprintf/ft_putchar.c \
	   ft_fprintf/check_format.c \
	   ft_fprintf/print_address.c \
	   ft_fprintf/to_hex.c \
	   ft_fprintf/ft_fprintf.c \
	   ft_fprintf/ft_putnbr.c \
	   ft_fprintf/print_str.c \
	   ft_fprintf/unsigned_int.c

SRCS_BONUS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c


FLAGS = -Wall -Wextra -Werror -MMD 
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)
BONUS = .bonus
CC = gcc

all: $(NAME)

%.o:%.c Makefile
	@printf "\033[0;33mGenerating libft objects... %-33.33s\r" $@
	@$(CC) $(FLAGS) -I ./ -c $< -o $@

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo ""
	@echo "$(YELLOW)Libft.a $(RESET)$(CYAN)$(BOLD)created$(RESET)"

bonus: $(BONUS)
	
$(BONUS): $(OBJS) $(OBJS_BONUS)
	@ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)
	touch $@

clean:
	@rm -f $(OBJS) $(OBJS_BONUS) $(DEPS) $(DEPS_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

-include $(DEPS)
-include $(DEPS_BONUS)

.PHONY: all clean fclean re bonus 
