#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "structures.h"

/* parser.c */
int		input_parser(char *line, t_shell *new); //split del input
// int		check_process(t_shell *new); //comprueba que los procesos sean validos
void	check_redaux(char *in, t_process *aux, int *i); //red checks
void	check_red(char *in, char *in2, t_process *aux, int *i); //red checks

/* utils.c*/
void	ft_free(char **arg, int size);
int		ft_word_count(const char *s1, char delimiter);
void	*free_null(char **s);
char	*ft_strjoinup(char **s1, char *s2);
void	*free_null(char **s);

/* executor.c */
void	exec_process(t_shell *all, char **envp);

/* pr_checker.c */
int		check_builtins(t_process *prcs);
int		check_command(t_process *prcs, char ***exec_args, char **envp);

/* command_aux.c */
int		search_path(char **env_1, char	**actual_path, \
	char *command, char ***exec_args);
int		init_execargs(char ***ex_argc, char *command);

/* commands.c */
int		check_cmd(char *command, char ***exec_args);
int		prepare_command(char *process, char ***exec_args, char **envp);
int		assign_path(char ***exec_args, char *command, char **envp);
void	double_free(char **aux, char **actual_path);

#endif