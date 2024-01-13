#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "structures.h"

/* Parser.c */
int	input_parser(char *line, t_shell *new);

#endif