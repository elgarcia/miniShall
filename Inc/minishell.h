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

// ENVP LIST
void					fill_init_env_list(t_paths *paths, char **envp);
t_env_lst				*find_env_node(t_env_lst *env_lst, char *key);
t_env_lst				*add_env_node(t_env_lst *head, \
						char *name, char *value, int equal);
void					ft_lstdelone_env(t_env_lst *lst);
void					ft_lstclear_env(t_env_lst **lst);
void					delete_env_value(t_env_lst *lst, char *key);
void					print_env_list(t_env_lst *head);

// BUILTINS
void					ft_env(t_paths *paths);
void					ft_cd(t_paths *paths, char *dir);
int						ft_pwd(void);
int						ft_echo(char **argv, int argc);
void					ft_export(t_paths *paths, char **argv, int i);
void					ft_exit(t_shell *shell);
#endif
