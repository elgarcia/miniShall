#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "structures.h"

/* parser.c */
int		input_parser(char *line, t_shell *new); //split del input
int		check_process(t_shell *new); //comprueba que los procesos sean validos
void	check_redaux(char *in, t_process *aux, int *i); //red checks
void	check_red(char *in, char *in2, t_process *aux, int *i); //red checks

/* utils.c*/
void	ft_free(char **arg, int size);
int		ft_word_count(const char *s1, char delimiter);
void	*free_null(char **s);
char	*ft_strjoinup(char **s1, char *s2);
void	*free_null(char **s);

#endif